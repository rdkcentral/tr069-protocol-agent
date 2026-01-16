/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/


/**********************************************************************

    module:	ccsp_cwmp_ifo_mpa.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This wrapper file defines the base class data structure and
        interface for the CCSP CWMP Management Parameter Access Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang
        Kang Quan

    ---------------------------------------------------------------

    revision:

        09/06/05    initial revision.
        06/15/11    supporting CCSP architecture
        10/12/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_IFO_MPA_
#define  _CCSP_CWMP_IFO_MPA_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_ifo_interface.h"

#if 0
#define  CCSP_CWMP_MPA_ENTITY_ACS                        "ACS"
#define  CCSP_CWMP_MPA_ENTITY_Subscriber                 "Subscriber"
#define  CCSP_CWMP_MPA_ENTITY_System                     "System"        /* software itself */
#endif

/***********************************************************
    CCSP CWMP MANAGEMENT PARAMETER ACCESS INTERFACE DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the os wrapper object definition.
 */
#define  CCSP_CWMP_MPA_INTERFACE_NAME                    "cwmpManagementParameterAccessIf"
#define  CCSP_CWMP_MPA_INTERFACE_ID                      0

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support), we
 * have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */
/**
 * @brief Lock write access to the parameter database.
 *
 * This function pointer typedef defines the callback interface for acquiring a write lock on the
 * parameter database before performing SetParameterValues operations. This ensures thread-safe
 * access when multiple RPC operations may occur concurrently. The lock must be released by calling
 * the corresponding UnlockWriteAccess function after completing the write operation.
 *
 * @param[in] hThisObject  - Handle to the MPA interface object instance.
 *
 * @return The lock acquisition status.
 * @retval TRUE  - Write lock successfully acquired.
 * @retval FALSE - Failed to acquire write lock.
 *
 */
typedef  BOOL
(*PFN_CWMPMPAIF_LOCK_ACCESS)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Unlock write access to the parameter database.
 *
 * This function pointer typedef defines the callback interface for releasing a write lock on the
 * parameter database after completing SetParameterValues operations. This function must be called
 * after acquiring the lock via LockWriteAccess to ensure proper lock management and allow other
 * pending write operations to proceed.
 *
 * @param[in] hThisObject  - Handle to the MPA interface object instance.
 *
 * @return The status of the unlock operation.
 * @retval ANSC_STATUS_SUCCESS - Write lock successfully released.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMPAIF_UNLOCK_ACCESS)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set parameter values in the TR-069 data model.
 *
 * This function pointer typedef defines the callback interface for the TR-069 SetParameterValues RPC
 * method implementation. It sets the values of one or more parameters in the CPE's data model. The function
 * validates parameter names, data types, and access permissions before applying changes. If any parameter
 * fails validation, the entire operation may be rolled back depending on the implementation.
 *
 * @param[in]  hThisObject       - Handle to the MPA interface object instance.
 * @param[in]  pParamValueArray  - Pointer to array of CCSP_CWMP_SET_PARAM_VALUE structures containing
 *                                  parameter names and values to set. Each entry specifies the parameter
 *                                  path, value, and data type.
 * @param[in]  ulArraySize       - Number of elements in pParamValueArray. Valid range: 1 to MAX_ULONG.
 * @param[out] piStatus          - Pointer to integer receiving operation status code.
 *                                  \n 0 = Success, non-zero indicates specific error conditions.
 * @param[out] phSoapFault       - Pointer to handle receiving CCSP_CWMP_SOAP_FAULT structure on failure.
 *                                  \n Set to NULL on success. Caller must free the fault structure.
 * @param[in]  bExcludeInvNs     - Boolean flag to exclude invalid namespaces from processing.
 *                                  \n TRUE = Skip invalid namespace parameters, FALSE = Fail on invalid namespace.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - All parameter values set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMPAIF_SET_VALUES)
    (
        ANSC_HANDLE                 hThisObject,
        void*                       pParamValueArray,
        ULONG                       ulArraySize,
        int*                        piStatus,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );

/**
 * @brief Set parameter values with a write transaction ID.
 *
 * This function pointer typedef defines the callback interface for setting parameter values with an
 * associated write transaction identifier. This extended version of SetParameterValues supports tracking
 * multiple concurrent write operations and coordinating commits across subsystems. The write ID allows
 * subsystems to batch parameter changes and apply them atomically when the transaction completes.
 *
 * @param[in]  hThisObject       - Handle to the MPA interface object instance.
 * @param[in]  pParamValueArray  - Pointer to array of CCSP_CWMP_SET_PARAM_VALUE structures containing
 *                                  parameter names and values to set.
 * @param[in]  ulArraySize       - Number of elements in pParamValueArray. Valid range: 1 to MAX_ULONG.
 * @param[in]  ulWriteID         - Transaction identifier for this write operation. Valid range: 0 to MAX_ULONG.
 *                                  \n Used for coordinating commits across multiple subsystems.
 * @param[out] piStatus          - Pointer to integer receiving operation status code.
 *                                  \n 0 = Success, non-zero indicates specific error conditions.
 * @param[out] phSoapFault       - Pointer to handle receiving CCSP_CWMP_SOAP_FAULT structure on failure.
 *                                  \n Set to NULL on success.
 * @param[in]  bExcludeInvNs     - Boolean flag to exclude invalid namespaces from processing.
 *                                  \n TRUE = Skip invalid namespace parameters, FALSE = Fail on invalid namespace.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - All parameter values set successfully with write ID.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMPAIF_SET_VALUES2)
    (
        ANSC_HANDLE                 hThisObject,
        void*                       pParamValueArray,
        ULONG                       ulArraySize,
        ULONG                       ulWriteID,
        int*                        piStatus,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );

/**
 * @brief Get parameter values from the TR-069 data model.
 *
 * This function pointer typedef defines the callback interface for the TR-069 GetParameterValues RPC
 * method implementation. It retrieves the current values of one or more parameters from the CPE's data
 * model. The function queries all specified parameters and returns their values along with data type
 * information. Partial path queries return all matching leaf parameters.
 *
 * @param[in]  hThisObject        - Handle to the MPA interface object instance.
 * @param[in]  pParamNameArray    - Pointer to SLAP_STRING_ARRAY structure containing parameter names to query.
 *                                   \n Each entry is a full or partial parameter path.
 * @param[in]  uMaxEntry          - Maximum number of parameter values to retrieve. Valid range: 1 to MAX_ULONG.
 *                                   \n Used to limit response size for large queries.
 * @param[out] ppParamValueArray  - Pointer to receive allocated array of CCSP_CWMP_PARAM_VALUE structures.
 *                                   \n Each entry contains parameter name, value, and data type.
 *                                   \n Caller must free the returned array.
 * @param[out] pulArraySize       - Pointer to receive number of elements in ppParamValueArray.
 * @param[out] phSoapFault        - Pointer to handle receiving CCSP_CWMP_SOAP_FAULT structure on failure.
 *                                   \n Set to NULL on success.
 * @param[in]  bExcludeInvNs      - Boolean flag to exclude invalid namespaces from processing.
 *                                   \n TRUE = Skip invalid namespace parameters, FALSE = Fail on invalid namespace.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Parameter values retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMPAIF_GET_VALUES)
    (
        ANSC_HANDLE                 hThisObject,
        SLAP_STRING_ARRAY*          pParamNameArray,
		ULONG						uMaxEntry,
        void**                      ppParamValueArray,
        PULONG                      pulArraySize,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );

/**
 * @brief Get parameter names from the TR-069 data model.
 *
 * This function pointer typedef defines the callback interface for the TR-069 GetParameterNames RPC
 * method implementation. It retrieves parameter or object names at or below a specified path in the
 * CPE's data model hierarchy. The bNextLevel flag controls whether to return only immediate children
 * (next level) or all descendant parameters recursively (full subtree).
 *
 * @param[in]  hThisObject        - Handle to the MPA interface object instance.
 * @param[in]  pParamPath         - Parameter path prefix to query. Empty string "" returns entire data model.
 *                                   \n Must be a valid object or parameter path.
 * @param[in]  bNextLevel         - Boolean flag controlling query depth.
 *                                   \n TRUE = Return only immediate children (next level).
 *                                   \n FALSE = Return all descendant parameters recursively.
 * @param[out] ppParamInfoArray   - Pointer to receive allocated array of CCSP_CWMP_PARAM_INFO structures.
 *                                   \n Each entry contains parameter name and writable flag.
 *                                   \n Caller must free the returned array.
 * @param[out] pulArraySize       - Pointer to receive number of elements in ppParamInfoArray.
 * @param[out] phSoapFault        - Pointer to handle receiving CCSP_CWMP_SOAP_FAULT structure on failure.
 *                                   \n Set to NULL on success.
 * @param[in]  bExcludeInvNs      - Boolean flag to exclude invalid namespaces from processing.
 *                                   \n TRUE = Skip invalid namespace parameters, FALSE = Fail on invalid namespace.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Parameter names retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMPAIF_GET_NAMES)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamPath,
        BOOL                        bNextLevel,
        void**                      ppParamInfoArray,
        PULONG                      pulArraySize,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );

/**
 * @brief Set parameter attributes in the TR-069 data model.
 *
 * This function pointer typedef defines the callback interface for the TR-069 SetParameterAttributes
 * RPC method implementation. It modifies notification and access control attributes for one or more
 * parameters. Attributes control when value changes trigger inform events (notification levels) and
 * which entities can modify parameters (access control lists).
 *
 * @param[in]  hThisObject          - Handle to the MPA interface object instance.
 * @param[in]  pSetParamAttribArray - Pointer to array of CCSP_CWMP_SET_PARAM_ATTRIB structures containing
 *                                     parameter names and attribute changes. Each entry specifies parameter
 *                                     path, notification level, notification change flag, access list, and
 *                                     access list change flag.
 * @param[in]  ulArraySize          - Number of elements in pSetParamAttribArray. Valid range: 1 to MAX_ULONG.
 * @param[out] phSoapFault          - Pointer to handle receiving CCSP_CWMP_SOAP_FAULT structure on failure.
 *                                     \n Set to NULL on success.
 * @param[in]  bExcludeInvNs        - Boolean flag to exclude invalid namespaces from processing.
 *                                     \n TRUE = Skip invalid namespace parameters, FALSE = Fail on invalid namespace.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Parameter attributes set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMPAIF_SET_ATTRIBS)
    (
        ANSC_HANDLE                 hThisObject,
        void*                       pSetParamAttribArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );

/**
 * @brief Get parameter attributes from the TR-069 data model.
 *
 * This function pointer typedef defines the callback interface for the TR-069 GetParameterAttributes
 * RPC method implementation. It retrieves notification and access control attributes for one or more
 * parameters. The returned attributes include notification levels (passive/active/off), access control
 * lists (which entities can modify the parameter), and attribute change tracking flags.
 *
 * @param[in]  hThisObject         - Handle to the MPA interface object instance.
 * @param[in]  pParamNameArray     - Pointer to SLAP_STRING_ARRAY structure containing parameter names to query.
 *                                    \n Each entry is a full parameter path.
 * @param[in]  uMaxEntry           - Maximum number of parameter attributes to retrieve. Valid range: 1 to MAX_ULONG.
 *                                    \n Used to limit response size for large queries.
 * @param[out] ppParamAttribArray  - Pointer to receive allocated array of CCSP_CWMP_PARAM_ATTRIB structures.
 *                                    \n Each entry contains parameter name, notification level, and access list.
 *                                    \n Caller must free the returned array.
 * @param[out] pulArraySize        - Pointer to receive number of elements in ppParamAttribArray.
 * @param[out] phSoapFault         - Pointer to handle receiving CCSP_CWMP_SOAP_FAULT structure on failure.
 *                                    \n Set to NULL on success.
 * @param[in]  bExcludeInvNs       - Boolean flag to exclude invalid namespaces from processing.
 *                                    \n TRUE = Skip invalid namespace parameters, FALSE = Fail on invalid namespace.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Parameter attributes retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMPAIF_GET_ATTRIBS)
    (
        ANSC_HANDLE                 hThisObject,
        SLAP_STRING_ARRAY*          pParamNameArray,
		ULONG						uMaxEntry,
        void**                      ppParamAttribArray,
        PULONG                      pulArraySize,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );

/**
 * @brief Add a new object instance in the TR-069 data model.
 *
 * This function pointer typedef defines the callback interface for the TR-069 AddObject RPC method
 * implementation. It creates a new instance of a multi-instance object (table entry) in the CPE's
 * data model. The function allocates a unique instance number for the new object and initializes
 * all child parameters to their default values. The object path must specify a writable multi-instance
 * object with instance number creation enabled.
 *
 * @param[in]  hThisObject      - Handle to the MPA interface object instance.
 * @param[in]  pObjName         - Object path for the multi-instance object where a new instance should be created.
 *                                 \n Must end with a trailing dot.
 *                                 \n Must be a writable multi-instance object path.
 * @param[out] pulObjInsNumber  - Pointer to receive the allocated instance number for the newly created object.
 *                                 \n Valid range: 1 to MAX_ULONG.
 * @param[out] piStatus         - Pointer to integer receiving operation status code.
 *                                 \n 0 = Success, non-zero indicates specific error conditions.
 * @param[out] phSoapFault      - Pointer to handle receiving CCSP_CWMP_SOAP_FAULT structure on failure.
 *                                 \n Set to NULL on success.
 * @param[in]  bExcludeInvNs    - Boolean flag to exclude invalid namespaces from processing.
 *                                 \n TRUE = Skip invalid namespace parameters, FALSE = Fail on invalid namespace.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Object instance created successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMPAIF_ADD_OBJ)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pObjName,
        PULONG                      pulObjInsNumber,
        int*                        piStatus,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );

/**
 * @brief Delete an object instance from the TR-069 data model.
 *
 * This function pointer typedef defines the callback interface for the TR-069 DeleteObject RPC method
 * implementation. It removes an existing instance of a multi-instance object (table entry) from the
 * CPE's data model. The function deallocates all associated resources and removes all child parameters
 * of the deleted object. The object path must specify a writable multi-instance object with instance
 * number deletion enabled, and must include the specific instance number to delete.
 *
 * @param[in]  hThisObject   - Handle to the MPA interface object instance.
 * @param[in]  pObjName      - Full object instance path including the instance number to delete.
 *                             \n Must end with a trailing dot.
 *                             \n Must be a writable multi-instance object instance path.
 * @param[out] piStatus      - Pointer to integer receiving operation status code.
 *                             \n 0 = Success, non-zero indicates specific error conditions.
 * @param[out] phSoapFault   - Pointer to handle receiving CCSP_CWMP_SOAP_FAULT structure on failure.
 *                             \n Set to NULL on success.
 * @param[in]  bExcludeInvNs - Boolean flag to exclude invalid namespaces from processing.
 *                             \n TRUE = Skip invalid namespace parameters, FALSE = Fail on invalid namespace.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Object instance deleted successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMPAIF_DEL_OBJ)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pObjName,
        int*                        piStatus,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );


/*
 * In each direction, the order of SOAP envelopes is defined independently from the number of enve-
 * lopes per HTTP post/response pair. Specifically, envelopes are ordered from first to last within
 * a single HTTP post/response and then between successive post/response pairs.
 *
 * On reception of SOAP requests from the ACS, the CPE MUST respond to each request in the order
 * they were received, where order is defined as described above. The definition of order places no
 * constraint on whether multiple responses are sent in a single HTTP post (if the ACS can accept
 * more than one envelope), or distributed over multiple HTTP posts.
 */
#define  CCSP_CWMP_MPA_INTERFACE_CLASS_CONTENT                                              \
    /* duplication of the base object class content */                                      \
    ANSCIFO_CLASS_CONTENT                                                                   \
    /* start of object class content */                                                     \
    PFN_CWMPMPAIF_LOCK_ACCESS       LockWriteAccess;                                        \
    PFN_CWMPMPAIF_UNLOCK_ACCESS     UnlockWriteAccess;                                      \
                                                                                            \
    /* RPC handling APIs */                                                                 \
    PFN_CWMPMPAIF_SET_VALUES        SetParameterValues;                                     \
    PFN_CWMPMPAIF_SET_VALUES2       SetParameterValuesWithWriteID;                          \
    PFN_CWMPMPAIF_GET_VALUES        GetParameterValues;                                     \
    PFN_CWMPMPAIF_GET_NAMES         GetParameterNames;                                      \
    PFN_CWMPMPAIF_SET_ATTRIBS       SetParameterAttributes;                                 \
    PFN_CWMPMPAIF_GET_ATTRIBS       GetParameterAttributes;                                 \
    PFN_CWMPMPAIF_ADD_OBJ           AddObject;                                              \
    PFN_CWMPMPAIF_DEL_OBJ           DeleteObject;                                           \
    /* end of object class content */                                                       \

typedef  struct
_CCSP_CWMP_MPA_INTERFACE
{
    CCSP_CWMP_MPA_INTERFACE_CLASS_CONTENT
}
CCSP_CWMP_MPA_INTERFACE,  *PCCSP_CWMP_MPA_INTERFACE;

#define  ACCESS_CCSP_CWMP_MPA_INTERFACE(p)               \
         ACCESS_CONTAINER(p, CCSP_CWMP_MPA_INTERFACE, Linkage)


#endif
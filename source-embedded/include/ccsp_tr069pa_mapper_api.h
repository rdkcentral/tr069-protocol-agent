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

    module: ccsp_tr069pa_mapper_api.h

        For CCSP TR-069 PA mapper file

    ---------------------------------------------------------------

    description:

        This file defines all data structures and macros for
        handling CCSP TR-069 PA mapper file.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Kang Quan

    ---------------------------------------------------------------

    revision:

        06/07/2011    initial revision.

**********************************************************************/

#ifndef  _CCSP_TR069_MAPPER_API_DEC_
#define  _CCSP_TR069_MAPPER_API_DEC_

#include "ccsp_tr069pa_mapper_def.h"
#include "ccsp_base_api.h"

/**
 * @brief Loads the TR-069 PA mapping file and initializes mapper structures.
 *
 * This function loads the XML-based mapping file for TR-069 Protocol Agent, which contains
 * error code mappings (CCSP to CWMP), RPC namespace mappings, instance number mappings,
 * parameter information trees, and alias mappings. The function
 * parses the XML file, allocates memory for various mapper structures, and builds internal
 * data structures for parameter translation and error code conversion. The returned handle
 * is used by all subsequent mapper API functions.
 *
 * @param[in] MappingFile  Path to the XML mapping file.
 *
 * @return opaque handle to the mapper context for use with other mapper APIs.
 * @retval Non-NULL handle  Successfully loaded mapping file and initialized mapper structures.
 * @retval NULL            Failed to load mapping file or allocate memory for mapper structures.
 *
 */
CCSP_HANDLE
CcspTr069PA_LoadMappingFile
    (
        CCSP_STRING                 MappingFile
    );

/**
 * @brief Unloads the TR-069 PA mapping file and releases all allocated resources.
 *
 * This function unloads the TR-069 PA mapper file and frees all memory allocated during
 * loading, including error code mapping tables, RPC namespace mapping structures, instance
 * number mapping tables, parameter information trees, alias manager resources, and subsystem
 * name arrays. This function should be called during TR-069 PA shutdown or cleanup.
 *
 * @param[in] MapperHandle  Opaque handle returned by CcspTr069PA_LoadMappingFile().
 *
 * @return Status of the unload operation.
 * @retval 0  Successfully unloaded mapper file and freed all resources.
 * @retval failure otherwise.
 */
CCSP_INT
CcspTr069PA_UnloadMappingFile
    (
        CCSP_HANDLE                 MapperHandle
    );

/**
 * @brief Maps CCSP error codes to TR-069 CWMP CPE error codes.
 *
 * This function translates CCSP internal error codes to TR-069 CWMP CPE fault codes
 * as defined in the TR-069 specification. It searches the error mapping table loaded
 * from the mapper file for matching CCSP error code.
 *
 * @param[in] MapperHandle  Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] CcspErrCode   CCSP internal error code to be mapped.
 *
 * @return The mapped TR-069 CWMP CPE fault code.
 * @retval Mapped fault code  Successfully found mapping in error mapping table.
 * @retval Original code      CCSP error code is already in CWMP range (9000-9019).
 * @retval 9002              No mapping found, returns CCSP_CWMP_CPE_CWMP_FaultCode_internalError.
 *
 */
CCSP_INT
CcspTr069PA_MapCcspErrCode
    (
        CCSP_HANDLE                 MapperHandle,
        CCSP_INT                    CcspErrCode
    );


/**
 * @brief Maps CWMP instance numbers to Data Model internal instance numbers.
 *
 * This function translates instance numbers within TR-069 CWMP parameter names to the
 * internal instance numbers used by the CCSP Data Model.
 *
 * Example mappings:
 *   Device.WiFi.Radio.10000. -> Device.WiFi.Radio.1.
 *   Device.WiFi.Radio.10100. -> Device.WiFi.Radio.2.
 *   Device.WiFi.SSID.10001.  -> Device.WiFi.SSID.1.
 *   Device.WiFi.SSID.10101.  -> Device.WiFi.SSID.2.
 *
 * @param[in] pCwmpString  TR-069 CWMP parameter name string with CWMP instance numbers.
 *
 * @return Newly allocated string with Data Model internal instance numbers. Caller must free.
 * @retval Non-NULL string  Successfully mapped instance number, string allocated with AnscAllocateMemory.
 * @retval NULL            No mapping found for the parameter or memory allocation failed.
 *
 */
CCSP_STRING
CcspTr069PA_MapInstNumCwmpToDmInt
    (
        CCSP_STRING                 pCwmpString
    );


/**
 * @brief Maps Data Model internal instance numbers to CWMP instance numbers.
 *
 * This function translates internal CCSP Data Model instance numbers to the TR-069 CWMP
 * instance numbers expected by the ACS.
 *
 * Example mappings:
 *   Device.WiFi.Radio.1.  -> Device.WiFi.Radio.10000.
 *   Device.WiFi.Radio.2.  -> Device.WiFi.Radio.10100.
 *   Device.WiFi.SSID.1.   -> Device.WiFi.SSID.10001.
 *   Device.WiFi.SSID.2.   -> Device.WiFi.SSID.10101.
 *
 * @param[in] pDmIntString  Parameter name string with Data Model internal instance numbers.
 *
 * @return Newly allocated string with CWMP instance numbers.
 * @retval Non-NULL string  Successfully mapped instance number.
 * @retval NULL            No mapping found for the parameter or memory allocation failed.
 *
 */
CCSP_STRING
CcspTr069PA_MapInstNumDmIntToCwmp
    (
        CCSP_STRING                 pDmIntString
    );

/**
 * @brief Retrieves the CCSP namespace mapping for a specific TR-069 RPC method and argument.
 *
 * This function maps TR-069 RPC method names and their arguments to CCSP internal namespace
 * strings as defined in the mapper file's RpcMapper section.
 *
 * @param[in] MapperHandle  Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] RpcType       RPC type identifier, one of CCSP_TR069_RPC_TYPE_Xxx constants
 * @param[in] ArgName       RPC argument name to map. NULL for RPCs
 *                          without arguments.
 *
 * @return The mapped CCSP namespace string.
 * @retval Non-NULL Namespace  Successfully found namespace mapping for the RPC method/argument.
 * @retval NULL                No mapping found for the specified RPC type and argument combination.
 *
 */
CCSP_STRING
CcspTr069PA_GetRpcNamespace
    (
        CCSP_HANDLE                 MapperHandle,
        CCSP_INT                    RpcType,            /* RPC type, one of CCSP_TR069_RPC_TYPE_Xxx */
        CCSP_STRING                 ArgName             /* NULL for RPCs that do not take any arguments such as Reboot */
    );

/**
 * @brief Converts TR-069 CWMP data type to CCSP data type enumeration.
 *
 * This function translates TR-069 CWMP parameter data type codes to CCSP internal data type
 * enumeration values.
 *
 * @param[in] cwmpType  TR-069 CWMP data type code.
 *
 * @return The corresponding CCSP data type enumeration value.
 * @retval enum dataType_e  Mapped CCSP data type
 *
 */
enum dataType_e
CcspTr069PA_Cwmp2CcspType
    (
        int                         cwmpType
    );

/**
 * @brief Converts CCSP data type enumeration to TR-069 CWMP data type.
 *
 * This function translates CCSP internal data type enumeration values to
 * TR-069 CWMP parameter data type codes.
 *
 * @param[in] ccspType  CCSP internal data type enumeration value.
 *
 * @return The corresponding TR-069 CWMP data type code.
 * @retval int  Mapped CWMP data type code for use in TR-069 SOAP messages.
 *
 */
int
CcspTr069PA_Ccsp2CwmpType
    (
        enum dataType_e             ccspType
    );

/**
 * @brief Retrieves the list of subsystems that own a given namespace.
 *
 * This function queries the parameter information tree to determine which CCSP subsystems
 * own Functional Components (FCs) that manage the specified namespace.
 *
 * @param[in] MapperHandle      Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] Namespace         Parameter namespace to query.
 * @param[out] pSubsystems      String array allocated by caller to receive subsystem names.
 * @param[in,out] pNumSubsystems  [in] Maximum number of subsystem strings the array can hold.
 *                                [out] Actual number of subsystems found that own the namespace.
 * @param[in] bCheckInvPiTree   Boolean flag indicating whether to check invisible parameter tree.
 *
 * @return None.
 *
 */
CCSP_VOID
CcspTr069PA_GetNamespaceSubsystems
    (
        CCSP_HANDLE                 MapperHandle,
        CCSP_STRING                 Namespace,          /* namespace to be queried */
        CCSP_STRING*                pSubsystems,        /* string array allocated by caller */
        CCSP_INT*                   pNumSubsystems,     /* [in/out] max number of strings  */
        CCSP_BOOL                   bCheckInvPiTree     /* whether or not check invisible parameter tree */
    );

/**
 * @brief Checks if a given namespace is supported on a specific subsystem.
 *
 * This function verifies whether the specified CCSP subsystem supports the given parameter
 * namespace by searching the parameter information trees. This is useful for validating
 * parameter requests and routing operations to the correct subsystem.
 *
 * @param[in] MapperHandle     Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] Namespace        Parameter namespace to query.
 * @param[in] Subsystem        Subsystem name to check.
 * @param[in] bCheckInvPiTree  Boolean flag indicating whether to check invisible parameter tree.
 *
 * @return Boolean indicating namespace support.
 * @retval CCSP_TRUE   The specified subsystem supports the given namespace.
 * @retval CCSP_FALSE  The subsystem does not support the namespace or namespace not found.
 *
 */
CCSP_BOOL
CcspTr069PA_IsNamespaceSupported
    (
        CCSP_HANDLE                 MapperHandle,
        CCSP_STRING                 Namespace,          /* namespace to be queried */
        CCSP_STRING                 Subsystem,          /* sub-system name */
        CCSP_BOOL                   bCheckInvPiTree     /* whether or not check invisible parameter tree */
    );

/**
 * @brief Checks if a given namespace is marked as invisible to the TR-069 ACS.
 *
 * This function determines whether the specified parameter namespace is configured as
 * invisible in the mapper file, meaning it should be hidden from the TR-069 Auto-Configuration
 * Server.
 *
 * @param[in] MapperHandle  Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] Namespace     Parameter namespace to query.
 *
 * @return Boolean indicating namespace visibility to ACS.
 * @retval CCSP_TRUE   The namespace is marked as invisible and should be hidden from ACS.
 * @retval CCSP_FALSE  The namespace is visible to ACS or not found in invisible tree.
 *
 */
CCSP_BOOL
CcspTr069PA_IsNamespaceInvisible
    (
        CCSP_HANDLE                 MapperHandle,
        CCSP_STRING                 Namespace           /* namespace to be queried */
    );

/**
 * @brief Checks if a given namespace is marked as visible to the TR-069 ACS.
 *
 * This function determines whether the specified parameter namespace is configured as visible
 * in the mapper file, meaning it can be accessed by the TR-069 Auto-Configuration Server.
 *
 * @param[in] MapperHandle  Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] Namespace     Parameter namespace to query.
 *
 * @return Boolean indicating namespace visibility to ACS.
 * @retval CCSP_TRUE   The namespace is visible and accessible to ACS.
 * @retval CCSP_FALSE  The namespace is marked as invisible or not found in visible tree.
 *
 */
CCSP_BOOL
CcspTr069PA_IsNamespaceVisible
    (
        CCSP_HANDLE                 MapperHandle,
        CCSP_STRING                 Namespace           /* namespace to be queried */
    );

/**
 * @brief Retrieves the total number of subsystems managed by TR-069 PA.
 *
 * This function returns the count of unique CCSP subsystems found in the loaded parameter
 * information tree. Each subsystem represents a CCSP component that owns and manages a
 * specific set of parameters.
 *
 * @param[in] MapperHandle  Opaque handle returned by CcspTr069PA_LoadMappingFile().
 *
 * @return Integer count of subsystems.
 * @retval >=0  The number of unique subsystems found in the parameter tree.
 *
 */
CCSP_INT
CcspTr069PA_GetSubsystemCount
    (
        CCSP_HANDLE                 MapperHandle
    );

/**
 * @brief Retrieves the subsystem name at the specified index.
 *
 * This function returns the name of the CCSP subsystem at the given index in the parameter
 * information tree managed by TR-069 PA. This function is typically used to iterate through
 * all subsystems in the system.
 *
 * @param[in] MapperHandle  Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] index         Zero-based index of the subsystem to retrieve.
 *
 * @return Subsystem name string.
 * @retval Non-NULL  Pointer to the subsystem name string.
 * @retval NULL      Index out of range or mapper handle invalid.
 *
 */
CCSP_STRING
CcspTr069PA_GetSubsystemByIndex
    (
        CCSP_HANDLE                 MapperHandle,
        CCSP_INT                    index
    );


/**
 * @brief Callback function prototype for parameter information tree traversal.
 *
 * This typedef defines the signature for callback functions invoked during parameter
 * information tree traversal operations. The callback is called for each parameter node
 * in the tree that matches the traversal filter criteria, providing access to the
 * parameter's information structure.
 *
 * @param[in] pContext    Context handle provided by the caller for callback state management.
 * @param[in] pParamInfo  Pointer to the CCSP_TR069_PARAM_INFO structure containing parameter details
 *
 * @return Boolean indicating whether to continue traversal.
 * @retval CCSP_TRUE   Continue traversing the parameter tree.
 * @retval CCSP_FALSE  Stop traversal immediately and break out of tree traversal.
 *
 */
typedef
CCSP_BOOL
(*PFN_CCSP_TR069PA_PITREE_CB)
    (
        CCSP_HANDLE                 pContext,
        PCCSP_TR069_PARAM_INFO      pParamInfo
    );

/**
 * @brief Traverses the parameter information tree with filtering options.
 *
 * This function walks through the parameter information tree starting from the specified
 * root node, applying filters based on node type (leaf only) and subsystem ownership. Subsystem
 * filtering allows traversal of parameters owned by a specific CCSP component.
 *
 * @param[in] MapperHandle   Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] pRoot          Pointer to the root CCSP_TR069_PARAM_INFO node to start traversal from.
 * @param[in] bLeafNodeOnly  Boolean flag to traverse only leaf nodes (parameters).
 * @param[in] Subsystem      Subsystem name filter, or NULL for all subsystems.
 * @param[in] TraversalCB    User-defined callback function invoked for each matching parameter.
 * @param[in] pCBContext     Context handle passed to the callback for state management.
 *
 * @return None.
 *
 */
CCSP_VOID
CcspTr069PA_TraversePiTree
    (
        CCSP_HANDLE                 MapperHandle,
        PCCSP_TR069_PARAM_INFO      pRoot,
        CCSP_BOOL                   bLeafNodeOnly,
        CCSP_STRING                 Subsystem,
        PFN_CCSP_TR069PA_PITREE_CB  TraversalCB,
        CCSP_HANDLE                 pCBContext
    );

/**
 * @brief Traverses the remote parameter information tree.
 *
 * This function walks through the parameter information tree containing only namespaces
 * that are owned by remote CCSP subsystems. This is useful for discovering and managing parameters across
 * distributed CCSP components. The function applies filters based on node type and subsystem,
 * invoking the callback for each matching parameter.
 *
 * @param[in] MapperHandle   Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] bLeafNodeOnly  Boolean flag to traverse only leaf nodes (parameters).
 * @param[in] Subsystem      Subsystem name filter, or NULL for all remote subsystems.
 * @param[in] TraversalCB    User-defined callback function invoked for each matching parameter.
 * @param[in] pCBContext     Context handle passed to the callback for state management.
 *
 * @return None.
 *
 */
CCSP_VOID
CcspTr069PA_TraverseRemotePiTree
    (
        CCSP_HANDLE                 MapperHandle,
        CCSP_BOOL                   bLeafNodeOnly,
        CCSP_STRING                 Subsystem,
        PFN_CCSP_TR069PA_PITREE_CB  TraversalCB,
        CCSP_HANDLE                 pCBContext
    );

/**
 * @brief Retrieves the full parameter name from a parameter info structure.
 *
 * This function constructs the full parameter name from a CCSP_TR069_PARAM_INFO
 * structure and stores it in the provided buffer. The function traverses up the
 * parameter tree hierarchy to build the complete path.
 *
 * @param[in] pParamInfo   Pointer to the CCSP_TR069_PARAM_INFO structure.
 * @param[out] pFnBuf      Buffer to receive the full parameter name string.
 * @param[in] nFnBufLen    Size of the buffer in bytes.
 *
 * @return Integer status code.
 * @retval 0   Successfully retrieved and stored the full parameter name.
 * @retval -1  Buffer too small or parameter info invalid.
 *
 */
int
CcspTr069PA_GetPiFullName
    (
        PCCSP_TR069_PARAM_INFO      pParamInfo,
        char*                       pFnBuf,
        int                         nFnBufLen
    );

#ifdef   _DEBUG

/**
 * @brief Retrieves the root of the parameter information tree for debugging purposes.
 *
 * This debug function returns a pointer to the root node of either the visible or invisible
 * parameter information tree. It provides direct access to the tree structure for debugging,
 * diagnostics, and tree traversal operations.
 *
 * @param[in] bInvPiTree  Boolean flag indicating which tree to return.
 *
 * @return Pointer to the root of the parameter information tree.
 * @retval Non-NULL  Pointer to CCSP_TR069_PARAM_INFO structure representing the tree root.
 * @retval NULL      Parameter tree not initialized or invalid flag value.
 *
 */
PCCSP_TR069_PARAM_INFO
CcspTr069PA_GetPiTreeRoot
    (
        CCSP_BOOL                   bInvPiTree
    );

#endif

/**
 * @brief Retrieves the list of internal parameter names corresponding to an external parameter.
 *
 * This function maps an external TR-069 parameter name to its corresponding
 * internal CCSP parameter name(s). The mapping handles alias resolution and namespace translation.
 *
 * @param[in] MapperHandle  Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] ParamName     External TR-069 parameter name.
 *
 * @return Pointer to single-linked list header containing internal parameter names.
 * @retval Non-NULL  Pointer to PSLIST_HEADER with internal parameter name entries.
 * @retval NULL      No matching internal parameter found or error occurred.
 *
 */
PSLIST_HEADER
CcspTr069PA_GetParamInternalNames
    (
        CCSP_HANDLE                MapperHandle,
        CCSP_STRING                ParamName
    );

/**
 * @brief Retrieves the next internal parameter name from the list.
 *
 * This function iterates through the single-linked list of internal parameter names returned
 * by CcspTr069PA_GetParamInternalNames(). Each call returns the next name in the list until
 * all names have been retrieved. The function maintains internal iteration state within the
 * list header structure.
 *
 * @param[in,out] pListHeader  Pointer to the PSLIST_HEADER structure returned by
 *                             CcspTr069PA_GetParamInternalNames().
 *
 * @return Pointer to the next internal parameter name string.
 * @retval Non-NULL  Pointer to const char string containing the internal parameter name.
 * @retval NULL      No more entries in the list or list is empty.
 *
 */
const char *
CcspTr069PA_GetNextInternalName
    (
        PSLIST_HEADER              pListHeader
    );

/**
 * @brief Retrieves the first internal parameter name for an external parameter.
 *
 * This is a convenience function that combines CcspTr069PA_GetParamInternalNames() and
 * CcspTr069PA_GetNextInternalName() to directly retrieve the first internal parameter name
 * corresponding to the given external TR-069 parameter.
 *
 * @param[in] MapperHandle  Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] ParamName     External TR-069 parameter name.
 *
 * @return Pointer to the first internal parameter name string.
 * @retval Non-NULL  Pointer to const char string containing the first internal parameter name.
 * @retval NULL      No matching internal parameter found or error occurred.
 *
 */
const char *
CcspTr069PA_GetParamFirstInternalName
    (
        CCSP_HANDLE                MapperHandle,
        CCSP_STRING                ParamName
    );

/**
 * @brief Frees the internal parameter names list.
 *
 * This function deallocates all memory associated with the single-linked list of internal
 * parameter names returned by CcspTr069PA_GetParamInternalNames().
 *
 * @param[in] pListHeader  Pointer to the PSLIST_HEADER structure to be freed.
 *
 * @return None.
 *
 */
VOID
CcspTr069PA_FreeInternalNamesList
    (
        PSLIST_HEADER             pListHeader
    );

/**
 * @brief Retrieves the external TR-069 parameter name from an internal parameter name.
 *
 * This function performs the reverse mapping of CcspTr069PA_GetParamInternalNames(), converting
 * an internal CCSP parameter name to its corresponding external TR-069 parameter name as exposed
 * to the ACS. This mapping handles namespace translation and alias resolution in the reverse
 * direction.
 *
 * @param[in] MapperHandle  Opaque handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] ParamName     Internal CCSP parameter name.
 *
 * @return External TR-069 parameter name string.
 * @retval Non-NULL  Pointer to newly allocated string containing the external parameter name.
 * @retval NULL      No matching external parameter found or error occurred.
 *
 */
CCSP_STRING
CcspTr069PA_GetParamExternalName
    (
        CCSP_HANDLE                MapperHandle,
        CCSP_STRING                ParamName
    );
/**
 * @brief Maps the first internal alias in a parameter name.
 *
 * This function resolves alias-based parameter references to their corresponding internal
 * instance-based names.
 *
 * @param[in] hTr069PaMapper      Opaque mapper handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in,out] pParamName      Pointer to parameter name string pointer. On success, the pointer
 *                                is updated to point to the resolved name with the first alias replaced.
 * @param[out] pbIncludeInvQuery  Pointer to boolean flag indicating whether to include invisible
 *                                parameters in the query.
 * @param[in] bFreeMemory         Boolean flag indicating whether to free the original parameter name
 *                                string memory. [Values: TRUE to free, FALSE to preserve].
 *
 * @return Status code.
 * @retval ANSC_STATUS_SUCCESS  Alias successfully mapped to internal instance number.
 * @retval ANSC_STATUS_FAILURE  Alias resolution failed or alias not found.
 *
 */
ANSC_STATUS
CcspTr069PaMapFirstInternalAlias
    (
        CCSP_HANDLE                hTr069PaMapper,
        CCSP_STRING*               pParamName,
        BOOL*                      pbIncludeInvQuery,
        BOOL                       bFreeMemory
    );

/**
 * @brief Maps internal instance numbers to external alias-based parameter names.
 *
 * This function performs the reverse operation of CcspTr069PaMapFirstInternalAlias(), converting
 * internal instance-based parameter references to their corresponding alias-based external names.
 *
 * @param[in] hTr069PaMapper  Opaque mapper handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in,out] pParamName  Pointer to parameter name string pointer. On success, the pointer
 *                            is updated to point to the resolved name with alias notation.
 *
 * @return None.
 *
 */
VOID
CcspTr069PaMapToExternalAlias
    (
        CCSP_HANDLE                hTr069PaMapper,
        CCSP_STRING*               pParamName
    );

/**
 * @brief Checks if a file exists at the specified path.
 *
 * This utility function verifies the existence of a file at the given filesystem path.
 *
 * @param[in] path  Filesystem path to check.
 *
 * @return Boolean indicating file existence.
 * @retval CCSP_TRUE   The file exists and is accessible.
 * @retval CCSP_FALSE  The file does not exist or is not accessible.
 *
 */
CCSP_BOOL
CcspTr069PA_CheckFileExists
    (
        const char*                path
    );

/**
 * @brief Loads an additional custom mapping file into an existing mapper instance.
 *
 * This function loads supplementary mapper configuration from a custom XML mapping file
 * and merges it with the existing mapper structures initialized by CcspTr069PA_LoadMappingFile().
 * All resources allocated by this function are automatically cleaned up when
 * CcspTr069PA_UnloadMappingFile() is called on the mapper handle.
 *
 * @param[in] CcspHandle   Opaque mapper handle returned by CcspTr069PA_LoadMappingFile().
 * @param[in] MappingFile  Path to the custom XML mapping file to load.
 *
 * @return None.
 *
 */
void
CcspTr069PA_LoadCustomMappingFile
    (
        CCSP_HANDLE                 CcspHandle,
        CCSP_STRING                 MappingFile
    );
#endif
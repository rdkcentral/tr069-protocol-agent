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

    module:	ccsp_cwmp_ifo_mco.h

        For CCSP CWMP protocol implementation

    ---------------------------------------------------------------

    description:

        This wrapper file defines the base class data structure and
        interface for the CCSP CWMP Management Client Operation Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang
        Kang Quan

    ---------------------------------------------------------------

    revision:

        09/01/05    initial revision.
        01/04/2011  support ChangeDUState RPC.
        10/12/11    resolve name conflict with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_IFO_MCO_
#define  _CCSP_CWMP_IFO_MCO_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_ifo_interface.h"


/***********************************************************
    CCSP CWMP MANAGEMENT CLIENT OPERATION INTERFACE DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the os wrapper object definition.
 */
#define  CCSP_CWMP_MCO_INTERFACE_NAME                    "cwmpManagementClientOperationIf"
#define  CCSP_CWMP_MCO_INTERFACE_ID                      0

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support), we
 * have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */

/**
 * @brief Function pointer type to notify ACS status.
 *
 * This callback notifies the session manager about the ACS communication status,
 * indicating whether more requests are pending and if new requests should be held.
 *
 * @param[in] hThisObject      Handle to the CWMP session object.
 * @param[in] bNoMoreRequests  Flag indicating no more requests from ACS.
 *                              - TRUE: No more requests pending from ACS
 *                              - FALSE: More requests expected from ACS
 * @param[in] bHoldRequests    Flag indicating whether to hold new requests.
 *                              - TRUE: Hold new requests temporarily
 *                              - FALSE: Process requests normally
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if notification is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_NOTIFY)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bNoMoreRequests,
        BOOL                        bHoldRequests
    );

/**
 * @brief Function pointer type to get the next RPC method type.
 *
 * This callback retrieves the type identifier of the next pending RPC method
 * to be processed, identified by its request ID.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string identifying the RPC.
 *                          Must be a valid, null-terminated string.
 *
 * @return RPC method type identifier.
 * @retval ULONG representing the method type code.
 *
 */
typedef  ULONG
(*PFN_CWMPMCOIF_GET_TYPE)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

/**
 * @brief Function pointer type to process SOAP response from ACS.
 *
 * This callback processes a SOAP response message received from the ACS
 * in reply to a previous RPC method call from the CPE.
 *
 * @param[in] hThisObject    Handle to the CWMP session object.
 * @param[in] hSoapResponse  Handle to SOAP response envelope structure.
 *                            Must be a valid CCSP_CWMP_SOAP_RESPONSE handle.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if response processing is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_PROCESS)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSoapResponse
    );

/**
 * @brief Function pointer type to process SOAP error/fault from ACS.
 *
 * This callback handles SOAP fault responses received from the ACS when
 * an RPC method call results in an error condition.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string of the failed RPC.
 *                          Must be a valid, null-terminated string.
 * @param[in] pMethodName  Pointer to RPC method name that caused the fault.
 *                          Must be a valid, null-terminated string.
 * @param[in] hSoapFault   Handle to SOAP fault structure containing error details.
 *                          Must be a valid CCSP_CWMP_SOAP_FAULT handle.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if fault processing is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_PROCESS2)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pMethodName,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Function pointer type to invoke unknown/unsupported RPC method.
 *
 * This callback handles invocation of RPC methods that are not recognized
 * or supported by the CPE, typically returning a method not supported fault.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string of the RPC.
 *                          Must be a valid, null-terminated string.
 * @param[in] pMethodName  Pointer to unknown RPC method name.
 *                          Must be a valid, null-terminated string.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if fault response is generated successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_INVOKE)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pMethodName
    );

/**
 * @brief Function pointer type to handle GetRPCMethods RPC from ACS.
 *
 * This callback processes the GetRPCMethods request, returning a list of
 * all RPC methods supported by the CPE.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string identifying this RPC call.
 *                          Must be a valid, null-terminated string.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if method list is returned successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_GET_METHODS)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

/**
 * @brief Function pointer type to handle SetParameterValues RPC from ACS.
 *
 * This callback processes SetParameterValues request, setting one or more
 * parameter values in the CPE's data model as specified by the ACS.
 *
 * @param[in] hThisObject        Handle to the CWMP session object.
 * @param[in] pRequestID         Pointer to request ID string.
 *                                Must be a valid, null-terminated string.
 * @param[in] hParamValueArray   Handle to array of parameter value structures.
 *                                Each entry contains parameter name, value, and type.
 * @param[in] ulArraySize        Number of elements in parameter value array.
 *                                Valid range: 1 to ULONG_MAX.
 * @param[in] pParamKey          Pointer to parameter key string for tracking changes.
 *                                Can be NULL or empty string.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if all parameters are set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_SET_PARAM_V)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hParamValueArray,
        ULONG                       ulArraySize,
        char*                       pParamKey
    );

/**
 * @brief Function pointer type to handle GetParameterValues RPC from ACS.
 *
 * This callback processes GetParameterValues request, retrieving current values
 * of specified parameters from the CPE's data model.
 *
 * @param[in] hThisObject     Handle to the CWMP session object.
 * @param[in] pRequestID      Pointer to request ID string.
 *                             Must be a valid, null-terminated string.
 * @param[in] pParamNameArray Pointer to string array containing parameter names to retrieve.
 *                             Each entry is a full parameter path or partial path.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if parameter values are retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_GET_PARAM_V)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        SLAP_STRING_ARRAY*          pParamNameArray
    );

/**
 * @brief Function pointer type to handle GetParameterNames RPC from ACS.
 *
 * This callback processes GetParameterNames request, returning names and writability
 * of parameters matching the specified path, optionally at next level only.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string.
 *                          Must be a valid, null-terminated string.
 * @param[in] pParamPath   Pointer to parameter path prefix to search.
 *                          Can be full object path or partial path.
 * @param[in] bNextLevel   Flag to limit search to next level only.
 *                          - TRUE: Return only immediate children
 *                          - FALSE: Return all descendants recursively
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if parameter names are retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_GET_PARAM_N)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pParamPath,
        BOOL                        bNextLevel
    );

/**
 * @brief Function pointer type to handle SetParameterAttributes RPC from ACS.
 *
 * This callback processes SetParameterAttributes request, setting notification
 * and access control attributes for specified parameters.
 *
 * @param[in] hThisObject           Handle to the CWMP session object.
 * @param[in] pRequestID            Pointer to request ID string.
 *                                   Must be a valid, null-terminated string.
 * @param[in] hSetParamAttribArray  Handle to array of parameter attribute structures.
 *                                   Each entry contains parameter name and attributes to set.
 * @param[in] ulArraySize           Number of elements in attribute array.
 *                                   Valid range: 1 to ULONG_MAX.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if attributes are set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_SET_PARAM_A)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSetParamAttribArray,
        ULONG                       ulArraySize
    );

/**
 * @brief Function pointer type to handle GetParameterAttributes RPC from ACS.
 *
 * This callback processes GetParameterAttributes request, retrieving notification
 * and access control attributes for specified parameters.
 *
 * @param[in] hThisObject     Handle to the CWMP session object.
 * @param[in] pRequestID      Pointer to request ID string.
 *                             Must be a valid, null-terminated string.
 * @param[in] pParamNameArray Pointer to string array containing parameter names.
 *                             Each entry is a full parameter path.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if attributes are retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_GET_PARAM_A)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        SLAP_STRING_ARRAY*          pParamNameArray
    );

/**
 * @brief Function pointer type to handle AddObject RPC from ACS.
 *
 * This callback processes AddObject request, creating a new instance of a
 * multi-instance object in the CPE's data model.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string.
 *                          Must be a valid, null-terminated string.
 * @param[in] pObjectName  Pointer to object path where new instance will be created.
 *                          Must end with a dot and refer to a multi-instance object.
 * @param[in] pParamKey    Pointer to parameter key string for tracking changes.
 *                          Can be NULL or empty string.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if object instance is created successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_ADD_OBJECT)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pObjectName,
        char*                       pParamKey
    );

/**
 * @brief Function pointer type to handle DeleteObject RPC from ACS.
 *
 * This callback processes DeleteObject request, removing an existing instance
 * of a multi-instance object from the CPE's data model.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string.
 *                          Must be a valid, null-terminated string.
 * @param[in] pObjectName  Pointer to full object instance path to delete.
 *                          Must include instance number and end with a dot.
 * @param[in] pParamKey    Pointer to parameter key string for tracking changes.
 *                          Can be NULL or empty string.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if object instance is deleted successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_DEL_OBJECT)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pObjectName,
        char*                       pParamKey
    );

/**
 * @brief Function pointer type to handle Download RPC from ACS.
 *
 * This callback processes Download request, causing the CPE to download a file
 * (such as firmware image or configuration) from the specified URL.
 *
 * @param[in] hThisObject   Handle to the CWMP session object.
 * @param[in] pRequestID    Pointer to request ID string.
 *                           Must be a valid, null-terminated string.
 * @param[in] hDownloadReq  Handle to CCSP_CWMP_MCO_DOWNLOAD_REQ structure.
 *                           Contains URL, file type, credentials, delay, and callback URLs.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if download is initiated successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_DOWNLOAD)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hDownloadReq
    );

/**
 * @brief Function pointer type to handle Reboot RPC from ACS.
 *
 * This callback processes Reboot request, causing the CPE to reboot after
 * completing current session and optional delay period.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string.
 *                          Must be a valid, null-terminated string.
 * @param[in] pCommandKey  Pointer to command key string for tracking this reboot.
 *                          Included in boot inform event after reboot.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if reboot is scheduled successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_REBOOT)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pCommandKey
    );

/**
 * @brief Function pointer type to handle GetQueuedTransfers RPC from ACS.
 *
 * This callback processes GetQueuedTransfers request, returning information about
 * pending or in-progress download and upload operations.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string.
 *                          Must be a valid, null-terminated string.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if queued transfers are returned successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_GET_Q_TRANS)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

/**
 * @brief Function pointer type to handle ScheduleInform RPC from ACS.
 *
 * This callback processes ScheduleInform request, scheduling a future inform
 * session to the ACS at the specified time offset.
 *
 * @param[in] hThisObject    Handle to the CWMP session object.
 * @param[in] pRequestID     Pointer to request ID string.
 *                            Must be a valid, null-terminated string.
 * @param[in] ulDelaySeconds Time delay in seconds before inform.
 *                            Valid range: 0 to ULONG_MAX.
 * @param[in] pCommandKey    Pointer to command key string for this scheduled inform.
 *                            Included in the scheduled inform event.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if inform is scheduled successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_SCHEDULE_IN)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ULONG                       ulDelaySeconds,
        char*                       pCommandKey
    );

/**
 * @brief Function pointer type to handle SetVouchers RPC from ACS.
 *
 * This callback processes SetVouchers request, setting voucher information
 * for option-based services (optional RPC method).
 *
 * @param[in] hThisObject   Handle to the CWMP session object.
 * @param[in] pRequestID    Pointer to request ID string.
 *                           Must be a valid, null-terminated string.
 * @param[in] pVoucherList  Pointer to string array containing voucher data.
 *                           Each entry is a base64-encoded voucher.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if vouchers are set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_SET_VOUCHER)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        SLAP_STRING_ARRAY*          pVoucherList
    );

/**
 * @brief Function pointer type to handle GetOptions RPC from ACS.
 *
 * This callback processes GetOptions request, retrieving option information
 * for specified service (optional RPC method).
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string.
 *                          Must be a valid, null-terminated string.
 * @param[in] pOptionName  Pointer to option name string to query.
 *                          Must be a valid, null-terminated string.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if options are retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_GET_OPTIONS)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pOptionName
    );

/**
 * @brief Function pointer type to handle Upload RPC from ACS.
 *
 * This callback processes Upload request, causing the CPE to upload a file
 * (such as logs or configuration) to the specified URL.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string.
 *                          Must be a valid, null-terminated string.
 * @param[in] hUploadReq   Handle to CCSP_CWMP_MCO_UPLOAD_REQ structure.
 *                          Contains URL, file type, credentials, and delay.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if upload is initiated successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_UPLOAD)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hUploadReq
    );

/**
 * @brief Function pointer type to handle FactoryReset RPC from ACS.
 *
 * This callback processes FactoryReset request, causing the CPE to reset
 * all configuration parameters to factory default values and reboot.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string.
 *                          Must be a valid, null-terminated string.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if factory reset is scheduled successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_FACTORY_RES)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

/**
 * @brief Function pointer type to handle ChangeDUState RPC from ACS.
 *
 * This callback processes ChangeDUState (Change Deployment Unit State) request,
 * managing software module installation, update, or uninstallation operations.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pRequestID   Pointer to request ID string.
 *                          Must be a valid, null-terminated string.
 * @param[in] hCdsReq      Handle to ChangeDUState request structure.
 *                          Contains operation type and deployment unit details.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if DU state change is initiated successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMCOIF_CHANGE_DU_STATE)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hCdsReq
    );

/**
 * @brief Function pointer type to get parameter data type.
 *
 * This callback retrieves the data type of a specified parameter, returning
 * the CWMP type code.
 *
 * @param[in] hThisObject  Handle to the CWMP session object.
 * @param[in] pParanName   Pointer to parameter name string.
 *                          Must be a valid, full parameter path.
 *
 * @return Parameter data type identifier.
 * @retval ULONG representing CWMP data type code.
 *
 */
typedef  ULONG
(*PFN_CWMPMCOIF_GET_PARAM_TYPE)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParanName
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
#define  CCSP_CWMP_MCO_INTERFACE_CLASS_CONTENT                                              \
    /* duplication of the base object class content */                                      \
    ANSCIFO_CLASS_CONTENT                                                                   \
    /* start of object class content */                                                     \
    PFN_CWMPMCOIF_NOTIFY            NotifyAcsStatus;                                        \
    PFN_CWMPMCOIF_GET_TYPE          GetNextMethod;                                          \
    PFN_CWMPMCOIF_PROCESS           ProcessSoapResponse;                                    \
    PFN_CWMPMCOIF_PROCESS2          ProcessSoapError;                                       \
    PFN_CWMPMCOIF_INVOKE            InvokeUnknownMethod;                                    \
                                                                                            \
    PFN_CWMPMCOIF_GET_METHODS       GetRpcMethods;                                          \
    PFN_CWMPMCOIF_SET_PARAM_V       SetParameterValues;                                     \
    PFN_CWMPMCOIF_GET_PARAM_V       GetParameterValues;                                     \
    PFN_CWMPMCOIF_GET_PARAM_N       GetParameterNames;                                      \
    PFN_CWMPMCOIF_SET_PARAM_A       SetParameterAttributes;                                 \
    PFN_CWMPMCOIF_GET_PARAM_A       GetParameterAttributes;                                 \
    PFN_CWMPMCOIF_ADD_OBJECT        AddObject;                                              \
    PFN_CWMPMCOIF_DEL_OBJECT        DeleteObject;                                           \
    PFN_CWMPMCOIF_DOWNLOAD          Download;                                               \
    PFN_CWMPMCOIF_REBOOT            Reboot;                                                 \
                                                                                            \
    PFN_CWMPMCOIF_CHANGE_DU_STATE   ChangeDUState;                                          \
                                                                                            \
    PFN_CWMPMCOIF_GET_Q_TRANS       GetQueuedTransfers;                                     \
    PFN_CWMPMCOIF_SCHEDULE_IN       ScheduleInform;                                         \
    PFN_CWMPMCOIF_SET_VOUCHER       SetVouchers;                                            \
    PFN_CWMPMCOIF_GET_OPTIONS       GetOptions;                                             \
    PFN_CWMPMCOIF_UPLOAD            Upload;                                                 \
    PFN_CWMPMCOIF_FACTORY_RES       FactoryReset;                                           \
                                                                                            \
    PFN_CWMPMCOIF_GET_PARAM_TYPE    GetParamDataType;                                       \
    /* end of object class content */                                                       \

typedef  struct
_CCSP_CWMP_MCO_INTERFACE
{
    CCSP_CWMP_MCO_INTERFACE_CLASS_CONTENT
}
CCSP_CWMP_MCO_INTERFACE,  *PCCSP_CWMP_MCO_INTERFACE;

#define  ACCESS_CCSP_CWMP_MCO_INTERFACE(p)               \
         ACCESS_CONTAINER(p, CCSP_CWMP_MCO_INTERFACE, Linkage)


/***********************************************************
   CCSP CWMP MANAGEMENT CLIENT OPERATION PARAMETERS DEFINITION
***********************************************************/

/*
 * the Download() method may be used by the Server to cause the CPE to download a specified file
 * from the designated location. The following data structure encapsulates the calling arguments
 * for this method.
 */
typedef  struct
_CCSP_CWMP_MCO_DOWNLOAD_REQ
{
    char*                           CommandKey;
    char*                           FileType;
    char*                           Url;
    char*                           Username;
    char*                           Password;
    ULONG                           FileSize;
    char*                           TargetFileName;
    ULONG                           DelaySeconds;
    char*                           SuccessUrl;
    char*                           FailureUrl;
}
CCSP_CWMP_MCO_DOWNLOAD_REQ,  *PCCSP_CWMP_MCO_DOWNLOAD_REQ;

#define  CcspCwmpMcoCleanDownloadReq(download_req)                                              \
         {                                                                                  \
            if ( download_req->CommandKey )                                                 \
            {                                                                               \
                AnscFreeMemory(download_req->CommandKey);                                   \
                                                                                            \
                download_req->CommandKey = NULL;                                            \
            }                                                                               \
                                                                                            \
            if ( download_req->FileType )                                                   \
            {                                                                               \
                AnscFreeMemory(download_req->FileType);                                     \
                                                                                            \
                download_req->FileType = NULL;                                              \
            }                                                                               \
                                                                                            \
            if ( download_req->Url )                                                        \
            {                                                                               \
                AnscFreeMemory(download_req->Url);                                          \
                                                                                            \
                download_req->Url = NULL;                                                   \
            }                                                                               \
                                                                                            \
            if ( download_req->Username )                                                   \
            {                                                                               \
                AnscFreeMemory(download_req->Username);                                     \
                                                                                            \
                download_req->Username = NULL;                                              \
            }                                                                               \
                                                                                            \
            if ( download_req->Password )                                                   \
            {                                                                               \
                AnscFreeMemory(download_req->Password);                                     \
                                                                                            \
                download_req->Password = NULL;                                              \
            }                                                                               \
                                                                                            \
            if ( download_req->TargetFileName )                                             \
            {                                                                               \
                AnscFreeMemory(download_req->TargetFileName);                               \
                                                                                            \
                download_req->TargetFileName = NULL;                                        \
            }                                                                               \
                                                                                            \
            if ( download_req->SuccessUrl )                                                 \
            {                                                                               \
                AnscFreeMemory(download_req->SuccessUrl);                                   \
                                                                                            \
                download_req->SuccessUrl = NULL;                                            \
            }                                                                               \
                                                                                            \
            if ( download_req->FailureUrl )                                                 \
            {                                                                               \
                AnscFreeMemory(download_req->FailureUrl);                                   \
                                                                                            \
                download_req->FailureUrl = NULL;                                            \
            }                                                                               \
         }

#define  CcspCwmpMcoFreeDownloadReq(download_req)                                               \
         {                                                                                  \
            CcspCwmpMcoCleanDownloadReq(download_req);                                          \
            AnscFreeMemory         (download_req);                                          \
         }

/*
 * The Upload() method may be used by the Server to cause the CPE to upload a specified file to the
 * designated location. The support for this method is optional. The following data structure encap-
 * sulates the calling arguments for this method.
 */
typedef  struct
_CCSP_CWMP_MCO_UPLOAD_REQ
{
    char*                           CommandKey;
    char*                           FileType;
    char*                           Url;
    char*                           Username;
    char*                           Password;
    ULONG                           DelaySeconds;
}
CCSP_CWMP_MCO_UPLOAD_REQ,  *PCCSP_CWMP_MCO_UPLOAD_REQ;

#define  CcspCwmpMcoCleanUploadReq(upload_req)                                                  \
         {                                                                                  \
            if ( upload_req->CommandKey )                                                   \
            {                                                                               \
                AnscFreeMemory(upload_req->CommandKey);                                     \
                                                                                            \
                upload_req->CommandKey = NULL;                                              \
            }                                                                               \
                                                                                            \
            if ( upload_req->FileType )                                                     \
            {                                                                               \
                AnscFreeMemory(upload_req->FileType);                                       \
                                                                                            \
                upload_req->FileType = NULL;                                                \
            }                                                                               \
                                                                                            \
            if ( upload_req->Url )                                                          \
            {                                                                               \
                AnscFreeMemory(upload_req->Url);                                            \
                                                                                            \
                upload_req->Url = NULL;                                                     \
            }                                                                               \
                                                                                            \
            if ( upload_req->Username )                                                     \
            {                                                                               \
                AnscFreeMemory(upload_req->Username);                                       \
                                                                                            \
                upload_req->Username = NULL;                                                \
            }                                                                               \
                                                                                            \
            if ( upload_req->Password )                                                     \
            {                                                                               \
                AnscFreeMemory(upload_req->Password);                                       \
                                                                                            \
                upload_req->Password = NULL;                                                \
            }                                                                               \
         }

#define  CcspCwmpMcoFreeUploadReq(upload_req)                                                   \
         {                                                                                  \
            CcspCwmpMcoCleanUploadReq(upload_req);                                              \
            AnscFreeMemory       (upload_req);                                              \
         }


#endif
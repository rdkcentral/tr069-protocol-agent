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

    module:	ccsp_cwmp_ifo_mso.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This wrapper file defines the base class data structure and
        interface for the CCSP CWMP Management Server Operation Object.

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
        06/21/11    decouple TR-069 PA from Data Model Manager
                    and make it work with CCSP architecture.
        10/12/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_IFO_MSO_
#define  _CCSP_CWMP_IFO_MSO_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_ifo_interface.h"
#include "slap_definitions.h"

/***********************************************************
    CCSP CWMP MANAGEMENT SERVER OPERATION INTERFACE DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the os wrapper object definition.
 */
#define  CCSP_CWMP_MSO_INTERFACE_NAME                    "cwmpManagementServerOperationIf"
#define  CCSP_CWMP_MSO_INTERFACE_ID                      0

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support), we
 * have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */
/**
 * @brief Get the list of supported RPC methods.
 *
 * This function pointer typedef defines the callback interface for querying the list of RPC methods
 * supported by the CPE or ACS. It corresponds to the TR-069 GetRPCMethods RPC and returns an array
 * of method name strings. This allows discovery of available CPE capabilities and optional TR-069
 * methods implemented by the device.
 *
 * @param[in]  hThisObject   - Handle to the MSO interface object instance.
 * @param[out] ppMethodList  - Pointer to receive allocated SLAP_STRING_ARRAY structure containing
 *                              method names. Each entry is a string representing one supported RPC method.
 *                              \n Caller must free the returned array.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Method list retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMSOIF_GET_METHODS)
    (
        ANSC_HANDLE                 hThisObject,
        SLAP_STRING_ARRAY**         ppMethodList
    );

/**
 * @brief Queue an Inform event to be sent to the ACS.
 *
 * This function pointer typedef defines the callback interface for queuing TR-069 Inform RPC requests.
 * The Inform method notifies the ACS of CPE events such as boot, value changes, periodic informs, or
 * connection requests. The function queues the inform event with the specified event code and command key,
 * optionally triggering an immediate session connection to the ACS based on the bConnectNow flag.
 *
 * @param[in] hThisObject  - Handle to the MSO interface object instance.
 * @param[in] pEventCode   - Event code string indicating the reason for the Inform.
 *                            \n Common values: "0 BOOTSTRAP", "1 BOOT", "2 PERIODIC", "4 VALUE CHANGE",
 *                            "6 CONNECTION REQUEST", "7 TRANSFER COMPLETE", "8 DIAGNOSTICS COMPLETE",
 *                            "M Reboot", "M ScheduleInform", "M Download", "M Upload".
 * @param[in] pCommandKey  - Command key string associated with the event. Empty string "" if no command key.
 *                            \n Used for correlating ACS requests with CPE responses.
 * @param[in] bConnectNow  - Boolean flag to trigger immediate ACS session.
 *                            \n TRUE = Initiate connection immediately, FALSE = Queue for next scheduled session.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Inform event queued successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMSOIF_INFORM)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pEventCode,
        char*                       pCommandKey,
        BOOL                        bConnectNow
    );

/**
 * @brief Queue a TransferComplete event to be sent to the ACS.
 *
 * This function pointer typedef defines the callback interface for queuing TR-069 TransferComplete RPC
 * requests. The TransferComplete method notifies the ACS when a file transfer initiated by Download or
 * Upload RPC completes (successfully or with failure). It provides the command key, fault information,
 * and timestamps for transfer start and completion times.
 *
 * @param[in] hThisObject    - Handle to the MSO interface object instance.
 * @param[in] bIsDownload    - Boolean flag indicating transfer direction.
 *                              \n TRUE = Download transfer, FALSE = Upload transfer.
 * @param[in] pCommandKey    - Command key string from the original Download or Upload request.
 *                              \n Used to correlate the completion with the ACS-initiated transfer.
 * @param[in] hFault         - Handle to CCSP_CWMP_FAULT structure if transfer failed, NULL if successful.
 *                              \n Contains fault code and fault string describing the error.
 * @param[in] hStartTime     - Handle to ANSC_UNIVERSAL_TIME structure with transfer start time in UTC.
 * @param[in] hCompleteTime  - Handle to ANSC_UNIVERSAL_TIME structure with transfer completion time in UTC.
 * @param[in] bNewSession    - Boolean flag to indicate if RPC should be sent in a new CWMP session.
 *                              \n TRUE = Start new session immediately, FALSE = Use current or next scheduled session.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - TransferComplete event queued successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMSOIF_TRANSFER_COMP)
    (
        ANSC_HANDLE                 hThisObject,
		BOOL						bIsDownload,
        char*                       pCommandKey,        /* 'CommentKey' argument passed in Download() or Upload() */
        ANSC_HANDLE                 hFault,             /* non-zero FaultCode is specified if transfer failed     */
        ANSC_HANDLE                 hStartTime,         /* the date and time transfer was started in UTC          */
        ANSC_HANDLE                 hCompleteTime,      /* the date and time transfer compoleted in UTC           */
        BOOL                        bNewSession         /* to indicate if this RPC needs to be sent in a new CWMP session */
    );

/**
 * @brief Queue an AutonomousTransferComplete event to be sent to the ACS.
 *
 * This function pointer typedef defines the callback interface for queuing TR-069 AutonomousTransferComplete
 * RPC requests. This method notifies the ACS when a file transfer initiated autonomously by the CPE (not
 * triggered by ACS Download/Upload RPC) completes. It provides transfer details including URLs, file type,
 * file size, target filename, fault information, and timestamps.
 *
 * @param[in] hThisObject      - Handle to the MSO interface object instance.
 * @param[in] bIsDownload      - Boolean flag indicating transfer direction.
 *                                \n TRUE = Autonomous download, FALSE = Autonomous upload.
 * @param[in] AnnounceURL      - URL string where the CPE discovered the file transfer announcement.
 *                                \n May be empty string "" if not applicable.
 * @param[in] TransferURL      - URL string used for the file transfer operation.
 *                                \n The actual source (download) or destination (upload) URL.
 * @param[in] FileType         - File type string indicating the type of transferred file.
 *                                \n Common values: "1 Firmware Upgrade Image", "2 Web Content", "3 Vendor Configuration File".
 * @param[in] FileSize         - Size of transferred file in bytes. Valid range: 0 to MAX_UINT.
 * @param[in] TargetFileName   - Target filename string on the CPE filesystem where file was stored.
 *                                \n May be empty string "" if not applicable.
 * @param[in] hFault           - Handle to CCSP_CWMP_FAULT structure if transfer failed, NULL if successful.
 * @param[in] hStartTime       - Handle to ANSC_UNIVERSAL_TIME structure with transfer start time in UTC.
 * @param[in] hCompleteTime    - Handle to ANSC_UNIVERSAL_TIME structure with transfer completion time in UTC.
 * @param[in] bNewSession      - Boolean flag to indicate if RPC should be sent in a new CWMP session.
 *                                \n TRUE = Start new session immediately, FALSE = Use current or next scheduled session.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - AutonomousTransferComplete event queued successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMSOIF_AT_TRANSFER_COMP)
    (
        ANSC_HANDLE                 hThisObject,
		BOOL						bIsDownload,
        char*                       AnnounceURL,
        char*                       TransferURL,
        char*                       FileType,
        unsigned int                FileSize,
        char*                       TargetFileName,
        ANSC_HANDLE                 hFault,             /* non-zero FaultCode is specified if transfer failed     */
        ANSC_HANDLE                 hStartTime,         /* the date and time transfer was started in UTC          */
        ANSC_HANDLE                 hCompleteTime,      /* the date and time transfer compoleted in UTC           */
        BOOL                        bNewSession         /* to indicate if this RPC needs to be sent in a new CWMP session */
    );

/**
 * @brief Queue a DUStateChangeComplete event to be sent to the ACS.
 *
 * This function pointer typedef defines the callback interface for queuing TR-069 DUStateChangeComplete
 * RPC requests. This method notifies the ACS when a deployment unit (software module) state change
 * operation initiated by the ACS ChangeDUState RPC completes. It provides the results of install, update,
 * or uninstall operations for software modules on the CPE.
 *
 * @param[in] hThisObject   - Handle to the MSO interface object instance.
 * @param[in] hDsccReq      - Handle to CCSP_CWMP_DUSTATE_CHANGE_COMPLETE structure containing deployment
 *                             unit state change completion details. Includes operation results for each
 *                             affected deployment unit with fault codes and resolved/execution/resolved states.
 * @param[in] bNewSession   - Boolean flag to indicate if RPC should be sent in a new CWMP session.
 *                             \n TRUE = Start new session immediately, FALSE = Use current or next scheduled session.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - DUStateChangeComplete event queued successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMSOIF_DSC_COMP)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hDsccReq,
        BOOL                        bNewSession         /* to indicate if this RPC needs to be sent in a new CWMP session */
    );

/**
 * @brief Queue an AutonomousDUStateChangeComplete event to be sent to the ACS.
 *
 * This function pointer typedef defines the callback interface for queuing TR-069 AutonomousDUStateChangeComplete
 * RPC requests. This method notifies the ACS when a deployment unit (software module) state change operation
 * initiated autonomously by the CPE (not triggered by ACS ChangeDUState RPC) completes. It provides the results
 * of autonomous install, update, or uninstall operations for software modules.
 *
 * @param[in] hThisObject   - Handle to the MSO interface object instance.
 * @param[in] hAdsccReq     - Handle to CCSP_CWMP_AUTONOMOUS_DUSTATE_CHANGE_COMPLETE structure containing
 *                             autonomous deployment unit state change completion details. Includes operation
 *                             results for each affected deployment unit with fault codes and execution states.
 * @param[in] bNewSession   - Boolean flag to indicate if RPC should be sent in a new CWMP session.
 *                             \n TRUE = Start new session immediately, FALSE = Use current or next scheduled session.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - AutonomousDUStateChangeComplete event queued successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMSOIF_ADSC_COMP)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hAdsccReq,
        BOOL                        bNewSession         /* to indicate if this RPC needs to be sent in a new CWMP session */
    );

/**
 * @brief Handle a kicked notification from external connection request.
 *
 * This function pointer typedef defines the callback interface for handling TR-069 Kicked RPC events.
 * The Kicked method processes external connection requests with extended parameters beyond the standard
 * connection request mechanism. It handles custom command strings, referer URLs, arguments, and next-hop
 * URLs for advanced CPE control scenarios.
 *
 * @param[in]  hThisObject  - Handle to the MSO interface object instance.
 * @param[in]  pCommand     - Command string from the connection request.
 *                             \n Specifies the action or operation to perform on the CPE.
 * @param[in]  pReferer     - Referer URL string indicating the source of the connection request.
 *                             \n May be empty string "" if not provided.
 * @param[in]  pArg         - Argument string providing additional parameters for the command.
 *                             \n May be empty string "" if not applicable.
 * @param[in]  pNext        - Next-hop URL string for redirection or chaining requests.
 *                             \n May be empty string "" if not applicable.
 * @param[out] ppNextUrl    - Pointer to receive allocated next URL string for CPE response.
 *                             \n Caller must free the returned string. Set to NULL if no next URL.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Kicked event handled successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMSOIF_KICKED)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pCommand,
        char*                       pReferer,
        char*                       pArg,
        char*                       pNext,
        char**                      ppNextUrl
    );

/**
 * @brief Queue a RequestDownload event to be sent to the ACS.
 *
 * This function pointer typedef defines the callback interface for queuing TR-069 RequestDownload RPC
 * requests. The RequestDownload method notifies the ACS that the CPE requires a file download to operate
 * properly. The CPE specifies the file type and optional file type arguments, and the ACS responds with
 * a Download RPC to initiate the transfer.
 *
 * @param[in] hThisObject         - Handle to the MSO interface object instance.
 * @param[in] pFileType           - File type string indicating the type of file requested.
 *                                   \n Common values: "1 Firmware Upgrade Image", "2 Web Content",
 *                                   "3 Vendor Configuration File", "4 Tone File", "5 Ringer File".
 * @param[in] hFileTypeArgArray   - Handle to array of CCSP_CWMP_FILE_TYPE_ARG structures containing
 *                                   file type-specific arguments. May be NULL if no arguments.
 * @param[in] ulArraySize         - Number of elements in hFileTypeArgArray. Valid range: 0 to MAX_ULONG.
 *                                   \n Set to 0 if hFileTypeArgArray is NULL.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - RequestDownload event queued successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMSOIF_REQ_DOWNLOAD)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pFileType,
        ANSC_HANDLE                 hFileTypeArgArray,
        ULONG                       ulArraySize
    );

/**
 * @brief Notify the ACS of a parameter value change.
 *
 * This function pointer typedef defines the callback interface for queuing parameter value change
 * notifications to the ACS. When a parameter with active notification is modified, this method queues
 * a VALUE CHANGE inform event with the parameter name, new value, and data type. The bConnectNow flag
 * controls whether an immediate session should be initiated or if the notification should be queued
 * for the next scheduled inform.
 *
 * @param[in] hThisObject    - Handle to the MSO interface object instance.
 * @param[in] pParamName     - Full parameter path name that changed.
 *                              \n Must be a valid parameter path in the CPE data model.
 * @param[in] pParamValue    - String representation of the new parameter value.
 *                              \n Value is converted to string regardless of actual data type.
 * @param[in] CwmpDataType   - CWMP data type enumeration for the parameter.
 *                              \n Valid values: CCSP_CWMP_TR069_DATA_TYPE_* constants.
 * @param[in] bConnectNow    - Boolean flag to trigger immediate ACS session.
 *                              \n TRUE = Initiate connection immediately, FALSE = Queue for next scheduled session.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Value change notification queued successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPMSOIF_CHANGED)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName,
        char*                       pParamValue,
        ULONG                       CwmpDataType,
        BOOL                        bConnectNow
    );

/*
 * The CPE will initiate a transaction session to the ACS as a result of the conditions listed
 * below:
 *
 *      - The first time CPE establishes a connection to the access network on initial
 *        installation
 *      - On power-up or reset
 *      - Once every PeriodicInformInterval (for example, every 24-hours)
 *      - When so instructed by the optional ScheduleInform method
 *      - Whenever the CPE receives a valid Connection Request from an ACS
 *      - Whenever the URL of the ACS changes
 *      - Whenever a parameter is modified that is required to initiate an Inform on
 *        change.
 *      - Whenever the value of a parameter that the ACS has marked for "active
 *        notification" via the SetParameterAttributes method is modified by an external
 *        cause.
 *
 * Once the connection to the ACS is successfully established, the CPE initiates a session by
 * sending an initial Inform request to the ACS. This indicates to the ACS the current status of
 * the CPE and that the CPE is ready to accept request from the ACS.
 */
#define  CCSP_CWMP_MSO_INTERFACE_CLASS_CONTENT                                                   \
    /* duplication of the base object class content */                                      \
    ANSCIFO_CLASS_CONTENT                                                                   \
    /* start of object class content */                                                     \
    PFN_CWMPMSOIF_GET_METHODS       GetRpcMethods;                                          \
    PFN_CWMPMSOIF_INFORM            Inform;                                                 \
    PFN_CWMPMSOIF_TRANSFER_COMP     TransferComplete;                                       \
    PFN_CWMPMSOIF_AT_TRANSFER_COMP  AutonomousTransferComplete;                             \
    PFN_CWMPMSOIF_DSC_COMP          DuStateChangeComplete;                                  \
    PFN_CWMPMSOIF_ADSC_COMP         AutonomousDuStateChangeComplete;                        \
                                                                                            \
    PFN_CWMPMSOIF_KICKED            Kicked;                                                 \
    PFN_CWMPMSOIF_REQ_DOWNLOAD      RequestDownload;                                        \
    PFN_CWMPMSOIF_CHANGED           ValueChanged;                                           \
    /* end of object class content */                                                       \

typedef  struct
_CCSP_CWMP_MSO_INTERFACE
{
    CCSP_CWMP_MSO_INTERFACE_CLASS_CONTENT
}
CCSP_CWMP_MSO_INTERFACE,  *PCCSP_CWMP_MSO_INTERFACE;

#define  ACCESS_CCSP_CWMP_MSO_INTERFACE(p)               \
         ACCESS_CONTAINER(p, CCSP_CWMP_MSO_INTERFACE, Linkage)


#endif

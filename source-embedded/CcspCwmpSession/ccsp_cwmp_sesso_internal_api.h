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

    module:	ccsp_cwmp_sesso_internal_api.h

        For CCSP CWMP protocol implementation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the internal functions provided by the CCSP CWMP Session
        Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang
        Kang Quan

    ---------------------------------------------------------------

    revision:

        09/13/05    initial revision.
        06/21/11    decouple TR-069 PA from Data Model Manager
                    and make it work with CCSP architecture.
        10/13/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_SESSO_INTERNAL_API_
#define  _CCSP_CWMP_SESSO_INTERNAL_API_


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMPSO_STATES.C
***********************************************************/

/**
* @brief Get the CCSP CWMP ACS Connection object handle.
*
* This function is called to retrieve the handle to the CCSP CWMP ACS Connection object
* associated with this CCSP CWMP Session object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP ACS Connection object.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpsoGetCcspCwmpAcsConnection
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the CCSP CWMP MCO Interface handle.
*
* This function is called to retrieve the handle to the CCSP CWMP MCO (Method Call Object)
* Interface associated with this CCSP CWMP Session object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP MCO Interface.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpsoGetCcspCwmpMcoIf
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the CCSP CWMP CPE Controller object handle.
*
* This function is called to retrieve the handle to the CCSP CWMP CPE Controller object
* associated with this CCSP CWMP Session object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP CPE Controller object.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpsoGetCcspCwmpCpeController
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the CCSP CWMP CPE Controller object handle.
*
* This function is called to configure the handle to the CCSP CWMP CPE Controller object
* for this CCSP CWMP Session object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hCpeController  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n Must be a valid CPE Controller handle.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoSetCcspCwmpCpeController
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCpeController
    );

/**
* @brief Get the CCSP CWMP Processor object handle.
*
* This function is called to retrieve the handle to the CCSP CWMP Processor object
* associated with this CCSP CWMP Session object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP Processor object.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpsoGetCcspCwmpProcessor
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the CCSP CWMP Processor object handle.
*
* This function is called to configure the handle to the CCSP CWMP Processor object
* for this CCSP CWMP Session object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hWmpProcessor  - Handle to the CCSP CWMP Processor Object.
*                    \n Must be a valid CWMP Processor handle.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoSetCcspCwmpProcessor
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpProcessor
    );

/**
* @brief Reset the CCSP CWMP Session object.
*
* This function is called to reset the entire CCSP CWMP Session object to its
* initial state, clearing all session data and event queues.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoReset
    (
        ANSC_HANDLE                 hThisObject
    );

/***********************************************************
       FUNCTIONS IMPLEMENTED IN CCSP_CWMPSO_OPERATION.C
***********************************************************/

/**
* @brief Acquire access lock to the session object.
*
* This function is called to acquire exclusive access to this CCSP CWMP Session object
* for thread-safe operations.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoAcqAccess
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Release access lock from the session object.
*
* This function is called to release exclusive access to this CCSP CWMP Session object
* after thread-safe operations are complete.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoRelAccess
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Handle session timer expiration.
*
* This function is called when the session timer expires, indicating that the ACS
* did not respond in time and the HTTP session must be closed.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoSessionTimerInvoke
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Handle session retry timer expiration.
*
* This function is called when the session retry timer expires to attempt
* reconnection to the ACS after a failed session or connection error.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoSessionRetryTimerInvoke
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Handle delayed active notification timer expiration.
*
* This function is called when the delayed active notification timer expires to send
* deferred parameter value change notifications to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoDelayedActiveNotifTimerInvoke
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Start the session retry timer.
*
* This function is called to start the retry timer which controls the wait period
* before attempting to reconnect to the ACS after a session failure.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoStartRetryTimer
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Stop the session retry timer.
*
* This function is called to stop the retry timer when a successful connection
* is established or when retry attempts should be canceled.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoStopRetryTimer
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Cancel the retry delay and optionally reconnect.
*
* This function is called to cancel the current retry delay timer and optionally
* establish a new connection to the ACS immediately.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bConnectAgain  - Flag indicating whether to reconnect immediately.
*                    \n TRUE to establish new connection, FALSE to just cancel timer.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoCancelRetryDelay
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bConnectAgain
    );

/**
* @brief Stop the delayed active notification timer.
*
* This function is called to stop the delayed active notification timer when
* notifications have been sent or should be canceled.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoStopDelayedActiveNotifTimer
	(
		ANSC_HANDLE					hThisObject
	);

/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMPSO_CONTROL.C
***********************************************************/

/**
* @brief Check if ACS is currently connected.
*
* This function is called to check whether the ACS (Auto-Configuration Server)
* is currently connected to the CPE.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The connection status.
* @retval TRUE if ACS is connected.
* @retval FALSE if ACS is not connected or session is not active.
*
*/
BOOL
CcspCwmpsoIsAcsConnected
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Connect to the ACS (Auto-Configuration Server).
*
* This function is called to establish a connection to the specified ACS
* using the configured URL and credentials.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoConnectToAcs
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Close the connection to the ACS.
*
* This function is called to close the current connection to the ACS
* and clean up associated resources.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoCloseConnection
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
      FUNCTIONS IMPLEMENTED IN CCSP_CWMPSO_MANAGEMENT.C
***********************************************************/

/**
* @brief Add a CWMP event to the session.
*
* This function is called to add an event that will be included in the next
* Inform method call to the ACS. Single events are deduplicated.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hCwmpEvent  - Handle to the CWMP Event structure to be added.
*                    \n Contains event code, command key, and other event details.
* @param[in] bConnectNow  - Flag indicating whether to connect to ACS immediately.
*                    \n TRUE to establish connection right away, FALSE otherwise.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoAddCwmpEvent
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCwmpEvent,
        BOOL                        bConnectNow
    );

/**
* @brief Discard a CWMP event from the session.
*
* This function is called to remove a specific event from the session's event queue
* based on the event code.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] EventCode  - The event code of the event to be discarded.
*                    \n Must match a CWMP event code.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoDiscardCwmpEvent
    (
        ANSC_HANDLE                 hThisObject,
        int                         EventCode
    );

/**
* @brief Delete all CWMP events from the session.
*
* This function is called to remove all events from the session's event queue,
* typically after they have been successfully delivered to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoDelAllEvents
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Add a modified parameter to the session.
*
* This function is called to add a parameter that has been modified and needs to be
* reported to the ACS in the next Inform message (passive or active notification).
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamName  - Name of the modified parameter.
*                    \n Full parameter path.
* @param[in] pParamValue  - New value of the parameter.
*                    \n String representation of the parameter value.
* @param[in] CwmpDataType  - CWMP data type of the parameter.
*                    \n One of CCSP_CWMP_TR069_DATA_TYPE_xxx constants.
* @param[in] bConnectNow  - Flag indicating whether to connect to ACS immediately.
*                    \n TRUE for active notification, FALSE for passive.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoAddModifiedParameter
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName,
        char*                       pParamValue,
        ULONG                       CwmpDataType,
        BOOL                        bConnectNow
    );

/**
* @brief Delete all modified parameters from the session.
*
* This function is called to remove all modified parameters from the session's parameter list,
* typically after they have been successfully reported to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoDelAllParameters
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Save CWMP events to persistent storage.
*
* This function is called to save the current session's events to persistent storage
* so they can survive reboots and be delivered to the ACS later.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoSaveCwmpEvent
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Check if an Inform is pending.
*
* This function is called to check whether there are pending events or parameters
* that require an Inform message to be sent to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The pending status.
* @retval TRUE if Inform is pending.
* @retval FALSE if no Inform is needed.
*
*/
BOOL
CcspCwmpsoInformPending
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMPSO_INVOKE.C
***********************************************************/

/**
* @brief Discover the set of RPC methods supported by the server.
*
* This function is called to discover the set of RPC methods supported by the ACS
* by sending a GetRPCMethods request.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[out] ppMethodList  - Pointer to receive the array of method names.
*                    \n Returns string array containing names of supported RPC methods.
* @param[out] pulErrorCode  - Pointer to receive the error code.
*                    \n Set to 0 on success, non-zero on error.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if session state is not informed.
*
*/
ANSC_STATUS
CcspCwmpsoGetRpcMethods
    (
        ANSC_HANDLE                 hThisObject,
        SLAP_STRING_ARRAY**         ppMethodList,
        PULONG                      pulErrorCode
    );

/**
* @brief Send an Inform message to the ACS.
*
* This function is called to send an Inform message to the ACS containing device information,
* events, and modified parameters. This is the primary mechanism for CPE-initiated communication.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[out] pulErrorCode  - Pointer to receive the error code.
*                    \n Set to 0 on success, non-zero on error.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if session state is invalid.
*
*/
ANSC_STATUS
CcspCwmpsoInform
    (
        ANSC_HANDLE                 hThisObject,
        PULONG                      pulErrorCode
    );

/**
* @brief Send a TransferComplete message to the ACS.
*
* This function is called to notify the ACS of the completion of a Download or Upload
* operation previously requested by the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bIsDownload  - Flag indicating transfer type.
*                    \n TRUE for Download, FALSE for Upload.
* @param[in] pCommandKey  - CommandKey from the original Download/Upload request.
*                    \n String identifying the transfer operation.
* @param[in] hFault  - Handle to fault structure if transfer failed.
*                    \n NULL if transfer was successful.
* @param[in] hStartTime  - Handle to the start time structure.
*                    \n Time when transfer began.
* @param[in] hCompleteTime  - Handle to the complete time structure.
*                    \n Time when transfer completed.
* @param[out] pulErrorCode  - Pointer to receive the error code.
*                    \n Set to 0 on success, non-zero on error.
* @param[in] bAddEventCode  - Flag indicating whether to add TransferComplete event.
*                    \n TRUE to add event to queue, FALSE otherwise.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if session state is invalid.
*
*/
ANSC_STATUS
CcspCwmpsoTransferComplete
    (
        ANSC_HANDLE                 hThisObject,
		BOOL						bIsDownload,
        char*                       pCommandKey,
        ANSC_HANDLE                 hFault,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime,
        PULONG                      pulErrorCode,
        BOOL                        bAddEventCode
    );

/**
* @brief Send a Kicked message to the ACS.
*
* This function is called when the CPE is "kicked" by an external entity to notify
* the ACS and potentially receive a redirect URL.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pCommand  - Command received in the kick request.
*                    \n Command string from the kick.
* @param[in] pReferer  - Referer received in the kick request.
*                    \n Source of the kick request.
* @param[in] pArg  - Argument received in the kick request.
*                    \n Additional argument from the kick.
* @param[in] pNext  - Next URL received in the kick request.
*                    \n Suggested next URL.
* @param[out] ppNextUrl  - Pointer to receive the next URL from ACS.
*                    \n Returns URL where CPE should redirect.
* @param[out] pulErrorCode  - Pointer to receive the error code.
*                    \n Set to 0 on success, non-zero on error.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if session state is invalid.
*
*/
ANSC_STATUS
CcspCwmpsoKicked
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pCommand,
        char*                       pReferer,
        char*                       pArg,
        char*                       pNext,
        char**                      ppNextUrl,
        PULONG                      pulErrorCode
    );

/**
* @brief Send a RequestDownload message to the ACS.
*
* This function is called when the CPE needs to request a file download from the ACS,
* typically for firmware upgrades or configuration files.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pFileType  - Type of file being requested.
*                    \n File type identifier (e.g., firmware, configuration).
* @param[in] hFileTypeArgArray  - Handle to array of file type arguments.
*                    \n Additional arguments specific to the file type.
* @param[in] ulArraySize  - Size of the file type argument array.
*                    \n Number of elements in hFileTypeArgArray.
* @param[out] pulErrorCode  - Pointer to receive the error code.
*                    \n Set to 0 on success, non-zero on error.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if session state is invalid.
*
*/
ANSC_STATUS
CcspCwmpsoRequestDownload
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pFileType,
        ANSC_HANDLE                 hFileTypeArgArray,
        ULONG                       ulArraySize,
        PULONG                      pulErrorCode
    );

/**
* @brief Send an AutonomousTransferComplete message to the ACS.
*
* This function is called to notify the ACS of the completion of an autonomous file transfer
* (one not initiated by the ACS).
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bIsDownload  - Flag indicating transfer direction.
*                    \n TRUE for Download, FALSE for Upload.
* @param[in] hFault  - Handle to fault structure if transfer failed.
*                    \n NULL if transfer was successful.
* @param[in] hStartTime  - Handle to the start time structure.
*                    \n Time when transfer began.
* @param[in] hCompleteTime  - Handle to the complete time structure.
*                    \n Time when transfer completed.
* @param[in] AnnounceURL  - URL where transfer was announced.
*                    \n Used for autonomous transfers.
* @param[in] TransferURL  - URL from which file was transferred.
*                    \n Source or destination URL.
* @param[in] FileType  - Type of file transferred.
*                    \n MIME type or file category.
* @param[in] FileSize  - Size of transferred file in bytes.
*                    \n Total file size.
* @param[in] TargetFileName  - Name of the target file.
*                    \n Destination filename.
* @param[out] pulErrorCode  - Pointer to receive the error code.
*                    \n Set to 0 on success, non-zero on error.
* @param[in] bAddEventCode  - Flag indicating whether to add AutonomousTransferComplete event.
*                    \n TRUE to add event to queue, FALSE otherwise.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if session state is invalid.
*
*/
ANSC_STATUS
CcspCwmpsoAutonomousTransferComplete
    (
        ANSC_HANDLE                 hThisObject,
		BOOL						bIsDownload,
        ANSC_HANDLE                 hFault,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime,
        char*                       AnnounceURL,
        char*                       TransferURL,
        char*                       FileType,
        unsigned int                FileSize,
        char*                       TargetFileName,
        PULONG                      pulErrorCode,
        BOOL                        bAddEventCode
    );

/**
* @brief Send a DUStateChangeComplete message to the ACS.
*
* This function is called to notify the ACS of the completion of a Deployment Unit (DU)
* state change operation previously requested by the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hDsccReq  - Handle to DUStateChangeComplete request structure.
*                    \n Contains deployment unit operation details and results.
* @param[out] pulErrorCode  - Pointer to receive the error code.
*                    \n Set to 0 on success, non-zero on error.
* @param[in] bAddEventCode  - Flag indicating whether to add DUStateChangeComplete event.
*                    \n TRUE to add event to queue, FALSE otherwise.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if session state is invalid.
*
*/
ANSC_STATUS
CcspCwmpsoDUStateChangeComplete
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hDsccReq,
        PULONG                      pulErrorCode,
        BOOL                        bAddEventCode
    );

/**
* @brief Send an AutonomousDUStateChangeComplete message to the ACS.
*
* This function is called to notify the ACS of the completion of an autonomous Deployment Unit (DU)
* state change operation (one not initiated by the ACS).
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hAdsccReq  - Handle to AutonomousDUStateChangeComplete request structure.
*                    \n Contains autonomous deployment unit state change details.
* @param[out] pulErrorCode  - Pointer to receive the error code.
*                    \n Set to 0 on success, non-zero on error.
* @param[in] bAddEventCode  - Flag indicating whether to add AutonomousDUStateChangeComplete event.
*                    \n TRUE to add event to queue, FALSE otherwise.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if session state is invalid.
*
*/
ANSC_STATUS
CcspCwmpsoAutonomousDUStateChangeComplete
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hAdsccReq,
        PULONG                      pulErrorCode,
        BOOL                        bAddEventCode
    );


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMPSO_PROCESS.C
***********************************************************/

/**
* @brief Receive and process a SOAP message from the ACS.
*
* This function is called to process a CWMP SOAP message received from the ACS,
* parsing the XML and dispatching to the appropriate RPC method handlers.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pMessage  - Pointer to the SOAP message string to be processed.
*                    \n XML-formatted SOAP envelope.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoRecvSoapMessage
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pMessage
    );

/**
* @brief Notify that the session has been closed.
*
* This function is called to handle cleanup and state transitions when the CWMP session
* with the ACS has been closed, either normally or due to an error.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoNotifySessionClosed
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Asynchronous task for processing RPC method calls.
*
* This function is called as an asynchronous task to process queued RPC method calls
* from the ACS without blocking the main session thread.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoAsyncProcessTask
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
         FUNCTIONS IMPLEMENTED IN CCSP_CWMPSO_MCOIF.C
***********************************************************/

/**
* @brief Notify the ACS status to the session.
*
* This function is called to update the session with the ACS status indicating whether
* there are more requests pending or if requests should be held.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bNoMoreRequests  - Flag indicating if ACS has no more requests.
*                    \n TRUE if session can be closed, FALSE if more requests expected.
* @param[in] bHoldRequests  - Flag indicating if CPE should hold requests.
*                    \n TRUE to pause sending requests, FALSE to continue.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoNotifyAcsStatus
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bNoMoreRequests,
        BOOL                        bHoldRequests
    );

/**
* @brief Get the next method in the request queue.
*
* This function is called to retrieve the next RPC method in the queue that is
* waiting for a response from the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID to search for in the queue.
*                    \n NULL to get the first method in queue.
*
* @return The method type.
* @retval CCSP_CWMP_METHOD_* constant indicating the method type.
* @retval CCSP_CWMP_METHOD_Unknown if no matching method found.
*
*/
ULONG
CcspCwmpsoMcoGetNextMethod
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

/**
* @brief Process a SOAP response from the ACS.
*
* This function is called to process a SOAP response received from the ACS in reply
* to a CPE-initiated RPC method call.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hSoapResponse  - Handle to the SOAP response structure.
*                    \n Contains parsed response data.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoProcessSoapResponse
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSoapResponse
    );

/**
* @brief Process a SOAP fault/error from the ACS.
*
* This function is called to process a SOAP fault received from the ACS indicating
* an error in processing a CPE-initiated RPC method call.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID of the failed method.
*                    \n Identifies which request failed.
* @param[in] pMethodName  - Name of the method that failed.
*                    \n RPC method name.
* @param[in] hSoapFault  - Handle to the SOAP fault structure.
*                    \n Contains fault code and fault string.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoProcessSoapError
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pMethodName,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Handle invocation of an unknown RPC method.
*
* This function is called when the ACS invokes an RPC method that is not recognized
* or supported by the CPE.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID of the unknown method.
*                    \n From the SOAP header.
* @param[in] pMethodName  - Name of the unknown method.
*                    \n RPC method name that is not supported.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoInvokeUnknownMethod
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pMethodName
    );

/**
* @brief Handle GetRPCMethods request from ACS.
*
* This function is called when the ACS invokes the GetRPCMethods method to discover
* the set of RPC methods supported by the CPE.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoGetRpcMethods
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

/**
* @brief Handle SetParameterValues request from ACS.
*
* This function is called when the ACS invokes the SetParameterValues method to modify
* one or more CPE parameter values.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] hParamValueArray  - Handle to array of parameter value structures.
*                    \n Contains parameter names, values, and types.
* @param[in] ulArraySize  - Size of the parameter value array.
*                    \n Number of parameters to set.
* @param[in] pParamKey  - Parameter key from ACS.
*                    \n Used to track configuration changes.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoSetParameterValues
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hParamValueArray,
        ULONG                       ulArraySize,
        char*                       pParamKey
    );

/**
* @brief Handle GetParameterValues request from ACS.
*
* This function is called when the ACS invokes the GetParameterValues method to retrieve
* the current values of one or more CPE parameters.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] pParamNameArray  - Array of parameter names to retrieve.
*                    \n Full parameter paths or partial paths.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoGetParameterValues
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        SLAP_STRING_ARRAY*          pParamNameArray
    );

/**
* @brief Handle GetParameterNames request from ACS.
*
* This function is called when the ACS invokes the GetParameterNames method to discover
* the parameters supported by the CPE.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] pParamPath  - Parameter path to search.
*                    \n Root path for parameter discovery.
* @param[in] bNextLevel  - Flag indicating search depth.
*                    \n TRUE for immediate children only, FALSE for entire subtree.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoGetParameterNames
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pParamPath,
        BOOL                        bNextLevel
    );

/**
* @brief Handle SetParameterAttributes request from ACS.
*
* This function is called when the ACS invokes the SetParameterAttributes method to modify
* the notification attributes of CPE parameters.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] hSetParamAttribArray  - Handle to array of parameter attribute structures.
*                    \n Contains parameter names and notification settings.
* @param[in] ulArraySize  - Size of the parameter attribute array.
*                    \n Number of parameters to modify.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoSetParameterAttributes
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSetParamAttribArray,
        ULONG                       ulArraySize
    );

/**
* @brief Handle GetParameterAttributes request from ACS.
*
* This function is called when the ACS invokes the GetParameterAttributes method to retrieve
* the notification attributes of CPE parameters.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] pParamNameArray  - Array of parameter names to query.
*                    \n Full parameter paths.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoGetParameterAttributes
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        SLAP_STRING_ARRAY*          pParamNameArray
    );

/**
* @brief Handle AddObject request from ACS.
*
* This function is called when the ACS invokes the AddObject method to create a new
* instance of a multi-instance object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] pObjectName  - Name of the object to create.
*                    \n Must be a multi-instance object path.
* @param[in] pParamKey  - Parameter key from ACS.
*                    \n Used to track configuration changes.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoAddObject
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pObjectName,
        char*                       pParamKey
    );

/**
* @brief Handle DeleteObject request from ACS.
*
* This function is called when the ACS invokes the DeleteObject method to remove
* an instance of a multi-instance object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] pObjectName  - Name of the object instance to delete.
*                    \n Must be a specific object instance path.
* @param[in] pParamKey  - Parameter key from ACS.
*                    \n Used to track configuration changes.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoDeleteObject
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pObjectName,
        char*                       pParamKey
    );

/**
* @brief Handle Download request from ACS.
*
* This function is called when the ACS invokes the Download method to instruct the CPE
* to download a file.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] hDownloadReq  - Handle to the download request structure.
*                    \n Contains URL, file type, size, and other download parameters.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoDownload
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hDownloadReq
    );

/**
* @brief Handle Reboot request from ACS.
*
* This function is called when the ACS invokes the Reboot method to instruct the CPE
* to reboot immediately.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] pCommandKey  - Command key from ACS.
*                    \n Used to identify the reboot operation.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoReboot
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pCommandKey
    );

/**
* @brief Set the reboot reason.
*
* This function is called to set the reboot reason before executing a reboot,
* storing it for the next boot cycle.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS CcspCwmpSetRebootReason(ANSC_HANDLE                 hThisObject);

/**
* @brief Handle ChangeDUState request from ACS.
*
* This function is called when the ACS invokes the ChangeDUState method to install,
* update, or uninstall deployment units (software modules).
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] hDownloadReq  - Handle to the ChangeDUState request structure.
*                    \n Contains operations and deployment unit details.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoChangeDUState
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hDownloadReq
    );

/**
* @brief Handle GetQueuedTransfers request from ACS.
*
* This function is called when the ACS invokes the GetQueuedTransfers method to retrieve
* information about queued and in-progress file transfers.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoGetQueuedTransfers
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

/**
* @brief Handle ScheduleInform request from ACS.
*
* This function is called when the ACS invokes the ScheduleInform method to request
* that the CPE send an Inform message after a specified delay.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] ulDelaySeconds  - Delay in seconds before sending Inform.
*                    \n Seconds from current time to schedule.
* @param[in] pCommandKey  - Command key for the scheduled Inform.
*                    \n String identifying the scheduled inform.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoScheduleInform
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ULONG                       ulDelaySeconds,
        char*                       pCommandKey
    );

/**
* @brief Handle SetVouchers request from ACS.
*
* This function is called when the ACS invokes the SetVouchers method to set option
* vouchers on the CPE for future validation.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] pVoucherList  - Array of voucher strings.
*                    \n Base64-encoded voucher data.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoSetVouchers
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        SLAP_STRING_ARRAY*          pVoucherList
    );

/**
* @brief Handle GetOptions request from ACS.
*
* This function is called when the ACS invokes the GetOptions method to retrieve
* option information from the CPE.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] pOptionName  - Name of the option to retrieve.
*                    \n Option identifier.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoGetOptions
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pOptionName
    );

/**
* @brief Handle Upload request from ACS.
*
* This function is called when the ACS invokes the Upload method to instruct the CPE
* to upload a file to a specified location.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
* @param[in] hUploadReq  - Handle to the upload request structure.
*                    \n Contains URL, file type, and other upload parameters.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoUpload
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hUploadReq
    );

/**
* @brief Handle FactoryReset request from ACS.
*
* This function is called when the ACS invokes the FactoryReset method to instruct the CPE
* to reset to factory default settings and reboot.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID from the SOAP header.
*                    \n Used to correlate request and response.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpsoMcoFactoryReset
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );


/**
* @brief Get the CWMP data type of a parameter.
*
* This function is called to retrieve the CWMP data type of a specified parameter
* for proper type handling in RPC method responses.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Session Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamName  - Name of the parameter.
*                    \n Full parameter path.
*
* @return The CWMP data type.
* @retval CCSP_CWMP_TR069_DATA_TYPE_* constant indicating the data type.
*
*/
ULONG
CcspCwmpsoMcoGetParamDataType
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName
    );

#endif

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

    module:	ccsp_cwmp_sesso_interface.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This wrapper file defines all the platform-independent
        functions and macros for the CCSP CWMP Wmp Session Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang
        Kang Quan

    ---------------------------------------------------------------

    revision:

        09/02/05    initial revision.
        06/21/11    decouple TR-069 PA from Data Model Manager
                    and make it work with CCSP architecture.
        10/12/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_SESSO_INTERFACE_
#define  _CCSP_CWMP_SESSO_INTERFACE_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_co_interface.h"
#include "ansc_co_external_api.h"
#include "slap_definitions.h"
#include "ccsp_cwmp_properties.h"
#include "ccsp_cwmp_ifo_mco.h"


/***********************************************************
         CCSP CWMP SESSION COMPONENT OBJECT DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the object mapper object definition.
 */
#define  CCSP_CWMPSO_MAX_EVENT_NUMBER                64
#define  CCSP_CWMPSO_MAX_PARAM_NUMBER                128
#define  CCSP_CWMPSO_MAX_CALL_RETRY_TIMES            3

#define  CCSP_CWMPSO_RPCCALL_TIMEOUT                 45          /* in seconds */
#define  CCSP_CWMPSO_SESSION_TIMEOUT                 60          /* in seconds */
#define  CCSP_CWMPSO_SESSION_RETRY_INTERVAL          10          /* in seconds */

#define  CCSP_CWMPSO_SESSION_STATE_idle              0
#define  CCSP_CWMPSO_SESSION_STATE_connectNow        1
#define  CCSP_CWMPSO_SESSION_STATE_connected         2
#define  CCSP_CWMPSO_SESSION_STATE_informed          3
#define  CCSP_CWMPSO_SESSION_STATE_disconnectNow     4
#define  CCSP_CWMPSO_SESSION_STATE_abort             5
#define  CCSP_CWMPSO_SESSION_STATE_timeout           6
#define  CCSP_CWMPSO_SESSION_STATE_reconnect         7

#define  CCSP_CWMPSO_EVENTCODE_ValueChange           4
#define  CCSP_CWMPSO_EVENTCODE_ConnectionRequest     6

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support),
 * we have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */
/**
 * @brief Get a context handle from the CWMP Session object.
 *
 * This function pointer typedef defines the callback interface for retrieving context handles
 * from the CWMP Session.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return Handle to the requested context object.
 * @return Handle to the requested context object on success.
 * @return NULL if not available.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPSESSO_GET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set a context handle in the CWMP Session object.
 *
 * This function pointer typedef defines the callback interface for setting context handles in the CWMP Session.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 * @param[in] hContext    - Handle to the context object to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Context handle set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_SET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hContext
    );

/**
 * @brief Get an interface handle from the CWMP Session object.
 *
 * This function pointer typedef defines the callback interface for retrieving interface handles
 * from the CWMP Session. Used to get handles to interface objects such as the Management Client
 * Operation (MCO) interface.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return Handle to the requested interface object.
 * @retval Handle to the requested interface object on success.
 * @retval NULL if not available.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPSESSO_GET_IF)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set an interface handle in the CWMP Session object.
 *
 * This function pointer typedef defines the callback interface for setting interface handles in the CWMP Session.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 * @param[in] hInterface  - Handle to the interface object to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Interface handle set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_SET_IF)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hInterface
    );

/**
 * @brief Get a name string from the CWMP Session object.
 *
 * This function pointer typedef defines the callback interface for retrieving name strings
 * from the CWMP Session.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return Pointer to the name string.
 * @retval Pointer to the name string on success.
 * @retval NULL if not available.
 *
 */
typedef  char*
(*PFN_CWMPSESSO_GET_NAME)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set a name string in the CWMP Session object.
 *
 * This function pointer typedef defines the callback interface for setting name strings
 * in the CWMP Session.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 * @param[in] pName       - Pointer to the name string to set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Name string set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_SET_NAME)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
 * @brief Get the property configuration from the CWMP Session object.
 *
 * This function pointer typedef defines the callback interface for retrieving the property
 * configuration structure from the CWMP Session. Properties include session-specific settings
 * and operational parameters.
 *
 * @param[in]  hThisObject - Handle to the CWMP Session object instance.
 * @param[out] hProperty   - Handle to the property structure to be filled with current property values.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Property configuration retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_GET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Set the property configuration in the CWMP Session object.
 *
 * This function pointer typedef defines the callback interface for setting the property
 * configuration structure in the CWMP Session.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 * @param[in] hProperty   - Handle to the property structure containing new property values to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Property configuration set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_SET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Reset the CWMP Session object to initial state.
 *
 * This function pointer typedef defines the callback interface for resetting the CWMP Session object.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Session reset successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_RESET)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Acquire access lock for the CWMP Session object.
 *
 * This function pointer typedef defines the callback interface for acquiring the access lock
 * to the CWMP Session object.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Access lock acquired successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_ACQ_ACCESS)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Release access lock for the CWMP Session object.
 *
 * This function pointer typedef defines the callback interface for releasing the access lock
 * on the CWMP Session object.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Access lock released successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_REL_ACCESS)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Invoke a timer callback in the CWMP Session object.
 *
 * This function pointer typedef defines the callback interface for timer invocation operations.
 * Used for session timer callbacks, retry timer callbacks, and delayed active notification timer.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Timer callback invoked successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_INVOKE)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Check if the session is connected to the ACS.
 *
 * This function pointer typedef defines the callback interface for checking whether the CWMP
 * Session has an active connection to the ACS.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return Boolean indicating connection status.
 * @retval TRUE  - Session is connected to the ACS.
 * @retval FALSE - Session is not connected to the ACS.
 *
 */
typedef  BOOL
(*PFN_CWMPSESSO_IS_CONNECTED)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Connect the session to the ACS.
 *
 * This function pointer typedef defines the callback interface for establishing a connection
 * to the ACS.  Connection uses ACS URL from the CPE Controller configuration.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Connection to ACS established successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_CONNECT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Close the connection to the ACS.
 *
 * This function pointer typedef defines the callback interface for closing the active connection
 * to the ACS. Called when both CPE and ACS have no more requests to exchange.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Connection to ACS closed successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_CLOSE_CONN)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Reboot the CPE device.
 *
 * This function pointer typedef defines the callback interface for initiating a CPE reboot.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Reboot initiated successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_REBOOT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Perform session operations.
 *
 * This function pointer typedef defines the callback interface for performing general session operations.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Session operations performed successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_PERFORM)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Add a CWMP event to the session's event queue.
 *
 * This function pointer typedef defines the callback interface for adding a CWMP event to the
 * session for inclusion in the next Inform method call to ACS.
 *
 * @param[in] hThisObject  - Handle to the CWMP Session object instance.
 * @param[in] hCwmpEvent   - Handle to the CWMP event structure containing event code and command key.
 * @param[in] bConnectNow  - Boolean flag indicating if immediate connection is required.
 *                           TRUE = Connect to ACS immediately, FALSE = Queue event for next session.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Event added successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_ADD_EVENT)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCwmpEvent,
        BOOL                        bConnectNow
    );

/**
 * @brief Discard a specific CWMP event from the session's event queue.
 *
 * This function pointer typedef defines the callback interface for removing a specific event
 * from the session's event queue by event code.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 * @param[in] EventCode   - Event code to discard.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Event discarded successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_DISCARD_EVENT)
    (
        ANSC_HANDLE                 hThisObject,
        int                         EventCode
    );

/**
 * @brief Save the session's events to persistent storage.
 *
 * This function pointer typedef defines the callback interface for persisting queued events
 * to non-volatile storage. This ensures events are not lost across reboots or power failures
 * and will be redelivered when the CPE next connects to the ACS.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Events saved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_SAVE_EVENT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Delete all items from a session queue.
 *
 * This function pointer typedef defines the callback interface for deleting all items from
 * a session queue. Used by DelAllEvents (clears event queue) and DelAllParameters (clears
 * modified parameter queue).
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - All items deleted successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_DEL_ALL)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Add a modified parameter to the session's parameter queue.
 *
 * This function pointer typedef defines the callback interface for adding a parameter that has
 * changed value to the session's modified parameter array.
 *
 * @param[in] hThisObject   - Handle to the CWMP Session object instance.
 * @param[in] pParamName    - Parameter name that was modified.
 * @param[in] pParamValue   - New value of the parameter as a string.
 * @param[in] CwmpDataType  - CWMP data type of the parameter.
 * @param[in] bConnectNow   - Boolean flag indicating if immediate connection is required.
 *                            TRUE = Connect to ACS immediately, FALSE = Queue parameter for next session.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Modified parameter added successfully.
 * @retval ANSC_STATUS_RESOURCES - Failed due to resource constraint.
 * @retval ANSC_STATUS_FAILURE - Failed to added modified parameter.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_ADD_PARAM)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName,
        char*                       pParamValue,
        ULONG                       CwmpDataType,
        BOOL                        bConnectNow
    );

/**
 * @brief Get the list of RPC methods supported by the CPE.
 *
 * This function pointer typedef defines the callback interface for retrieving the list of
 * RPC methods supported by the CPE.
 *
 * @param[in]  hThisObject   - Handle to the CWMP Session object instance.
 * @param[out] ppMethodList  - Pointer to receive the SLAP string array containing supported method names.
 * @param[out] pulErrorCode  - Pointer to receive the error code if the operation fails.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Method list retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_GET_METHODS)
    (
        ANSC_HANDLE                 hThisObject,
        SLAP_STRING_ARRAY**         ppMethodList,
        PULONG                      pulErrorCode
    );

/**
 * @brief Send an Inform RPC to the ACS.
 *
 * This function pointer typedef defines the callback interface for sending an Inform RPC to
 * the ACS. The Inform method initiates every TR-069 session and reports device status, events,
 * parameter changes, and device capabilities.
 *
 * @param[in]  hThisObject  - Handle to the CWMP Session object instance.
 * @param[out] pulErrorCode - Pointer to receive the error code if the Inform operation fails.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Inform RPC sent successfully and response received.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_INFORM)
    (
        ANSC_HANDLE                 hThisObject,
        PULONG                      pulErrorCode
    );

/**
 * @brief Send a TransferComplete RPC to the ACS.
 *
 * This function pointer typedef defines the callback interface for sending a TransferComplete
 * RPC to notify the ACS that a file transfer (Download or Upload) has completed.
 *
 * @param[in]  hThisObject   - Handle to the CWMP Session object instance.
 * @param[in]  bIsDownload   - Boolean flag indicating transfer direction.
 *                             TRUE = Download completion, FALSE = Upload completion.
 * @param[in]  pCommandKey   - CommandKey argument passed to CPE in the Download or Upload method call that initiated the transfer.
 * @param[in]  hFault        - Handle to fault structure if transfer failed, or NULL on success.
 *                             Non-zero FaultCode indicates transfer failure.
 * @param[in]  hStartTime    - Handle to start time structure (date and time transfer was started in UTC).
 * @param[in]  hCompleteTime - Handle to completion time structure (date and time transfer completed in UTC).
 * @param[out] pulErrorCode  - Pointer to receive the error code if the operation fails.
 * @param[in]  bAddEventCode - Boolean flag indicating if event code shall be added into session.
 *                             TRUE = Add event, FALSE = Skip event addition.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - TransferComplete RPC sent successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_TRANSFER_COMP)
    (
        ANSC_HANDLE                 hThisObject,
		BOOL						bIsDownload,
        char*                       pCommandKey,        /* 'CommentKey' argument passed in Download() or Upload() */
        ANSC_HANDLE                 hFault,             /* non-zero FaultCode is specified if transfer failed     */
        ANSC_HANDLE                 hStartTime,         /* the date and time transfer was started in UTC          */
        ANSC_HANDLE                 hCompleteTime,      /* the date and time transfer compoleted in UTC           */
        PULONG                      pulErrorCode,
        BOOL                        bAddEventCode       /* if event code(s) shall be added into session */
    );

/**
 * @brief Send an AutonomousTransferComplete RPC to the ACS.
 *
 * This function pointer typedef defines the callback interface for sending an AutonomousTransferComplete
 * RPC to the ACS. This informs the ACS of autonomous file transfers (downloads or uploads) initiated
 * by the CPE without explicit ACS instruction.
 *
 * @param[in]  hThisObject     - Handle to the CWMP Session object instance.
 * @param[in]  bIsDownload     - Boolean flag indicating transfer direction.
 *                               TRUE = Autonomous download, FALSE = Autonomous upload.
 * @param[in]  hFault          - Handle to fault structure if transfer failed, or NULL on success.
 * @param[in]  hStartTime      - Handle to start time structure (date and time transfer was started in UTC).
 * @param[in]  hCompleteTime   - Handle to completion time structure (date and time transfer completed in UTC).
 * @param[in]  AnnounceURL     - Announce URL where CPE discovered the file.
 * @param[in]  TransferURL     - Actual URL from which file was transferred.
 * @param[in]  FileType        - File type identifier.
 * @param[in]  FileSize        - Size of transferred file in bytes.
 * @param[in]  TargetFileName  - Target filename on CPE filesystem.
 * @param[out] pulErrorCode    - Pointer to receive the error code if the operation fails.
 * @param[in]  bAddEventCode   - Boolean flag indicating if event code shall be added into session.
 *                               TRUE = Add event, FALSE = Skip event addition (when PA tries to redeliver this RPC).
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - AutonomousTransferComplete RPC sent successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_AT_TRANSFER_COMP)
    (
        ANSC_HANDLE                 hThisObject,
		BOOL						bIsDownload,
        ANSC_HANDLE                 hFault,             /* non-zero FaultCode is specified if transfer failed     */
        ANSC_HANDLE                 hStartTime,         /* the date and time transfer was started in UTC          */
        ANSC_HANDLE                 hCompleteTime,      /* the date and time transfer compoleted in UTC           */
        char*                       AnnounceURL,
        char*                       TransferURL,
        char*                       FileType,
        unsigned int                FileSize,
        char*                       TargetFileName,
        PULONG                      pulErrorCode,
        BOOL                        bAddEventCode       /* if event code(s) shall be added into session */
    );

/**
 * @brief Send a DUStateChangeComplete RPC to the ACS.
 *
 * This function pointer typedef defines the callback interface for sending a DUStateChangeComplete
 * RPC to notify the ACS of Deployment Unit (DU) state change completion.
 *
 * @param[in]  hThisObject   - Handle to the CWMP Session object instance.
 * @param[in]  hDsccReq      - Handle to DU State Change Complete request structure.
 * @param[out] pulErrorCode  - Pointer to receive the error code if the operation fails.
 * @param[in]  bAddEventCode - Boolean flag indicating if event code shall be added into session.
 *                             TRUE = Add event, FALSE = Skip event addition.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - DUStateChangeComplete RPC sent successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_DUSC_COMP)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hDsccReq,
        PULONG                      pulErrorCode,
        BOOL                        bAddEventCode       /* if event code(s) shall be added into session */
    );

/**
 * @brief Send an AutonomousDUStateChangeComplete RPC to the ACS.
 *
 * This function pointer typedef defines the callback interface for sending an AutonomousDUStateChangeComplete
 * RPC to notify the ACS of autonomous Deployment Unit (DU) state changes.
 *
 * @param[in]  hThisObject   - Handle to the CWMP Session object instance.
 * @param[in]  hAdsccReq     - Handle to Autonomous DU State Change Complete request structure.
 * @param[out] pulErrorCode  - Pointer to receive the error code if the operation fails.
 * @param[in]  bAddEventCode - Boolean flag indicating if event code shall be added into session.
 *                             TRUE = Add event, FALSE = Skip event addition.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - AutonomousDUStateChangeComplete RPC sent successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_AT_DUSC_COMP)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hAdsccReq,
        PULONG                      pulErrorCode,
        BOOL                        bAddEventCode       /* if event code(s) shall be added into session */
    );

/**
 * @brief Send a Kicked RPC to the ACS.
 *
 * This function pointer typedef defines the callback interface for sending a Kicked RPC to the ACS.
 * This notification is sent when the CPE has been "kicked" off its current session by another entity
 * attempting to establish a connection request.
 *
 * @param[in]  hThisObject - Handle to the CWMP Session object instance.
 * @param[in]  pCommand    - Command string that initiated the kick operation. Specifies a generic argument
 *                           that may be used by the server for identification or other purposes.
 * @param[in]  pReferer    - Referer string identifying the source of the kick request. Specifies the content
 *                           of the "Referer" HTTP header sent to the CPE when it was kicked.
 * @param[in]  pArg        - Argument string with additional kick operation parameters. Specifies a generic argument
 *                           that may be used by the server for identification or other purposes.
 * @param[in]  pNext       - Next action string indicating what should follow the kick. Specifies the URL the server
 *                           should return in the method response under normal conditions.
 * @param[out] ppNextUrl   - Pointer to receive the next URL string for session continuation, or NULL.
 *                           Returns the next URL the user's browser should be redirected to.
 * @param[out] pulErrorCode - Pointer to receive the error code if the operation fails.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Kicked RPC sent successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_KICKED)
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
 * @brief Send a RequestDownload RPC to the ACS.
 *
 * This function pointer typedef defines the callback interface for sending a RequestDownload
 * RPC to request the ACS initiate a file download to the CPE.
 *
 * @param[in]  hThisObject         - Handle to the CWMP Session object instance.
 * @param[in]  pFileType           - File type string identifier.
 * @param[in]  hFileTypeArgArray   - Handle to array of file type argument structures, or NULL if none. Specifies the array
 *                                   of zero or more additional arguments, where each argument is a structure of name-value pairs.
 * @param[in]  ulArraySize         - Size of the file type argument array. Specifies the number of name-value
 *                                   pairs in the 'hFileTypeArgArray' argument.
 * @param[out] pulErrorCode        - Pointer to receive the error code if the operation fails.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - RequestDownload RPC sent successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_REQ_DOWNLOAD)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pFileType,
        ANSC_HANDLE                 hFileTypeArgArray,
        ULONG                       ulArraySize,
        PULONG                      pulErrorCode
    );

/**
 * @brief Receive and process a SOAP message from the ACS.
 *
 * This function pointer typedef defines the callback interface for receiving and processing SOAP
 * messages from the ACS connection.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 * @param[in] pMessage    - SOAP message string received from the ACS. Must be a valid XML SOAP envelope.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - SOAP message processed successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_RECV)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pMessage
    );

/**
 * @brief Notify that the CWMP session has closed.
 *
 * This function pointer typedef defines the callback interface for notifying the CPE Controller
 * that the CWMP session with the ACS has been closed.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Session closed notification completed successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_NOTIFY)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Asynchronously process CWMP session tasks.
 *
 * This function pointer typedef defines the callback interface for asynchronous processing of
 * CWMP session tasks in a separate thread. This task is created to stream-line SOAP requests and responses
 * and construct SOAP messages sent to the ACS.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Async processing task completed successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_ASYNC_PROCESS)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Perform session timer action operations.
 *
 * This function pointer typedef defines the callback interface for performing timer-related
 * actions on the CWMP session. Actions include StartRetryTimer (schedule session retry after failure),
 * StopRetryTimer (cancel pending retry), and StopDelayedActiveNotifTimer (cancel delayed active
 * notification timer). Used for managing session timing behavior and retry logic.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Timer action completed successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_ACTION)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Cancel the session retry delay timer.
 *
 * This function pointer typedef defines the callback interface for canceling the retry delay timer
 * and optionally initiating an immediate connection to the ACS. Used when external events require
 * immediate session establishment instead of waiting for the scheduled retry interval.
 *
 * @param[in] hThisObject   - Handle to the CWMP Session object instance.
 * @param[in] bConnectAgain - Boolean flag indicating whether to connect immediately after canceling retry.
 *                            TRUE = Connect to ACS immediately, FALSE = Only cancel retry timer.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Retry delay canceled successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSESSO_CANCEL_RETRY)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bConnectAgain
    );

/**
 * @brief Check if an Inform RPC is pending.
 *
 * This function pointer typedef defines the callback interface for checking whether an Inform RPC
 * is pending for transmission to the ACS. Used to check if the session has to send inform immediately,
 * probably due to an event has been generated.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance.
 *
 * @return Boolean indicating if Inform is pending.
 * @retval TRUE  - Inform RPC is pending, session should be initiated.
 * @retval FALSE - No Inform pending, no immediate session required.
 *
 */
typedef  BOOL
(*PFN_CWMPSESSO_INF_PENDING)
    (
        ANSC_HANDLE                 hThisObject
    );


/*
 * All transaction sessions MUST begin with an Inform message from the CPE contained in the initial
 * HTTP post. This serves to initiate the set of transactions and communicate the limitations of
 * the CPE with regard to message encoding. The session ceases when both the ACS and CPE have no
 * more requests to send, no responses remain due from either the ACS or the CPE. At such time, the
 * CPE may close the connection.
 *
 * No more than one transaction session between a CPE and its associated ACS may exist at a time.
 */
#define  CCSP_CWMP_SESSION_CLASS_CONTENT                                                    \
    /* duplication of the base object class content */                                      \
    ANSCCO_CLASS_CONTENT                                                                    \
    /* start of object class content */                                                     \
    ANSC_HANDLE                     hSessionTimerObj;                                       \
    ANSC_HANDLE                     hSessionTimerIf;                                        \
    ANSC_HANDLE                     hRetryTimerObj;                                         \
    ANSC_HANDLE                     hRetryTimerIf;                                          \
	ANSC_HANDLE						hDelayedActiveNotifTimerObj;							\
	ANSC_HANDLE						hDelayedActiveNotifTimerIf;								\
	BOOL							bDelayedActiveNotifTimerScheduled;						\
    ANSC_HANDLE                     hCcspCwmpAcsConnection;                                 \
    ANSC_HANDLE                     hCcspCwmpMcoIf;                                         \
    ANSC_HANDLE                     hCcspCwmpCpeController;                                 \
    ANSC_HANDLE                     hCcspCwmpProcessor;                                     \
    ULONG                           AsyncTaskCount;                                         \
    ANSC_LOCK                       AccessLock;                                             \
    BOOL                            bActive;                                                \
                                                                                            \
    ULONG                           GlobalRequestID;                                        \
    ULONG                           SessionState;                                           \
    ULONG                           CpeMaxEnvelopes;                                        \
    ULONG                           AcsMaxEnvelopes;                                        \
    ULONG                           ActiveResponses;                                        \
    BOOL                            bHoldRequests;                                          \
    BOOL                            bNoMoreRequests;                                        \
    BOOL                            bLastEmptyRequestSent;                                  \
                                                                                            \
    ULONG                           EventCount;                                             \
    ANSC_HANDLE                     EventArray[CCSP_CWMPSO_MAX_EVENT_NUMBER];               \
    ULONG                           RetryCount;                                             \
    ULONG                           ModifiedParamCount;                                     \
    char*                           ModifiedParamArray[CCSP_CWMPSO_MAX_PARAM_NUMBER];       \
    char*                           ModifiedParamValueArray[CCSP_CWMPSO_MAX_PARAM_NUMBER];  \
    ULONG                           ModifiedParamTypeArray[CCSP_CWMPSO_MAX_PARAM_NUMBER];   \
                                                                                            \
    BOOL                            bInformWhenActive;                                      \
                                                                                            \
    QUEUE_HEADER                    AsyncReqQueue;                                          \
    ANSC_LOCK                       AsyncReqQueueLock;                                      \
    QUEUE_HEADER                    SavedReqQueue;                                          \
    ANSC_LOCK                       SavedReqQueueLock;                                      \
    QUEUE_HEADER                    AsyncRepQueue;                                          \
    ANSC_LOCK                       AsyncRepQueueLock;                                      \
    ANSC_EVENT                      AsyncProcessEvent;                                      \
																							\
    PFN_CWMPSESSO_GET_CONTEXT       GetCcspCwmpAcsConnection;                               \
    PFN_CWMPSESSO_GET_IF            GetCcspCwmpMcoIf;                                       \
    PFN_CWMPSESSO_GET_CONTEXT       GetCcspCwmpCpeController;                               \
    PFN_CWMPSESSO_SET_CONTEXT       SetCcspCwmpCpeController;                               \
    PFN_CWMPSESSO_GET_CONTEXT       GetCcspCwmpProcessor;                                   \
    PFN_CWMPSESSO_SET_CONTEXT       SetCcspCwmpProcessor;                                   \
    PFN_CWMPSESSO_RESET             Reset;                                                  \
                                                                                            \
    PFN_CWMPSESSO_ACQ_ACCESS        AcqAccess;                                              \
    PFN_CWMPSESSO_REL_ACCESS        RelAccess;                                              \
    PFN_CWMPSESSO_INVOKE            SessionTimerInvoke;                                     \
    PFN_CWMPSESSO_INVOKE            SessionRetryTimerInvoke;                                \
    PFN_CWMPSESSO_INVOKE            DelayedActiveNotifTimerInvoke;                          \
    PFN_CWMPSESSO_ACTION            StartRetryTimer;                                        \
    PFN_CWMPSESSO_ACTION            StopRetryTimer;                                         \
    PFN_CWMPSESSO_ACTION            StopDelayedActiveNotifTimer;                            \
                                                                                            \
    PFN_CWMPSESSO_IS_CONNECTED      IsAcsConnected;                                         \
    PFN_CWMPSESSO_CONNECT           ConnectToAcs;                                           \
    PFN_CWMPSESSO_CLOSE_CONN        CloseConnection;                                        \
                                                                                            \
    PFN_CWMPSESSO_ADD_EVENT         AddCwmpEvent;                                           \
    PFN_CWMPSESSO_DISCARD_EVENT     DiscardCwmpEvent;                                       \
    PFN_CWMPSESSO_DEL_ALL           DelAllEvents;                                           \
    PFN_CWMPSESSO_ADD_PARAM         AddModifiedParameter;                                   \
    PFN_CWMPSESSO_DEL_ALL           DelAllParameters;                                       \
    PFN_CWMPSESSO_SAVE_EVENT        SaveCwmpEvent;                                          \
                                                                                            \
    PFN_CWMPSESSO_GET_METHODS       GetRpcMethods;                                          \
    PFN_CWMPSESSO_INFORM            Inform;                                                 \
    PFN_CWMPSESSO_TRANSFER_COMP     TransferComplete;                                       \
    PFN_CWMPSESSO_AT_TRANSFER_COMP  AutonomousTransferComplete;                             \
    PFN_CWMPSESSO_KICKED            Kicked;                                                 \
    PFN_CWMPSESSO_REQ_DOWNLOAD      RequestDownload;                                        \
                                                                                            \
    PFN_CWMPSESSO_RECV              RecvSoapMessage;                                        \
    PFN_CWMPSESSO_NOTIFY            NotifySessionClosed;                                    \
    PFN_CWMPSESSO_ASYNC_PROCESS     AsyncProcessTask;                                       \
                                                                                            \
    PFN_CWMPSESSO_CANCEL_RETRY      CancelRetryDelay;                                       \
                                                                                            \
    PFN_CWMPSESSO_DUSC_COMP         DUStateChangeComplete;                                  \
    PFN_CWMPSESSO_AT_DUSC_COMP      AutonomousDUStateChangeComplete;                        \
                                                                                            \
    PFN_CWMPSESSO_INF_PENDING       InformPending;                                          \
    /* end of object class content */                                                       \

typedef  struct
_CCSP_CWMP_SESSION_OBJECT
{
    CCSP_CWMP_SESSION_CLASS_CONTENT
}
CCSP_CWMP_SESSION_OBJECT,  *PCCSP_CWMP_SESSION_OBJECT;

#define  ACCESS_CCSP_CWMP_SESSION_OBJECT(p)          \
         ACCESS_CONTAINER(p, CCSP_CWMP_SESSION_OBJECT, Linkage)


/***********************************************************
       CCSP CWMP REQUEST/RESPONSE STRUCTURE DEFINITIONS
***********************************************************/

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

/*
 * On reception of SOAP requests from the ACS, the CPE MUST respond to each request in the order
 * they were received, where order is defined as described in section 3.4.1. This definition of
 * order places no constraint on whether multiple responses are sent in a single HTTP post (if the
 * ACS can accept more than one envelope), or distributed over multiple HTTP posts.
 *
 * To prevent deadlocks, the CPE MUST NOT hold off responding to an ACS request to wait for a res-
 * ponse from the ACS to an earlier CPE request.
 */
typedef  struct
_CCSP_CWMPSO_ASYNC_REQUEST
{
    SINGLE_LINK_ENTRY               Linkage;
    ANSC_STATUS                     CallStatus;
    ANSC_EVENT                      AsyncEvent;
    ULONG                           Method;
    char*                           MethodName;
    char*                           RequestID;
    char*                           SoapEnvelope;
    ANSC_HANDLE                     hSoapResponse;
}
CCSP_CWMPSO_ASYNC_REQUEST,  *PCCSP_CWMPSO_ASYNC_REQUEST;

#define  ACCESS_CCSP_CWMPSO_ASYNC_REQUEST(p)         \
         ACCESS_CONTAINER(p, CCSP_CWMPSO_ASYNC_REQUEST, Linkage)

#define  CcspCwmpsoAllocAsyncRequest(async_req)                                             \
         {                                                                                  \
            async_req =                                                                     \
                (PCCSP_CWMPSO_ASYNC_REQUEST)AnscAllocateMemory                              \
                        (                                                                   \
                            sizeof(CCSP_CWMPSO_ASYNC_REQUEST)                               \
                        );                                                                  \
                                                                                            \
            if ( async_req )                                                                \
            {                                                                               \
                async_req->CallStatus    = ANSC_STATUS_TIMEOUT;                             \
                async_req->Method        = CCSP_CWMP_METHOD_Unknown;                        \
                async_req->MethodName    = NULL;                                            \
                async_req->RequestID     = NULL;                                            \
                async_req->SoapEnvelope  = NULL;                                            \
                async_req->hSoapResponse = (ANSC_HANDLE)NULL;                               \
                                                                                            \
                AnscInitializeEvent(&async_req->AsyncEvent);                                \
                AnscResetEvent     (&async_req->AsyncEvent);                                \
            }                                                                               \
         }

#define  CcspCwmpsoSignalAsyncRequest(async_req, status)                                    \
         {                                                                                  \
            async_req->CallStatus = status;                                                 \
                                                                                            \
            AnscSetEvent(&async_req->AsyncEvent);                                           \
         }

#define  CcspCwmpsoFreeAsyncRequest(async_req)                                              \
         {                                                                                  \
            if ( async_req->MethodName )                                                    \
            {                                                                               \
                AnscFreeMemory(async_req->MethodName);                                      \
                                                                                            \
                async_req->MethodName = NULL;                                               \
            }                                                                               \
                                                                                            \
            if ( async_req->RequestID )                                                     \
            {                                                                               \
                AnscFreeMemory(async_req->RequestID);                                       \
                                                                                            \
                async_req->RequestID = NULL;                                                \
            }                                                                               \
                                                                                            \
            if ( async_req->SoapEnvelope )                                                  \
            {                                                                               \
                AnscFreeMemory(async_req->SoapEnvelope);                                    \
                                                                                            \
                async_req->SoapEnvelope = NULL;                                             \
            }                                                                               \
                                                                                            \
            if ( async_req->hSoapResponse )                                                 \
            {                                                                               \
                CcspCwmpFreeSoapResponse                                                    \
                    (                                                                       \
                        ((PCCSP_CWMP_SOAP_RESPONSE)async_req->hSoapResponse)                \
                    );                                                                      \
                                                                                            \
                async_req->hSoapResponse = (ANSC_HANDLE)NULL;                               \
            }                                                                               \
                                                                                            \
            AnscFreeEvent     (&async_req->AsyncEvent);                                     \
            AnscFreeMemory(async_req);                                                      \
         }

typedef  struct
_CCSP_CWMPSO_ASYNC_RESPONSE
{
    SINGLE_LINK_ENTRY               Linkage;
    ULONG                           Method;
    char*                           SoapEnvelope;
}
CCSP_CWMPSO_ASYNC_RESPONSE,  *PCCSP_CWMPSO_ASYNC_RESPONSE;

#define  ACCESS_CCSP_CWMPSO_ASYNC_RESPONSE(p)        \
         ACCESS_CONTAINER(p, CCSP_CWMPSO_ASYNC_RESPONSE, Linkage)

#define  CcspCwmpsoAllocAsyncResponse(async_rep)                                            \
         {                                                                                  \
            async_rep =                                                                     \
                (PCCSP_CWMPSO_ASYNC_RESPONSE)AnscAllocateMemory                             \
                        (                                                                   \
                            sizeof(CCSP_CWMPSO_ASYNC_RESPONSE)                              \
                        );                                                                  \
                                                                                            \
            if ( async_rep )                                                                \
            {                                                                               \
                async_rep->Method       = CCSP_CWMP_METHOD_Unknown;                         \
                async_rep->SoapEnvelope = NULL;                                             \
            }                                                                               \
         }

#define  CcspCwmpsoFreeAsyncResponse(async_rep)                                             \
         {                                                                                  \
            if ( async_rep->SoapEnvelope )                                                  \
            {                                                                               \
                AnscFreeMemory(async_rep->SoapEnvelope);                                    \
                                                                                            \
                async_rep->SoapEnvelope = NULL;                                             \
            }                                                                               \
                                                                                            \
            AnscFreeMemory(async_rep);                                                      \
         }

#endif
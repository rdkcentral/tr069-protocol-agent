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

    module:	ccsp_cwmp_proco_internal_api.h

        For CCSP CWMP protocol implementation,

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the internal functions provided by the CCSP CWMP Processor
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

        09/12/05    initial revision.
        10/13/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_PROCO_INTERNAL_API_
#define  _CCSP_CWMP_PROCO_INTERNAL_API_

#include "ccsp_message_bus.h"
#include "ccsp_base_api.h"
#include "ccsp_types.h"
#include "ccsp_tr069pa_mapper_def.h"

/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMPPO_STATES.C
***********************************************************/

/**
* @brief Get the CCSP CWMP CPE Controller handle.
*
* This function is called to retrieve the handle to the CCSP CWMP CPE Controller object
* associated with this CCSP CWMP Processor object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP CPE Controller.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmppoGetCcspCwmpCpeController
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the CCSP CWMP CPE Controller handle.
*
* This function is called to configure the handle to the CCSP CWMP CPE Controller object
* for this CCSP CWMP Processor object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hCpeController  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n Must be a valid CPE Controller handle.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSetCcspCwmpCpeController
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCpeController
    );

/**
* @brief Get the Initial Contact flag.
*
* This function is called to retrieve the Initial Contact flag status, which indicates
* if this is the first contact with the ACS after a reboot.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The Initial Contact flag status.
* @retval TRUE if this is the initial contact.
* @retval FALSE if this is not the initial contact.
*
*/
BOOL
CcspCwmppoGetInitialContact
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the Initial Contact flag.
*
* This function is called to configure the Initial Contact flag, which marks
* if this is the first contact with the ACS after a reboot.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bEnabled  - Initial Contact flag value.
*                    \n TRUE to mark as initial contact, FALSE otherwise.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSetInitialContact
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bEnabled
    );

/**
* @brief Get the Initial Contact Factory flag.
*
* This function is called to retrieve the Initial Contact Factory flag status, which indicates
* if this is the first contact with the ACS after a factory reset.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The Initial Contact Factory flag status.
* @retval TRUE if this is the initial contact after factory reset.
* @retval FALSE otherwise.
*
*/
BOOL
CcspCwmppoGetInitialContactFactory
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the Initial Contact Factory flag.
*
* This function is called to configure the Initial Contact Factory flag, which marks
* if this is the first contact with the ACS after a factory reset.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bEnabled  - Initial Contact Factory flag value.
*                    \n TRUE to mark as initial contact after factory reset, FALSE otherwise.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSetInitialContactFactory
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bEnabled
    );

/**
* @brief Check if CWMP is enabled.
*
* This function is called to check whether the CWMP (TR-069) protocol is currently enabled
* on the device.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The CWMP enabled status.
* @retval TRUE if CWMP is enabled.
* @retval FALSE if CWMP is disabled.
*
*/
BOOL
CcspCwmppoIsCwmpEnabled
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the ACS URL.
*
* This function is called to retrieve the URL of the Auto-Configuration Server (ACS)
* used for TR-069 communications.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the ACS URL string.
* @retval char* if the operation is successful.
*
*/
char*
CcspCwmppoGetAcsUrl
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the ACS URL.
*
* This function is called to configure the URL of the Auto-Configuration Server (ACS)
* used for TR-069 communications. It can be set manually or acquired from DHCP.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pString  - Pointer to the ACS URL string.
*                    \n Must be a valid HTTP or HTTPS URL.
* @param[in] bAcquiredFromDhcp  - Flag indicating if URL was acquired from DHCP.
*                    \n TRUE if from DHCP, FALSE if manually configured.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSetAcsUrl
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pString,
        BOOL                        bAcquiredFromDhcp
    );

/**
* @brief Get the ACS username.
*
* This function is called to retrieve the username used for HTTP authentication
* with the Auto-Configuration Server (ACS).
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the ACS username string.
* @retval char* if the operation is successful.
*
*/
char*
CcspCwmppoGetAcsUsername
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the ACS username.
*
* This function is called to configure the username used for HTTP authentication
* with the Auto-Configuration Server (ACS).
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pString  - Pointer to the ACS username string.
*                    \n Can be NULL to clear the username.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSetAcsUsername
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pString
    );

/**
* @brief Get the ACS password.
*
* This function is called to retrieve the password used for HTTP authentication
* with the Auto-Configuration Server (ACS).
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the ACS password string.
* @retval char* if the operation is successful.
*
*/
char*
CcspCwmppoGetAcsPassword
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the ACS password.
*
* This function is called to configure the password used for HTTP authentication
* with the Auto-Configuration Server (ACS).
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pString  - Pointer to the ACS password string.
*                    \n Can be NULL to clear the password.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSetAcsPassword
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pString
    );

/**
* @brief Get the Periodic Inform enabled status.
*
* This function is called to retrieve whether periodic inform messages to the ACS
* are currently enabled.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The periodic inform enabled status.
* @retval TRUE if periodic inform is enabled.
* @retval FALSE if periodic inform is disabled.
*
*/
BOOL
CcspCwmppoGetPeriodicInformEnabled
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the Periodic Inform enabled status.
*
* This function is called to enable or disable periodic inform messages to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bEnabled  - Periodic inform enabled flag.
*                    \n TRUE to enable periodic inform, FALSE to disable.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSetPeriodicInformEnabled
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bEnabled
    );

/**
* @brief Get the Periodic Inform interval.
*
* This function is called to retrieve the interval (in seconds) at which periodic
* inform messages are sent to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The periodic inform interval in seconds.
* @retval ULONG representing the interval value.
*
*/
ULONG
CcspCwmppoGetPeriodicInformInterval
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the Periodic Inform interval.
*
* This function is called to configure the interval (in seconds) at which periodic
* inform messages are sent to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] ulValue  - Periodic inform interval in seconds.
*                    \n Range: 1 to maximum ULONG value. Value of 0 is invalid.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSetPeriodicInformInterval
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulValue
    );

/**
* @brief Get the Periodic Inform time reference.
*
* This function is called to retrieve the time reference for periodic inform scheduling.
* This is used to calculate when the next periodic inform should be sent.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Handle to the periodic inform time structure.
* @retval ANSC_HANDLE representing the time structure.
*
*/
ANSC_HANDLE
CcspCwmppoGetPeriodicInformTime
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the Periodic Inform time reference.
*
* This function is called to configure the time reference for periodic inform scheduling.
* This is used to calculate when the next periodic inform should be sent.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hTime  - Handle to the time structure.
*                    \n Must be a valid time structure handle.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSetPeriodicInformTime
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hTime
    );

/**
* @brief Retrieve the object property.
*
* This function is called to retrieve the property configuration of the
* CCSP CWMP Processor object and copy it to the provided property structure.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[out] hProperty  - Handle to the property data structure to be filled.
*                    \n This structure will receive the current object property.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoGetProperty
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
* @brief Configure the object property.
*
* This function is called to configure the property of the CCSP CWMP Processor object
* using the provided property structure.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hProperty  - Handle to the property data structure.
*                    \n Contains the new property configuration to be applied.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSetProperty
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
* @brief Reset the object property to default values.
*
* This function is called to reset the property of the CCSP CWMP Processor object
* back to its default factory configuration.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoResetProperty
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Reset the CCSP CWMP Processor object.
*
* This function is called to reset the entire CCSP CWMP Processor object to its
* initial state, including all properties and runtime configurations.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoReset
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the CCSP CWMP MPA Interface handle.
*
* This function is called to retrieve the handle to the CCSP CWMP MPA (Management Protocol Adapter)
* Interface associated with this CCSP CWMP Processor object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP MPA Interface.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmppoGetCcspCwmpMpaIf
    (
        ANSC_HANDLE                 hThisObject
    );

/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMPPO_OPERATION.C
***********************************************************/

/**
* @brief Engage (activate) the CCSP CWMP Processor object.
*
* This function is called to engage the object activity and start CWMP operations.
* It sets up the environment and marks the processor as active.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bRestart  - Flag indicating if this is a restart operation.
*                    \n TRUE for restart, FALSE for initial engagement.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_NOT_READY if CPE Controller is not ready.
*
*/
ANSC_STATUS
CcspCwmppoEngage
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bRestart
    );

/**
* @brief Cancel (disengage) the CCSP CWMP Processor object activity.
*
* This function is called to cancel (deactivate) the CCSP CWMP Processor and stop
* all CWMP operations.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoCancel
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Setup the runtime environment for CWMP operations.
*
* This function is called to set up the runtime environment required for CWMP operations,
* including timer initialization and session preparation.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bRestart  - Flag indicating if this is a restart operation.
*                    \n TRUE for restart, FALSE for initial setup.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if environment setup fails.
*
*/
ANSC_STATUS
CcspCwmppoSetupEnv
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bRestart
    );

/**
* @brief Close the runtime environment for CWMP operations.
*
* This function is called to close and clean up the runtime environment used for CWMP operations,
* including stopping timers and releasing resources.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoCloseEnv
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Invoke the periodic timer handler.
*
* This function is called when the periodic timer expires to trigger periodic inform
* messages to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoPeriodicTimerInvoke
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Invoke the schedule timer handler.
*
* This function is called when the schedule timer expires to trigger scheduled inform
* messages to the ACS at a specific time.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoScheduleTimerInvoke
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Invoke the pending inform timer handler.
*
* This function is called when the pending inform timer expires to trigger deferred
* inform messages that were delayed due to various reasons.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoPendingInformTimerInvoke
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Save TransferComplete event to persistent storage.
*
* This function is called to save a TransferComplete event (Download or Upload) to
* persistent storage for delivery to the ACS in the next inform.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pCommandKey  - CommandKey associated with the transfer.
*                    \n String identifying the transfer operation.
* @param[in] hStartTime  - Handle to the start time structure.
*                    \n Time when transfer began.
* @param[in] hCompleteTime  - Handle to the complete time structure.
*                    \n Time when transfer completed.
* @param[in] bIsDownload  - Flag indicating transfer type.
*                    \n TRUE for Download, FALSE for Upload.
* @param[in] pFault  - Pointer to fault structure if transfer failed.
*                    \n NULL if transfer was successful.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSaveTransferComplete
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pCommandKey,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime,
        BOOL                        bIsDownload,
        PCCSP_CWMP_FAULT            pFault
    );

/**
* @brief Save ValueChange event to persistent storage.
*
* This function is called to save a ValueChange event for a parameter to persistent storage
* for delivery to the ACS in the next inform.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParameterName  - Name of the parameter that changed.
*                    \n Must be a full parameter name.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSaveValueChanged
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParameterName
    );

/**
* @brief Discard ValueChange event from persistent storage.
*
* This function is called to remove a saved ValueChange event for a specific parameter
* from persistent storage.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParameterName  - Name of the parameter whose value change event should be discarded.
*                    \n Must be a full parameter name.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoDiscardValueChanged
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParameterName
    );

/**
* @brief Load ValueChange events from persistent storage.
*
* This function is called to load all saved ValueChange events from persistent storage
* to be included in the next inform message to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoLoadValueChanged
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Load TransferComplete events from persistent storage.
*
* This function is called to load all saved TransferComplete events from persistent storage
* to be included in the next inform message to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoLoadTransferComplete
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Save AutonomousTransferComplete event to persistent storage.
*
* This function is called to save an AutonomousTransferComplete event (autonomous file transfer)
* to persistent storage (PSM) for delivery to the ACS in the next inform.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bIsDownload  - Flag indicating transfer direction.
*                    \n TRUE for Download, FALSE for Upload.
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
* @param[in] hFault  - Handle to fault structure if transfer failed.
*                    \n NULL if transfer was successful.
* @param[in] hStartTime  - Handle to the start time structure.
*                    \n Time when transfer began.
* @param[in] hCompleteTime  - Handle to the complete time structure.
*                    \n Time when transfer completed.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if processor is not active.
*
*/
ANSC_STATUS
CcspCwmppoSaveAutonomousTransferComplete
    (
        ANSC_HANDLE                 hThisObject,
		BOOL						bIsDownload,
        char*                       AnnounceURL,
        char*                       TransferURL,
        char*                       FileType,
        unsigned int                FileSize,
        char*                       TargetFileName,
        ANSC_HANDLE                 hFault,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime
    );

/**
* @brief Load AutonomousTransferComplete events from persistent storage.
*
* This function is called to load all saved AutonomousTransferComplete events from persistent
* storage to be included in the next inform message to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoLoadAutonomousTransferComplete
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Save DUStateChangeComplete event to persistent storage.
*
* This function is called to save a DUStateChangeComplete event (Deployment Unit state change)
* to persistent storage (PSM) for delivery to the ACS in the next inform.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hDsccReq  - Handle to DUStateChangeComplete request structure.
*                    \n Contains deployment unit operation details and results.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if processor is not active.
*
*/
ANSC_STATUS
CcspCwmppoSaveDUStateChangeComplete
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hDsccReq
    );

/**
* @brief Load DUStateChangeComplete events from persistent storage.
*
* This function is called to load all saved DUStateChangeComplete events from persistent
* storage to be included in the next inform message to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoLoadDUStateChangeComplete
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Save AutonomousDUStateChangeComplete event to persistent storage.
*
* This function is called to save an AutonomousDUStateChangeComplete event (autonomous deployment
* unit state change) to persistent storage (PSM) for delivery to the ACS in the next inform.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hAdsccReq  - Handle to AutonomousDUStateChangeComplete request structure.
*                    \n Contains autonomous deployment unit state change details.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if processor is not active.
*
*/
ANSC_STATUS
CcspCwmppoSaveAutonomousDUStateChangeComplete
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hAdsccReq
    );

/**
* @brief Load AutonomousDUStateChangeComplete events from persistent storage.
*
* This function is called to load all saved AutonomousDUStateChangeComplete events from
* persistent storage to be included in the next inform message to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoLoadAutonomousDUStateChangeComplete
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Redeliver undelivered events to the ACS.
*
* This function is called to attempt redelivery of events that were not successfully
* delivered to the ACS in previous inform sessions.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoRedeliverEvents
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get all undelivered events and add to session.
*
* This function is called to retrieve all types of undelivered events (TransferComplete,
* AutonomousTransferComplete, DUStateChangeComplete, AutonomousDUStateChangeComplete)
* from persistent storage and add them to the specified WMP session for delivery to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hWmpSession  - Handle to the WMP Session object.
*                    \n Session where undelivered events will be added.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoGetUndeliveredEvents
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
* @brief Get undelivered TransferComplete events.
*
* This function retrieves undelivered TransferComplete events from persistent storage
* and adds them to the specified WMP session for delivery to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hWmpSession  - Handle to the WMP Session object.
*                    \n Session where events will be added.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoGetUndeliveredTcEvents
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
* @brief Get undelivered AutonomousTransferComplete events.
*
* This function retrieves undelivered AutonomousTransferComplete events from persistent storage
* and adds them to the specified WMP session for delivery to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hWmpSession  - Handle to the WMP Session object.
*                    \n Session where events will be added.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoGetUndeliveredAtcEvents
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
* @brief Get undelivered DUStateChangeComplete events.
*
* This function retrieves undelivered DUStateChangeComplete events from persistent storage
* and adds them to the specified WMP session for delivery to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hWmpSession  - Handle to the WMP Session object.
*                    \n Session where events will be added.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoGetUndeliveredDscEvents
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
* @brief Get undelivered AutonomousDUStateChangeComplete events.
*
* This function retrieves undelivered AutonomousDUStateChangeComplete events from persistent storage
* and adds them to the specified WMP session for delivery to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hWmpSession  - Handle to the WMP Session object.
*                    \n Session where events will be added.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoGetUndeliveredAdscEvents
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
* @brief Discard all undelivered events.
*
* This function is called to remove all undelivered events from persistent storage,
* clearing the queue of events pending delivery to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoDiscardUndeliveredEvents
    (
        ANSC_HANDLE                 hThisObject
    );

/***********************************************************
      FUNCTIONS IMPLEMENTED IN CCSP_CWMPPO_MANAGEMENT.C
***********************************************************/

/**
* @brief Acquire a WMP (CWMP) session.
*
* This function is called to acquire access to the first active WMP session in the queue.
* The session is used to manage the CWMP protocol state machine and transactions with the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Handle to the acquired WMP Session.
* @retval ANSC_HANDLE if successful.
* @retval NULL if no session is available.
*
*/
ANSC_HANDLE
CcspCwmppoAcqWmpSession
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Acquire a WMP session (variant 2).
*
* This function creates or acquires a WMP session object for communication with the ACS.
* This is an alternate acquisition method with simplified parameters.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Handle to the acquired WMP Session
* @retval Handle to the acquired WMP Session on success.
* @retval NULL if acquisition fails.
*
*/
ANSC_HANDLE
CcspCwmppoAcqWmpSession2
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Acquire a WMP session (variant 3).
*
* This function creates or acquires a WMP session object for communication with the ACS.
* This is another alternate acquisition method with simplified parameters.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Handle to the acquired WMP Session.
* @retval Handle to the acquired WMP Session on success.
* @retval NULL if acquisition fails.
*
*/
ANSC_HANDLE
CcspCwmppoAcqWmpSession3
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Release a WMP session.
*
* This function releases a previously acquired WMP session, freeing it for reuse
* or cleanup. The session remains in the session pool.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hWmpSession  - Handle to the WMP Session to release.
*                    \n Session previously acquired via AcqWmpSession.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoRelWmpSession
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
* @brief Delete a WMP session.
*
* This function permanently removes a WMP session from the session pool, freeing
* all associated resources.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hWmpSession  - Handle to the WMP Session to delete.
*                    \n Session to be removed from the session pool.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoDelWmpSession
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
* @brief Delete all WMP sessions.
*
* This function removes all active WMP sessions from the session pool, freeing
* all associated resources and clearing the session queue.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoDelAllSessions
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the count of active WMP sessions.
*
* This function returns the number of WMP sessions that are currently active
* (not in idle state) in the session pool.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bQueueLockAcquired  - Flag indicating if queue lock is already held.
*                    \n TRUE if lock is already acquired, FALSE otherwise.
*
* @return Number of active WMP sessions.
*
*/
ULONG
CcspCwmppoGetActiveWmpSessionCount
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bQueueLockAcquired
    );

/**
* @brief Initialize the parameter attribute cache.
*
* This function initializes the cache used to store TR-069 parameter attributes
* (notification, access control) for efficient access and management.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoInitParamAttrCache
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Push all value change notifications to backend.
*
* This function pushes all pending value change notifications to the backend
* data model for processing and storage.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoPushAllVcToBackend
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Update the parameter attribute cache.
*
* This function updates the cached parameter notification attributes with new values
* from an array of parameter attributes. It manages both the in-memory cache and
* persistent storage (PSM) for notification settings.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hParamAttrArray  - Handle to an array of parameter attribute structures.
*                    \n Contains parameter names and their notification attributes.
* @param[in] ulParamCount  - Number of parameters in the attribute array.
*                    \n Size of the hParamAttrArray.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if PSM operations fail.
*
*/
ANSC_STATUS
CcspCwmppoUpdateParamAttrCache
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hParamAttrArray,
        ULONG                       ulParamCount
    );

/**
* @brief Check the parameter attribute cache for notification setting.
*
* This function checks the cached parameter attributes to retrieve the notification
* setting for a specific parameter or its parent hierarchy.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamName  - Name of the parameter to check.
*                    \n Full parameter name path.
*
* @return Notification attribute value.
* @retval CCSP_CWMP_NOTIFICATION_xxx, parameter attribute
*
*/
ULONG
CcspCwmppoCheckParamAttrCache
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName
    );

/**
* @brief Synchronize namespaces with Component Registrar.
*
* This function synchronizes the parameter namespace information with the CCSP
* Component Registrar (CR) to ensure consistent data model view.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bRemoteOnly  - Flag indicating whether to sync only remote namespaces.
*                    \n TRUE to sync only remote subsystems.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSyncNamespacesWithCR
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bRemoteOnly
    );

/**
* @brief Synchronize a remote namespace.
*
* This function synchronizes a specific remote namespace parameter with the local
* data model cache based on parameter information.
*
* @param[in] pContext  - Context handle for the operation.
*                    \n Context providing necessary state information.
* @param[in] pParamInfo  - Pointer to parameter information structure.
*                    \n Contains details about the parameter to synchronize.
*
* @return The status of operation.
* @retval TRUE if synchronization is successful.
* @retval FALSE otherwise.
*
*/
CCSP_BOOL
CcspCwmppoSyncRemoteNamespace
    (
        CCSP_HANDLE                 pContext,
        PCCSP_TR069_PARAM_INFO      pParamInfo
    );

/**
* @brief Check if there is a pending inform message.
*
* This function checks whether there is a pending inform message that needs to be
* sent to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of operation.
* @retval TRUE if there is a pending inform.
* @retval FALSE otherwise.
*
*/
BOOL
CcspCwmppoHasPendingInform
    (
        ANSC_HANDLE                 hThisObject
    );

/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMPPO_PROCESS.C
***********************************************************/

/**
* @brief Configure the periodic inform mechanism.
*
* This function configures the periodic inform timer that sends regular inform messages
* to the ACS at specified intervals. It calculates timer intervals based on the time reference
* and periodic inform interval parameters, and handles enable/disable states.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if periodic inform interval is 0 or configuration fails.
*
*/
ANSC_STATUS
CcspCwmppoConfigPeriodicInform
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Schedule an inform message.
*
* This function schedules an inform message to be sent to the ACS after a specified delay.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] ulDelaySeconds  - Delay in seconds before sending inform.
*                    \n Seconds from current time to schedule.
* @param[in] pCommandKey  - Command key for the inform message.
*                    \n String identifying the scheduled inform.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoScheduleInform
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulDelaySeconds,
        char*                       pCommandKey
    );

/**
* @brief Signal a WMP session.
*
* This function signals a session-related event to trigger appropriate session handling
* and state transitions for the specified WMP session.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hWmpSession  - Handle to the WMP Session.
*                    \n Session to signal.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoSignalSession
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
* @brief Asynchronous connection task.
*
* This function implements an asynchronous task for establishing and managing connections
* to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoAsyncConnectTask
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMPPO_MPAIF.C
***********************************************************/

/**
* @brief Lock write access for parameter operations.
*
* This function acquires a write lock to ensure exclusive access for parameter
* write operations, preventing concurrent modifications.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of operation.
* @retval TRUE if lock is acquired successfully.
* @retval FALSE otherwise.
*
*/
BOOL
CcspCwmppoMpaLockWriteAccess
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Unlock write access for parameter operations.
*
* This function releases a previously acquired write lock, allowing other operations
* to access and modify parameters.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoMpaUnlockWriteAccess
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set parameter values via MPA interface.
*
* This function sets one or more parameter values through the Management Parameter
* Access (MPA) interface to the backend data model.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamValueArray  - Array of parameter values to set.
*                    \n Contains parameter names and values.
* @param[in] ulArraySize  - Size of the parameter value array.
*                    \n Number of parameters to set.
* @param[in,out] piStatus  - Pointer to status code.
*                    \n Returns detailed status information.
* @param[out] phSoapFault  - Pointer to SOAP fault handle.
*                    \n Returns fault information if operation fails.
* @param[in] bExcludeInvNs  - Flag to exclude invalid namespaces.
*                    \n TRUE to skip parameters in invalid namespaces.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoMpaSetParameterValues
    (
        ANSC_HANDLE                 hThisObject,
        void*                       pParamValueArray,
        ULONG                       ulArraySize,
        int*                        piStatus,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );

/**
* @brief Set parameter values with write ID.
*
* This function sets one or more parameter values with a specific write ID to ensure
* transactional integrity through the MPA interface.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamValueArray  - Array of parameter values to set.
*                    \n Contains parameter names and values.
* @param[in] ulArraySize  - Size of the parameter value array.
*                    \n Number of parameters to set.
* @param[in] ulWriteID  - Write identifier for transaction.
*                    \n ID obtained from LockWriteAccess.
* @param[in,out] piStatus  - Pointer to status code.
*                    \n Returns detailed status information.
* @param[out] phSoapFault  - Pointer to SOAP fault handle.
*                    \n Returns fault information if operation fails.
* @param[in] bExcludeInvNs  - Flag to exclude invalid namespaces.
*                    \n TRUE to skip parameters in invalid namespaces.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoMpaSetParameterValuesWithWriteID
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
* @brief Get parameter values via MPA interface.
*
* This function retrieves one or more parameter values through the Management Parameter
* Access (MPA) interface from the backend data model.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamNameArray  - Pointer to parameter name array.
*                    \n Contains full parameter paths.
* @param[in] uMaxEntry  - Maximum number of entries to retrieve.
*                    \n Limits the number of returned parameters.
* @param[out] ppParamValueArray  - Pointer to returned parameter value array.
*                    \n Returns parameter names and values.
* @param[out] pulArraySize  - Pointer to returned array size.
*                    \n Returns number of retrieved parameters.
* @param[out] phSoapFault  - Pointer to SOAP fault handle.
*                    \n Returns fault information if operation fails.
* @param[in] bExcludeInvNs  - Flag to exclude invalid namespaces.
*                    \n TRUE to skip parameters in invalid namespaces.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoMpaGetParameterValues
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
* @brief Get parameter names via MPA interface.
*
* This function retrieves parameter names matching a specified path through the
* Management Parameter Access (MPA) interface.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamPath  - Parameter path to search.
*                    \n Can include wildcards for partial matching.
* @param[in] bNextLevel  - Flag indicating next level only.
*                    \n TRUE to return only immediate children.
* @param[out] ppParamInfoArray  - Pointer to returned parameter info array.
*                    \n Returns parameter names and attributes.
* @param[out] pulArraySize  - Pointer to returned array size.
*                    \n Returns number of found parameters.
* @param[out] phSoapFault  - Pointer to SOAP fault handle.
*                    \n Returns fault information if operation fails.
* @param[in] bExcludeInvNs  - Flag to exclude invalid namespaces.
*                    \n TRUE to skip parameters in invalid namespaces.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoMpaGetParameterNames
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
* @brief Set parameter attributes via MPA interface.
*
* This function sets attributes (notification, access control) for one or more parameters
* through the Management Parameter Access (MPA) interface.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pSetParamAttribArray  - Array of parameter attributes to set.
*                    \n Contains parameter names and attribute values.
* @param[in] ulArraySize  - Size of the parameter attribute array.
*                    \n Number of parameters to update.
* @param[out] phSoapFault  - Pointer to SOAP fault handle.
*                    \n Returns fault information if operation fails.
* @param[in] bExcludeInvNs  - Flag to exclude invalid namespaces.
*                    \n TRUE to skip parameters in invalid namespaces.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoMpaSetParameterAttributes
    (
        ANSC_HANDLE                 hThisObject,
        void*                       pSetParamAttribArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );

/**
* @brief Get parameter attributes via MPA interface.
*
* This function retrieves attributes (notification, access control) for one or more parameters
* through the Management Parameter Access (MPA) interface.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamNameArray  - Pointer to parameter name array.
*                    \n Contains full parameter paths.
* @param[in] uMaxEntry  - Maximum number of entries to retrieve.
*                    \n Limits the number of returned attributes.
* @param[out] ppParamAttribArray  - Pointer to returned parameter attribute array.
*                    \n Returns parameter names and attribute values.
* @param[out] pulArraySize  - Pointer to returned array size.
*                    \n Returns number of retrieved attributes.
* @param[out] phSoapFault  - Pointer to SOAP fault handle.
*                    \n Returns fault information if operation fails.
* @param[in] bExcludeInvNs  - Flag to exclude invalid namespaces.
*                    \n TRUE to skip parameters in invalid namespaces.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoMpaGetParameterAttributes
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
* @brief Add an object instance via MPA interface.
*
* This function creates a new instance of a multi-instance object through the
* Management Parameter Access (MPA) interface.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pObjName  - Name of the object to create.
*                    \n Must be a multi-instance object path.
* @param[out] pulObjInsNumber  - Pointer to returned instance number.
*                    \n Returns the assigned instance number.
* @param[out] piStatus  - Pointer to status code.
*                    \n Returns detailed status information.
* @param[out] phSoapFault  - Pointer to SOAP fault handle.
*                    \n Returns fault information if operation fails.
* @param[in] bExcludeInvNs  - Flag to exclude invalid namespaces.
*                    \n TRUE to skip parameters in invalid namespaces.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoMpaAddObject
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pObjName,
        PULONG                      pulObjInsNumber,
        int*                        piStatus,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );

/**
* @brief Delete an object instance via MPA interface.
*
* This function deletes an existing instance of a multi-instance object through the
* Management Parameter Access (MPA) interface.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pObjName  - Name of the object instance to delete.
*                    \n Must be a complete object instance path.
* @param[out] piStatus  - Pointer to status code.
*                    \n Returns detailed status information.
* @param[out] phSoapFault  - Pointer to SOAP fault handle.
*                    \n Returns fault information if operation fails.
* @param[in] bExcludeInvNs  - Flag to exclude invalid namespaces.
*                    \n TRUE to skip parameters in invalid namespaces.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoMpaDeleteObject
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pObjName,
        int*                        piStatus,
        ANSC_HANDLE*                phSoapFault,
        BOOL                        bExcludeInvNs
    );

/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMPPO_PROCESS.C
***********************************************************/

/**
* @brief Get ACS (Auto Configuration Server) information.
*
* This function retrieves ACS connection and configuration information from the data model,
* including URL, credentials, periodic inform settings, and STUN configuration. It also
* determines if CWMP should be started, stopped, or reconfigured based on parameter changes.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmppoGetAcsInfo
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Management Server value changed notification.
*
* This function is called by Management Server Functional Component when the value of
* a parameter has changed. It triggers appropriate actions such as retrieving new ACS
* configuration or sending diagnostics complete notifications.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP Processor Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hMsvcObjectID  - Object identifier indicating which parameters changed.
*                    \n Bitmask of CCSP_MSVC_OBJECT_xxx values.
*
* @return void
*
*/
void
CcspCwmppoMsValueChanged
    (
        ANSC_HANDLE                 hThisObject,
        int                         hMsvcObjectID
    );

/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMPPO_EVENT.C
***********************************************************/

/**
* @brief Parameter value changed callback.
*
* This callback function is invoked when monitored parameter values change,
* allowing the processor to handle value change events appropriately.
*
* @param[in] val  - Pointer to parameter signal structure.
*                    \n Contains changed parameter information.
* @param[in] size  - Size of the parameter signal structure.
*                    \n Size in bytes.
* @param[in] user_data  - User-defined data passed to callback.
*                    \n Context provided during registration.
*
* @return void
*
*/
void
CcspCwmppoParamValueChangedCB
    (
        parameterSigStruct_t*       val,
        int                         size,
        void*                       user_data
    );

/**
* @brief System ready signal callback.
*
* This callback function is invoked when the system becomes ready,
* allowing the TR-069 processor to begin operations.
*
* @param[in] user_data  - User-defined data passed to callback.
*                    \n Context provided during registration.
*
* @return void
*
*/
void
CcspCwmppoSysReadySignalCB
    (
        void*                       user_data
    );

/**
* @brief Diagnostics complete signal callback.
*
* This callback function is invoked when diagnostic operations complete,
* allowing the processor to handle diagnostic results and notifications.
*
* @param[in] user_data  - User-defined data passed to callback.
*                    \n Context provided during registration.
*
* @return void
*
*/
void
CcspCwmppoDiagCompleteSignalCB
    (
        void*                       user_data
    );

/**
* @brief Process system ready signal.
*
* This function processes the system ready signal and initiates necessary TR-069
* operations once the system is ready.
*
* @param[in] cbContext  - Callback context for the signal processing.
*                    \n Context provided for the ready signal handler.
*
* @return void
*
*/
void
CcspCwmppoProcessSysReadySignal
    (
		void*	cbContext
    );

/**
* @brief Wait until system is ready.
*
* This function blocks until the system reaches a ready state, ensuring all necessary
* components are initialized before proceeding.
*
* @param[in] cbContext  - Callback context for the wait operation.
*                    \n Context provided to the waiting function.
*
* @return void
*
*/
void waitUntilSystemReady(	void*	cbContext);

/**
* @brief Check if system is ready.
*
* This function checks whether the system has reached a ready state where TR-069
* operations can be performed.
*
* @return System ready status.
* @retval 1 if system is ready.
* @retval 0 if system is not ready.
*
*/
int checkIfSystemReady(void);

#endif

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

    module:	ccsp_cwmp_stunmo_internal_api.h

        For CCSP CWMP protocol

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the internal functions provided by the CCSP CWMP Stun Manager
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

        08/05/08    initial revision.
        11/02/11    migrate to CCSP framework

**********************************************************************/


#ifndef  _CCSP_CWMP_STUNMO_INTERNAL_API_
#define  _CCSP_CWMP_STUNMO_INTERNAL_API_


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_STUNMO_STATES.C
***********************************************************/

/**
* @brief Get the CCSP CWMP CPE Controller handle.
*
* This function retrieves the handle to the CCSP CWMP CPE Controller object
* associated with the STUN Manager.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Handle to the CPE Controller object.
* @retval ANSC_HANDLE pointing to the CPE Controller if configured.
*
*/
ANSC_HANDLE
CcspCwmpStunmoGetCcspCwmpCpeController
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the CCSP CWMP CPE Controller handle.
*
* This function configures the handle to the CCSP CWMP CPE Controller object
* to be used by the STUN Manager.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hCpeController  - Handle to the CPE Controller object.
*                    \n The CPE Controller to be associated with this STUN Manager.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoSetCcspCwmpCpeController
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCpeController
    );

/**
* @brief Get the STUN Simple Client handle.
*
* This function retrieves the handle to the STUN Simple Client object
* used for STUN binding requests.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Handle to the STUN Simple Client object.
* @retval ANSC_HANDLE pointing to the STUN client if configured.
*
*/
ANSC_HANDLE
CcspCwmpStunmoGetStunSimpleClient
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the STUN client IP address.
*
* This function retrieves the IP address used by the STUN client for
* binding requests.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The client IP address.
* @retval ULONG containing the IPv4 address in network byte order.
*
*/
ULONG
CcspCwmpStunmoGetClientAddr
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the STUN client IP address.
*
* This function configures the IP address to be used by the STUN client
* for binding requests.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] ulAddr  - Client IP address to be configured.
*                    \n IPv4 address in network byte order.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoSetClientAddr
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulAddr
    );

/**
* @brief Get STUN Manager property.
*
* This function retrieves the property configuration of the STUN Manager,
* including client address and port settings.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[out] hProperty  - Handle to CCSP_CWMP_STUN_MANAGER_PROPERTY structure.
*                    \n Structure to be filled with property data.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoGetProperty
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
* @brief Set STUN Manager property.
*
* This function configures the property settings of the STUN Manager,
* including client address and port.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hProperty  - Handle to CCSP_CWMP_STUN_MANAGER_PROPERTY structure.
*                    \n Property data to be copied to the object.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoSetProperty
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
* @brief Reset STUN Manager property to defaults.
*
* This function resets the STUN Manager property configuration to default
* values, including clearing client address and resetting ports.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoResetProperty
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Reset STUN Manager object states.
*
* This function resets the internal states of the STUN Manager object
* to their initial values.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoReset
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
       FUNCTIONS IMPLEMENTED IN CCSP_CWMP_STUNMO_OPERATION.C
***********************************************************/

/**
* @brief Engage the STUN Manager.
*
* This function activates the STUN Manager by setting up the environment,
* configuring the STUN Simple Client, and loading STUN policy settings.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_NOT_READY if CPE Controller is not configured.
*
*/
ANSC_STATUS
CcspCwmpStunmoEngage
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Cancel the STUN Manager activity.
*
* This function deactivates the STUN Manager by canceling the STUN Simple Client,
* waiting for retry tasks to complete, and closing the environment.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoCancel
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Setup the STUN Manager operating environment.
*
* This function initializes the operating environment required for
* STUN Manager operation.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoSetupEnv
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Close the STUN Manager operating environment.
*
* This function cleans up and closes the operating environment used by
* the STUN Manager.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoCloseEnv
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_STUNMO_POLICY.C
***********************************************************/

/**
* @brief Load STUN policy configuration.
*
* This function loads STUN configuration from the system registry and
* applies the settings to the STUN Simple Client.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoLoadPolicy
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Apply STUN configuration settings.
*
* This function applies the current STUN configuration to the STUN Simple Client,
* including server address, port, credentials, and keep-alive intervals.
* If STUNServerAddress is empty, the ACS hostname is used as the STUN server.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoApplyStunSettings
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get ACS hostname from ACS URL.
*
* This function extracts the hostname from the configured ACS URL.
* The ACS URL is in the format: x-dslf_cwmp://host:port/ or x-dslf_cwmps://host:port/
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the hostname string.
* @retval char* containing the extracted hostname if successful.
* @retval NULL if ACS URL is not configured or parsing fails.
*
*/
char*
CcspCwmpStunmoGetAcsHostName
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
       FUNCTIONS IMPLEMENTED IN CCSP_CWMP_STUNMO_REG_STUN.C
***********************************************************/

/**
* @brief Get STUN configuration from registry.
*
* This function retrieves STUN configuration parameters from the Management Server
* data model, including enable flag, server address, port, credentials, and
* keep-alive intervals.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if string copy operations fail.
*
*/
ANSC_STATUS
CcspCwmpStunmoRegGetStunInfo
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set STUN configuration to registry.
*
* This function saves STUN configuration parameters to the Management Server
* data model, including NAT detection status and UDP connection request address.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoRegSetStunInfo
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
      FUNCTIONS IMPLEMENTED IN CCSP_CWMP_STUNMO_STUNBSMIF.C
***********************************************************/

/**
* @brief Process STUN Binding Response message (Role 1).
*
* This function processes a STUN Binding Response message received by the
* STUN Simple Client during NAT discovery. It extracts the mapped address
* and updates the UDP connection request address.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] buffer  - Pointer to the STUN message buffer.
*                    \n Contains the STUN Binding Response message.
* @param[in] ulSize  - Size of the message buffer in bytes.
*                    \n Length of the STUN message.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoStunBsmRecvMsg1
    (
        ANSC_HANDLE                 hThisObject,
        void*                       buffer,
        ULONG                       ulSize
    );

/**
* @brief Process UDP Connection Request message.
*
* This function processes a UDP Connection Request message received through
* the STUN client. It validates the request, authenticates the signature,
* and triggers a session initiation with the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] buffer  - Pointer to the UDP Connection Request buffer.
*                    \n Contains the HTTP GET request with connection parameters.
* @param[in] ulSize  - Size of the message buffer in bytes.
*                    \n Length of the UDP Connection Request message.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoStunBsmRecvMsg2
    (
        ANSC_HANDLE                 hThisObject,
        void*                       buffer,
        ULONG                       ulSize
    );

/**
* @brief Process STUN client notification events.
*
* This function handles notification events from the STUN Simple Client,
* including timeout events that trigger STUN retry attempts.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP STUN Manager Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] ulEvent  - Event type notification.
*                    \n STUN client event code.
* @param[in] hReserved  - Reserved parameter for future use.
*                    \n Currently unused.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpStunmoStunBsmNotify
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulEvent,
        ANSC_HANDLE                 hReserved
    );


#endif

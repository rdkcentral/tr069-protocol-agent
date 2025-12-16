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

    module: ccsp_management_server_pa_api.h

        For the interface of the management_server exposed to PA.

    ---------------------------------------------------------------

    description:

        This file defines all interface functions of management_server
        exposed to PA.
        The component management_server shares same process with PA,
        so the interface functions is directly called by PA.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Hui Ma

    ---------------------------------------------------------------

    revision:

        06/14/2011    initial revision.

**********************************************************************/

#ifndef  _CCSP_MANAGEMENT_SERVER_PA_API_DEC_
#define  _CCSP_MANAGEMENT_SERVER_PA_API_DEC_

#include "ccsp_types.h"
#include "ccsp_base_api.h"

/***************
no set parameter needed ***********************/

#define CCSP_MSVC_OBJECT_ManagementServer 	0x00000001			/*  any parameters right under Device.ManagementServer. */
#define CCSP_MSVC_OBJECT_ATCP 			0x00000002
#define CCSP_MSVC_OBJECT_DSCCP 			0x00000004
#define CCSP_MSVC_OBJECT_DiagComplete 	0x00000008			    /* received '8 DIAGNOSTICS COMPLETE' event  */

#define CCSP_MGMT_CRPWD_FILE    "/nvram/.keys/MgmtCRPwdID"
#define CCSP_MGMT_PWD_FILE      "/nvram/.keys/MgmtPwdID"

/**
 * @brief Callback function pointer type for TR-069 Management Server parameter value changes.
 *
 * This callback function pointer typedef defines the interface for notifying PA (Protocol Agent)
 * when specific management server parameters or parameter groups have changed. The callback
 * is invoked by the Management Server component when monitored parameters are modified, allowing
 * PA to respond to configuration changes.
 *
 * @param[in] hContext      Context handle passed into CcspManagementServer_Init() during
 *                          initialization. Used to identify the callback context.
 * @param[in] changedObjID  Bitwise OR'ed value of CCSP_MSVC_OBJECT_xxx flags indicating which
 *                          parameter groups changed.
 *
 * @return None.
 *
 */
typedef
CCSP_VOID
(*PFN_CCSPMS_VALUECHANGE)
    (
	  CCSP_HANDLE			hContext,		/* msvcCtx passed into CcspManagementServer_Init() */
	  CCSP_INT				changedObjID	/* Or'ed value of CCSP_MSVC_OBJECT_xxx */
    );

/**
 * @brief Callback function pointer type for system ready signal notification.
 *
 * This callback function pointer typedef defines the interface for receiving notification
 * when the TR-069 system ready signal is received from the Component Registrar (CR) via
 * Message Bus. The Management Server registers for "systemReadySignal" events and invokes
 * this callback to notify PA that the system initialization is complete and ready for operations.
 *
 * @param[in] user_data  User-defined context data passed during callback registration
 *                       via CcspManagementServer_Init(). Typically contains cbContext handle.
 *
 * @return None.
 *
 */
typedef
void
(*PFN_CCSP_SYSREADYSIG_CB)
    (
        void*               user_data
    );

/**
 * @brief Callback function pointer type for diagnostic complete signal notification.
 *
 * This callback function pointer typedef defines the interface for receiving notification
 * when a diagnostics operation completes. The Management Server registers for
 * "diagCompleteSignal" events via Message Bus and invokes this callback to notify PA
 * when diagnostic tests finish execution.
 *
 * @param[in] user_data  User-defined context data passed during callback registration
 *                       via CcspManagementServer_Init(). Typically contains cbContext handle.
 *
 * @return None.
 *
 */
typedef
void
(*PFN_CCSP_DIAGCOMPSIG_CB)
    (
        void*               user_data
    );

/**
 * @brief Initializes the TR-069 CCSP Management Server component.
 *
 * This function is called by PA (Protocol Agent) to initialize the Management Server component,
 * register it on the Message Bus, load the Supported Data Model configuration file, register
 * callback handlers for system ready and diagnostic complete signals, discover peer components
 * (PAM), register namespace for TR-069 parameters, and read TLV data for ACS configuration.
 * The function sets up the entire Management Server infrastructure including D-Bus communication,
 * PSM storage, and parameter management.
 *
 * @param[in] ComponentName      Component name string for registration on Message Bus.
 * @param[in] SubsystemPrefix    Subsystem prefix for PSM parameter namespace.
 * @param[in] hMBusHandle        Handle to the Message Bus for component communication.
 * @param[in] msValueChangeCB    Callback function pointer of type PFN_CCSPMS_VALUECHANGE invoked
 *                               when monitored Management Server parameters change. May be NULL.
 * @param[in] sysReadySignalCB   Callback function pointer of type PFN_CCSP_SYSREADYSIG_CB invoked
 *                               when system ready signal is received from CR. May be NULL.
 * @param[in] diagCompleteCB     Callback function pointer of type PFN_CCSP_DIAGCOMPSIG_CB invoked
 *                               when diagnostic complete signal is received. May be NULL.
 * @param[in] cbContext          Context handle passed to callback functions for state identification.
 * @param[in] cpeContext         CPE context handle for accessing CPE Controller operations.
 * @param[in] sdmXmlFilename     Path to the Supported Data Model XML configuration file. If NULL,
 *                               defaults to _CCSP_MANAGEMENT_SERVER_DEFAULT_SDM_FILE.
 *
 * @return None.
 *
 */
CCSP_VOID
CcspManagementServer_Init
    (
        CCSP_STRING             ComponentName,
        CCSP_STRING             SubsystemPrefix,
        CCSP_HANDLE             hMBusHandle,
        PFN_CCSPMS_VALUECHANGE	msValueChangeCB,
        PFN_CCSP_SYSREADYSIG_CB sysReadySignalCB,
        PFN_CCSP_DIAGCOMPSIG_CB diagCompleteCB,
        CCSP_HANDLE             cbContext,
        CCSP_HANDLE             cpeContext,
        CCSP_STRING             sdmXmlFilename
    );

/**
 * @brief Receives and processes parameter value change signals from PAM component.
 *
 * This function is called when parameter value change signals are received from the PAM
 * component via Message Bus. It processes the changed parameter structures to update
 * Management Server internal state and trigger appropriate actions based on the changed
 * parameters.
 *
 * @param[in] val   Pointer to array of parameterSigStruct_t structures containing information
 *                  about changed parameters.
 * @param[in] size  Number of elements in the val array.
 *
 * @return Status of the parameter processing operation.
 * @retval CCSP_TRUE   Successfully processed parameter value changes.
 * @retval CCSP_FALSE  Failed to process parameter value changes.
 *
 */
CCSP_BOOL CcspManagementServer_paramValueChanged
	(
		parameterSigStruct_t*		val,
		int				size
	);

#ifdef   _CCSP_CWMP_STUN_ENABLED
/**
 * @brief Notifies Management Server of STUN binding changes for UDP Connection Request.
 *
 * This function is called when STUN (Session Traversal Utilities for NAT) binding discovery
 * completes, providing NAT detection status and the resulting UDP Connection Request URL.
 * The Management Server updates Device.ManagementServer.NATDetected and
 * Device.ManagementServer.UDPConnectionRequestAddress parameters with the new values.
 *
 * @param[in] NATDetected     Boolean flag indicating whether NAT was detected during STUN binding
 *                            [Values: CCSP_TRUE (NAT detected), CCSP_FALSE (no NAT detected)].
 * @param[in] UdpConnReqURL   UDP Connection Request URL string obtained from STUN binding response.
 *                            Contains IP address and port for UDP-based connection requests.
 *
 * @return None.
 *
 */
CCSP_VOID
CcspManagementServer_StunBindingChanged
    (
        CCSP_BOOL                   NATDetected,
        char*                       UdpConnReqURL
    );
#endif

/**
 * @brief Retrieves the EnableCWMP parameter value from Device.ManagementServer.
 *
 * This function retrieves the boolean value of Device.ManagementServer.EnableCWMP, which
 * enables or disables the TR-069 CPE WAN Management Protocol. When FALSE, the CPE does not
 * initiate sessions with the ACS and ignores connection requests. The function returns a
 * boolean value by comparing the stored string value against "0" or "false" strings.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The EnableCWMP parameter value.
 * @retval CCSP_TRUE   CWMP is enabled .
 * @retval CCSP_FALSE  CWMP is disabled .
 *
 */
CCSP_BOOL
CcspManagementServer_GetEnableCWMP
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the EnableCWMP parameter value as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.EnableCWMP.
 * It returns "true" or "false" based on the stored boolean value, providing a standardized
 * string format for TR-069 parameter queries. Defaults to "false" if parameter value is "0".
 *
 * @param[in] ComponentName  Component name string..
 *
 * @return The EnableCWMP parameter value as a string.
 * @retval "true"   CWMP is enabled.
 * @retval "false"  CWMP is disabled.
 *
 */
CCSP_STRING
CcspManagementServer_GetEnableCWMPStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the EnableCWMP parameter in Device.ManagementServer.
 *
 * This function sets the boolean value of Device.ManagementServer.EnableCWMP, which
 * enables or disables the TR-069 CPE WAN Management Protocol. When set to FALSE, the CPE
 * stops initiating sessions with the ACS and ignores connection requests. The new value
 * is persisted to PSM (Persistent Storage Manager) and triggers value change callbacks.
 *
 * @param[in] ComponentName  Component name string.
 * @param[in] bEnableCWMP    Boolean value to enable (CCSP_TRUE) or disable (CCSP_FALSE) CWMP.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set EnableCWMP parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetEnableCWMP
    (
        CCSP_STRING                 ComponentName,
        CCSP_BOOL                   bEnableCWMP
    );

/**
 * @brief Retrieves the ACS URL parameter from Device.ManagementServer.
 *
 * This function retrieves the URL of the TR-069 Auto-Configuration Server (ACS) from
 * Device.ManagementServer.URL. If the PSM-stored value is empty or NULL, it attempts to
 * retrieve a default URL from g_Tr069PaAcsDefAddr, which is particularly important for
 * ETHWAN mode devices. The URL specifies the address for CPE-ACS communication.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The ACS URL parameter value as a string.
 * @retval Non-empty string  The configured or default ACS URL.
 * @retval Empty string ""   No URL is configured and no default URL is available.
 *
 */
CCSP_STRING
CcspManagementServer_GetURL
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the ACS URL parameter in Device.ManagementServer.
 *
 * This function sets the URL of the TR-069 Auto-Configuration Server (ACS) in
 * Device.ManagementServer.URL. The URL specifies the HTTP/HTTPS address where the CPE
 * should connect to establish TR-069 sessions. The new value is persisted to PSM
 * (Persistent Storage Manager) and triggers value change callbacks.
 *
 * @param[in] ComponentName  Component name string.
 * @param[in] pURL           ACS URL string.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set URL parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetURL
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pURL
    );

/**
 * @brief Retrieves the ACS authentication username from Device.ManagementServer.
 *
 * This function retrieves the username used for HTTP authentication when the CPE connects
 * to the ACS from Device.ManagementServer.Username. If the stored value is empty or NULL,
 * it attempts to generate a platform-specific default username via
 * CcspManagementServer_GenerateDefaultUsername() and saves it to PSM for future use.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The username parameter value as a string.
 * @retval Non-empty string  The configured or generated default username.
 * @retval Empty string ""   No username configured and default generation failed.
 *
 */
CCSP_STRING
CcspManagementServer_GetUsername
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the ACS authentication username in Device.ManagementServer.
 *
 * This function sets the username used for HTTP authentication when the CPE connects to
 * the ACS in Device.ManagementServer.Username. This credential is sent to the ACS during
 * session establishment for CPE authentication. The new value is persisted to PSM
 * (Persistent Storage Manager) and triggers value change callbacks.
 *
 * @param[in] ComponentName  Component name string.
 * @param[in] pUsername      Username string for ACS authentication.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set Username parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetUsername
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pUsername
    );

/**
 * @brief Retrieves the ACS authentication password from Device.ManagementServer.
 *
 * This function retrieves the password used for HTTP authentication when the CPE connects
 * to the ACS from Device.ManagementServer.Password. Per TR-069 specification, when read by
 * the ACS, this parameter should return an empty string. Internally, if the stored value is
 * empty or NULL, it attempts to generate a platform-specific default password via
 * CcspManagementServer_GenerateDefaultPassword() and saves it to PSM for future use.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The password parameter value.
 * @retval Non-empty string  The configured STUN password.
 * @retval Empty string ""   Per TR-069 spec when queried externally.
 *
 */
CCSP_STRING
CcspManagementServer_GetPassword
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the ACS authentication password in Device.ManagementServer.
 *
 * This function sets the password used for HTTP authentication when the CPE connects to
 * the ACS in Device.ManagementServer.Password. This credential is sent to the ACS during
 * session establishment for CPE authentication. The password is encrypted before being
 * persisted to PSM (Persistent Storage Manager) and triggers value change callbacks.
 *
 * @param[in] ComponentName  Component name string.
 * @param[in] pPassword      Password string for ACS authentication.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set Password parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetPassword
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pPassword
    );

/**
 * @brief Retrieves the PeriodicInformEnable parameter from Device.ManagementServer.
 *
 * This function retrieves the boolean value of Device.ManagementServer.PeriodicInformEnable,
 * which enables or disables periodic TR-069 Inform sessions to the ACS. When enabled, the CPE
 * sends Inform messages at intervals specified by PeriodicInformInterval. When disabled, the
 * CPE only sends Inform messages triggered by events or connection requests.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The PeriodicInformEnable parameter value.
 * @retval CCSP_TRUE   Periodic Inform is enabled.
 * @retval CCSP_FALSE  Periodic Inform is disabled.
 *
 */
CCSP_BOOL
CcspManagementServer_GetPeriodicInformEnable
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the PeriodicInformEnable parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.PeriodicInformEnable.
 * It returns "true" or "false" based on the stored boolean value, providing a standardized
 * string format for TR-069 parameter queries.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The PeriodicInformEnable parameter value as a string.
 * @retval "true"   Periodic Inform is enabled.
 * @retval "false"  Periodic Inform is disabled.
 *
 */
CCSP_STRING
CcspManagementServer_GetPeriodicInformEnableStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the PeriodicInformEnable parameter in Device.ManagementServer.
 *
 * This function sets the boolean value of Device.ManagementServer.PeriodicInformEnable,
 * which enables or disables periodic TR-069 Inform sessions to the ACS. When set to TRUE,
 * the CPE begins sending Inform messages at intervals specified by PeriodicInformInterval.
 * The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName          Component name string.
 * @param[in] bPeriodicInformEnable  Boolean value to enable (CCSP_TRUE) or disable (CCSP_FALSE)
 *                                   periodic Inform sessions.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set PeriodicInformEnable parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetPeriodicInformEnable
    (
        CCSP_STRING                 ComponentName,
        CCSP_BOOL                   bPeriodicInformEnable
    );

/**
 * @brief Retrieves the PeriodicInformInterval parameter from Device.ManagementServer.
 *
 * This function retrieves the unsigned integer value of Device.ManagementServer.PeriodicInformInterval,
 * which specifies the time interval in seconds between periodic Inform sessions. The CPE uses
 * this interval to schedule Inform messages to the ACS when PeriodicInformEnable is TRUE.
 * Defaults to 3600 seconds if no value is stored.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The PeriodicInformInterval parameter value in seconds.
 * @retval Configured value  The stored interval in seconds.
 * @retval 3600              Default value when parameter is not configured.
 *
 */
CCSP_UINT
CcspManagementServer_GetPeriodicInformInterval
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the PeriodicInformInterval parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.PeriodicInformInterval,
 * which specifies the time interval in seconds between periodic Inform sessions. The string
 * format is suitable for TR-069 parameter queries and responses.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The PeriodicInformInterval parameter value as a string.
 * @retval Numeric string  The interval value in seconds.
 *
 */
CCSP_STRING
CcspManagementServer_GetPeriodicInformIntervalStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the PeriodicInformTime parameter from Device.ManagementServer.
 *
 * This function retrieves the unsigned integer value of Device.ManagementServer.PeriodicInformTime,
 * which is an absolute time reference in UTC to align the start of periodic Inform sessions.
 * The CPE calculates the next Inform time based on this reference and PeriodicInformInterval.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The PeriodicInformTime parameter value as seconds.
 * @retval Configured value  The stored reference time in seconds.
 * @retval 0                 Default value when parameter is not configured.
 *
 */
CCSP_UINT
CcspManagementServer_GetPeriodicInformTime
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the PeriodicInformTime parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.PeriodicInformTime
 * via a platform-specific custom implementation (CcspManagementServer_GetPeriodicInformTimeStrCustom).
 *
 * @param[in] ComponentName  Component name string..
 *
 * @return The PeriodicInformTime parameter value as a string.
 * @retval Datetime string  The reference time.
 *
 */
CCSP_STRING
CcspManagementServer_GetPeriodicInformTimeStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the PeriodicInformTime parameter in Device.ManagementServer.
 *
 * This function sets the unsigned integer value of Device.ManagementServer.PeriodicInformTime,
 * which is an absolute time reference in UTC used to align the start of periodic Inform sessions.
 * The CPE recalculates the next Inform time based on this reference and PeriodicInformInterval.
 * The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName        Component name string.
 * @param[in] uiPeriodicInformTime  Absolute time value as seconds.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set PeriodicInformTime parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetPeriodicInformTime
    (
        CCSP_STRING                 ComponentName,
        CCSP_UINT                   uiPeriodicInformTime
    );

/**
 * @brief Retrieves the ParameterKey value from Device.ManagementServer.
 *
 * This function retrieves the string value of Device.ManagementServer.ParameterKey, which
 * is set by the ACS to track the last successful SetParameterValues or AddObject operation.
 * The ParameterKey is included in subsequent Inform messages to verify parameter changes
 * and is managed by PA.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The ParameterKey parameter value as a string.
 * @retval Non-empty string  The last ParameterKey set by ACS during parameter operations.
 * @retval Empty string ""   No ParameterKey has been set or parameter is not initialized.
 *
 */
CCSP_STRING
CcspManagementServer_GetParameterKey
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the ParameterKey value in Device.ManagementServer (PA-only access).
 *
 * This function sets the string value of Device.ManagementServer.ParameterKey, which is
 * set by the ACS during SetParameterValues or AddObject operations and returned in subsequent
 * Inform messages. This parameter is read-only from external perspective but writable by PA.
 * The function writes the ParameterKey directly to PSM for persistence and logging.
 *
 * @param[in] ComponentName  Component name string.
 * @param[in] pParameterKey  ParameterKey string value provided by ACS during parameter operations.
 *
 * @return Status of the set operation.
 * @retval CCSP_SUCCESS  Successfully set and persisted ParameterKey to PSM.
 * @retval Error code    Failed to write ParameterKey to PSM.
 *
 */
CCSP_INT
CcspManagementServer_SetParameterKey
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pParameterKey
    );

/**
 * @brief Retrieves the Connection Request URL from Device.ManagementServer.
 *
 * This function retrieves the URL from Device.ManagementServer.ConnectionRequestURL, which
 * the ACS uses to initiate connection requests to the CPE. The URL is dynamically constructed
 * from the first upstream IP address, connection request port, and path. In simulation mode,
 * it constructs the URL from the first Ethernet interface IP.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Connection Request URL as a string. Caller must free the returned string.
 * @retval Non-empty URL string  Constructed URL.
 * @retval Empty string ""       Failed to construct URL or discover peer components.
 *
 */
CCSP_STRING
CcspManagementServer_GetConnectionRequestURL
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the first upstream IP address for Connection Request URL construction.
 *
 * This function is called by PA to retrieve the IP address of the first upstream network
 * interface. It queries com.cisco.spvtg.ccsp.pam.Helper.FirstUpstreamIpAddress via the PAM
 * component or retrieves the PSM-stored value. This IP address is used to construct the
 * Device.ManagementServer.ConnectionRequestURL for ACS-initiated connection requests.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The first upstream IP address as a string. Caller must free the returned string.
 * @retval Non-empty IP string  IPv4 or IPv6 address of first upstream interface.
 * @retval Empty string ""      Failed to retrieve IP address from PAM or PSM.
 *
 */
CCSP_STRING
CcspManagementServer_GetFirstUpstreamIpAddress
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the Connection Request URL port from Device.ManagementServer.
 *
 * This function retrieves the port number from Device.ManagementServer.X_CISCO_COM_ConnectionRequestURLPort,
 * which specifies the TCP port on which the CPE listens for HTTP-based connection requests from
 * the ACS. This port is used to construct the full ConnectionRequestURL.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Connection Request URL port as a string.
 * @retval Port string  TCP port number.
 * @retval NULL         Port parameter is not configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetConnectionRequestURLPort
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the Connection Request URL path from Device.ManagementServer.
 *
 * This function retrieves the path component from Device.ManagementServer.X_CISCO_COM_ConnectionRequestURLPath,
 * which specifies the HTTP path portion of the connection request URL. The path is appended to
 * the base URL to form the complete ConnectionRequestURL.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Connection Request URL path as a string.
 * @retval Path string  HTTP path component.
 * @retval NULL         Path parameter is not configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetConnectionRequestURLPath
    (
        CCSP_STRING                 ComponentName
    );

/* CcspManagementServer_SetConnectionRequestURL is called to set
 * Device.ManagementServer.ConnectionRequestURL.
 * This parameter is read-only.
 * This component itself gets the parameter value from somewhere but cannt be written.
 * Return value - 0 if success.
 *
 */
/*CCSP_INT
CcspManagementServer_SetConnectionRequestURL
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pConnectionRequestURL
    );*/

/**
 * @brief Retrieves the Connection Request username from Device.ManagementServer.
 *
 * This function retrieves the username from Device.ManagementServer.ConnectionRequestUsername,
 * which the ACS must provide for HTTP authentication when initiating connection requests to
 * the CPE. This credential validates that connection requests originate from the authorized ACS.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Connection Request username as a string.
 * @retval Non-empty string  The configured username for ACS connection request authentication.
 * @retval Empty string ""   Username parameter is not configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetConnectionRequestUsername
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the Connection Request username in Device.ManagementServer.
 *
 * This function sets the username in Device.ManagementServer.ConnectionRequestUsername, which
 * the ACS must provide for HTTP authentication when initiating connection requests to the CPE.
 * The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName               Component name string.
 * @param[in] pConnectionRequestUsername  Username string for ACS connection request authentication.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set ConnectionRequestUsername parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetConnectionRequestUsername
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pConnectionRequestUsername
    );

/**
 * @brief Retrieves the Connection Request password from Device.ManagementServer.
 *
 * This function retrieves the password from Device.ManagementServer.ConnectionRequestPassword,
 * which the ACS must provide for HTTP authentication when initiating connection requests to
 * the CPE. Per TR-069 specification, when read by the ACS, this parameter should return an
 * empty string for security.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Connection Request password as a string.
 * @retval Empty string ""  Per TR-069 spec, always returns empty when queried externally.
 *
 */
CCSP_STRING
CcspManagementServer_GetConnectionRequestPassword
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the Connection Request password in Device.ManagementServer.
 *
 * This function sets the password in Device.ManagementServer.ConnectionRequestPassword, which
 * the ACS must provide for HTTP authentication when initiating connection requests to the CPE.
 * The password is encrypted before being persisted to PSM (Persistent Storage Manager) and
 * triggers value change callbacks.
 *
 * @param[in] ComponentName               Component name string.
 * @param[in] pConnectionRequestPassword  Password string for ACS connection request authentication.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set ConnectionRequestPassword parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetConnectionRequestPassword
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pConnectionRequestPassword
    );

/**
 * @brief Retrieves the ACSOverride parameter from Device.ManagementServer.
 *
 * This function retrieves the boolean value of Device.ManagementServer.ACSOverride, which
 * indicates whether the ACS (Auto-Configuration Server) URL can be overridden manually.
 * When TRUE, the CPE allows manual configuration of the ACS URL, typically for debugging
 * or testing purposes.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The ACSOverride parameter value.
 * @retval CCSP_TRUE   ACS Override is enabled.
 * @retval CCSP_FALSE  ACS Override is disabled.
 *
 */
CCSP_BOOL
CcspManagementServer_GetACSOverride
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the ACSOverride parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.ACSOverride.
 * It returns "true" or "false" based on the stored boolean value, providing a standardized
 * string format for TR-069 parameter queries.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The ACSOverride parameter value as a string.
 * @retval "true"   ACS Override is enabled.
 * @retval "false"  ACS Override is disabled.
 *

 */
CCSP_STRING
CcspManagementServer_GetACSOverrideStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the UpgradesManaged parameter from Device.ManagementServer.
 *
 * This function retrieves the boolean value of Device.ManagementServer.UpgradesManaged, which
 * indicates whether the CPE can autonomously perform firmware/software upgrades. When TRUE,
 * the ACS has permission to manage software/firmware upgrades via Download RPC commands.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The UpgradesManaged parameter value.
 * @retval CCSP_TRUE   Upgrades are managed by ACS.
 * @retval CCSP_FALSE  Upgrades are not managed by ACS.
 *
 */
CCSP_BOOL
CcspManagementServer_GetUpgradesManaged
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the UpgradesManaged parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.UpgradesManaged.
 * It returns "true" or "false" based on the stored boolean value, providing a standardized
 * string format for TR-069 parameter queries.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The UpgradesManaged parameter value as a string.
 * @retval "true"   Upgrades are managed by ACS.
 * @retval "false"  Upgrades are not managed by ACS.
 *
 */
CCSP_STRING
CcspManagementServer_GetUpgradesManagedStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the UpgradesManaged parameter in Device.ManagementServer.
 *
 * This function sets the boolean value of Device.ManagementServer.UpgradesManaged, which
 * indicates whether the CPE allows the ACS to manage software/firmware upgrades via Download
 * RPC commands. The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName    Component name string.
 * @param[in] bUpgradesManaged  Boolean value to enable (CCSP_TRUE) or disable (CCSP_FALSE)
 *                              ACS-managed upgrades.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set UpgradesManaged parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetUpgradesManaged
    (
        CCSP_STRING                 ComponentName,
        CCSP_BOOL                   bUpgradesManaged
    );

/**
 * @brief Retrieves the KickURL parameter from Device.ManagementServer.
 *
 * This function retrieves the URL from Device.ManagementServer.KickURL, which specifies
 * the URL to be opened by the CPE's Web GUI in response to the ACS's Kicked RPC method.
 * This parameter is read-only and managed internally by the Management Server component.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The KickURL parameter value as a string.
 * @retval Non-empty string  The configured Kick URL.
 * @retval NULL/Empty        KickURL parameter is not configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetKickURL
    (
        CCSP_STRING                 ComponentName
    );

/* CcspManagementServer_SetKickURL is called to set
 * Device.ManagementServer.KickURL.
 * This parameter is read-only.
 * This component itself gets the parameter value from somewhere but cannt be written.
 * Return value - 0 if success.
 *
 */
/*CCSP_INT
CcspManagementServer_SetKickURL
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pKickURL
    );*/

/**
 * @brief Retrieves the DownloadProgressURL parameter from Device.ManagementServer.
 *
 * This function retrieves the URL from Device.ManagementServer.DownloadProgressURL, which
 * specifies the URL to which the CPE should redirect its Web GUI to display download progress
 * during firmware/software downloads. This parameter is read-only and managed internally.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The DownloadProgressURL parameter value as a string.
 * @retval Non-empty string  The configured Download Progress URL.
 * @retval NULL/Empty        DownloadProgressURL parameter is not configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetDownloadProgressURL
    (
        CCSP_STRING                 ComponentName
    );

/* CcspManagementServer_SetDownloadProgressURL is called to set
 * Device.ManagementServer.DownloadProgressURL.
 * This parameter is read-only.
 * This component itself gets the parameter value from somewhere but cannt be written.
 * Return value - 0 if success.
 *
 */
/*CCSP_INT
CcspManagementServer_SetDownloadProgressURL
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pDownloadProgressURL
    );*/

/**
 * @brief Retrieves the DefaultActiveNotificationThrottle parameter from Device.ManagementServer.
 *
 * This function retrieves the unsigned integer value of Device.ManagementServer.DefaultActiveNotificationThrottle,
 * which specifies the maximum number of active notification messages that can be sent within
 * the throttle period. This controls the rate at which value change notifications are sent to the ACS.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The DefaultActiveNotificationThrottle parameter value.
 * @retval Configured value  The stored throttle value.
 * @retval 0                 Parameter not configured or conversion failed.
 *
 */
CCSP_UINT
CcspManagementServer_GetDefaultActiveNotificationThrottle
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the DefaultActiveNotificationThrottle parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.DefaultActiveNotificationThrottle.
 * If the parameter value is NULL, it defaults to "1".
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The DefaultActiveNotificationThrottle parameter value as a string.
 * @retval Numeric string  The throttle value.
 * @retval "1"             Default value when parameter is NULL.
 *
 */
CCSP_STRING
CcspManagementServer_GetDefaultActiveNotificationThrottleStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the DefaultActiveNotificationThrottle parameter in Device.ManagementServer.
 *
 * This function sets the unsigned integer value of Device.ManagementServer.DefaultActiveNotificationThrottle,
 * which specifies the maximum number of active notification messages that can be sent within
 * the throttle period. The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                         Component name string.
 * @param[in] uiDefaultActiveNotificationThrottle   Throttle value.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set DefaultActiveNotificationThrottle parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetDefaultActiveNotificationThrottle
    (
        CCSP_STRING                 ComponentName,
        CCSP_UINT                   uiDefaultActiveNotificationThrottle
    );

/**
 * @brief Retrieves the CWMPRetryMinimumWaitInterval parameter from Device.ManagementServer.
 *
 * This function retrieves the unsigned integer value of Device.ManagementServer.CWMPRetryMinimumWaitInterval,
 * which specifies the minimum wait interval in seconds before the CPE retries to establish
 * a connection with the ACS after a failed session attempt.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The CWMPRetryMinimumWaitInterval parameter value in seconds.
 * @retval Configured value  The stored minimum wait interval.
 * @retval 0                 Parameter not configured or conversion failed.
 *
 */
CCSP_UINT
CcspManagementServer_GetCWMPRetryMinimumWaitInterval
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the CWMPRetryMinimumWaitInterval parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.CWMPRetryMinimumWaitInterval,
 * which specifies the minimum wait interval in seconds before retry.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The CWMPRetryMinimumWaitInterval parameter value as a string.
 * @retval Numeric string  The minimum wait interval in seconds.
 *
 */
CCSP_STRING
CcspManagementServer_GetCWMPRetryMinimumWaitIntervalStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the CWMPRetryMinimumWaitInterval parameter in Device.ManagementServer.
 *
 * This function sets the unsigned integer value of Device.ManagementServer.CWMPRetryMinimumWaitInterval,
 * which specifies the minimum wait interval in seconds before the CPE retries to establish
 * a connection with the ACS. The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                    Component name string.
 * @param[in] uiCWMPRetryMinimumWaitInterval   Minimum wait interval in seconds.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set CWMPRetryMinimumWaitInterval parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetCWMPRetryMinimumWaitInterval
    (
        CCSP_STRING                 ComponentName,
        CCSP_UINT                   uiCWMPRetryMinimumWaitInterval
    );

/**
 * @brief Retrieves the CWMPRetryIntervalMultiplier parameter from Device.ManagementServer.
 *
 * This function retrieves the unsigned integer value of Device.ManagementServer.CWMPRetryIntervalMultiplier,
 * which specifies the multiplier factor applied to the wait interval for each subsequent retry
 * attempt when the CPE fails to connect to the ACS.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The CWMPRetryIntervalMultiplier parameter value.
 * @retval Configured value  The stored multiplier value .
 * @retval 0                 Parameter not configured or conversion failed.
 *
 */
CCSP_UINT
CcspManagementServer_GetCWMPRetryIntervalMultiplier
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the CWMPRetryIntervalMultiplier parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.CWMPRetryIntervalMultiplier,
 * which specifies the multiplier factor for retry wait intervals.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The CWMPRetryIntervalMultiplier parameter value as a string.
 * @retval Numeric string  The multiplier value
 *
 */
CCSP_STRING
CcspManagementServer_GetCWMPRetryIntervalMultiplierStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the CWMPRetryIntervalMultiplier parameter in Device.ManagementServer.
 *
 * This function sets the unsigned integer value of Device.ManagementServer.CWMPRetryIntervalMultiplier,
 * which specifies the multiplier factor applied to the wait interval for each subsequent retry.
 * The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                    Component name string.
 * @param[in] uiCWMPRetryIntervalMultiplier    Multiplier value.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set CWMPRetryIntervalMultiplier parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetCWMPRetryIntervalMultiplier
    (
        CCSP_STRING                 ComponentName,
        CCSP_UINT                   uiCWMPRetryIntervalMultiplier
    );

/**
 * @brief Retrieves the UDPConnectionRequestAddress from Device.ManagementServer.
 *
 * This function retrieves the UDP Connection Request Address from
 * Device.ManagementServer.UDPConnectionRequestAddress, which contains the IP address and
 * port number for UDP-based connection requests discovered through STUN binding. This
 * parameter is read-only and updated internally when STUN binding completes successfully.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The UDPConnectionRequestAddress parameter value as a string.
 * @retval Non-empty string  UDP address in format "ip:port" obtained from STUN binding.
 * @retval NULL/Empty        STUN binding not performed or address not available.
 *
 */
CCSP_STRING
CcspManagementServer_GetUDPConnectionRequestAddress
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the UDPConnectionRequestAddressNotificationLimit from Device.ManagementServer.
 *
 * This function retrieves the string value of Device.ManagementServer.UDPConnectionRequestAddressNotificationLimit,
 * which specifies the maximum number of UDP Connection Request Address change notifications
 * the CPE will send within a notification period. This helps prevent excessive notifications
 * when NAT bindings change frequently.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The UDPConnectionRequestAddressNotificationLimit parameter value as a string.
 * @retval Numeric string  The notification limit value.
 * @retval NULL            Parameter not configured.
 *
 */
// CCSP_UINT
CCSP_STRING
CcspManagementServer_GetUDPConnectionRequestAddressNotificationLimit
    (
        CCSP_STRING                 ComponentName
    );

/* CcspManagementServer_SetUDPConnectionRequestAddress is called to set
 * Device.ManagementServer.UDPConnectionRequestAddress.
 * This parameter is read-only.
 * This component itself gets the parameter value from somewhere but cannt be written.
 * Return value - 0 if success.
 *
 */
/*CCSP_INT
CcspManagementServer_SetUDPConnectionRequestAddress
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pUDPConnectionRequestAddress
    );*/

/**
 * @brief Retrieves the STUNEnable parameter from Device.ManagementServer.
 *
 * This function retrieves the boolean value of Device.ManagementServer.STUNEnable, which
 * enables or disables STUN (Session Traversal Utilities for NAT) functionality for
 * discovering the CPE's public IP address and port for UDP connection requests when behind NAT.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The STUNEnable parameter value.
 * @retval CCSP_TRUE   STUN is enabled.
 * @retval CCSP_FALSE  STUN is disabled.
 *
 */
CCSP_BOOL
CcspManagementServer_GetSTUNEnable
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the STUNEnable parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.STUNEnable.
 * It returns "true" or "false" based on the stored boolean value.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The STUNEnable parameter value as a string.
 * @retval "true"   STUN is enabled.
 * @retval "false"  STUN is disabled.
 *
 */
CCSP_STRING
CcspManagementServer_GetSTUNEnableStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the CustomDataModelEnabled parameter as a string.
 *
 * This function retrieves the string value indicating whether custom data model extensions
 * are enabled in the TR-069 Protocol Agent. Custom data models allow vendor-specific
 * parameters beyond the standard TR-069 data model.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The CustomDataModelEnabled parameter value as a string.
 * @retval "true"   Custom data model is enabled.
 * @retval "false"  Custom data model is disabled.
 *
 */
CCSP_STRING
CcspManagementServer_GetCustomDataModelEnabledStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the STUNEnable parameter in Device.ManagementServer.
 *
 * This function sets the boolean value of Device.ManagementServer.STUNEnable, which
 * enables or disables STUN functionality for NAT traversal and UDP connection request
 * address discovery. The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName  Component name string.
 * @param[in] bSTUNEnable    Boolean value to enable (CCSP_TRUE) or disable (CCSP_FALSE) STUN.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set STUNEnable parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetSTUNEnable
    (
        CCSP_STRING                 ComponentName,
        CCSP_BOOL                   bSTUNEnable
    );

/**
 * @brief Retrieves the STUNServerAddress parameter from Device.ManagementServer.
 *
 * This function retrieves the STUN server address from Device.ManagementServer.STUNServerAddress,
 * which specifies the IP address or hostname of the STUN server used for NAT binding discovery
 * and UDP connection request address determination.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The STUNServerAddress parameter value as a string.
 * @retval Non-empty string  STUN server IP address or hostname.
 * @retval NULL/Empty        STUN server address not configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetSTUNServerAddress
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the STUNServerAddress parameter in Device.ManagementServer.
 *
 * This function sets the STUN server address in Device.ManagementServer.STUNServerAddress,
 * which specifies the IP address or hostname of the STUN server for NAT binding discovery.
 * The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName       Component name string.
 * @param[in] pSTUNServerAddress  STUN server IP address or hostname string.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set STUNServerAddress parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetSTUNServerAddress
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pSTUNServerAddress
    );

/**
 * @brief Retrieves the STUNServerPort parameter from Device.ManagementServer.
 *
 * This function retrieves the unsigned integer value of Device.ManagementServer.STUNServerPort,
 * which specifies the UDP port number of the STUN server used for NAT binding discovery.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The STUNServerPort parameter value.
 * @retval Configured value  The stored STUN server port.
 * @retval 0                 Parameter not configured or conversion failed.
 *
 */
CCSP_UINT
CcspManagementServer_GetSTUNServerPort
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the STUNServerPort parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.STUNServerPort,
 * which specifies the UDP port number of the STUN server.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The STUNServerPort parameter value as a string.
 * @retval Numeric string  The STUN server port.
 *
 */
CCSP_STRING
CcspManagementServer_GetSTUNServerPortStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the STUNServerPort parameter in Device.ManagementServer.
 *
 * This function sets the unsigned integer value of Device.ManagementServer.STUNServerPort,
 * which specifies the UDP port number of the STUN server. The new value is persisted to PSM
 * and triggers value change callbacks.
 *
 * @param[in] ComponentName    Component name string.
 * @param[in] uiSTUNServerPort  STUN server port number.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set STUNServerPort parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetSTUNServerPort
    (
        CCSP_STRING                 ComponentName,
        CCSP_UINT                   uiSTUNServerPort
    );

/**
 * @brief Retrieves the STUNUsername parameter from Device.ManagementServer.
 *
 * This function retrieves the username from Device.ManagementServer.STUNUsername, which
 * specifies the username for authentication with the STUN server if required. This credential
 * is used when the STUN server requires authentication for binding requests.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The STUNUsername parameter value as a string.
 * @retval Non-empty string  The configured STUN username.
 * @retval NULL/Empty        STUN username not configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetSTUNUsername
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the STUNUsername parameter in Device.ManagementServer.
 *
 * This function sets the username in Device.ManagementServer.STUNUsername, which specifies
 * the username for authentication with the STUN server. The new value is persisted to PSM
 * and triggers value change callbacks.
 *
 * @param[in] ComponentName  Component name string.
 * @param[in] pSTUNUsername  STUN username string for server authentication.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set STUNUsername parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetSTUNUsername
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pSTUNUsername
    );

/**
 * @brief Retrieves the STUNPassword parameter from Device.ManagementServer.
 *
 * This function retrieves the password from Device.ManagementServer.STUNPassword, which
 * specifies the password for authentication with the STUN server. Per TR-069 specification,
 * when read by the ACS, this parameter returns an empty value for security. Internally,
 * the actual password value is stored and used for STUN authentication.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The STUNPassword parameter value as a string.
 * @retval Non-empty string  The configured STUN password.
 * @retval Empty string ""   Per TR-069 spec when queried externally.
 *
 */
CCSP_STRING
CcspManagementServer_GetSTUNPassword
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the STUNPassword parameter in Device.ManagementServer.
 *
 * This function sets the password in Device.ManagementServer.STUNPassword, which specifies
 * the password for authentication with the STUN server. The password is encrypted before
 * being persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName  Component name string.
 * @param[in] pSTUNPassword  STUN password string for server authentication.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set STUNPassword parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetSTUNPassword
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pSTUNPassword
    );

/**
 * @brief Retrieves the STUNMaximumKeepAlivePeriod parameter from Device.ManagementServer.
 *
 * This function retrieves the signed integer value of Device.ManagementServer.STUNMaximumKeepAlivePeriod,
 * which specifies the maximum time interval in seconds between STUN binding refresh requests.
 * A value of -1 indicates no maximum limit. This ensures NAT bindings remain active.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The STUNMaximumKeepAlivePeriod parameter value in seconds.
 * @retval Positive value  The maximum keep-alive period in seconds.
 * @retval -1              No maximum limit on keep-alive period.
 * @retval 0               Parameter not configured or conversion failed.
 *
 */
CCSP_INT
CcspManagementServer_GetSTUNMaximumKeepAlivePeriod
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the STUNMaximumKeepAlivePeriod parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.STUNMaximumKeepAlivePeriod,
 * which specifies the maximum keep-alive period in seconds.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The STUNMaximumKeepAlivePeriod parameter value as a string.
 * @retval Numeric string  The maximum keep-alive period.
 *
 */
CCSP_STRING
CcspManagementServer_GetSTUNMaximumKeepAlivePeriodStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the STUNMaximumKeepAlivePeriod parameter in Device.ManagementServer.
 *
 * This function sets the signed integer value of Device.ManagementServer.STUNMaximumKeepAlivePeriod,
 * which specifies the maximum time interval between STUN binding refresh requests.
 * The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                 Component name string.
 * @param[in] iSTUNMaximumKeepAlivePeriod   Maximum keep-alive period in seconds, or -1 for no limit.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set STUNMaximumKeepAlivePeriod parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetSTUNMaximumKeepAlivePeriod
    (
        CCSP_STRING                 ComponentName,
        CCSP_INT                    iSTUNMaximumKeepAlivePeriod
    );

/**
 * @brief Retrieves the STUNMinimumKeepAlivePeriod parameter from Device.ManagementServer.
 *
 * This function retrieves the unsigned integer value of Device.ManagementServer.STUNMinimumKeepAlivePeriod,
 * which specifies the minimum time interval in seconds between STUN binding refresh requests.
 * This value is used as the initial keep-alive interval and can be adjusted based on NAT
 * binding timeout behavior.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The STUNMinimumKeepAlivePeriod parameter value in seconds.
 * @retval Configured value  The stored minimum keep-alive period.
 * @retval 0                 Parameter not configured or conversion failed.
 *
 */
CCSP_UINT
CcspManagementServer_GetSTUNMinimumKeepAlivePeriod
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the STUNMinimumKeepAlivePeriod parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.STUNMinimumKeepAlivePeriod,
 * which specifies the minimum keep-alive period in seconds.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The STUNMinimumKeepAlivePeriod parameter value as a string.
 * @retval Numeric string  The minimum keep-alive period.
 *
 */
CCSP_STRING
CcspManagementServer_GetSTUNMinimumKeepAlivePeriodStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the STUNMinimumKeepAlivePeriod parameter in Device.ManagementServer.
 *
 * This function sets the unsigned integer value of Device.ManagementServer.STUNMinimumKeepAlivePeriod,
 * which specifies the minimum time interval between STUN binding refresh requests.
 * The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                 Component name string.
 * @param[in] uiSTUNMinimumKeepAlivePeriod  Minimum keep-alive period in seconds [Range: 1 to maximum unsigned int].
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set STUNMinimumKeepAlivePeriod parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetSTUNMinimumKeepAlivePeriod
    (
        CCSP_STRING                 ComponentName,
        CCSP_UINT                   uiSTUNMinimumKeepAlivePeriod
    );

/**
 * @brief Retrieves the NATDetected parameter from Device.ManagementServer.
 *
 * This function retrieves the boolean value of Device.ManagementServer.NATDetected, which
 * indicates whether the CPE is behind a NAT (Network Address Translation) device. This
 * value is determined through STUN binding discovery and indicates if the CPE's public
 * IP address differs from its local IP address. This parameter is read-only and updated
 * internally via STUN operations.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The NATDetected parameter value.
 * @retval CCSP_TRUE   NAT detected.
 * @retval CCSP_FALSE  NAT not detected.
 *
 */
CCSP_BOOL
CcspManagementServer_GetNATDetected
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the NATDetected parameter as a string from Device.ManagementServer.
 *
 * This function retrieves the string representation of Device.ManagementServer.NATDetected.
 * It returns "true" or "false" based on the stored boolean value.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The NATDetected parameter value as a string.
 * @retval "true"   NAT detected.
 * @retval "false"  NAT not detected.
 *
 */
CCSP_STRING
CcspManagementServer_GetNATDetectedStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the NATDetected parameter in Device.ManagementServer (PA-only access).
 *
 * This function sets the boolean value of Device.ManagementServer.NATDetected, which
 * indicates whether NAT was detected. This parameter is read-only from external perspective
 * but can be written by PA (Protocol Agent) internally when STUN binding discovery completes.
 * The new value is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName  Component name string.
 * @param[in] bNATDetected   Boolean value indicating NAT detection status (CCSP_TRUE=detected, CCSP_FALSE=not detected).
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set NATDetected parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetNATDetected
    (
        CCSP_STRING                 ComponentName,
        CCSP_BOOL                   bNATDetected
    );

/*
 * Device.ManagementServer.ManageableDevice.{i}.
 * is not supported. So Device.ManagementServer.ManageableDeviceNumberOfEntries
 * is not supported here.
 *
 */

/**
 * @brief Retrieves the AutonomousTransferCompletePolicy Enable parameter from Device.ManagementServer.
 *
 * This function retrieves the boolean value of Device.ManagementServer.AutonomousTransferCompletePolicy.Enable,
 * which enables or disables the autonomous transfer complete policy. When enabled, the CPE
 * sends autonomous TransferComplete messages to the ACS for file transfers matching the
 * configured filter criteria without waiting for ACS polling.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The AutonomousTransferCompletePolicy.Enable parameter value.
 * @retval CCSP_TRUE   Autonomous transfer complete policy is enabled.
 * @retval CCSP_FALSE  Autonomous transfer complete policy is disabled.
 *
 */
CCSP_BOOL
CcspManagementServer_GetAutonomousTransferCompletePolicy_Enable
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the AutonomousTransferCompletePolicy Enable parameter as a string.
 *
 * This function retrieves the string representation of Device.ManagementServer.AutonomousTransferCompletePolicy.Enable.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The AutonomousTransferCompletePolicy.Enable parameter value as a string.
 * @retval "true"   Autonomous transfer complete policy is enabled.
 * @retval "false"  Autonomous transfer complete policy is disabled.
 *
 */
CCSP_STRING
CcspManagementServer_GetAutonomousTransferCompletePolicy_EnableStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the AutonomousTransferCompletePolicy Enable parameter.
 *
 * This function sets the boolean value of Device.ManagementServer.AutonomousTransferCompletePolicy.Enable,
 * which enables or disables autonomous transfer complete notifications. The new value is
 * persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                               Component name string.
 * @param[in] bAutonomousTransferCompletePolicy_Enable    Boolean value to enable (CCSP_TRUE) or disable (CCSP_FALSE)
 *                                                         autonomous transfer complete policy.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set AutonomousTransferCompletePolicy.Enable parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetAutonomousTransferCompletePolicy_Enable
    (
        CCSP_STRING                 ComponentName,
        CCSP_BOOL                   bAutonomousTransferCompletePolicy_Enable
    );

/**
 * @brief Retrieves the AutonomousTransferCompletePolicy TransferTypeFilter parameter.
 *
 * This function retrieves the comma-separated list string from
 * Device.ManagementServer.AutonomousTransferCompletePolicy.TransferTypeFilter, which
 * specifies the transfer types for which autonomous TransferComplete messages should be sent.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The TransferTypeFilter parameter value as a string.
 * @retval Non-empty string  Comma-separated transfer types.
 * @retval NULL/Empty        No filter configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetAutonomousTransferCompletePolicy_TransferTypeFilter
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the AutonomousTransferCompletePolicy TransferTypeFilter parameter.
 *
 * This function sets the comma-separated list string in
 * Device.ManagementServer.AutonomousTransferCompletePolicy.TransferTypeFilter, which
 * specifies the transfer types for autonomous notifications. The new value is persisted
 * to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                                         Component name string.
 * @param[in] pAutonomousTransferCompletePolicy_TransferTypeFilter  Comma-separated transfer types.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set TransferTypeFilter parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetAutonomousTransferCompletePolicy_TransferTypeFilter
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pAutonomousTransferCompletePolicy_TransferTypeFilter
    );

/**
 * @brief Retrieves the AutonomousTransferCompletePolicy ResultTypeFilter parameter.
 *
 * This function retrieves the comma-separated list string from
 * Device.ManagementServer.AutonomousTransferCompletePolicy.ResultTypeFilter, which
 * specifies the transfer result types for which autonomous TransferComplete messages should
 * be sent.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The ResultTypeFilter parameter value as a string.
 * @retval Non-empty string  Comma-separated result types.
 * @retval NULL/Empty        No filter configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetAutonomousTransferCompletePolicy_ResultTypeFilter
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the AutonomousTransferCompletePolicy ResultTypeFilter parameter.
 *
 * This function sets the comma-separated list string in
 * Device.ManagementServer.AutonomousTransferCompletePolicy.ResultTypeFilter, which
 * specifies the transfer result types for autonomous notifications. The new value is
 * persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                                        Component name string.
 * @param[in] pAutonomousTransferCompletePolicy_ResultTypeFilter   Comma-separated result types.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set ResultTypeFilter parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetAutonomousTransferCompletePolicy_ResultTypeFilter
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pAutonomousTransferCompletePolicy_ResultTypeFilter
    );

/**
 * @brief Retrieves the AutonomousTransferCompletePolicy FileTypeFilter parameter.
 *
 * This function retrieves the comma-separated list string from
 * Device.ManagementServer.AutonomousTransferCompletePolicy.FileTypeFilter, which
 * specifies the file types for which autonomous TransferComplete messages should be sent.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The FileTypeFilter parameter value as a string. Caller must free the returned string.
 * @retval Non-empty string  Comma-separated file type codes.
 * @retval NULL/Empty        No filter configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetAutonomousTransferCompletePolicy_FileTypeFilter
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the AutonomousTransferCompletePolicy FileTypeFilter parameter.
 *
 * This function sets the comma-separated list string in
 * Device.ManagementServer.AutonomousTransferCompletePolicy.FileTypeFilter, which
 * specifies the file types for autonomous notifications. The new value is persisted
 * to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                                      Component name string.
 * @param[in] pAutonomousTransferCompletePolicy_FileTypeFilter   Comma-separated file type codes.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set FileTypeFilter parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetAutonomousTransferCompletePolicy_FileTypeFilter
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pAutonomousTransferCompletePolicy_FileTypeFilter
    );

/**
 * @brief Retrieves the DUStateChangeComplPolicy Enable parameter from Device.ManagementServer.
 *
 * This function retrieves the boolean value of Device.ManagementServer.DUStateChangeComplPolicy.Enable,
 * which enables or disables the DU state change complete policy. When enabled,
 * the CPE sends autonomous DUStateChangeComplete messages to the ACS for software module
 * operations matching the configured filter criteria.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The DUStateChangeComplPolicy.Enable parameter value.
 * @retval CCSP_TRUE   DU state change complete policy is enabled.
 * @retval CCSP_FALSE  DU state change complete policy is disabled.
 *
 */
CCSP_BOOL
CcspManagementServer_GetDUStateChangeComplPolicy_Enable
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the DUStateChangeComplPolicy Enable parameter as a string.
 *
 * This function retrieves the string representation of Device.ManagementServer.DUStateChangeComplPolicy.Enable.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The DUStateChangeComplPolicy.Enable parameter value as a string.
 * @retval "true"   DU state change complete policy is enabled.
 * @retval "false"  DU state change complete policy is disabled.
 *
 */
CCSP_STRING
CcspManagementServer_GetDUStateChangeComplPolicy_EnableStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the DUStateChangeComplPolicy Enable parameter.
 *
 * This function sets the boolean value of Device.ManagementServer.DUStateChangeComplPolicy.Enable,
 * which enables or disables autonomous DU state change complete notifications. The new value
 * is persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                      Component name string.
 * @param[in] bDUStateChangeComplPolicy_Enable   Boolean value to enable (CCSP_TRUE) or disable (CCSP_FALSE)
 *                                                DU state change complete policy.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set DUStateChangeComplPolicy.Enable parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetDUStateChangeComplPolicy_Enable
    (
        CCSP_STRING                 ComponentName,
        CCSP_BOOL                   bDUStateChangeComplPolicy_Enable
    );

/**
 * @brief Retrieves the DUStateChangeComplPolicy OperationTypeFilter parameter.
 *
 * This function retrieves the comma-separated list string from
 * Device.ManagementServer.DUStateChangeComplPolicy.OperationTypeFilter, which specifies
 * the software module operation types for which autonomous DUStateChangeComplete messages
 * should be sent.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The OperationTypeFilter parameter value as a string.
 * @retval Non-empty string  Comma-separated operation types.
 * @retval NULL/Empty        No filter configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetDUStateChangeComplPolicy_OperationTypeFilter
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the DUStateChangeComplPolicy OperationTypeFilter parameter.
 *
 * This function sets the comma-separated list string in
 * Device.ManagementServer.DUStateChangeComplPolicy.OperationTypeFilter, which specifies
 * the operation types for autonomous DU state change notifications. The new value is
 * persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                                 Component name string.
 * @param[in] pDUStateChangeComplPolicy_OperationTypeFilter  Comma-separated operation types.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set OperationTypeFilter parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetDUStateChangeComplPolicy_OperationTypeFilter
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pDUStateChangeComplPolicy_OperationTypeFilter
    );

/**
 * @brief Retrieves the DUStateChangeComplPolicy ResultTypeFilter parameter.
 *
 * This function retrieves the comma-separated list string from
 * Device.ManagementServer.DUStateChangeComplPolicy.ResultTypeFilter, which specifies
 * the operation result types for which autonomous DUStateChangeComplete messages should
 * be sent.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The ResultTypeFilter parameter value as a string. Caller must free the returned string.
 * @retval Non-empty string  Comma-separated result types.
 * @retval NULL/Empty        No filter configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetDUStateChangeComplPolicy_ResultTypeFilter
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the DUStateChangeComplPolicy ResultTypeFilter parameter.
 *
 * This function sets the comma-separated list string in
 * Device.ManagementServer.DUStateChangeComplPolicy.ResultTypeFilter, which specifies
 * the result types for autonomous DU state change notifications. The new value is
 * persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                               Component name string.
 * @param[in] pDUStateChangeComplPolicy_ResultTypeFilter  Comma-separated result types.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set ResultTypeFilter parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetDUStateChangeComplPolicy_ResultTypeFilter
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pDUStateChangeComplPolicy_ResultTypeFilter
    );

/**
 * @brief Retrieves the DUStateChangeComplPolicy FaultCodeFilter parameter.
 *
 * This function retrieves the comma-separated list string from
 * Device.ManagementServer.DUStateChangeComplPolicy.FaultCodeFilter, which specifies
 * the fault codes for which autonomous DUStateChangeComplete messages should be sent when
 * operations fail.
 *
 * @param[in] ComponentName  Component name string .
 *
 * @return The FaultCodeFilter parameter value as a string. Caller must free the returned string.
 * @retval Non-empty string  Comma-separated fault codes.
 * @retval NULL/Empty        No filter configured.
 *
 */
CCSP_STRING
CcspManagementServer_GetDUStateChangeComplPolicy_FaultCodeFilter
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the DUStateChangeComplPolicy FaultCodeFilter parameter.
 *
 * This function sets the comma-separated list string in
 * Device.ManagementServer.DUStateChangeComplPolicy.FaultCodeFilter, which specifies
 * the fault codes for autonomous DU state change notifications. The new value is
 * persisted to PSM and triggers value change callbacks.
 *
 * @param[in] ComponentName                              Component name string.
 * @param[in] pDUStateChangeComplPolicy_FaultCodeFilter  Comma-separated fault codes.
 *
 * @return Status of the set operation.
 * @retval 0  Successfully set FaultCodeFilter parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetDUStateChangeComplPolicy_FaultCodeFilter
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 pDUStateChangeComplPolicy_FaultCodeFilter
    );

/**
 * @brief Retrieves the TR-069 Protocol Agent component name.
 *
 * This function retrieves the component name from com.cisco.spvtg.ccsp.tr069pa.Name,
 * which identifies the TR-069 Protocol Agent component name registered on the Message Bus.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The TR069pa Name parameter value as a string.
 * @retval Non-empty string  The component name.
 *
 */
CCSP_STRING
CcspManagementServer_GetTr069pa_Name
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the TR-069 Protocol Agent component version.
 *
 * This function retrieves the version string from com.cisco.spvtg.ccsp.tr069pa.Version,
 * which identifies the software version of the TR-069 Protocol Agent component.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The TR069pa Version parameter value as a string.
 * @retval Non-empty string  The component version .
 *
 */
CCSP_STRING
CcspManagementServer_GetTr069pa_Version
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the TR-069 Protocol Agent component author information.
 *
 * This function retrieves the author string from com.cisco.spvtg.ccsp.tr069pa.Author,
 * which identifies the author or organization that developed the TR-069 Protocol Agent.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The TR069pa Author parameter value as a string.
 * @retval Non-empty string  The component author.
 *
 */
CCSP_STRING
CcspManagementServer_GetTr069pa_Author
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the TR-069 Protocol Agent component health status.
 *
 * This function retrieves the health status string from com.cisco.spvtg.ccsp.tr069pa.Health,
 * which indicates the operational health of the TR-069 Protocol Agent component.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The TR069pa Health parameter value as a string.
 * @retval "Green"   Component is operating normally.
 * @retval "Yellow"  Component is degraded but operational.
 * @retval "Red"     Component has failed or is not operational.
 *
 */
CCSP_STRING
CcspManagementServer_GetTr069pa_Health
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the TR-069 Protocol Agent component state.
 *
 * This function retrieves the state string from com.cisco.spvtg.ccsp.tr069pa.State,
 * which indicates the current operational state of the TR-069 Protocol Agent component.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The TR069pa State parameter value as a string.
 * @retval Non-empty string  The component state.
 *
 */
CCSP_STRING
CcspManagementServer_GetTr069pa_State
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the TR-069 Protocol Agent data model XML path.
 *
 * This function retrieves the file path string from com.cisco.spvtg.ccsp.tr069pa.DTXml,
 * which specifies the location of the XML data model definition file used by the TR-069
 * Protocol Agent component.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The TR069pa DTXml parameter value as a string.
 * @retval Non-empty string  The XML file path.
 *
 */
CCSP_STRING
CcspManagementServer_GetTr069pa_DTXml
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the minimum memory usage as a string.
 *
 * This function retrieves the minimum memory usage from com.cisco.spvtg.ccsp.tr069pa.Memory.MinUsage
 * as a string. The minimum usage represents the memory consumed by the TR-069 Protocol Agent
 * immediately after initialization and does not change during runtime.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Memory MinUsage parameter value as a string in bytes.
 * @retval Numeric string  The minimum memory usage in bytes.
 *
 */
CCSP_STRING
CcspManagementServer_GetMemory_MinUsageStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the maximum memory usage.
 *
 * This function retrieves the maximum memory usage from
 * com.cisco.spvtg.ccsp.tr069pa.Memory.MaxUsage. This value represents the highest
 * memory consumption recorded by the TR-069 Protocol Agent since startup.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Memory MaxUsage parameter value as unsigned long in bytes.
 * @retval ULONG value  The maximum memory usage in bytes.
 *
 */
ULONG
CcspManagementServer_GetMemory_MaxUsage
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the maximum memory usage as a string.
 *
 * This function retrieves the maximum  memory usage from
 * com.cisco.spvtg.ccsp.tr069pa.Memory.MaxUsage as a string. The value is obtained from
 * g_ulAllocatedSizePeak global variable.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Memory MaxUsage parameter value as a string in bytes.
 * @retval Numeric string  The maximum memory usage in bytes.
 *
 */
CCSP_STRING
CcspManagementServer_GetMemory_MaxUsageStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the current memory consumption.
 *
 * This function retrieves the current memory consumption from
 * com.cisco.spvtg.ccsp.tr069pa.Memory.Consumed. This value represents the current
 * memory allocated by the TR-069 Protocol Agent (g_ulAllocatedSizeCurr).
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Memory Consumed parameter value as unsigned long in bytes.
 * @retval ULONG value  The current memory consumption in bytes.
 *
 */
ULONG
CcspManagementServer_GetMemory_Consumed
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the current memory consumption as a string.
 *
 * This function retrieves the current memory consumption from
 * com.cisco.spvtg.ccsp.tr069pa.Memory.Consumed as a string. The value is obtained by
 * calling CcspManagementServer_GetMemory_Consumed() and converting to string.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Memory Consumed parameter value as a string in bytes.
 * @retval Numeric string  The current memory consumption in bytes.
 *
 */
CCSP_STRING
CcspManagementServer_GetMemory_ConsumedStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the logging enable status as a string.
 *
 * This function retrieves the logging enable status from com.cisco.spvtg.ccsp.tr069pa.Logging.Enable
 * as a string. When enabled, the TR-069 Protocol Agent outputs log messages according to
 * the configured log level.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Logging Enable parameter value as a string.
 * @retval "true"   Logging is enabled.
 * @retval "false"  Logging is disabled.
 *
 */
CCSP_STRING
CcspManagementServer_GetLogging_EnableStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the logging enable status.
 *
 * This function sets the logging enable status in com.cisco.spvtg.ccsp.tr069pa.Logging.Enable.
 * When set to "true" or "1", logging is enabled at the level specified by LogLevel. When set
 * to "false", the trace level is set to CCSP_TRACE_INVALID_LEVEL to disable all logging.
 *
 * @param[in] ComponentName  Component name string.
 * @param[in] Value          String value to enable ("true"/"1") or disable ("false"/"0") logging.
 *
 * @return Status of the set operation.
 * @retval CCSP_SUCCESS  Successfully set Logging.Enable parameter value.
 *
 */
CCSP_INT
CcspManagementServer_SetLogging_EnableStr
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 Value
    );

/**
 * @brief Retrieves the logging log level as a string.
 *
 * This function retrieves the log level from com.cisco.spvtg.ccsp.tr069pa.Logging.LogLevel
 * as a string. The log level controls the verbosity of log messages. If the parameter value
 * is NULL, returns the current g_iTraceLevel global variable value.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Logging LogLevel parameter value as a string.
 * @retval Numeric string  The log level.
 *
 */
CCSP_STRING
CcspManagementServer_GetLogging_LogLevelStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Configures the logging log level.
 *
 * This function sets the log level in com.cisco.spvtg.ccsp.tr069pa.Logging.LogLevel.
 * The log level controls message verbosity (1=Emergency, 2=Alert, 3=Critical, 4=Error,
 * 5=Warning, 6=Notice, 7=Info, 8=Debug). If logging is enabled, the new trace level is
 * applied immediately via AnscSetTraceLevel().
 *
 * @param[in] ComponentName  Component name string.
 * @param[in] Value          String numeric log level value.
 *
 * @return Status string representation of the set operation.
 * @retval "0"  Successfully set Logging.LogLevel parameter value .
 *
 */
CCSP_STRING
CcspManagementServer_SetLogging_LogLevelStr
    (
        CCSP_STRING                 ComponentName,
        CCSP_STRING                 Value
    );

/**
 * @brief Retrieves the TR-069 notification status as a string.
 *
 * This function retrieves notification-related information for TR-069 operations. The specific
 * notification data returned depends on the internal implementation and component state.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The TR069 Notification parameter value as a string.
 * @retval Non-empty string  Notification status or information.
 *
 */
CCSP_STRING
CcspManagementServer_GetTR069_NotificationStr
    (
        CCSP_STRING                 ComponentName
    );

/**
 * @brief Retrieves the connected client information as a string.
 *
 * This function retrieves information about the currently connected TR-069 client or ACS
 * session. The specific client data returned depends on the internal implementation and
 * active connection state.
 *
 * @param[in] ComponentName  Component name string.
 *
 * @return The Connected Client parameter value as a string.
 * @retval Non-empty string  Connected client information.
 * @retval Empty string      No client currently connected.
 *
 */
CCSP_STRING
CcspManagementServer_GetConnected_ClientStr
    (
        CCSP_STRING                 ComponentName
    );

#endif
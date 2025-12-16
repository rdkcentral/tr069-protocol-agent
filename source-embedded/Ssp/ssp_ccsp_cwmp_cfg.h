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

    module:	ssp_ccsp_cwmp_cfg.h

        For CCSP TR-069 PA SSP,
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        Implementation of the CCSP CWMP Cfg interface for CCSP TR-069
        PA.

    ---------------------------------------------------------------

    environment:

        platform dependent

    ---------------------------------------------------------------

    author:

        Kang Quan

    ---------------------------------------------------------------

    revision:

        08/03/2011  initial revision.

**********************************************************************/


#ifndef  _SSP_CCSP_CWMP_CFG_
#define  _SSP_CCSP_CWMP_CFG_

#ifdef   _ANSC_USE_OPENSSL_
/**
 * @brief Sets the OpenSSL certificate file locations for TR-069 SSL/TLS connections.
 *
 * This function parses the TR-069 PA configuration file to extract and set the file paths
 * for OpenSSL certificates used in secure TR-069 communications with the ACS.
 *
 * @param[in] pCfgFileName  Path to the TR-069 PA XML configuration file.
 * @param[out] returnCA     Pointer to receive the CA certificate file path string.
 * @param[out] returnDEV    Pointer to receive the device certificate file path string.
 * @param[out] returnPKey   Pointer to receive the private key file path string.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully retrieved certificate locations.
 * @retval ANSC_STATUS_FAILURE  Failed to parse configuration file or retrieve certificate paths.
 *
 */
ANSC_STATUS
CcspTr069PaSsp_SetOpensslCertificateLocation
    (
        char*                       pCfgFileName,
        char**                      returnCA,
        char**                      returnDEV,
        char**                      returnPKey
    );
#endif

/**
 * @brief Initializes the CCSP CWMP configuration interface for TR-069 PA.
 *
 * This function initializes the CCSP_CWMP_CFG_INTERFACE structure by setting up function
 * pointers for various configuration callbacks.
 *
 * @return The status of the initialization operation.
 * @retval 0  Successfully initialized the CCSP CWMP configuration interface.
 *
 */
int
CcspTr069PaSsp_InitCcspCwmpCfgIf
    (
    );

/**
 * @brief Returns a bitmask indicating which TR-069 RPC methods are not supported.
 *
 * This function returns a bitmask that specifies which TR-069 RPC methods should be excluded
 * from the device's capabilities. The returned value is used by the TR-069 PA to filter out
 * unsupported methods when building the RPC capability list sent to the ACS.
 *
 * @param[in] hThisObject  Handle to the CCSP CWMP CPE Controller object.
 *
 * @return Bitmask indicating unsupported RPC methods.
 * @retval Bitmask  Combination of CCSP_CWMP_CFG_RPC_METHOD_NO_* flags indicating which
 *                  RPC methods are not supported by this device.
 *
 */
ULONG
CcspTr069PaSsp_CcspCwmpCfgNoRPCMethods
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Retrieves the device data model version supported by the TR-069 PA.
 *
 * This function returns the major and minor version numbers of the TR-069 data model
 * supported by the device.
 *
 * @param[in] hThisObject        Handle to the CCSP CWMP CPE Controller object.
 * @param[out] pulDevVerionMajor Pointer to receive the major version number.
 * @param[out] pulDevVersionMinor Pointer to receive the minor version number.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully retrieved data model version.
 *
 */
ANSC_STATUS
CcspTr069PaSsp_CcspCwmpCfgGetDevDataModelVersion
    (
        ANSC_HANDLE                 hThisObject,
        PULONG                      pulDevVerionMajor,
        PULONG                      pulDevVersionMinor
    );

/**
 * @brief Returns the HTTP session idle timeout value for TR-069 connections.
 *
 * This function returns the maximum idle timeout duration (in seconds) for HTTP sessions
 * between the CPE and ACS. When a TR-069 HTTP session remains idle for this duration,
 * the connection is closed.
 *
 * @param[in] hThisObject  Handle to the CCSP CWMP CPE Controller object.
 *
 * @return HTTP session idle timeout in seconds.
 * @retval HTTP session idle timeout duration on success.
 *
 */
ULONG
CcspTr069PaSsp_GetHttpSessionIdleTimeout
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Returns the CWMP RPC timeout value for TR-069 operations.
 *
 * This function returns the maximum timeout duration (in seconds) for TR-069 RPC method
 * execution. If an RPC method takes longer than this timeout to complete, the operation
 * is aborted and an error is returned to the ACS.
 *
 * @param[in] hThisObject  Handle to the CCSP CWMP CPE Controller object.
 *
 * @return CWMP RPC timeout in seconds.
 * @retval CWMP RPC timeout duration on success.
 *
 */
ULONG
CcspTr069PaSsp_GetCwmpRpcTimeout
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Retrieves custom forced inform parameters for TR-069 Inform messages.
 *
 * This function is called to load customized forced inform parameters that should be
 * included in every TR-069 Inform message, in addition to those defined in the TR-069
 * data model specification.
 *
 * @param[in] hThisObject  Handle to the CCSP CWMP CPE Controller object.
 *
 * @return Comma-separated list of custom forced inform parameter names.
 * @retval Non-NULL  Pointer to allocated string containing parameter names.
 * @retval NULL      No custom forced inform parameters configured.
 *
 */
char*
CcspTr069PaSsp_GetCustomForcedInformParams
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Retrieves the TR-069 certificate location configured for syndication partners.
 *
 * This function queries the PSM database to retrieve the TR-069 CA certificate file path
 * configured for syndication partners. It executes the PSM command to fetch the
 * Device.DeviceInfo.X_RDKCENTRAL-COM_Syndication.TR69CertLocation parameter value.
 *
 * @param[out] ppretTr069CertLocation  Pointer to receive the allocated certificate file path string.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully retrieved the certificate location.
 * @retval ANSC_STATUS_FAILURE  Failed to execute PSM command, parameter not found, or memory allocation failed.
 *
 */
ANSC_STATUS
CcspTr069PaSsp_GetTr069CertificateLocationForSyndication
    (
		char**						ppretTr069CertLocation
	);

/**
 * @brief Retrieves a configuration item value from the bootstrap JSON file by partner ID and item name.
 *
 * This function parses the bootstrap.json file to extract a specific configuration parameter
 * value for a given syndication partner. It searches for the partner ID object within the JSON
 * structure, locates the specified item name, and retrieves its ActiveValue.
 *
 * @param[in] partnerID   Partner identifier string.
 * @param[in] itemName    Configuration item name to retrieve.
 * @param[out] retVal     Pointer to receive the allocated configuration value string.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully retrieved the configuration item value.
 * @retval ANSC_STATUS_FAILURE  Failed to open JSON file, parse JSON, find partner ID, find item, or allocate memory.
 *
 */
ANSC_STATUS
CcspTr069PaSsp_JSON_GetItemByName    (
        char*                      partnerID,
        char*                      itemName,
        char**                     retVal
     );

/**
 * @brief Loads and parses the TR-069 PA configuration file.
 *
 * This function loads the TR-069 PA XML configuration file, parses it using the XML DOM parser,
 * and extracts various configuration parameters including OpenSSL certificate locations,
 * outbound interface settings, and ACS default address. Configuration values are stored in global
 * variables for use by the TR-069 PA components.
 *
 * @param[in] pCfgFileName  Path to the TR-069 PA XML configuration file.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully loaded and parsed the configuration file.
 * @retval ANSC_STATUS_FAILURE  Failed to open file, allocate memory, parse XML, or retrieve configuration values.
 * @retval ANSC_STATUS_RESOURCES Memory allocation failed.
 *
 */
ANSC_STATUS
CcspTr069PaSsp_LoadCfgFile
    (
        char*                       pCfgFileName
    );

/**
 * @brief Retrieves the TR-069 certificate location configured for syndication partners.
 *
 * This function queries the PSM database to retrieve the TR-069 CA certificate file path
 * configured for syndication partners. It executes the PSM command to fetch the
 * Device.DeviceInfo.X_RDKCENTRAL-COM_Syndication.TR69CertLocation parameter value.
 *
 * @param[out] ppretTr069CertLocation  Pointer to receive the allocated certificate file path string.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully retrieved the certificate location.
 * @retval ANSC_STATUS_FAILURE  Failed to execute PSM command, parameter not found, or memory allocation failed.
 *
 */
ANSC_STATUS
CcspTr069PaSsp_GetTr069CertificateLocationForSyndication
    (
                char**                                          ppretTr069CertLocation
        );

#endif
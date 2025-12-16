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

    module:	ccsp_cwmp_ifo_cfg.h

        For Broadband Home Manager Model Implementation (BBHM),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        This wrapper file defines the base class data structure and
        interface for CCSP CWMP configuration Objects.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Kang Quan

    ---------------------------------------------------------------

    revision:

        07/30/08    initial revision.
        10/12/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_IFO_CFG_
#define  _CCSP_CWMP_IFO_CFG_


/***********************************************************
    CCSP CWMP CONFIGURATION INTERFACE DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the os wrapper object definition.
 */
#define  CCSP_CWMP_CFG_INTERFACE_NAME                    "cwmpConfigurationIf"
#define  CCSP_CWMP_CFG_INTERFACE_ID                      0


#define  CCSP_CWMP_CFG_EVENT_CODE_BootstrapInformed               1
#define  CCSP_CWMP_CFG_EVENT_CODE_BootInformed                    2
#define  CCSP_CWMP_CFG_EVENT_CODE_AcsUrlChanged                   3

#define  CCSP_CWMP_CFG_RPC_METHOD_NO_Download            0x00000001
#define  CCSP_CWMP_CFG_RPC_METHOD_NO_Upload              0x00000002
#define  CCSP_CWMP_CFG_RPC_METHOD_NO_AddObject           0x00000004
#define  CCSP_CWMP_CFG_RPC_METHOD_NO_DeleteObject        0x00000008
#define  CCSP_CWMP_CFG_RPC_METHOD_NO_GetQueuedTransfers  0x00000010
#define  CCSP_CWMP_CFG_RPC_METHOD_NO_SetVouchers         0x00000020
#define  CCSP_CWMP_CFG_RPC_METHOD_NO_GetOptions          0x00000040
#define  CCSP_CWMP_CFG_RPC_METHOD_NO_ScheduleInform      0x00000080
#define  CCSP_CWMP_CFG_RPC_METHOD_NO_FactoryReset        0x00000100
#define  CCSP_CWMP_CFG_RPC_METHOD_NO_ChangeDUState       0x00000200

/* Hidden parameter ID */
#define  CCSP_CWMP_CFG_HPID_InitialContact               1
#define  CCSP_CWMP_CFG_HPID_EnableCWMP                   2
#define  CCSP_CWMP_CFG_HPID_TriggerCommand               3
#define  CCSP_CWMP_CFG_HPID_TriggerCommandKey            4
#define  CCSP_CWMP_CFG_HPID_SavedEvents                  5

/* Hidden parameter name */
#define  CCSP_CWMP_CFG_HPN_Device_InitialContact         "Device.X_CISCO_COM_COSADataModel.InitialContact"
#define  CCSP_CWMP_CFG_HPN_Device_EnableCWMP             "Device.X_CISCO_COM_COSADataModel.EnableCWMP"
#define  CCSP_CWMP_CFG_HPN_Device_TriggerCommand         "Device.X_CISCO_COM_COSADataModel.TriggerCommand"
#define  CCSP_CWMP_CFG_HPN_Device_TriggerCommandKey      "Device.X_CISCO_COM_COSADataModel.TriggerCommandKey"
#define  CCSP_CWMP_CFG_HPN_Device_SavedEvents            "Device.X_CISCO_COM_COSADataModel.SavedEvents"

#define  CCSP_CWMP_CFG_HPN_IGD_InitialContact            "InternetGatewayDevice.X_CISCO_COM_COSADataModel.InitialContact"
#define  CCSP_CWMP_CFG_HPN_IGD_EnableCWMP                "InternetGatewayDevice.X_CISCO_COM_COSADataModel.EnableCWMP"
#define  CCSP_CWMP_CFG_HPN_IGD_TriggerCommand            "InternetGatewayDevice.X_CISCO_COM_COSADataModel.TriggerCommand"
#define  CCSP_CWMP_CFG_HPN_IGD_TriggerCommandKey         "InternetGatewayDevice.X_CISCO_COM_COSADataModel.TriggerCommandKey"
#define  CCSP_CWMP_CFG_HPN_IGD_SavedEvents               "InternetGatewayDevice.X_CISCO_COM_COSADataModel.SavedEvents"

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support), we
 * have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */
/**
 * @brief Function pointer type to get delay value in seconds.
 *
 * This callback retrieves a delay value used for timing CWMP operations such as
 * bootstrap inform, boot inform, reboot, or factory reset delays.
 *
 * @param[in] hThisObject  Handle to the CWMP configuration object.
 *
 * @return Delay value in seconds.
 * @retval ULONG representing delay time in seconds (0 to ULONG_MAX).
 */
typedef  ULONG
(*PFN_CWMPCFGIF_GET_DELAY)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Function pointer type to get retry delay based on retry attempt number.
 *
 * This callback calculates the delay before retrying an inform operation,
 * typically with exponential backoff based on the retry count.
 *
 * @param[in] hThisObject    Handle to the CWMP configuration object.
 * @param[in] ulRetryNumber  Current retry attempt number.
 *                            Valid range: 0 to ULONG_MAX.
 *
 * @return Retry delay value in seconds.
 * @retval ULONG representing retry delay time in seconds.
 */
typedef  ULONG
(*PFN_CWMPCFGIF_GET_RETRY_DELAY)
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulRetryNumber
    );

/**
 * @brief Function pointer type to check if device is in bootstrap mode.
 *
 * This callback determines whether the CPE is performing its first-time
 * configuration (bootstrap) with the ACS or normal operation.
 *
 * @param[in] hThisObject  Handle to the CWMP configuration object.
 *
 * @return Bootstrap status flag.
 * @retval TRUE if device is in bootstrap mode (first contact with ACS).
 * @retval FALSE if device is in normal operational mode.
 *
 */
typedef  BOOL
(*PFN_CWMPCFGIF_IS_BOOTSTRAP)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Function pointer type to check if CWMP can start.
 *
 * This callback verifies whether CWMP protocol operations can be started,
 * checking prerequisites such as EnableCWMP parameter setting.
 *
 * @param[in] hThisObject  Handle to the CWMP configuration object.
 *
 * @return CWMP start permission flag.
 * @retval TRUE if CWMP operations are allowed to start.
 * @retval FALSE if CWMP operations should not start.
 *
 */
typedef  BOOL
(*PFN_CWMPCFGIF_CAN_START)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Function pointer type to notify configuration events.
 *
 * This callback notifies the configuration system of significant CWMP events
 * such as bootstrap informed, boot informed, or ACS URL changes.
 *
 * @param[in] hThisObject  Handle to the CWMP configuration object.
 * @param[in] ulEventCode  Event code identifier.
 *                          Valid values:
 *                          - CCSP_CWMP_CFG_EVENT_CODE_BootstrapInformed (1)
 *                          - CCSP_CWMP_CFG_EVENT_CODE_BootInformed (2)
 *                          - CCSP_CWMP_CFG_EVENT_CODE_AcsUrlChanged (3)
 *
 * @return None.
 *
 */
typedef  void
(*PFN_CWMPCFGIF_NOTIFY)
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulEventCode
    );

/**
 * @brief Function pointer type to get string configuration value.
 *
 * This callback retrieves string-based configuration values such as
 * default ACS username, connection request URL, username, or password.
 *
 * @param[in] hThisObject  Handle to the CWMP configuration object.
 *
 * @return Pointer to null-terminated string value.
 * @retval char* pointer to configuration string.
 * @retval NULL if value is not available.
 *
 */
typedef  char*
(*PFN_CWMPCFGIF_GET_STRING)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Function pointer type to set string configuration value.
 *
 * This callback sets string-based configuration values such as
 * connection request username or password.
 *
 * @param[in] hThisObject  Handle to the CWMP configuration object.
 * @param[in] pString      Pointer to null-terminated string value to set.
 *                          Must be a valid string pointer.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if operation is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCFGIF_SET_STRING)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pString
    );

/**
 * @brief Function pointer type to get bitmask of unsupported RPC methods.
 *
 * This callback returns a bitmask indicating which TR-069 RPC methods are
 * not supported or disabled on this device.
 *
 * @param[in] hThisObject  Handle to the CWMP configuration object.
 *
 * @return Bitmask of disabled RPC methods.
 * @retval ULONG bitmask with flags from CCSP_CWMP_CFG_RPC_METHOD_NO_* constants.
 *
 */
typedef  ULONG
(*PFN_CWMPCFGIF_NO_METHODS)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Function pointer type to get hidden parameter name by ID.
 *
 * This callback maps a hidden parameter ID to its full parameter path name
 * in either Device (TR-181) or IGD (TR-098) data model.
 *
 * @param[in] hThisObject      Handle to the CWMP configuration object.
 * @param[in] ulHiddenParamId  Hidden parameter identifier.
 *                              Valid values:
 *                              - CCSP_CWMP_CFG_HPID_InitialContact (1)
 *                              - CCSP_CWMP_CFG_HPID_EnableCWMP (2)
 *                              - CCSP_CWMP_CFG_HPID_TriggerCommand (3)
 *                              - CCSP_CWMP_CFG_HPID_TriggerCommandKey (4)
 *                              - CCSP_CWMP_CFG_HPID_SavedEvents (5)
 *
 * @return Pointer to full parameter path string.
 * @retval char* pointer to parameter name string.
 * @retval NULL if parameter ID is not recognized.
 *
 */
typedef  char*
(*PFN_CWMPCFGIF_GET_HPARAM_NAME)
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulHiddenParamId
    );

/**
 * @brief Function pointer type to generate connection request URL path.
 *
 * This callback generates the URL path component for the connection request URL,
 * which the ACS uses to initiate connections to the CPE.
 *
 * @param[in]  hThisObject    Handle to the CWMP configuration object.
 * @param[out] pConnReqUrl    Pointer to buffer for storing generated URL path.
 *                             Must be pre-allocated with sufficient size.
 * @param[in]  ulSize         Size of the pConnReqUrl buffer in bytes.
 *                             Valid range: 1 to ULONG_MAX.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if URL path generation is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCFGIF_GEN_CR_URL_PATH)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pConnReqUrl,
        ULONG                       ulSize
    );

/**
 * @brief Function pointer type to customize ACS URL.
 *
 * This callback allows customization or transformation of the ACS URL
 * before establishing connection to the Auto Configuration Server.
 *
 * @param[in] hThisObject  Handle to the CWMP configuration object.
 * @param[in] pAcsUrl      Pointer to original ACS URL string.
 *                          Must be a valid, null-terminated string.
 *
 * @return Pointer to customized ACS URL string.
 * @retval char* pointer to modified or original ACS URL.
 * @retval NULL if customization is not needed.
 *
 */
typedef	 char*
(*PFN_CWMPCFGIF_CUSTOMIZE_ACSURL)
	(
		ANSC_HANDLE					hThisObject,
		char*						pAcsUrl
	);

/**
 * @brief Function pointer type to get device data model version.
 *
 * This callback retrieves the major and minor version numbers of the
 * TR-069 data model supported by the device.
 *
 * @param[in]  hThisObject        Handle to the CWMP configuration object.
 * @param[out] pulDevVerionMajor  Pointer to store major version number.
 *                                 Typically 1 for TR-098, 2 for TR-181.
 * @param[out] pulDevVersionMinor Pointer to store minor version number.
 *                                 Typically 0 or higher.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS if version retrieval is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCFGIF_GET_DEV_DM_VER)
    (
        ANSC_HANDLE                 hThisObject,
        PULONG                      pulDevVerionMajor,
        PULONG                      pulDevVersionMinor
    );

/**
 * @brief Function pointer type to get timeout value in seconds.
 *
 * This callback retrieves timeout values for HTTP session idle timeout
 * or CWMP RPC operation timeout.
 *
 * @param[in] hThisObject  Handle to the CWMP configuration object.
 *
 * @return Timeout value in seconds.
 * @retval ULONG representing timeout in seconds (0 to ULONG_MAX).
 *
 */
typedef	 ULONG
(*PFN_CWMPCFGIF_GET_TIMEOUT)
	(
		ANSC_HANDLE					hThisObject
	);

/**
 * @brief Function pointer type to get custom forced inform parameters.
 *
 * This callback retrieves comma-separated list of custom parameter names to be
 * included in Inform messages beyond the standard forced inform parameters
 * defined in TR-098 or TR-181 data models. The returned string is allocated
 * by this function and must be freed by the caller.
 *
 * @param[in] hThisObject  Handle to the CWMP configuration object.
 *
 * @return Pointer to comma-separated parameter names string.
 * @retval char* pointer to dynamically allocated string of parameter names.
 * @retval NULL if no custom forced inform parameters are configured.
 *
 */
typedef	 char*
(*PFN_CWMPCFGIF_GET_CFIP)
	(
		ANSC_HANDLE					hThisObject
	);


/*
 * As a general requirement, each module SHOULD provide an interface for external components to
 * configure its parameters and policies. Although the benefit of unifying the definition and usage
 * of such an interface is obvious, we DON'T want to impose any set of rules on the implementation.
 * Instead, we expect every module will implement its configuration interfaces independently.
 */
#define  CCSP_CWMP_CFG_INTERFACE_CLASS_CONTENT                                              \
    /* duplication of the base object class content */                                      \
    ANSCIFO_CLASS_CONTENT                                                                   \
    /* start of object class content */                                                     \
    PFN_CWMPCFGIF_NO_METHODS        NoRPCMethods;                                           \
                                                                                            \
    PFN_CWMPCFGIF_IS_BOOTSTRAP      IsBootstrap;                                            \
    PFN_CWMPCFGIF_GET_DELAY         GetBootstrapInformDelay;                                \
    PFN_CWMPCFGIF_GET_DELAY         GetBootInformDelay;                                     \
    PFN_CWMPCFGIF_GET_RETRY_DELAY   GetRetryInformDelay;                                    \
                                                                                            \
    PFN_CWMPCFGIF_NOTIFY            NotifyEvent;                                            \
                                                                                            \
    PFN_CWMPCFGIF_GET_STRING        GetDefaultAcsUsername;                                  \
    PFN_CWMPCFGIF_GET_STRING        GetConnRequestUrl;                                      \
    PFN_CWMPCFGIF_GET_STRING        GetConnRequestUsername;                                 \
    PFN_CWMPCFGIF_SET_STRING        SetConnRequestUsername;                                 \
    PFN_CWMPCFGIF_GET_STRING        GetConnRequestPassword;                                 \
    PFN_CWMPCFGIF_SET_STRING        SetConnRequestPassword;                                 \
                                                                                            \
    PFN_CWMPCFGIF_GET_DELAY         GetRebootDelay;                                         \
    PFN_CWMPCFGIF_GET_DELAY         GetFactoryResetDelay;                                   \
                                                                                            \
    PFN_CWMPCFGIF_GET_HPARAM_NAME   GetHiddenCwmpParamName;                                 \
    PFN_CWMPCFGIF_CAN_START         CanCwmpStart;                                           \
    PFN_CWMPCFGIF_GEN_CR_URL_PATH   GenerateConnReqUrlPath;                                 \
																							\
	PFN_CWMPCFGIF_CUSTOMIZE_ACSURL	CustomizeAcsUrl;										\
                                                                                            \
    PFN_CWMPCFGIF_GET_DEV_DM_VER    GetDevDataModelVer;                                     \
																							\
	PFN_CWMPCFGIF_GET_TIMEOUT		GetHttpSessionIdleTimeout;								\
	PFN_CWMPCFGIF_GET_TIMEOUT		GetCwmpRpcTimeout;										\
																							\
	/* API GetCustomForcedInformParams is called while configured to load customized		\
     * Forced Inform Parameters other than those defined in Data Model Definition such		\
     * as TR-098 or TR-181 etc. Return value would be comma-separated full parameter		\
     * names, this API allocates the memory returned and caller will release it */			\
	PFN_CWMPCFGIF_GET_CFIP			GetCustomForcedInformParams;							\
    /* end of object class content */                                                       \

typedef  struct
_CCSP_CWMP_CFG_INTERFACE
{
    CCSP_CWMP_CFG_INTERFACE_CLASS_CONTENT
}
CCSP_CWMP_CFG_INTERFACE,  *PCCSP_CWMP_CFG_INTERFACE;

#define  ACCESS_CCSP_CWMP_CFG_INTERFACE(p)               \
         ACCESS_CONTAINER(p, CCSP_CWMP_CFG_INTERFACE, Linkage)


#endif

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

    module:	ccsp_cwmp_stunmo_interface.h

        For CCSP CWMP protocol

    ---------------------------------------------------------------

    description:

        This wrapper file defines the base class data structure and
        interface for the CCSP CWMP Stun Manager Objects.

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


#ifndef  _CCSP_CWMP_STUNMO_INTERFACE_
#define  _CCSP_CWMP_STUNMO_INTERFACE_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_co_interface.h"
#include "ansc_co_external_api.h"
#include "ccsp_cwmp_properties.h"

#include "stun_ifo_bsm.h"


/***********************************************************
    CCSP CWMP STUN MANAGER COMPONENT OBJECT DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the os wrapper object definition.
 */

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support), we
 * have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */

/**
 * @brief Retrieves a context handle from the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for retrieving internal context handles
 * from the STUN Manager object, such as the CPE Controller handle or STUN Simple Client handle.
 * These context handles are used for inter-object communication within the TR-069 framework.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Handle to the requested context object.
 * @retval Valid ANSC_HANDLE  Successfully retrieved context handle.
 * @retval NULL               Context not set or object not initialized.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CCSPSTUNMO_GET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Configures a context handle in the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for setting internal context handles
 * in the STUN Manager object, such as the CPE Controller handle. This establishes relationships
 * between the STUN Manager and other TR-069 component objects.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 * @param[in] hContext    Handle to the context object to be configured.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully configured context handle.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_SET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hContext
    );

/**
 * @brief Retrieves an interface handle from the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for retrieving interface handles
 * from the STUN Manager object. These interfaces provide communication pathways between
 * the STUN Manager and other system components in the TR-069 architecture.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Handle to the requested interface.
 * @retval Valid ANSC_HANDLE  Successfully retrieved interface handle.
 * @retval NULL               Interface not available or not initialized.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CCSPSTUNMO_GET_IF)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Configures an interface handle in the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for setting interface handles
 * in the STUN Manager object. This establishes communication pathways and callbacks
 * between the STUN Manager and other system components.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 * @param[in] hInterface  Handle to the interface object to be configured.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully configured interface handle.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_SET_IF)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hInterface
    );

/**
 * @brief Retrieves the name string from the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for retrieving the name or
 * identifier string associated with the STUN Manager object. This name is used for
 * identification and debugging purposes within the TR-069 framework.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Pointer to the name string.
 * @retval Non-NULL  Pointer to the object's name string.
 * @retval NULL      Name not set or object not initialized.
 *
 */
typedef  char*
(*PFN_CCSPSTUNMO_GET_NAME)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Configures the name string for the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for setting the name or identifier
 * string for the STUN Manager object. This name is used for identification and debugging
 * purposes within the TR-069 framework.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 * @param[in] name        Pointer to the name string to be assigned to the object.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully configured name string.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_SET_NAME)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       name
    );

/**
 * @brief Retrieves the client IP address from the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for retrieving the STUN client's
 * IP address from the STUN Manager's property configuration. The address is used for
 * STUN binding requests and NAT traversal operations.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return IPv4 address in network byte order (ULONG value).
 * @retval Non-zero  Valid IPv4 address configured for STUN client.
 * @retval 0         No address configured (may use default local address).
 *
 */
typedef  ULONG
(*PFN_CCSPSTUNMO_GET_ADDR)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Configures the client IP address in the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for setting the STUN client's
 * IP address in the STUN Manager's property configuration. This address is used for
 * STUN binding requests and NAT traversal operations.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 * @param[in] ulAddr      IPv4 address in network byte order (ULONG value) to be configured.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully configured client IP address.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_SET_ADDR)
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulAddr
    );

/**
 * @brief Retrieves the property configuration from the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for retrieving the STUN Manager's
 * property configuration, which includes client address and port settings. The property
 * data is copied into the caller-provided structure.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 * @param[out] hProperty  Handle to the property data structure to be filled with current
 *                        configuration (CCSP_CWMP_STUN_MANAGER_PROPERTY).
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully retrieved property configuration.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_GET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Configures the property settings for the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for setting the STUN Manager's
 * property configuration, which includes client address and port settings. The property
 * data is copied from the caller-provided structure into the object's internal state.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 * @param[in] hProperty   Handle to the property data structure containing the configuration
 *                        to be applied (CCSP_CWMP_STUN_MANAGER_PROPERTY).
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully configured property settings.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_SET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Retrieves the operating mode from the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for retrieving the current
 * operating mode of the STUN Manager. The mode determines the behavior and configuration
 * of STUN protocol operations.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Current operating mode (ULONG value).
 *
 */
typedef  ULONG
(*PFN_CCSPSTUNMO_GET_MODE)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Configures the operating mode for the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for setting the operating mode
 * of the STUN Manager. The mode determines the behavior and configuration of STUN
 * protocol operations.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 * @param[in] ulMode      Operating mode value to be configured.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully configured operating mode.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_SET_MODE)
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulMode
    );

/**
 * @brief Resets the CCSP CWMP STUN Manager object to its initial state.
 *
 * This function pointer typedef defines the interface for resetting the STUN Manager
 * object. When used as ResetProperty, it resets property configuration to default values.
 * When used as Reset, it resets the object's runtime state.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully reset object state or properties.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_RESET)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Engages the CCSP CWMP STUN Manager object to start STUN operations.
 *
 * This function pointer typedef defines the interface for activating the STUN Manager
 * object. It sets up the STUN BSM interface, configures the STUN Simple Client, calls
 * SetupEnv to prepare the operating environment, sets the bActive flag to TRUE, and
 * loads STUN policy configuration. If already active, returns immediately.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS   Successfully engaged STUN Manager operations.
 * @retval ANSC_STATUS_NOT_READY CPE Controller not configured, cannot engage.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_ENGAGE)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Cancels the CCSP CWMP STUN Manager object's active operations.
 *
 * This function pointer typedef defines the interface for deactivating the STUN Manager
 * object. It sets bActive to FALSE, waits for any retry tasks to complete (up to 10 seconds),
 * cancels the STUN Simple Client operations, resets the object state, and calls CloseEnv
 * to tear down the operating environment. If already inactive, returns immediately.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully canceled STUN Manager operations.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_CANCEL)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Sets up the operating environment for the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for preparing the operating
 * environment before engaging STUN operations.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully set up operating environment.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_SETUP_ENV)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Closes the operating environment for the CCSP CWMP STUN Manager object.
 *
 * This function pointer typedef defines the interface for tearing down the operating
 * environment after canceling STUN operations.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully closed operating environment.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_CLOSE_ENV)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Loads the STUN policy configuration from system registry.
 *
 * This function pointer typedef defines the interface for loading STUN policy and
 * configuration settings. It retrieves STUN information from the registry via
 * RegGetStunInfo and applies the settings to the STUN Simple Client via ApplyStunSettings.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully loaded and applied STUN policy.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_LOAD)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Applies STUN configuration settings to the STUN Simple Client.
 *
 * This function pointer typedef defines the interface for applying STUN configuration
 * changes. It resolves the STUN server address (from STUNServerAddress or ACS URL hostname),
 * cancels the current STUN client, configures client/server addresses and ports, sets
 * username/password/keep-alive intervals, re-engages the client, and initiates STUN
 * binding requests if STUN is enabled.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully applied STUN settings to client.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_APPLY)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Retrieves the ACS hostname from the ACS URL for STUN operations.
 *
 * This function pointer typedef defines the interface for extracting the hostname from
 * the ACS URL. It parses the URL to extract the host portion. The hostname is used as
 * the STUN server address when STUNServerAddress is not explicitly configured. The
 * caller must free the returned string.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Pointer to dynamically allocated hostname string.
 * @retval Non-NULL  Successfully extracted hostname from ACS URL (caller must free).
 * @retval NULL      ACS URL not configured or hostname extraction failed.
 *
 */
typedef  char*
(*PFN_CCSPSTUNMO_GET_HOST)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Retrieves STUN configuration from the system registry.
 *
 * This function pointer typedef defines the interface for loading STUN configuration
 * parameters from the Management Server functional component. It retrieves STUNEnable,
 * STUNServerAddress, STUNServerPort, STUNUsername, STUNPassword, STUNMaximumKeepAlivePeriod,
 * STUNMinimumKeepAlivePeriod, and NATDetected values from the registry into the
 * CcspCwmpStunInfo structure.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully retrieved STUN configuration from registry.
 * @retval ANSC_STATUS_FAILURE  Failed to copy string values due to buffer size errors.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_REG_GET)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Writes STUN configuration to the system registry.
 *
 * This function pointer typedef defines the interface for persisting STUN configuration
 * parameters to the Management Server functional component. Currently a placeholder
 * implementation as STUN configuration writing is disabled.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP STUN Manager object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully wrote STUN configuration.
 *
 */
typedef  ANSC_STATUS
(*PFN_CCSPSTUNMO_REG_SET)
    (
        ANSC_HANDLE                 hThisObject
    );

/*
 * STUN is a lightweight protocol that allows applications to discover the presence and types of
 * NATs and firewalls between them and the public Internet. It also provides the ability for
 * applications to determine the public Internet Protocol addresses allocated to them by NAT. STUN
 * works with many existing NATs, and does not require any special behavior from them. As a result,
 * it allows a wide variety of applications to work through existing NAT infrastructure.
 */
#define  CCSP_CWMP_STUN_MANAGER_CLASS_CONTENT                                               \
    /* duplication of the base object class content */                                      \
    ANSCCO_CLASS_CONTENT                                                                    \
    /* start of object class content */                                                     \
    CCSP_CWMP_STUN_MANAGER_PROPERTY Property;                                               \
    CCSP_CWMP_STUN_INFO             CcspCwmpStunInfo;                                       \
    ANSC_HANDLE                     hCcspCwmpCpeController;                                 \
    ANSC_HANDLE                     hStunBsmIf;                                             \
    ANSC_HANDLE                     hStunSimpleClient;                                      \
    BOOL                            bActive;                                                \
    ULONG                           LastUdpConnReqTS;                                       \
    ULONG                           LastUdpConnReqID;                                       \
    BOOL                            bRetryTaskRunning;                                      \
                                                                                            \
    PFN_CCSPSTUNMO_GET_CONTEXT      GetCcspCwmpCpeController;                               \
    PFN_CCSPSTUNMO_SET_CONTEXT      SetCcspCwmpCpeController;                               \
    PFN_CCSPSTUNMO_GET_CONTEXT      GetStunSimpleClient;                                    \
    PFN_CCSPSTUNMO_GET_ADDR         GetClientAddr;                                          \
    PFN_CCSPSTUNMO_SET_ADDR         SetClientAddr;                                          \
    PFN_CCSPSTUNMO_GET_PROPERTY     GetProperty;                                            \
    PFN_CCSPSTUNMO_SET_PROPERTY     SetProperty;                                            \
    PFN_CCSPSTUNMO_RESET            ResetProperty;                                          \
    PFN_CCSPSTUNMO_RESET            Reset;                                                  \
                                                                                            \
    PFN_CCSPSTUNMO_ENGAGE           Engage;                                                 \
    PFN_CCSPSTUNMO_CANCEL           Cancel;                                                 \
    PFN_CCSPSTUNMO_SETUP_ENV        SetupEnv;                                               \
    PFN_CCSPSTUNMO_CLOSE_ENV        CloseEnv;                                               \
                                                                                            \
    PFN_CCSPSTUNMO_LOAD             LoadPolicy;                                             \
    PFN_CCSPSTUNMO_APPLY            ApplyStunSettings;                                      \
    PFN_CCSPSTUNMO_GET_HOST         GetAcsHostName;                                         \
                                                                                            \
    PFN_CCSPSTUNMO_REG_GET          RegGetStunInfo;                                         \
    PFN_CCSPSTUNMO_REG_SET          RegSetStunInfo;                                         \
                                                                                            \
    PFN_STUNBSMIF_RECV              StunBsmRecvMsg1;                                        \
    PFN_STUNBSMIF_RECV              StunBsmRecvMsg2;                                        \
    PFN_STUNBSMIF_NOTIFY            StunBsmNotify;                                          \
    /* end of object class content */                                                       \

typedef  struct
_CCSP_CWMP_STUN_MANAGER_OBJECT
{
    CCSP_CWMP_STUN_MANAGER_CLASS_CONTENT
}
CCSP_CWMP_STUN_MANAGER_OBJECT,  *PCCSP_CWMP_STUN_MANAGER_OBJECT;

#define  ACCESS_CCSP_CWMP_STUN_MANAGER_OBJECT(p)         \
         ACCESS_CONTAINER(p, CCSP_CWMP_STUN_MANAGER_OBJECT, Linkage)


#endif

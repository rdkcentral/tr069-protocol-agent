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

    module:	ccsp_cwmp_tcpcrho_interface.h

        For CCSP CWMP protocol implementation

    ---------------------------------------------------------------

    description:

        This wrapper file defines all the platform-independent
        functions and macros for CCSP CWMP TCP Connection Request
        Handler object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Kang Quan

    ---------------------------------------------------------------

    revision:

        08/19/08    initial revision.
        10/12/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_TCPCRHO_INTERFACE_
#define  _CCSP_CWMP_TCPCRHO_INTERFACE_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_co_interface.h"
#include "ansc_co_external_api.h"

#include "ansc_dsto_interface.h"
#include "ansc_dsto_external_api.h"
#include "ansc_dstowo_interface.h"

#include "http_properties.h"
#include "http_autho_info.h"
#include "web_properties.h"

/***********************************************************
PLATFORM INDEPENDENT CCSP CWMP TCP CONNECTION REQUEST HANDLER
***********************************************************/

/***********************************************************
CCSP CWMP TCP CONNECTION REQUEST HANDLER PROPERTY DEFINITION
***********************************************************/

#define  CCSP_CWMP_TCPCR_HANDLER_NAME                    "cwmpTcpConnReqHandler"
#define  CCSP_CWMP_TCPCR_HANDLER_OID                     0

#define  CCSP_CWMP_TCPCR_HANDLER_MODE_useXsocket         0x00000001

#define  CCSP_CWMP_TCPCR_HANDLER_DefSessionTimeout       1200    /* in seconds */

#define  CCSP_CWMP_TCPCR_MAX_MSG_SIZE                    4096    /* in bytes */

#define  CCSP_CWMP_TCPCR_SESSION_MODE_FINISH             0
#define  CCSP_CWMP_TCPCR_SESSION_MODE_COLLECT            1
#define  CCSP_CWMP_TCPCR_SESSION_MODE_PROCESS            2

#define  CCSP_CWMP_TCPCR_CWMP_TCP_PORT                   7547

#define  CCSP_CWMP_TCPCR_COOKIE_MAGIC_NUMBER             "MGCN"

typedef  struct
_CCSP_CWMP_TCPCR_HANDLER_PROPERTY
{
#ifdef _ANSC_IPV6_COMPATIBLE_
    char                            HostAddr[INET6_ADDRSTRLEN];
#else
    ANSC_IPV4_ADDRESS               HostAddress;
#endif
    USHORT                          HostPort;
    ULONG                           ServerMode;

    ULONG                           SessionTimeout;

    WEB_AUTH_SERVER_PROPERTY        AuthProperty;
}
CCSP_CWMP_TCPCR_HANDLER_PROPERTY,  *PCCSP_CWMP_TCPCR_HANDLER_PROPERTY;


typedef  struct
_CCSP_CWMP_TCPCR_HANDLER_SESSINFO
{
    WEB_AUTH_SESS_INFO_CONTENT

#ifdef _ANSC_IPV6_COMPATIBLE_
    char                            RemoteAddress[INET6_ADDRSTRLEN];
#else
    ULONG                           RemoteAddr;
#endif
}
CCSP_CWMP_TCPCR_HANDLER_SESSINFO, *PCCSP_CWMP_TCPCR_HANDLER_SESSINFO;


/*
 * Define some const values that will be used in the object mapper object definition.
 */

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support),
 * we have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */

/**
 * @brief Retrieves a context handle from the CCSP CWMP TCP Connection Request Handler object.
 *
 * This function pointer typedef defines the interface for retrieving internal context handles
 * from the TCP Connection Request Handler, specifically the CPE Controller handle. These context
 * handles are used for inter-object communication within the TR-069 framework.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 *
 * @return Handle to the requested context object.
 * @retval Valid ANSC_HANDLE  Successfully retrieved context handle (CPE Controller).
 * @retval NULL               Context not set or object not initialized.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPTCPCRHO_GET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Configures a context handle in the CCSP CWMP TCP Connection Request Handler object.
 *
 * This function pointer typedef defines the interface for setting internal context handles,
 * specifically the CPE Controller handle. This establishes the relationship between the TCP
 * Connection Request Handler and the CPE Controller for processing connection requests.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 * @param[in] hContext    Handle to the context object (CPE Controller) to be configured.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully configured context handle.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPTCPCRHO_SET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hContext
    );

/**
 * @brief Retrieves an interface handle from the CCSP CWMP TCP Connection Request Handler object.
 *
 * This function pointer typedef defines the interface for retrieving the Web Access Control
 * Manager (ACM) interface handle. This interface is used for authentication and authorization
 * of incoming TCP connection requests from the ACS.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 *
 * @return Handle to the requested interface.
 * @retval Valid ANSC_HANDLE  Successfully retrieved Web ACM interface handle.
 * @retval NULL               Interface not configured or not initialized.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPTCPCRHO_GET_IF)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Configures an interface handle in the CCSP CWMP TCP Connection Request Handler object.
 *
 * This function pointer typedef defines the interface for setting the Web Access Control
 * Manager (ACM) interface handle. This interface provides authentication and authorization
 * services for validating incoming TCP connection requests.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 * @param[in] hInterface  Handle to the Web ACM interface object to be configured.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully configured interface handle.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPTCPCRHO_SET_IF)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hInterface
    );

/**
 * @brief Retrieves the property configuration from the CCSP CWMP TCP Connection Request Handler.
 *
 * This function pointer typedef defines the interface for retrieving the handler's property
 * configuration, which includes host address, port, server mode, session timeout, and
 * authentication properties. The property data is copied into the caller-provided structure.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 * @param[out] hProperty  Handle to the property data structure to be filled with current
 *                        configuration (CCSP_CWMP_TCPCR_HANDLER_PROPERTY).
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully retrieved property configuration.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPTCPCRHO_GET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Configures the property settings for the CCSP CWMP TCP Connection Request Handler.
 *
 * This function pointer typedef defines the interface for setting the handler's property
 * configuration, which includes host address, port, server mode, session timeout, and
 * authentication properties. The property data is copied from the caller-provided structure.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 * @param[in] hProperty   Handle to the property data structure containing the configuration
 *                        to be applied (CCSP_CWMP_TCPCR_HANDLER_PROPERTY).
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully configured property settings.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPTCPCRHO_SET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Resets the CCSP CWMP TCP Connection Request Handler object to initial state.
 *
 * This function pointer typedef defines the interface for resetting the handler object.
 * When used as ResetProperty, it resets property configuration to defaults. When used as Reset, it
 * resets runtime state including magic ID and last access time.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully reset object state or properties.
 * @retval ANSC_STATUS_FAILURE  Failed to copy string values during property reset.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPTCPCRHO_RESET)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Engages the CCSP CWMP TCP Connection Request Handler to start processing requests.
 *
 * This function pointer typedef defines the interface for activating the handler. It creates
 * TCP servers via CreateTcpServers, configures server mode (XSocket support), sets engine and
 * socket counts, configures host address/port, and engages the TCP server to listen for
 * incoming connection requests from the ACS on port 7547.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully engaged TCP Connection Request Handler.
 * @retval ANSC_STATUS_FAILURE  Failed to set host address during server configuration.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPTCPCRHO_ENGAGE)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Cancels the CCSP CWMP TCP Connection Request Handler's active operations.
 *
 * This function pointer typedef defines the interface for deactivating the handler. It sets
 * bActive to FALSE, cancels the TCP server to stop accepting new connections, and removes
 * TCP servers via RemoveTcpServers to tear down the listening infrastructure. If already
 * inactive, returns immediately.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully canceled TCP Connection Request Handler operations.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPTCPCRHO_CANCEL)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Processes incoming TCP connection request messages from the ACS.
 *
 * This function pointer typedef defines the interface for processing connection request
 * messages received on the TCP server. It validates the request format, performs authentication
 * via VerifyCredential if Web ACM interface is configured, generates HTTP response, sends the response back to the ACS, and signals the CPE Controller to
 * initiate a CWMP session if authentication succeeds.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 * @param[in] hSocket     Handle to the socket from which the message was received.
 * @param[in] buffer      Pointer to the data buffer containing the connection request message.
 * @param[in] ulSize      Size of the data buffer in bytes.
 *
 * @return Status of the operation.
 * @retval ANSC_STATUS_SUCCESS    Successfully processed request and sent response.
 * @retval ANSC_STATUS_RESOURCES  Failed to allocate memory for response message.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPTCPCRHO_PROCESS_REQ)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSocket,
        PVOID                       buffer,
        ULONG                       ulSize
    );

/**
 * @brief Authenticates incoming TCP connection requests.
 *
 * This function pointer typedef defines the interface for authenticating connection request
 * messages.
 *
 * @param[in] hThisObject Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 * @param[in] buffer      Pointer to the data buffer containing the request to authenticate.
 * @param[in] ulSize      Size of the data buffer in bytes.
 *
 * @return Status of the authentication operation.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPTCPCRHO_AUTH_REQ)
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        ULONG                       ulSize
    );

/**
 * @brief Verifies client credentials in the TCP connection request message.
 *
 * This function pointer typedef defines the interface for validating authentication credentials
 * provided in the connection request. It extracts HTTP authentication information (Basic or Digest),
 * retrieves the request host/URI, obtains the password from the Web ACM interface, verifies the
 * credentials, and updates the session authentication information if verification succeeds.
 *
 * @param[in] hThisObject    Handle to the CCSP CWMP TCP Connection Request Handler object itself.
 * @param[in] buffer         Pointer to the data buffer containing the request with credentials.
 * @param[in] ulSize         Size of the data buffer in bytes.
 * @param[in] hSessAuthInfo  Handle to the session's authentication info structure
 *                           (WEB_AUTH_SESSION_INFO) for credential verification.
 *
 * @return Status of the credential verification operation.
 * @retval ANSC_STATUS_SUCCESS       Successfully verified credentials.
 * @retval ANSC_STATUS_DO_IT_AGAIN   No authentication information found, retry needed.
 * @retval ANSC_STATUS_BAD_AUTH_DATA Failed to extract host/URI or invalid credentials.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPTCPCRHO_VERIFY_CRED)
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        ULONG                       ulSize,
        ANSC_HANDLE                 hSessAuthInfo
    );

/*
 * TR-069 defines a very simple way for CPE to connection to ACS in order for ACS to
 * manage CPE by using CWMP protocol. This object handles TCP connection request. By
 * nature, only one ACS is going to be used specified at any time to manage CPE. So
 * this object is actually an oversimplified web server that we can safely assume
 * there's only one session at most at any time. This object only maintains one
 * session that expires after the specified amount of time.
 */
#define  CCSP_CWMP_TCPCR_HANDLER_CLASS_CONTENT                                              \
    /* duplication of the base object class content */                                      \
    ANSCCO_CLASS_CONTENT                                                                    \
    /* start of object class content */                                                     \
    CCSP_CWMP_TCPCR_HANDLER_PROPERTY     Property;                                          \
    ANSC_HANDLE                     hTcpServer;                                             \
    ANSC_HANDLE                     hDstoWorker;                                            \
    BOOL                            bActive;                                                \
    ANSC_HANDLE                     hCcspCwmpCpeController;                                 \
    ULONG                           MagicID;                                                \
    ULONG                           LastAccessTime;                                         \
    CCSP_CWMP_TCPCR_HANDLER_SESSINFO     AuthSessionInfo;                                   \
    ANSC_HANDLE                     hWebAcmIf;                                              \
                                                                                            \
    PFN_CWMPTCPCRHO_GET_CONTEXT     GetCcspCwmpCpeController;                               \
    PFN_CWMPTCPCRHO_SET_CONTEXT     SetCcspCwmpCpeController;                               \
    PFN_CWMPTCPCRHO_GET_IF          GetWebAcmIf;                                            \
    PFN_CWMPTCPCRHO_SET_IF          SetWebAcmIf;                                            \
    PFN_CWMPTCPCRHO_GET_PROPERTY    GetProperty;                                            \
    PFN_CWMPTCPCRHO_SET_PROPERTY    SetProperty;                                            \
    PFN_CWMPTCPCRHO_RESET           ResetProperty;                                          \
    PFN_CWMPTCPCRHO_RESET           Reset;                                                  \
                                                                                            \
    PFN_CWMPTCPCRHO_ENGAGE          Engage;                                                 \
    PFN_CWMPTCPCRHO_CANCEL          Cancel;                                                 \
    PFN_CWMPTCPCRHO_ENGAGE          CreateTcpServers;                                       \
    PFN_CWMPTCPCRHO_CANCEL          RemoveTcpServers;                                       \
                                                                                            \
    PFN_DSTOWO_ACCEPT               DstowoAccept;                                           \
    PFN_DSTOWO_SETOUT               DstowoSetOut;                                           \
    PFN_DSTOWO_REMOVE               DstowoRemove;                                           \
    PFN_DSTOWO_QUERY                DstowoQuery;                                            \
    PFN_DSTOWO_PROCESS              DstowoProcessSync;                                      \
    PFN_DSTOWO_PROCESS              DstowoProcessAsync;                                     \
    PFN_DSTOWO_COMPLETE             DstowoSendComplete;                                     \
    PFN_DSTOWO_NOTIFY               DstowoNotify;                                           \
                                                                                            \
    PFN_CWMPTCPCRHO_PROCESS_REQ     ProcessRequest;                                         \
    PFN_CWMPTCPCRHO_VERIFY_CRED     VerifyCredential;                                       \
    /* end of object class content */                                                       \

typedef  struct
_CCSP_CWMP_TCPCR_HANDLER_OBJECT
{
    CCSP_CWMP_TCPCR_HANDLER_CLASS_CONTENT
}
CCSP_CWMP_TCPCR_HANDLER_OBJECT,  *PCCSP_CWMP_TCPCR_HANDLER_OBJECT;

#define  ACCESS_CCSP_CWMP_TCPCR_HANDLER_OBJECT(p)          \
         ACCESS_CONTAINER(p, CCSP_CWMP_TCPCR_HANDLER_OBJECT, Linkage)


#endif
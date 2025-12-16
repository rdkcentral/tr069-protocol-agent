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

    module: ccsp_cwmp_acsconn_internal_api.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the internal functions provided by the CCSP CWMP ACS Connection
        Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Bin Zhu
        Kang Quan

    ---------------------------------------------------------------

    revision:

        09/21/05    initial revision.
        10/13/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_ACSCONN_INTERNAL_API_
#define  _CCSP_CWMP_ACSCONN_INTERNAL_API_

/***********************************************************
         CONST VALUES FOR ACSCONNECTION
***********************************************************/
/*
 * URL for the CPE to connect to the ACS using the CPE
 * WAN Management Protocol. In one of the folowing forms:
 *
 *  x-dslf_cwmp://host:port/
 *  x-dslf_cwmps://host:port/
 *
 * The "s" suffix of the scheme component indicates the use
 * of SSL.
 */
#define  ACS_DSLF_CWMP                          "x-dslf_cwmp"
#define  ACS_DSLF_CWMPS                         "x-dslf_cwmps"

/***********************************************************
         FUNCTIONS IMPLEMENTED IN CCSP_CWMP_ACSCO_STATES.C
***********************************************************/

typedef  struct
_ANSC_ACS_INTERN_HTTP_CONTENT
{
    ULONG                           ulContentSize;
    PVOID                           pContent;
    PCHAR                           SoapMessage;
    ANSC_STATUS                     CompleteStatus;
    ANSC_EVENT                      CompleteEvent;
    PCHAR                           MethodName;
    BOOL                            bIsRedirect;
    BOOL                            bUnauthorized;
}
ANSC_ACS_INTERN_HTTP_CONTENT,  *PANSC_ACS_INTERN_HTTP_CONTENT;


/**
* @brief Get the HTTP Simple Client handle.
*
* This function is called to retrieve the HTTP Simple Client object handle
* associated with this CCSP CWMP ACS Connection object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the HTTP Simple Client.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpAcscoGetHttpSimpleClient
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the CCSP CWMP Session handle.
*
* This function is called to retrieve the CWMP Session object handle
* associated with this CCSP CWMP ACS Connection object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP Session.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpAcscoGetCcspCwmpSession
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the CCSP CWMP Session handle.
*
* This function is called to configure the CWMP Session object handle
* for this CCSP CWMP ACS Connection object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hContext  - Handle to the new CCSP CWMP Session object to be configured.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcscoSetCcspCwmpSession
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hContext
    );

/**
* @brief Get the ACS URL string.
*
* This function is called to retrieve the ACS (Auto-Configuration Server) URL
* used for TR-069 communication.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the ACS URL string.
* @retval Pointer to the ACS URL string if the operation is successful.
*
*/
char*
CcspCwmpAcscoGetAcsUrl
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the ACS URL string.
*
* This function is called to configure the ACS (Auto-Configuration Server) URL.
* It converts TR-069 specific URL schemes to standard HTTP/HTTPS URLs.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pName  - Pointer to the new ACS URL string.
*                    \n Format: x-dslf_cwmp://host:port/ or x-dslf_cwmps://host:port/
*                    \n or standard http:// or https:// URLs.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_RESOURCES if memory allocation fails.
* @retval ANSC_STATUS_FAILURE if string copy operation fails.
*
*/
ANSC_STATUS
CcspCwmpAcscoSetAcsUrl
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
* @brief Get the username for ACS authentication.
*
* This function is called to retrieve the username used for HTTP authentication
* with the ACS server.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the username string.
* @retval Pointer to the username string if the operation is successful.
*
*/
char*
CcspCwmpAcscoGetUsername
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the username for ACS authentication.
*
* This function is called to configure the username used for HTTP authentication
* with the ACS server. When username changes, it clears the HTTP authentication
* information cache to force re-authentication.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pName  - Pointer to the new username string.
*                    \n Can be NULL to clear the username.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcscoSetUsername
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
* @brief Get the password for ACS authentication.
*
* This function is called to retrieve the password used for HTTP authentication
* with the ACS server.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the password string.
* @retval Pointer to the password string if the operation is successful.
*
*/
char*
CcspCwmpAcscoGetPassword
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the password for ACS authentication.
*
* This function is called to configure the password used for HTTP authentication
* with the ACS server. When password changes, it clears the HTTP authentication
* information cache to force re-authentication.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pName  - Pointer to the new password string.
*                    \n Can be NULL to clear the password.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcscoSetPassword
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
* @brief Reset object states.
*
* This function is called to reset all internal states of the CCSP CWMP ACS Connection
* object to their default values.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcscoReset
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_ACSCO_PROCESS.C
***********************************************************/

/**
* @brief Connect to the ACS server.
*
* This function is called to establish an HTTP connection to the ACS (Auto-Configuration Server).
* It configures the HTTP client with session idle timeout and outbound interface settings,
* then engages the HTTP client to establish the connection.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_NOT_READY if the ACS URL is not configured or invalid.
* @retval ANSC_STATUS_FAILURE if string copy operation fails.
*
*/
ANSC_STATUS
CcspCwmpAcscoConnect
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Send a SOAP request to the ACS server.
*
* This function is called to send a SOAP message request to the ACS. It handles HTTP
* authentication, TLS/SSL connections, redirections, and processes the response. The function
* supports both HTTP and HTTPS protocols and manages cookies across requests.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pSoapMessage  - Pointer to the SOAP request message content.
*                    \n Can be NULL for empty HTTP POST.
* @param[in] pMethodName  - Pointer to the first SOAP method name string.
*                    \n Used for SOAPAction header. Can be NULL for multiple envelopes.
* @param[in] ulReqEnvCount  - Number of request envelopes in the SOAP message.
*                    \n Range: 0 to maximum supported envelopes.
* @param[in] ulRepEnvCount  - Number of response envelopes expected.
*                    \n Range: 0 to maximum supported envelopes.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_NOT_READY if the ACS URL is not configured.
* @retval ANSC_STATUS_FAILURE if the request fails or authentication fails.
* @retval ANSC_STATUS_INTERNAL_ERROR if URL parsing fails.
* @retval ANSC_STATUS_NOT_SUPPORTED if unsecured HTTP is blocked.
*
*/
ANSC_STATUS
CcspCwmpAcscoRequest
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pSoapMessage,
        char*                       pMethodName,
        ULONG                       ulReqEnvCount,
        ULONG                       ulRepEnvCount
    );

/**
* @brief Send an empty request to the ACS server.
*
* This function is called to send the last empty HTTP POST request to the ACS
* to complete the transaction sequence. It internally calls the Request function
* with NULL parameters.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_NOT_READY if the ACS URL is not configured.
* @retval ANSC_STATUS_FAILURE if the request fails.
*
*/
ANSC_STATUS
CcspCwmpAcscoRequestOnly
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Close the connection to the ACS server.
*
* This function is called to terminate the HTTP connection to the ACS server.
* It cancels the HTTP client operations and sets the connection to inactive state.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcscoClose
    (
        ANSC_HANDLE                 hThisObject
    );

/***********************************************************
         FUNCTIONS IMPLEMENTED IN CCSP_CWMP_ACSCO_HTTPBSPIF.C
***********************************************************/
/**
* @brief Polish the client HTTP request message before sending.
*
* This function is called to modify and polish the HTTP request message before it is sent
* to the ACS server. It adds Authorization header, Cookie headers, Content-Type, Content-Length,
* and SOAPAction headers.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hBmoReq  - Handle to the HTTP request message object to be polished.
* @param[in] hReqContext  - Handle to the request-specific context provided by the owner.
*                    \n Points to ANSC_ACS_INTERN_HTTP_CONTENT structure.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if string operations fail.
*
*/
ANSC_STATUS
CcspCwmpAcscoHttpBspPolish
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hBmoReq,
        ANSC_HANDLE                 hReqContext
    );

/**
* @brief Browse and process the HTTP response from the ACS server.
*
* This function is called to process the HTTP response received from the ACS server.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hBmoReq  - Handle to the HTTP request message object that triggered the response.
* @param[in] hBmoRep  - Handle to the HTTP response message to be processed.
* @param[in] hReqContext  - Handle to the request-specific context provided by the owner.
*                    \n Points to ANSC_ACS_INTERN_HTTP_CONTENT structure.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if response processing fails or unsupported status code.
* @retval ANSC_STATUS_DO_IT_AGAIN if authentication challenge received.
* @retval ANSC_STATUS_NO_MORE_DATA if redirect requires session cleanup.
* @retval ANSC_STATUS_RESOURCES if memory allocation fails.
*
*/
ANSC_STATUS
CcspCwmpAcscoHttpBspBrowse
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hBmoReq,
        ANSC_HANDLE                 hBmoRep,
        ANSC_HANDLE                 hReqContext
    );

/**
* @brief Notify when HTTP events occur unexpectedly.
*
* This function is called to notify the owner when unexpected events occur during HTTP
* communication with the ACS server. It handles various events including network failures,
* timeouts, socket closures, and TLS errors. It updates statistics counters and triggers
* session closure notifications.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] ulEvent  - Nature of the event to be processed.
* @param[in] ulError  - Error code associated with the event.
* @param[in] hReqContext  - Handle to the request-specific context provided by the owner.
*                    \n Points to ANSC_ACS_INTERN_HTTP_CONTENT structure.
* @param[in] hBmoReq  - Handle to the HTTP request message object if available.
* @param[in] hBmoRep  - Handle to the HTTP response message object if available.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcscoHttpBspNotify
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulEvent,
        ULONG                       ulError,
        ANSC_HANDLE                 hReqContext,
        ANSC_HANDLE                 hBmoReq,
        ANSC_HANDLE                 hBmoRep
    );

/**
* @brief Add a cookie to be included in future HTTP requests.
*
* This function is called to add a cookie that will be included in subsequent HTTP requests
* to the ACS server.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pCookie  - Pointer to the cookie string to be added.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_DISCARD if maximum cookie limit exceeded (CCSP_CWMP_ACSCO_MAX_COOKIE).
* @retval ANSC_STATUS_RESOURCES if memory allocation fails.
*
*/
ANSC_STATUS
CcspCwmpAcscoHttpAddCookie
    (
        ANSC_HANDLE                 hThisObject,
        PCHAR                       pCookie
    );

/**
* @brief Remove all saved cookies.
*
* This function is called to remove all cookies that have been saved from previous
* HTTP responses. It frees the memory associated with each cookie and resets the cookie count.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcscoHttpRemoveCookies
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Find a cookie with the specified name.
*
* This function is called to search for a cookie with a specified name in the saved
* cookies array.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pCookieName  - Pointer to the cookie name string to search for.
*
* @return The index of the cookie in the cookie array.
* @retval int >= 0 if cookie is found (index in array).
* @retval -1 if cookie with specified name is not found.
*
*/
int
CcspCwmpAcscoHttpFindCookie
	(
		ANSC_HANDLE                 hThisObject,
		PCHAR                       pCookieName
	);

/**
* @brief Delete a cookie at the specified index.
*
* This function is called to delete a cookie at the specified index in the cookies array.
* It removes the cookie, shifts remaining cookies down, and frees the memory.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] ulIndex  - Index of the cookie to be deleted.
*                    \n Range: 0 to (NumCookies - 1).
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_BAD_PARAMETER if the index is out of range.
*
*/
ANSC_STATUS
CcspCwmpAcscoHttpDelCookie
	(
		ANSC_HANDLE                 hThisObject,
		ULONG                       ulIndex
	);

/**
* @brief Handle HTTP session closure event.
*
* This function is called whenever the HTTP session with the ACS server is closed.
* It notifies the associated CWMP session about the closure so appropriate cleanup
* and state management can be performed.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcscoHttpSessionClosed
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
         FUNCTIONS IMPLEMENTED IN CCSP_CWMP_ACSCO_HTTPACMIF.C
***********************************************************/
/**
* @brief Get HTTP authentication credentials.
*
* This function is called to retrieve the username and password for HTTP authentication
* with the ACS server. It first attempts to get credentials from the CWMP Processor if
* a CWMP session is available, otherwise it uses the credentials stored in the connection object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Connection Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pHostName  - Pointer to the host name string.
*                    \n This parameter is not used in current implementation.
* @param[in] HostPort  - Host port number.
*                    \n This parameter is not used in current implementation.
* @param[in] pUriPath  - Pointer to the URI path string.
*                    \n This parameter is not used in current implementation.
* @param[out] ppUserName  - Pointer to receive the username string pointer.
*                    \n Memory is allocated or cloned by this function.
* @param[out] ppPassword  - Pointer to receive the password string pointer.
*                    \n Memory is allocated or cloned by this function.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcscoHttpGetCredential
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pHostName,
        USHORT                      HostPort,
        PUCHAR                      pUriPath,
        PUCHAR*                     ppUserName,
        PUCHAR*                     ppPassword
    );

#endif

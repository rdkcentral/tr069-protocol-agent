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

    module:	ccsp_cwmp_tcpcrho_internal_api.h

        For CCSP CWMP protocol implementation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the internal functions provided by CCSP CWMP TCP Connection
        Request Handler Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Kang Quan

    ---------------------------------------------------------------

    revision:

        08/19/08    initial revision.

**********************************************************************/


#ifndef  _CCSP_CWMP_TCPCRHO_INTERNAL_API_
#define  _CCSP_CWMP_TCPCRHO_INTERNAL_API_


/***********************************************************
          FUNCTIONS IMPLEMENTED IN CCSP_CWMP_TCPCRHO_STATES.C
***********************************************************/

/**
* @brief Get the CCSP CWMP CPE Controller handle.
*
* This function retrieves the handle to the CCSP CWMP CPE Controller object
* associated with the TCP Connection Request Handler.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Handle to the CPE Controller object.
* @retval ANSC_HANDLE pointing to the CPE Controller if configured.
*
*/
ANSC_HANDLE
CcspCwmpTcpcrhoGetCcspCwmpCpeController
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the CCSP CWMP CPE Controller handle.
*
* This function configures the handle to the CCSP CWMP CPE Controller object
* to be used by the TCP Connection Request Handler.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hCcspCwmpCpeController  - Handle to the CPE Controller object.
*                    \n The CPE Controller to be associated with this handler.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoSetCcspCwmpCpeController
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCcspCwmpCpeController
    );

/**
* @brief Get the Web Access Control Manager interface.
*
* This function retrieves the handle to the Web ACM (Access Control Manager)
* interface used for authentication.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Handle to the Web ACM interface.
* @retval ANSC_HANDLE pointing to the Web ACM interface if configured.
*
*/
ANSC_HANDLE
CcspCwmpTcpcrhoGetWebAcmIf
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the Web Access Control Manager interface.
*
* This function configures the handle to the Web ACM (Access Control Manager)
* interface for authentication operations.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hWebAcmIf  - Handle to the Web ACM interface.
*                    \n The Web ACM interface to be used for authentication.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoSetWebAcmIf
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWebAcmIf
    );

/**
* @brief Get TCP Connection Request Handler property.
*
* This function retrieves the property configuration of the handler,
* including host address, port, and server mode settings.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[out] hProperty  - Handle to CCSP_CWMP_TCPCR_HANDLER_PROPERTY structure.
*                    \n Structure to be filled with property data.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoGetProperty
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
* @brief Set TCP Connection Request Handler property.
*
* This function configures the property settings of the handler,
* including host address, port, and server mode.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hProperty  - Handle to CCSP_CWMP_TCPCR_HANDLER_PROPERTY structure.
*                    \n Property data to be copied to the object.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoSetProperty
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
* @brief Reset TCP Connection Request Handler property to defaults.
*
* This function resets the handler property configuration to default values,
* including clearing addresses and resetting ports.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoResetProperty
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Reset TCP Connection Request Handler object states.
*
* This function resets the internal states of the handler object
* to their initial values.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoReset
    (
        ANSC_HANDLE                 hThisObject
    );

/***********************************************************
       FUNCTIONS IMPLEMENTED IN CCSP_CWMP_TCPCRHO_OPERATION.C
***********************************************************/

/**
* @brief Engage the TCP Connection Request Handler.
*
* This function activates the handler by creating TCP servers, configuring
* network settings, and starting to listen for incoming connection requests.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoEngage
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Cancel the TCP Connection Request Handler activity.
*
* This function deactivates the handler by stopping TCP servers and
* releasing associated resources.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoCancel
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Create TCP server instances.
*
* This function creates and initializes TCP server objects required for
* handling incoming connection requests.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoCreateTcpServers
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Remove TCP server instances.
*
* This function removes and cleans up TCP server objects used for
* connection request handling.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoRemoveTcpServers
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Initialize worker interface.
*
* This function initializes the worker interface used for processing
* incoming TCP connection requests.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoWorkerInit
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Unload worker interface.
*
* This function unloads and cleans up the worker interface used for
* processing TCP connection requests.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoWorkerUnload
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
       FUNCTIONS IMPLEMENTED IN CCSP_CWMP_TCPCRHO_DSTOWO.C
***********************************************************/

/**
* @brief Accept incoming TCP connection from ACS.
*
* This function is called by the daemon server TCP object to accept
* incoming connections and allocate receive buffers.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hSocket  - Handle to the socket object for the new connection.
* @param[out] phClientContext  - Client context to be returned.
*
* @return TRUE if the connection is accepted, FALSE otherwise.
* @retval TRUE if the operation is successful.
*
*/
BOOL
CcspCwmpTcpcrhoDstowoAccept
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSocket,
        PANSC_HANDLE                phClientContext
    );

/**
* @brief Configure socket for output operations.
*
* This function is called by the daemon server TCP object to configure
* socket for sending data.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hSocket  - Handle to the socket object.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoDstowoSetOut
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSocket
    );

/**
* @brief Remove socket and cleanup resources.
*
* This function is called by the daemon server TCP object to remove a socket
* connection and free associated buffers.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hSocket  - Handle to the socket object to be removed.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoDstowoRemove
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSocket
    );

/**
* @brief Query socket buffer for complete HTTP request.
*
* This function examines received data to determine if a complete HTTP
* connection request has been received and needs processing.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hSocket  - Handle to the socket object.
* @param[in] buffer  - Pointer to the received data buffer.
* @param[in] ulSize  - Size of the received data.
* @param[out] phQueryContext  - Query context to be returned.
*
* @return The processing mode to be used.
* @retval ANSC_DSTOWO_PMODE_PROCESS_SYNC for synchronous processing.
* @retval ANSC_DSTOWO_PMODE_COLLECT to collect more data.
*
*/
ULONG
CcspCwmpTcpcrhoDstowoQuery
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSocket,
        PVOID                       buffer,
        ULONG                       ulSize,
        PANSC_HANDLE                phQueryContext
    );

/**
* @brief Process connection request synchronously.
*
* This function processes complete HTTP connection requests, verifies
* authentication, and triggers ACS connection if authorized.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hSocket  - Handle to the socket object.
* @param[in] buffer  - Pointer to the request data buffer.
* @param[in] ulSize  - Size of the request data.
* @param[in] hQueryContext  - Query context from the Query function.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the request was processed successfully.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoDstowoProcessSync
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSocket,
        PVOID                       buffer,
        ULONG                       ulSize,
        ANSC_HANDLE                 hQueryContext
    );

/**
* @brief Process connection request asynchronously.
*
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hSocket  - Handle to the socket object.
* @param[in] buffer  - Pointer to the request data buffer.
* @param[in] ulSize  - Size of the request data.
* @param[in] hQueryContext  - Query context from the Query function.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_UNAPPLICABLE if the operation is not supported.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoDstowoProcessAsync
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSocket,
        PVOID                       buffer,
        ULONG                       ulSize,
        ANSC_HANDLE                 hQueryContext
    );

/**
* @brief Handle send completion notification.
*
* This function is called by the daemon server TCP object when a send
* operation has completed.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hSocket  - Handle to the socket object.
* @param[in] hReserved  - Reserved context from send operation.
* @param[in] status  - Status of the send operation.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoDstowoSendComplete
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSocket,
        ANSC_HANDLE                 hReserved,
        ANSC_STATUS                 status
    );

/**
* @brief Handle socket event notifications.
*
* This function is called by the daemon server TCP object to notify of
* socket events such as errors, closure, resource issues, or timeouts.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hSocket  - Handle to the socket object.
* @param[in] ulEvent  - Event type being notified.
* @param[in] hReserved  - Reserved context associated with the event.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoDstowoNotify
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSocket,
        ULONG                       ulEvent,
        ANSC_HANDLE                 hReserved
    );


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_TCPCRHO_PROCESS.C
***********************************************************/

/**
* @brief Process HTTP connection request message.
*
* This function processes incoming connection request messages, validates
* the request format, authenticates the ACS, and triggers connection to
* the ACS server if authorized.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hSocket  - Handle to the socket from which the message was received.
* @param[in] buffer  - Pointer to the request data buffer.
* @param[in] ulSize  - Size of the request data.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the request is valid and authenticated.
* @retval ANSC_STATUS_BAD_AUTH_DATA if authentication failed.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoProcessRequest
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSocket,
        PVOID                       buffer,
        ULONG                       ulSize
    );

/**
* @brief Verify HTTP authentication credentials.
*
* This function verifies the authentication credentials provided by the
* ACS client against configured user credentials using either Basic or
* Digest HTTP authentication.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] buffer  - Pointer to the request data buffer.
* @param[in] ulSize  - Size of the request data.
* @param[in] hSessAuthInfo  - Handle to session authentication information.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if credentials are valid.
* @retval ANSC_STATUS_BAD_AUTH_DATA if credentials are invalid.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoVerifyCredential
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        ULONG                       ulSize,
        ANSC_HANDLE                 hSessAuthInfo
    );


/***********************************************************
   INTERNAL FUNCTIONS IMPLEMENTED IN CCSP_CWMP_TCPCRHO_AUTH.C
***********************************************************/

/**
* @brief Skip leading whitespace characters.
*
* This internal helper function skips leading space and tab characters
* in a buffer.
*
* @param[in] pMsg  - Pointer to the message buffer.
* @param[in] ulSize  - Size of the message buffer.
*
* @return Pointer to the first non-whitespace character.
* @retval Pointer to the first non-whitespace character on success.
* @retval NULL if none found.
*
*/
PUCHAR
CcspCwmpTcpcrhoSkipWS
    (
        PUCHAR                  pMsg,
        ULONG                   ulSize
    );

/**
* @brief Skip trailing whitespace characters.
*
* This internal helper function skips trailing space and tab characters
* in a buffer by scanning backwards.
*
* @param[in] pMsg  - Pointer to the end position in the message buffer.
* @param[in] ulSize  - Number of bytes to scan backwards.
*
* @return Pointer to the first non-whitespace character from the end.
* @retval Pointer to the first non-whitespace character from the end on success.
* @retval NULL if none found.
*
*/
PUCHAR
CcspCwmpTcpcrhoSkipTrailingWS
    (
        PUCHAR                  pMsg,
        ULONG                   ulSize
    );

/**
* @brief Convert binary data to hexadecimal string.
*
* This internal helper function converts binary data to lowercase
* hexadecimal string representation.
*
* @param[in] Bin  - Pointer to binary data.
* @param[in] ulBinLen  - Length of binary data in bytes.
* @param[out] Hex  - Buffer to receive hexadecimal string (null-terminated).
*
* @return None.
*
*/
void
CcspCwmpTcpcrhoBinToHex
    (
        PUCHAR                  Bin,
        ULONG                   ulBinLen,
        PUCHAR                  Hex
    );

/**
* @brief Find HTTP header by name.
*
* This internal helper function searches for a specific HTTP header by name
* and returns its value offset and length.
*
* @param[in] pMsg  - Pointer to HTTP message buffer.
* @param[in] ulSize  - Size of the message buffer.
* @param[in] pHeaderName  - Name of the header to find.
* @param[out] pulHdrValueOffset  - Pointer to receive offset to header value.
* @param[out] pulHdrValeLen  - Pointer to receive length of header value.
*
* @return Pointer to the start of the header
* @retval Pointer to the start of the header on success.
* @retval NULL if not found.
*
*/
PUCHAR
CcspCwmpTcpcrhoFindHeader
    (
        PUCHAR                  pMsg,
        ULONG                   ulSize,
        PUCHAR                  pHeaderName,
        PULONG                  pulHdrValueOffset,
        PULONG                  pulHdrValeLen
    );

/**
* @brief Calculate digest authentication response.
*
* This internal helper function calculates the digest response value for
* HTTP digest authentication according to RFC 2617.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] pMethodName  - HTTP method name.
* @param[in] pUserName  - Username for authentication.
* @param[in] pPassword  - Password for authentication.
* @param[in] pRealm  - Authentication realm.
* @param[in] pAlgorithm  - Algorithm name (MD5 or MD5-sess).
* @param[in] pNonce  - Server nonce value.
* @param[in] pCNonce  - Client nonce value.
* @param[in] pQop  - Quality of protection value.
* @param[in] pNC  - Nonce count as string.
* @param[in] pEntityDigest  - Entity body digest.
* @param[in] pDigestUri  - Digest URI.
*
* @return Pointer to calculated response string.
*
*/
PUCHAR
CcspCwmpTcpcrhoCalcDigResponse
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pMethodName,
        PUCHAR                      pUserName,
        PUCHAR                      pPassword,
        PUCHAR                      pRealm,
        PUCHAR                      pAlgorithm,
        PUCHAR                      pNonce,
        PUCHAR                      pCNonce,
        PUCHAR                      pQop,
        PUCHAR                      pNC,
        PUCHAR                      pEntityDigest,
        PUCHAR                      pDigestUri
    );

/**
* @brief Calculate digest authentication H(A1) value.
*
* This function calculates the H(A1) value for digest authentication,
* which is the hash of username, realm, and password.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pUserName  - Username for authentication.
* @param[in] pPassword  - Password for authentication.
* @param[in] pRealm  - Authentication realm.
* @param[in] pAlgorithm  - Algorithm name (MD5 or MD5-sess).
* @param[in] pNonce  - Server nonce value.
* @param[in] pCNonce  - Client nonce value.
* @param[out] pHA1  - Buffer to receive the calculated H(A1) value.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoCalcDigestHA1
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pUserName,
        PUCHAR                      pPassword,
        PUCHAR                      pRealm,
        PUCHAR                      pAlgorithm,
        PUCHAR                      pNonce,
        PUCHAR                      pCNonce,
        PUCHAR                      pHA1
    );

/**
* @brief Calculate digest authentication H(A2) value.
*
* This internal helper function calculates the H(A2) value for digest
* authentication based on method and URI.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] pMethodName  - HTTP method name.
* @param[in] pQop  - Quality of protection value.
* @param[in] pEntityDigest  - Entity body digest for qop=auth-int.
* @param[in] pDigestUri  - Digest URI.
* @param[out] pHA2  - Buffer to receive calculated H(A2) value.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoCalcDigestHA2
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pMethodName,
        PUCHAR                      pQop,
        PUCHAR                      pEntityDigest,
        PUCHAR                      pDigestUri,
        PUCHAR                      pHA2
    );

/**
* @brief Extract host and URI from HTTP request.
*
* This function parses the HTTP request to extract the hostname, port,
* and URI path.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] buffer  - Pointer to HTTP request buffer.
* @param[in] ulSize  - Size of the request buffer.
* @param[out] ppHostName  - Pointer to receive allocated hostname string.
* @param[out] pHostPort  - Pointer to receive host port number.
* @param[out] ppUriPath  - Pointer to receive allocated URI path string.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoGetRequestHostUri
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        ULONG                       ulSize,
        PUCHAR                      *ppHostName,
        PUSHORT                     pHostPort,
        PUCHAR                     *ppUriPath
    );

/**
* @brief Extract authentication information from HTTP request.
*
* This function parses the Authorization header from HTTP request and
* extracts authentication information.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] buffer  - Pointer to HTTP request buffer.
* @param[in] ulSize  - Size of the request buffer.
*
* @return Handle to HTTP authentication information structure.
*
*/
ANSC_HANDLE
CcspCwmpTcpcrhoGetAuthInfo
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        ULONG                       ulSize
    );

/**
* @brief Parse digest authentication parameters.
*
* This internal helper function parses digest authentication data from
* the Authorization header.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] hAuthInfo  - Handle to authentication info structure.
* @param[in] pDigData  - Pointer to digest data string.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoGetDigestAuthInfo
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hAuthInfo,
        PUCHAR                      pDigData
    );

/**
* @brief Generate Basic authentication challenge.
*
* This internal helper function creates a Basic authentication challenge
* string with the specified realm.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] pRealm  - Authentication realm string.
*
* @return Pointer to allocated challenge string.
*
*/
PUCHAR
CcspCwmpTcpcrhoGenBasicChallenge
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pRealm
    );

/**
* @brief Generate Digest authentication challenge.
*
* This internal helper function creates a Digest authentication challenge
* string with realm, nonce, algorithm, qop, and other parameters.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] pRealm  - Authentication realm string.
* @param[in] pDomain  - Domain string or NULL.
* @param[in] pAlgorithm  - Algorithm name (MD5 or MD5-sess).
* @param[in] pQop  - Quality of protection value or NULL.
* @param[in] pNonce  - Server nonce value.
* @param[in] bNonceExpired  - TRUE to include stale=true in challenge.
*
* @return Pointer to allocated challenge string.
*
*/
PUCHAR
CcspCwmpTcpcrhoGenDigestChallenge
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pRealm,
        PUCHAR                      pDomain,
        PUCHAR                      pAlgorithm,
        PUCHAR                      pQop,
        PUCHAR                      pNonce,
        BOOL                        bNonceExpired
    );

/**
* @brief Generate HTTP 401 response with Basic authentication challenge.
*
* This internal helper function creates an HTTP 401 Unauthorized response
* with Basic authentication challenge.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in,out] buffer  - Buffer to receive HTTP response message.
* @param[in,out] pulSize  - Size of buffer / actual response size.
* @param[in] pRealm  - Authentication realm string.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoGenBasicResponse
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        PULONG                      pulSize,
        PUCHAR                      pRealm
    );

/**
* @brief Generate HTTP 401 response with Digest authentication challenge.
*
* This internal helper function creates an HTTP 401 Unauthorized response
* with Digest authentication challenge.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in,out] buffer  - Buffer to receive HTTP response message.
* @param[in,out] pulSize  - Size of buffer / actual response size.
* @param[in] pRealm  - Authentication realm string.
* @param[in] pDomain  - Domain string or NULL.
* @param[in] pAlgorithm  - Algorithm name (MD5 or MD5-sess).
* @param[in] pQop  - Quality of protection value or NULL.
* @param[in] pNonce  - Server nonce value.
* @param[in] bNonceExpired  - TRUE to include stale=true in challenge.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoGenDigestResponse
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        PULONG                      pulSize,
        PUCHAR                      pRealm,
        PUCHAR                      pDomain,
        PUCHAR                      pAlgorithm,
        PUCHAR                      pQop,
        PUCHAR                      pNonce,
        BOOL                        bNonceExpired
    );

/**
* @brief Generate HTTP response message.
*
* This internal helper function creates an HTTP response message with
* authentication headers if provided.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in,out] buffer  - Buffer to receive HTTP response message.
* @param[in,out] pulSize  - Size of buffer / actual response size.
* @param[in] hAuthHeader  - Handle to authentication header or NULL.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoGenResponse
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        PULONG                      pulSize,
        ANSC_HANDLE                 hAuthHeader
    );

/**
* @brief Generate random nonce value.
*
* This internal helper function generates a random nonce value using
* MD5 hashing for digest authentication.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[out] pNonce  - Buffer to receive nonce string.
* @param[in] ulNonceLen  - Length of nonce buffer.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoGenNonce
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pNonce,
        ULONG                       ulNonceLen
    );

/**
* @brief Verify HTTP authentication credentials.
*
* This internal helper function verifies client credentials against
* server authentication requirements.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] buffer  - HTTP request buffer.
* @param[in] ulSize  - Size of request buffer.
* @param[in] hAuthInfo  - Handle to authentication info.
* @param[in] pPassword  - User password.
* @param[in] ulServerAuthType  - Server authentication type.
* @param[in] pServerAuthRealm  - Server authentication realm.
* @param[in] pServerNonce  - Server nonce value.
* @param[in] ulNonceTimeout  - Nonce timeout in seconds.
* @param[in] ulNonceTimestamp  - Nonce creation timestamp.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if credentials are valid.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoVerify
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        ULONG                       ulSize,
        ANSC_HANDLE                 hAuthInfo,
        PUCHAR                      pPassword,
        ULONG                       ulServerAuthType,
        PUCHAR                      pServerAuthRealm,
        PUCHAR                      pServerNonce,
        ULONG                       ulNonceTimeout,
        ULONG                       ulNonceTimestamp
    );

/**
* @brief Generate HTTP response with resource content.
*
* This internal helper function creates an HTTP 200 OK response with
* resource content and appropriate headers.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in,out] buffer  - Buffer to receive HTTP response message.
* @param[in,out] pulSize  - Size of buffer / actual response size.
* @param[in] pMimeType  - MIME type of the resource.
* @param[in] pRes  - Resource content data.
* @param[in] ulResLen  - Length of resource content.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpTcpcrhoGenResResponse
    (
        ANSC_HANDLE                 hThisObject,
        PVOID                       buffer,
        PULONG                      pulSize,
        char*                       pMimeType,
        char*                       pRes,
        ULONG                       ulResLen
    );

/***********************************************************
   INTERNAL FUNCTIONS IMPLEMENTED IN CCSP_CWMP_TCPCRHO_MSG.C
***********************************************************/

/**
* @brief Parse HTTP authentication credentials.
*
* This internal helper function parses the Authorization header value
* and determines authentication type (Basic or Digest).
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] hCredentials  - Handle to credentials structure to fill.
* @param[in] pBuf  - Buffer containing credentials string.
* @param[in] ulSize  - Size of the credentials buffer.
*
* @return The status of operation.
* @retval TRUE if the operation is successful.
* @retval FALSE otherwise.
*
*/
BOOL
CcspCwmpTcpcrhoParseCredentials
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCredentials,
        PUCHAR                      pBuf,
        ULONG                       ulSize
    );

/**
* @brief Parse Basic authentication credentials.
*
* This internal helper function decodes Base64-encoded Basic authentication
* credentials and extracts username and password.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] hCredentials  - Handle to credentials structure to fill.
* @param[in] pBuf  - Buffer containing Base64-encoded credentials.
* @param[in] ulSize  - Size of the credentials buffer.
*
* @return The status of operation.
* @retval TRUE if the operation is successful.
* @retval FALSE otherwise.
*
*/
BOOL
CcspCwmpTcpcrhoParseBasicCredentials
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCredentials,
        PUCHAR                      pBuf,
        ULONG                       ulSize
    );

/**
* @brief Parse Digest authentication credentials.
*
* This internal helper function parses digest authentication parameters
* including username, realm, nonce, URI, response, etc.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] hCredentials  - Handle to credentials structure to fill.
* @param[in] pBuf  - Buffer containing digest credentials string.
* @param[in] ulSize  - Size of the credentials buffer.
*
* @return The status of operation.
* @retval TRUE if the operation is successful.
* @retval FALSE otherwise.
*
*/
BOOL
CcspCwmpTcpcrhoParseDigestCredentials
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCredentials,
        PUCHAR                      pBuf,
        ULONG                       ulSize
    );

/**
* @brief Check if HTTP request is complete.
*
* This internal helper function examines received data to determine if
* a complete HTTP request has been received.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] pBuf  - Buffer containing HTTP request data.
* @param[in] ulSize  - Size of the request buffer.
*
* @return The status of operation.
* @retval TRUE if the operation is successful.
* @retval FALSE otherwise.
*
*/
BOOL
CcspCwmpTcpcrhoIsRequestComplete
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pBuf,
        ULONG                       ulSize
    );

/**
* @brief Validate TR-069 connection request HTTP message.
*
* This internal function validates whether the received buffer contains a valid TR-069 connection request
* by verifying it is a proper HTTP GET request with the correct URL path matching the ManagementServer.ConnectionRequestURL
* parameter. The function parses the HTTP request line, extracts the URL path, and compares it against the configured
* connection request URL from the device's data model.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] pBuf  - Buffer containing the received HTTP request message to validate.
* @param[in] ulSize  - Size of the buffer in bytes.
* @param[out] pUrlPath  - Pointer to receive the allocated URL path string from the request.
*
* @return The validation status of the connection request.
* @retval TRUE if the request is a valid HTTP GET with matching URL path.
* @retval FALSE if the request is invalid, malformed, or path does not match ConnectionRequestURL.
*
*/
BOOL
CcspCwmpTcpcrhoIsValidConnRequest
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pBuf,
        ULONG                       ulSize,
        PUCHAR*                     pUrlPath
    );

/**
* @brief Match request to authentication session.
*
* This internal helper function checks if the request matches an existing
* authentication session using session cookies.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP TCP Connection Request Handler Object.
* @param[in] hSocket  - Handle to the socket connection.
* @param[in] pBuf  - Buffer containing HTTP request data.
* @param[in] ulSize  - Size of the request buffer.
*
* @return The status of operation.
* @retval TRUE if the operation is successful.
* @retval FALSE otherwise.
*
*/
BOOL
CcspCwmpTcpcrhoMatchSession
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSocket,
        PUCHAR                      pBuf,
        ULONG                       ulSize
    );


#endif

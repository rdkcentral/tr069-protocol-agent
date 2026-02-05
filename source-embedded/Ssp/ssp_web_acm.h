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

    module:	ssp_bbhm_vsp.h

        For Broadband Home Manager Model Implementation (BBHM),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        SSP implementation of the BBHM interface Vendor Service
        Provider.

    ---------------------------------------------------------------

    environment:

        platform dependent

    ---------------------------------------------------------------

    author:

        Kang Quan

    ---------------------------------------------------------------

    revision:

        07/22/08  initial revision.

**********************************************************************/


#ifndef  _SSP_WEB_ACM_
#define  _SSP_WEB_ACM_

/**
 * @brief Initializes the Web Access Control Manager (ACM) interface.
 *
 * This function initializes the WEB_ACM_INTERFACE structure by setting the owner context,
 * size, and function pointer for the GetCredential callback. The Web ACM interface is used
 * by the TR-069 PA to authenticate incoming HTTP connection requests from the ACS.
 *
 * @return The status of the initialization operation.
 * @retval 0  Successfully initialized the Web ACM interface.
 *
 */
int
ssp_BbhmInitWebAcmIf
    (
        void
    );

/**
 * @brief Retrieves authentication credentials for TR-069 connection request authentication.
 *
 * This function implements the Web ACM interface GetCredential callback to authenticate
 * incoming HTTP connection requests from the TR-069 ACS. It retrieves the ConnectionRequestUsername
 * and ConnectionRequestPassword from the Management Server configuration, compares the provided
 * username with the configured value, and returns the password if authentication is successful.
 * This function is called by the TCP Connection Request Handler to validate ACS credentials.
 *
 * @param[in] hThisObject  Handle to the calling object.
 * @param[in] pHostName    Hostname or IP address of the requesting host.
 * @param[in] HostPort     Port number of the requesting host.
 * @param[in] pUriPath     URI path of the connection request.
 * @param[in] pUserName    Username provided in the HTTP authentication header.
 * @param[in] pRealm       Authentication realm.
 * @param[out] ppPassword  Pointer to receive the allocated password string if authentication succeeds.
 *
 * @return The status of the credential retrieval operation.
 * @retval ANSC_STATUS_SUCCESS  Username matches configured ConnectionRequestUsername,
 *                              password returned successfully.
 * @retval ANSC_STATUS_FAILURE  Username does not match, username is NULL, or credential
 *                              retrieval failed.
 *
 */
ANSC_STATUS
ssp_BbhmWebAcmIfGetCredential
    (
        ANSC_HANDLE                 hThisObject,
        PUCHAR                      pHostName,
        USHORT                      HostPort,
        PUCHAR                      pUriPath,
        PUCHAR                      pUserName,
        PUCHAR                      pRealm,
        PUCHAR*                     ppPassword
    );

#endif
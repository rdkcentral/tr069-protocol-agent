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

    module:	ccsp_cwmp_acsbo_exported_api.h

        For CCSP CWMP protocol Implementation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the exported functions provided by the CCSP CWMP Acs Broker
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

        09/01/05    initial revision.
        10/12/11    resolving name conflicts with DM library

**********************************************************************/


#ifndef  _CCSP_CWMP_ACSBO_EXPORTED_API_
#define  _CCSP_CWMP_ACSBO_EXPORTED_API_


/***********************************************************
       FUNCTIONS IMPLEMENTED IN CCSP_CWMP_ACSBO_INTERFACE.C
***********************************************************/

/**
* @brief Create a new CCSP CWMP ACS Broker object.
*
* This function creates and initializes a new CCSP CWMP ACS (Auto Configuration Server)
* Broker object, which manages communication between the CPE and ACS server.
*
* @param[in] hContainerContext  - Container context handle. This context is transparent to
*                                 the object mapper and meaningful only to the caller.
* @param[in] hOwnerContext  - Owner context handle. This context is transparent to
*                             the object mapper and meaningful only to the caller.
* @param[in] hAnscReserved  - Reserved context handle. This context is transparent to
*                             the object mapper and meaningful only to the caller.
*
* @return Handle of the newly created ACS Broker object.
*
*/
ANSC_HANDLE
CcspCwmpCreateAcsBroker
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );


/***********************************************************
          FUNCTIONS IMPLEMENTED IN CCSP_CWMP_ACSBO_BASE.C
***********************************************************/

/**
* @brief Construct the CCSP CWMP ACS Broker object.
*
* This function constructs the CCSP CWMP ACS Broker object, allocates memory,
* and initializes member variables and functions.
*
* @param[in] hContainerContext  - Container context handle. Used by the container object to interact
*                                 with the outside world. It could be the real container or an target object.
* @param[in] hOwnerContext  - Owner context handle. Passed in by the owner of this object.
* @param[in] hAnscReserved  - Reserved context handle. Passed in by the owner of this object.
*
* @return Handle of the newly created container object.
* @retval Handle of the newly created container object if allocation success.
* @retval NULL if allocation fails.
*/
ANSC_HANDLE
CcspCwmpAcsboCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );

/**
* @brief Destroy the CCSP CWMP ACS Broker object.
*
* This function destroys the ACS Broker object, canceling operations, resetting state,
* freeing the MSO interface, and releasing all allocated memory.
*
* @param[in] hThisObject  - Handle to the ACS Broker object to destroy.
*                           This is actually the pointer to the object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the object is destroyed successfully.
*
*/
ANSC_STATUS
CcspCwmpAcsboRemove
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Enroll all objects required by the ACS Broker.
*
* This function enrolls all dependent objects required by the ACS Broker.
*
* @param[in] hThisObject  - Handle to the ACS Broker object.
*                           This is actually the pointer to the object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if objects enrolled successfully.
* @retval ANSC_STATUS_RESOURCES if memory allocation fails.
* @retval ANSC_STATUS_FAILURE if string copy operation fails.
*
*/
ANSC_STATUS
CcspCwmpAcsboEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Initialize the CCSP CWMP ACS Broker object.
*
* This function first calls the initialization member function of the base class object to set
* the common member fields inherited from the base class. It then initializes the member fields
* that are specific to this object.
*
* @param[in] hThisObject  - Handle to the ACS Broker object.
*                           This is actually the pointer to the object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if initialization is successful.
*
*/
ANSC_STATUS
CcspCwmpAcsboInitialize
    (
        ANSC_HANDLE                 hThisObject
    );


#endif
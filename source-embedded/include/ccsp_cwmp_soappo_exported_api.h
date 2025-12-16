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

    module:	ccsp_cwmp_soappo_exported_api.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the exported functions provided by the CCSP CWMP Soap Parser
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

        09/02/05    initial revision.
        10/12/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_SOAPPO_EXPORTED_API_
#define  _CCSP_CWMP_SOAPPO_EXPORTED_API_


/***********************************************************
      FUNCTIONS IMPLEMENTED IN CCSP_CWMP_SOAPPO_INTERFACE.C
***********************************************************/

/**
 * @brief Create a new CWMP SOAP Parser object.
 *
 * This function creates and initializes a new CWMP SOAP Parser object instance.
 *
 * @param[in] hContainerContext - Container context handle. This context is transparent to the SOAP
 *                                Parser and is only meaningful to the caller.
 * @param[in] hOwnerContext     - Owner context handle. This context is transparent to the SOAP Parser
 *                                and is only meaningful to the caller.
 * @param[in] hAnscReserved     - Reserved handle for future use. This context is transparent to the
 *                                SOAP Parser and is only meaningful to the caller.
 *
 * @return Handle to the newly created CWMP SOAP Parser object.
 * @return Non-NULL Handle to the newly created CWMP SOAP Parser object on success.
 * @return NULL if creation fails.
 *
 */
ANSC_HANDLE
CcspCwmpCreateSoapParser
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );


/***********************************************************
         FUNCTIONS IMPLEMENTED IN CCSP_CWMP_SOAPPO_BASE.C
***********************************************************/

/**
 * @brief Construct the CWMP SOAP Parser object.
 *
 * This function constructs the CWMP SOAP Parser object by allocating memory for the object structure,
 * initializing member variables and function pointers, enrolling sub-objects, and performing initial setup.
 *
 * @param[in] hContainerContext - Container context handle used by the container object to interact
 *                                 with the outside world. Could be the real container or a target object.
 * @param[in] hOwnerContext     - Owner context handle passed in by the owner of this object.
 * @param[in] hAnscReserved     - Reserved handle passed in by the owner of this object.
 *
 * @return Handle to the newly created CWMP SOAP Parser object.
 * @return Non-NULL Handle to the newly created CWMP SOAP Parser object.
 * @return NULL if memory allocation fails.
 *
 */
ANSC_HANDLE
CcspCwmpSoappoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );

/**
 * @brief Destroy the CWMP SOAP Parser object.
 *
 * This function destroys the CWMP SOAP Parser object by releasing all allocated resources,
 * cleaning up member variables, and freeing the object memory.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance to be destroyed.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Object destroyed successfully.
 *
 */
ANSC_STATUS
CcspCwmpSoappoRemove
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Enroll all sub-objects required by the CWMP SOAP Parser.
 *
 * This function enrolls (creates and registers) all sub-objects and components required by
 * the CWMP SOAP Parser object.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - All sub-objects enrolled successfully.
 *
 */
ANSC_STATUS
CcspCwmpSoappoEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Initialize the CWMP SOAP Parser object member fields.
 *
 * This function first calls the initialization member function of the base class
 * object to set the common member fields inherited from the base class. It then initializes
 * the member fields that are specific to this object.

 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Object initialized successfully.
 *
 */
ANSC_STATUS
CcspCwmpSoappoInitialize
    (
        ANSC_HANDLE                 hThisObject
    );


#endif
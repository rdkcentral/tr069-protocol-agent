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

    module:	ccsp_cwmp_sesso_exported_api.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the exported functions provided by the CCSP CWMP Wmp Session
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


#ifndef  _CCSP_CWMP_SESSO_EXPORTED_API_
#define  _CCSP_CWMP_SESSO_EXPORTED_API_


/***********************************************************
       FUNCTIONS IMPLEMENTED IN CCSP_CWMP_SESSO_INTERFACE.C
***********************************************************/

/**
 * @brief Create a new CWMP Session object.
 *
 * This function creates and initializes a new CCSP CWMP Session object (WMP Session), which
 * manages a single TR-069 session with the ACS.
 *
 * @param[in] hContainerContext - Handle to the container context. This context is transparent
 *                                to the object and is meaningful only to the caller.
 * @param[in] hOwnerContext     - Handle to the owner context. This context is passed by the
 *                                 owner to establish ownership.
 * @param[in] hAnscReserved     - Reserved handle for future use. This context is transparent
 *                                 to the object.
 *
 * @return Handle to the newly created CWMP Session object.
 * @retval Non-NULL - Handle to the successfully created session object.
 * @retval NULL - Session object creation failed due to resource allocation errors.
 *
 */
ANSC_HANDLE
CcspCwmpCreateWmpSession
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );


/***********************************************************
          FUNCTIONS IMPLEMENTED IN CCSP_CWMP_SESSO_BASE.C
***********************************************************/

/**
 * @brief Construct and initialize a CCSP CWMP Session object.
 *
 * This function constructs the CCSP CWMP Session Object by allocating memory, initializing
 * member variables and functions, and enrolling required sub-objects.
 *
 * @param[in] hContainerContext - Handle used by the container object to interact with the
 *                                 outside world. Could be the real container or a target object.
 * @param[in] hOwnerContext     - Handle passed in by the owner of this object (typically the CWMP Processor).
 * @param[in] hAnscReserved     - Reserved handle passed by the owner.
 *
 * @return Handle to the newly created CWMP Session container object.
 * @retval Non-NULL - Handle to the successfully created and initialized session object.
 * @retval NULL - Object creation failed due to memory allocation failure.
 *
 */
ANSC_HANDLE
CcspCwmpsoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );

/**
 * @brief Destroy the CWMP Session object and release all resources.
 *
 * This function destroys the CWMP Session object by stopping all timers, cleaning up the
 * ACS connection, freeing the Management Client Operation (MCO) interface, releasing queued
 * events and RPC requests/responses, and deallocating all memory associated with the session.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance to be destroyed.
 *                          This is actually the pointer to the session object itself.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Session object destroyed successfully and all resources freed.
 *
 */
ANSC_STATUS
CcspCwmpsoRemove
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Enroll all required sub-objects for the CWMP Session object.
 *
 * This function enrolls (creates and initializes) all sub-objects required by the CWMP Session
 * object to function properly.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance. This is actually the
 *                          pointer to the session object itself.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - All required sub-objects enrolled successfully.
 * @retval ANSC_STATUS_RESOURCES - Object enrollment failed due to resource allocation errors.
 *
 */
ANSC_STATUS
CcspCwmpsoEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Initialize member fields of the CWMP Session object.
 *
 * This function first calls the initialization member function of the base class
 * object to set the common member fields inherited from the base class. It then
 * initializes the member fields that are specific to this object.
 *
 * @param[in] hThisObject - Handle to the CWMP Session object instance. This is actually the
 *                          pointer to the session object itself.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Session object initialized successfully.
 *
 */
ANSC_STATUS
CcspCwmpsoInitialize
    (
        ANSC_HANDLE                 hThisObject
    );


#endif
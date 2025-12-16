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

    module:	ccsp_cwmp_stunmo_exported_api.h

        For CCSP CWMP protocol

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the exported functions provided by the CCSP CWMP Stun Manager
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

        08/05/08    initial revision.
        11/02/11    migrate to CCSP framework

**********************************************************************/


#ifndef  _CCSP_CWMP_STUNMO_EXPORTED_API_
#define  _CCSP_CWMP_STUNMO_EXPORTED_API_


/***********************************************************
      FUNCTIONS IMPLEMENTED IN CCSP_CWMP_STUNMO_INTERFACE.C
***********************************************************/

/**
 * @brief Creates a new CCSP CWMP STUN Manager object.
 *
 * This function creates and initializes a new CCSP CWMP STUN Manager object, which
 * manages STUN (Session Traversal Utilities for NAT) protocol operations for TR-069
 * communication. The function serves as a wrapper that calls CcspCwmpStunmoCreate to
 * construct the actual STUN Manager object with the provided context handles.
 *
 * @param[in] hContainerContext Handle to the container context, transparent to the object
 *                              mapper wrapper, only meaningful to the caller.
 * @param[in] hOwnerContext     Handle to the owner context, transparent to the object mapper
 *                              wrapper, only meaningful to the caller.
 * @param[in] hAnscReserved     Reserved handle for future use, transparent to the object
 *                              mapper wrapper, only meaningful to the caller.
 *
 * @return Handle of the created CCSP CWMP STUN Manager object.
 * @retval Valid ANSC_HANDLE   Successfully created STUN Manager object.
 * @retval NULL                Failed to create STUN Manager object due to resource constraints.
 *
 */
ANSC_HANDLE
CcspCwmpCreateStunManager
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );


/***********************************************************
         FUNCTIONS IMPLEMENTED IN CCSP_CWMP_STUNMO_BASE.C
***********************************************************/

/**
 * @brief Constructs the CCSP CWMP STUN Manager object and initializes member variables and functions.
 *
 * This function constructs a new CCSP CWMP STUN Manager object by allocating memory for the
 * CCSP_CWMP_STUN_MANAGER_OBJECT structure, initializing base class fields, setting up function
 * pointers (Create, Remove, EnrollObjects, Initialize), enrolling required sub-objects (STUN BSM
 * interface and STUN Simple Client), and initializing member fields specific to STUN management.
 * The created object manages STUN protocol operations for NAT traversal in TR-069 communication.
 *
 * @param[in] hContainerContext Handle used by the container object to interact with the outside
 *                              world. It could be the real container or a target object.
 * @param[in] hOwnerContext     Handle passed in by the owner of this object for context preservation.
 * @param[in] hAnscReserved     Reserved handle passed in by the owner of this object for future use.
 *
 * @return Handle of the newly created CCSP CWMP STUN Manager object.
 * @retval Valid ANSC_HANDLE   Successfully constructed STUN Manager with initialized member fields.
 * @retval NULL                Failed to allocate memory for STUN Manager object.
 *
 */
ANSC_HANDLE
CcspCwmpStunmoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );

/**
 * @brief Destroys the CCSP CWMP STUN Manager object and releases all associated resources.
 *
 * This function destroys the CCSP CWMP STUN Manager object by canceling any ongoing STUN
 * operations, resetting the object to its initial state, freeing the STUN BSM interface
 * (StunBsmIf) and STUN Simple Client (StunSimpleClient) handles, and deallocating the
 * object's memory. This cleanup ensures proper resource management and prevents memory leaks
 * in the TR-069 STUN management subsystem.
 *
 * @param[in] hThisObject Handle that is actually the pointer to the CCSP CWMP STUN Manager
 *                        object itself to be destroyed.
 *
 * @return Status of the removal operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully removed STUN Manager and released all resources.
 *
 */
ANSC_STATUS
CcspCwmpStunmoRemove
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Enrolls all sub-objects required by the CCSP CWMP STUN Manager object.
 *
 * This function enrolls and initializes all sub-objects required by the STUN Manager,
 * including the STUN BSM (Binding State Machine) interface and the STUN Simple Client
 * object. The BSM interface is allocated and configured with callback functions (RecvMsg1,
 * RecvMsg2, Notify) for STUN message handling. The Simple Client is created via
 * StunCreateSimpleClient and linked to the BSM interface. This enrollment is essential
 * for enabling STUN protocol operations in TR-069 communication through NAT.
 *
 * @param[in] hThisObject Handle that is actually the pointer to the CCSP CWMP STUN Manager
 *                        object itself requiring sub-object enrollment.
 *
 * @return Status of the enrollment operation.
 * @retval ANSC_STATUS_SUCCESS    Successfully enrolled all required sub-objects.
 * @retval ANSC_STATUS_RESOURCES  Failed to allocate memory for BSM interface or Simple Client.
 * @retval ANSC_STATUS_FAILURE    Failed to copy interface name due to string operation error.
 *
 */
ANSC_STATUS
CcspCwmpStunmoEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Initializes the CCSP CWMP STUN Manager object's member fields.
 *
 * This function initializes the member fields specific to the CCSP CWMP STUN Manager object
 * after calling the base class initialization function (AnscCoInitialize) to set common
 * member fields inherited from the base class. This two-phase initialization ensures that
 * both inherited and STUN Manager-specific fields are properly initialized, preparing the
 * object for STUN protocol operations in TR-069 communication.
 *
 * @param[in] hThisObject Handle that is actually the pointer to the CCSP CWMP STUN Manager
 *                        object itself requiring initialization.
 *
 * @return Status of the initialization operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully initialized all member fields.
 *
 */
ANSC_STATUS
CcspCwmpStunmoInitialize
    (
        ANSC_HANDLE                 hThisObject
    );


#endif
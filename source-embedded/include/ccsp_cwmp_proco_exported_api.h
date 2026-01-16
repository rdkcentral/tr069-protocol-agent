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

    module:	ccsp_cwmp_proco_exported_api.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the exported functions provided by the CCSP CWMP Processor
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


#ifndef  _CCSP_CWMP_PROCO_EXPORTED_API_
#define  _CCSP_CWMP_PROCO_EXPORTED_API_


/***********************************************************
       FUNCTIONS IMPLEMENTED IN CCSP_CWMP_PROCO_INTERFACE.C
***********************************************************/

/**
* @brief Create a new CCSP CWMP Processor object.
*
* This function creates and initializes a new CCSP CWMP Processor object, which is
* the core component responsible for processing TR-069 RPC methods, managing sessions,
* handling periodic inform operations, and coordinating parameter value changes.
*
*
* @param[in] hContainerContext  - Container context handle.
*                    \n This context is transparent to the object mapper and meaningful only to the caller.
* @param[in] hOwnerContext  - Owner context handle.
*                    \n This context is transparent to the object mapper and meaningful only to the caller.
* @param[in] hAnscReserved  - Reserved context handle.
*                    \n This context is transparent to the object mapper and meaningful only to the caller.
*
* @return Handle of the newly created Processor object.
*
*/
ANSC_HANDLE
CcspCwmpCreateProcessor
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );


/***********************************************************
          FUNCTIONS IMPLEMENTED IN CCSP_CWMP_PROCO_BASE.C
***********************************************************/

/**
* @brief Construct the CCSP CWMP Processor object.
*
* This function constructs the CWMP Processor object, allocates memory, and initializes
* member variables and functions. It enrolls component objects and initializes the processor
* for handling TR-069 RPC operations.
*
*
* @param[in] hContainerContext  - Container context handle.
*                    \n Used by the container object to interact with the outside world.
* @param[in] hOwnerContext  - Owner context handle.
*                    \n Passed in by the owner of this object.
* @param[in] hAnscReserved  - Reserved context handle.
*                    \n Passed in by the owner of this object.
*
* @return Handle of CCSP CWMP Processor object.
* @return Handle of the newly created container object on success.
* @retval NULL if allocation fails.
*
*/
ANSC_HANDLE
CcspCwmppoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );

/**
* @brief Destroy the CCSP CWMP Processor object.
*
* This function destroys the Processor object, canceling operations, resetting state,
* removing all timers, freeing the MPA interface, namespace manager, parameter
* attribute cache, event locks, and releasing all allocated memory.
*
* @param[in] hThisObject  - Handle to the Processor object to destroy.
*                    \n This is actually the pointer to the object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the object is destroyed successfully.
*
*/
ANSC_STATUS
CcspCwmppoRemove
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Enroll all objects required by the CWMP Processor.
*
* This function enrolls all dependent objects required by the Processor, including
* Periodic inform timer for scheduled periodic communication with ACS, schedule
* timer for delayed inform operations,pending inform timer for retry mechanisms,
* MPA interface for parameter operations.
* All timers are configured with appropriate intervals and callback functions.
*
* @param[in] hThisObject  - Handle to the Processor object.
*                    \n This is actually the pointer to the object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if all objects enrolled successfully.
* @retval ANSC_STATUS_RESOURCES if memory allocation fails for any timer or interface.
*
*/
ANSC_STATUS
CcspCwmppoEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Initialize the CCSP CWMP Processor object.
*
* This function initializes the Processor object by first calling the base class
* initialization, then setting object-specific member fields including CPE Controller
* handle and active state, initial contact and factory reset flags, ACS configuration,
* periodic inform settings, function pointers for session management,Event handling
* parameter operations and attribute caching, timer invocation callbacks, queue and
* synchronization primitives.
*
* @param[in] hThisObject  - Handle to the Processor object.
*                    \n This is actually the pointer to the object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if initialization is successful.
*
*/
ANSC_STATUS
CcspCwmppoInitialize
    (
        ANSC_HANDLE                 hThisObject
    );


#endif
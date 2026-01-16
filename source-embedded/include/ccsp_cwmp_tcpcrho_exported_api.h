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

    module:	ccsp_cwmp_tcpcrho_exported_api.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the exported functions provided by CCSP CWMP TCP Connection
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
        10/12/11    resolve name conflicts with DM library.

**********************************************************************/

#ifndef  _CCSP_CWMP_TCPCRHO_EXPORTED_API_
#define  _CCSP_CWMP_TCPCRHO_EXPORTED_API_


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_TCPCRHO_INTERFACE.C
***********************************************************/

/**
 * @brief Creates a new CCSP CWMP TCP Connection Request Handler object.
 *
 * This function creates and initializes a new CCSP CWMP TCP Connection Request Handler
 * object, which manages incoming TCP connection requests from the ACS (Auto-Configuration
 * Server) according to TR-069 specifications. The function serves as a wrapper that calls
 * CcspCwmpTcpcrhoCreate to construct the actual TCP Connection Request Handler object.
 *
 * @param[in] hContainerContext Context handle transparent to the object mapper wrapper,
 *                              only meaningful to the caller for container interaction.
 * @param[in] hOwnerContext     Context handle transparent to the object mapper wrapper,
 *                              only meaningful to the caller for owner context.
 * @param[in] hAnscReserved     Reserved context handle transparent to the object mapper
 *                              wrapper, only meaningful to the caller.
 *
 * @return Handle of the created CCSP CWMP TCP Connection Request Handler object.
 * @retval Valid ANSC_HANDLE   Successfully created TCP Connection Request Handler object.
 * @retval NULL                Failed to create handler due to resource constraints.
 *
 */
ANSC_HANDLE
CcspCwmpCreateTcpConnReqHandler
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );


/***********************************************************
           FUNCTIONS IMPLEMENTED IN CCSP_CWMP_TCPCRHO_BASE.C
***********************************************************/

/**
 * @brief Constructs the CCSP CWMP TCP Connection Request Handler object and initializes member variables.
 *
 * This function constructs a new CCSP CWMP TCP Connection Request Handler object by allocating
 * memory for the CCSP_CWMP_TCPCR_HANDLER_OBJECT structure, initializing base class fields,
 * setting up function pointers (Create, Remove, EnrollObjects, Initialize), enrolling required
 * sub-objects (DSTO Worker for TCP server operations), and initializing member fields specific
 * to TCP connection request handling. The handler processes incoming HTTP connection requests
 * from the ACS as specified in TR-069.
 *
 * @param[in] hContainerContext Handle used by the container object to interact with the outside
 *                              world. It could be the real container or a target object.
 * @param[in] hOwnerContext     Handle passed in by the owner of this object for context preservation.
 * @param[in] hAnscReserved     Reserved handle passed in by the owner of this object (unused).
 *
 * @return Handle of the newly created CCSP CWMP TCP Connection Request Handler object.
 * @retval Valid ANSC_HANDLE   Successfully constructed TCP Connection Request Handler.
 * @retval NULL                Failed to allocate memory for handler object.
 *
 */
ANSC_HANDLE
CcspCwmpTcpcrhoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );

/**
 * @brief Destroys the CCSP CWMP TCP Connection Request Handler object and releases resources.
 *
 * This function destroys the CCSP CWMP TCP Connection Request Handler object by canceling
 * any active TCP connection request handling operations, resetting the object to its initial
 * state, and freeing the DSTO Worker handle used for TCP server
 * operations. This cleanup ensures proper resource management and prevents memory leaks in
 * the TR-069 TCP connection request subsystem.
 *
 * @param[in] hThisObject Handle that is actually the pointer to the CCSP CWMP TCP Connection
 *                        Request Handler object itself to be destroyed.
 *
 * @return Status of the removal operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully removed handler and released all resources.
 *
 */
ANSC_STATUS
CcspCwmpTcpcrhoRemove
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Enrolls all sub-objects required by the CCSP CWMP TCP Connection Request Handler.
 *
 * This function enrolls and initializes all sub-objects required by the TCP Connection Request
 * Handler, specifically the DSTO Worker. The DSTO Worker is allocated
 * and configured with callback functions for TCP server operations including Init, Unload, Accept,
 * SetOut, Remove, Query, ProcessSync, ProcessAsync, SendComplete, and Notify. This enrollment is
 * essential for enabling TCP connection request handling from the ACS in TR-069 communication.
 *
 * @param[in] hThisObject Handle that is actually the pointer to the CCSP CWMP TCP Connection
 *                        Request Handler object itself requiring sub-object enrollment.
 *
 * @return Status of the enrollment operation.
 * @retval ANSC_STATUS_SUCCESS    Successfully enrolled all required sub-objects.
 * @retval ANSC_STATUS_RESOURCES  Failed to allocate memory for DSTO Worker object.
 *
 */
ANSC_STATUS
CcspCwmpTcpcrhoEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Initializes the CCSP CWMP TCP Connection Request Handler object's member fields.
 *
 * This function initializes the member fields specific to the CCSP CWMP TCP Connection Request
 * Handler object after calling the base class initialization function to set common member fields
 * inherited from the base class. This two-phase initialization ensures that both inherited and
 * TCP Connection Request Handler-specific fields are properly initialized, preparing the object
 * for handling incoming TCP connection requests from the ACS in TR-069 communication.
 *
 * @param[in] hThisObject Handle that is actually the pointer to the CCSP CWMP TCP Connection
 *                        Request Handler object itself requiring initialization.
 *
 * @return Status of the initialization operation.
 * @retval ANSC_STATUS_SUCCESS  Successfully initialized all member fields.
 *
 */
ANSC_STATUS
CcspCwmpTcpcrhoInitialize
    (
        ANSC_HANDLE                 hThisObject
    );


#endif
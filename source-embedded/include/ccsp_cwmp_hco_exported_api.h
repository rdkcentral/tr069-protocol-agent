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

    module:	ccsp_cwmp_hco_exported_api.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the exported functions provided by the CCSP CWMP Helper
        Container Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang
        Kang Quan

    ---------------------------------------------------------------

    revision:

        10/20/05    initial revision.
        10/12/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_HCO_EXPORTED_API_
#define  _CCSP_CWMP_HCO_EXPORTED_API_


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_HCO_INTERFACE.C
***********************************************************/

/**
* @brief Create a new CCSP CWMP Helper Container object.
*
* This function creates and initializes a new CCSP CWMP Helper Container object.
*
* @param[in] hContainerContext  - Container context handle.
* @param[in] hOwnerContext  - Owner context handle.
* @param[in] hAnscReserved  - Reserved context handle.
*
* @return Handle of the newly created Helper Container object.
*
*/
ANSC_HANDLE
CcspCwmpCreateHelperContainer
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );


/***********************************************************
           FUNCTIONS IMPLEMENTED IN CCSP_CWMP_HCO_BASE.C
***********************************************************/

/**
* @brief Construct the CCSP CWMP Helper Container object.
*
* This function constructs the Helper Container object, allocates memory, and initializes
* member variables and functions.
*
* @param[in] hContainerContext  - Container context handle.
* @param[in] hOwnerContext  - Owner context handle.
* @param[in] hAnscReserved  - Reserved context handle.
*
* @return Handle of the newly created container object, or NULL if allocation fails.
* @retval Handle of the newly created container object on success.
* @retval NULL if allocation fails.
*
*/
ANSC_HANDLE
CcspCwmpHcoCreate
    (
        ANSC_HANDLE                 hContainerContext,
        ANSC_HANDLE                 hOwnerContext,
        ANSC_HANDLE                 hAnscReserved
    );

/**
* @brief Destroy the CCSP CWMP Helper Container object.
*
* This function destroys the Helper Container object and releasing all allocated memory resources.
*
* @param[in] hThisObject  - Handle to the Helper Container object to destroy.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the object is destroyed successfully.
*
*/
ANSC_STATUS
CcspCwmpHcoRemove
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Enroll all objects required by the Helper Container.
*
* This function enrolls all dependent utility objects and helper services required
* by the Helper Container for supporting TR-069 protocol operations.
*
* @param[in] hThisObject  - Handle to the Helper Container object.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if all objects enrolled successfully.
*
*/
ANSC_STATUS
CcspCwmpHcoEnrollObjects
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Initialize the CCSP CWMP Helper Container object.
*
* This function initializes the Helper Container object by calling the base class initializer
* and setting up object-specific fields and TR-069 interfaces.
*
* @param[in] hThisObject  - Handle to the Helper Container object.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if initialization is successful.
*
*/
ANSC_STATUS
CcspCwmpHcoInitialize
    (
        ANSC_HANDLE                 hThisObject
    );


#endif
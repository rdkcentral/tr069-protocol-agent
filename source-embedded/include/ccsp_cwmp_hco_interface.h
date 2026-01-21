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

    module:	ccsp_cwmp_hco_interface.h

        For CCSP CWMP protocol implementation

    ---------------------------------------------------------------

    description:

        This wrapper file defines all the platform-independent
        functions and macros for the CCSP CWMP Helper Container Object.

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
        10/12/11    resolve name conflict with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_HCO_INTERFACE_
#define  _CCSP_CWMP_HCO_INTERFACE_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_oco_interface.h"
#include "ansc_oco_external_api.h"


/***********************************************************
   PLATFORM INDEPENDENT OBJECT CONTAINER OBJECT DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the object mapper object definition.
 */
#define  CCSP_CWMP_HELPER_CONTAINER_NAME                 "cwmpHelpContainer"
#define  CCSP_CWMP_HELPER_CONTAINER_OID                  ANSC_OBJECT_OID_NULL
#define  CCSP_CWMP_HELPER_CONTAINER_TYPE                 ANSC_OBJECT_TYPE_NULL

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support),
 * we have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */

/**
* @brief Get context handle from the Helper Container object.
*
* This function pointer typedef defines the signature for retrieving a context handle
* associated with the CCSP CWMP Helper Container object. The context typically contains
* configuration or state information for the helper container.
*
* @param[in] hThisObject  - Handle to the Helper Container object.
*                    \n This is the object instance from which to retrieve the context.
*
* @return Handle to the context object.
* @retval Handle to the context object on success.
* @retval NULL if no context is set.
*
*/
typedef  ANSC_HANDLE
(*PFN_CWMPHCO_GET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set context handle for the Helper Container object.
*
* This function pointer typedef defines the signature for setting a context handle
* associated with the CCSP CWMP Helper Container object. The context can be used to
* store configuration or state information.
*
* @param[in] hThisObject  - Handle to the Helper Container object.
*                    \n This is the object instance for which to set the context.
* @param[in] hContext  - Handle to the context object to associate.
*                    \n Can be NULL to clear the existing context.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if context is set successfully.
*
*/
typedef  ANSC_STATUS
(*PFN_CWMPHCO_SET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hContext
    );

/**
* @brief Get interface handle from the Helper Container object.
*
* This function pointer typedef defines the signature for retrieving an interface handle
* from the CCSP CWMP Helper Container object. Interfaces provide access to specific
* functionality or services offered by the container.
*
* @param[in] hThisObject  - Handle to the Helper Container object.
*                    \n This is the object instance from which to retrieve the interface.
*
* @return Handle to the interface object
* @retval Handle to the interface object on success.
* @retval NULL if interface is not available.
*
*/
typedef  ANSC_HANDLE
(*PFN_CWMPHCO_GET_IF)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get carrier object for a session context.
*
* This function pointer typedef defines the signature for retrieving a carrier object
* associated with a specific session context. The carrier typically encapsulates data
* or messages being transported within the TR-069 protocol session.
*
* @param[in] hThisObject  - Handle to the Helper Container object.
*                    \n This is the object instance managing the sessions.
* @param[in] hSessionContext  - Handle to the session context.
*                    \n Identifies the specific session for which to retrieve the carrier.
*
* @return Handle to the carrier object.
* @retval Handle to the carrier object on success.
* @retval NULL if no carrier exists for the session.
*
*/
typedef  ANSC_HANDLE
(*PFN_CWMPHCO_GET_CARRIER)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSessionContext
    );

/**
* @brief Set carrier object for a session context.
*
* This function pointer typedef defines the signature for setting a carrier object
* for a specific session context. The carrier encapsulates data or messages being
* transported within the TR-069 protocol session.
*
* @param[in] hThisObject  - Handle to the Helper Container object.
*                    \n This is the object instance managing the sessions.
* @param[in] hSessionContext  - Handle to the session context.
*                    \n Identifies the specific session for which to set the carrier.
* @param[in] hCarrier  - Handle to the carrier object to associate with the session.
*                    \n Contains the data or message payload for the session.
* @param[in] ulSize  - Size of the carrier data in bytes.
*                    \n Used for memory management and validation.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if carrier is set successfully.
*
*/
typedef  ANSC_STATUS
(*PFN_CWMPHCO_SET_CARRIER)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hSessionContext,
        ANSC_HANDLE                 hCarrier,
        ULONG                       ulSize
    );

/*
 * As a standard practice, we encapsulate all functional and feature objects inside an Object
 * Container Object so it will function as a black-box implementation when we have to integrate
 * an Ansc component with other systems. However, that's not the only reason why we need to
 * define the Container Object: we also use container as the building block for constructing
 * larger systems.
 */
#define  CCSP_CWMP_HELPER_CONTAINER_CLASS_CONTENT                                           \
    /* duplication of the base object class content */                                      \
    ANSC_OBJECT_CONTAINER_CLASS_CONTENT                                                     \
    /* start of object class content */                                                     \
    /* end of object class content */                                                       \

typedef  struct
_CCSP_CWMP_HELPER_CONTAINER_OBJECT
{
    CCSP_CWMP_HELPER_CONTAINER_CLASS_CONTENT
}
CCSP_CWMP_HELPER_CONTAINER_OBJECT,  *PCCSP_CWMP_HELPER_CONTAINER_OBJECT;

#define  ACCESS_CCSP_CWMP_HELPER_CONTAINER_OBJECT(p)     \
         ACCESS_CONTAINER(p, CCSP_CWMP_HELPER_CONTAINER_OBJECT, Linkage)


#endif
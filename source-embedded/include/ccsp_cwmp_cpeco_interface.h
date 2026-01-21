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

    module: ccsp_cwmp_cpeco_interface.h

        For CCSP CWMP protocol implementation

    ---------------------------------------------------------------

    description:

        This wrapper file defines all the platform-independent
        functions and macros for the CCSP CWMP Cpe Controller Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang
        Bin     Zhu
        Kang Quan

    ---------------------------------------------------------------

    revision:

        09/09/2005    initial revision.
        02/04/2010    Bin added Statistics interface for TR69
        06/21/11      decouple TR-069 PA from Data Model Manager
                      and make it work with CCSP architecture.
        10/12/11      resolve namespace conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_CPECO_INTERFACE_
#define  _CCSP_CWMP_CPECO_INTERFACE_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_co_interface.h"
#include "ansc_co_external_api.h"
#include "ccsp_cwmp_properties.h"

#include "ccsp_cwmp_ifo_mco.h"
#include "ccsp_cwmp_ifo_cfg.h"

#include "ccsp_types.h"
#include "ccsp_tr069pa_mapper_def.h"
#include "ccsp_base_api.h"

/***********************************************************
       CCSP CWMP CPE CONTROLLER COMPONENT OBJECT DEFINITION
***********************************************************/

#define  CCSP_TR069PA_SESSION_PRIORITY_READONLY     9
#define  CCSP_TR069PA_SESSION_PRIORITY_WRTIABLE     10

/*
 * Define some const values that will be used in the object mapper object definition.
 */
#define  CCSP_CR_DEF_NAME                           CCSP_DBUS_INTERFACE_CR
#define  CCSP_TR069PA_DEF_NAME                      "com.cisco.spvtg.ccsp.tr069pa"

/*
 * Define CWMP statistics related structure
 */
#define  CCSP_CWMP_CONNECTION_STATUS_SUCCESS                     1
#define  CCSP_CWMP_CONNECTION_STATUS_FAILURE                     0

typedef  struct
_CCSP_CWMP_STATISTICS
{
    ULONG                           uTcpSuccess;
    ULONG                           uTcpFailures;
    ULONG                           uTlsFailures;
    ANSC_UNIVERSAL_TIME             LastConnectionTime;
    ULONG                           uLastConnectionStatus;
    ANSC_UNIVERSAL_TIME             LastInformResponseTime;
    ANSC_UNIVERSAL_TIME             LastReceivedSPVTime;
}
CCSP_CWMP_STATISTICS,  *PCCSP_CWMP_STATISTICS;


/* define CPE controller event notification type */
#define  CCSP_CWMP_CPECO_EVENT_Unkonwn                   0
#define  CCSP_CWMP_CPECO_EVENT_InterfaceUp               1
#define  CCSP_CWMP_CPECO_EVENT_InterfaceDown             2
#define  CCSP_CWMP_CPECO_EVENT_InterfaceIpAddrChanged    3


#define  CCSP_CWMP_CPECO_CWMP_START_INTERVAL				5 * 1000           /* in milli-seconds */


#define  CcspCwmpCpecoRemoveParamNameValues(numParams, names, values)                       \
    do {                                                                                \
        int                         i;                                                  \
        for (i = 0; i < numParams; i ++)                                                \
        {                                                                               \
            if ( names[i] ) AnscFreeMemory(names[i]);                                   \
            if ( values[i] ) CcspVariableClean(AnscFreeMemory, values[i]);              \
        }                                                                               \
        AnscFreeMemory(names);                                                          \
        AnscFreeMemory(values);                                                         \
    } while (0)

#define  CcspCwmpCpecoAllocateStringArray(numParams, sarray)                                \
    sarray = (char**)AnscAllocateMemory(numParams * sizeof(char*))

#define  CcspCwmpCpecoRemoveParamNameStringValues(numParams, names, values)                 \
    do {                                                                                \
        int                         i;                                                  \
        for (i = 0; i < numParams; i ++)                                                \
        {                                                                               \
            if ( names[i] ) AnscFreeMemory(names[i]);                                   \
            if ( values[i] ) AnscFreeMemory(values[i]);                                 \
        }                                                                               \
        AnscFreeMemory(names);                                                          \
        AnscFreeMemory(values);                                                         \
    } while (0)


/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support),
 * we have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */

/**
 * @brief Get context handle from the CPE Controller object.
 *
 * This function pointer type defines the signature for retrieving context handles
 * from the CCSP CWMP CPE Controller object, such as ACS Broker, Processor, SOAP Parser,
 * TCP Connection Request Handler, or Message Bus handle.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 *
 * @return Handle to the requested context object, or NULL if not set.
 * @retval Handle to the requested context object on success.
 * @retval NULL if not set.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPCPECO_GET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set context handle for the CPE Controller object.
 *
 * This function pointer type defines the signature for setting context handles
 * in the CCSP CWMP CPE Controller object.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] hContext    - Handle to the context object to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the operation is successful.
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_SET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hContext
    );

/**
 * @brief Get interface handle from the CPE Controller object.
 *
 * This function pointer type defines the signature for retrieving interface handles
 * from the CCSP CWMP CPE Controller object, such as MCO (Management Server Controller Interface)
 * or MSO (Management Server Object Interface) or CFG (Configuration Interface).
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 *
 * @return Handle to the requested interface object, or NULL if not available.
 * @retval Handle to the requested interface objecton success.
 * @retval NULL if not available.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPCPECO_GET_IF)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set interface handle for the CPE Controller object.
 *
 * This function pointer type defines the signature for setting interface handles
 * in the CCSP CWMP CPE Controller object, particularly the Configuration Interface.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] hInterface  - Handle to the interface object to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the operation is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_SET_IF)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hInterface
    );

/**
 * @brief Get property data from the CPE Controller object.
 *
 * This function pointer type defines the signature for retrieving the property
 * structure of the CCSP CWMP CPE Controller object.
 *
 * @param[in]  hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[out] hProperty   - Handle to the property structure to be filled with current property values.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the operation is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_GET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Set property data for the CPE Controller object.
 *
 * This function pointer type defines the signature for configuring the property
 * structure of the CCSP CWMP CPE Controller object.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] hProperty   - Handle to the property structure containing new configuration values.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the operation is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_SET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Reset the CPE Controller object to its initial state.
 *
 * This function pointer type defines the signature for resetting the CCSP CWMP CPE Controller object.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the operation is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_RESET)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Perform a generic action on the CPE Controller object.
 *
 * This function pointer type defines the signature for performing various actions
 * on the CCSP CWMP CPE Controller object, such as Engage, Cancel, SetupEnv, CloseEnv,
 * StopCWMP, or InformNow operations.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the action is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_ACTION)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Start the CWMP (TR-069) protocol operations.
 *
 * This function pointer type defines the signature for starting CWMP operations in the CPE Controller.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] bInformAcs  - Specifies if CPE is going to send Inform to ACS.
                            TRUE to send an Inform message to the ACS, FALSE to start without informing.
 * @param[in] bRestart    - TRUE if this is a restart operation, FALSE for initial start.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if CWMP is successfully started.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_START_CWMP)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bInformAcs,
        BOOL                        bRestart
    );

/**
 * @brief Restart the CWMP (TR-069) protocol operations.
 *
 * This function pointer type defines the signature for restarting CWMP operations.
 * This stops the current CWMP session and restarts it, optionally sending an Inform message.
 * The data model is not going to be unloaded.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] bInformAcs  - TRUE to send an Inform message to the ACS after restart, FALSE otherwise.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if CWMP is successfully restarted.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_RESTART_CWMP)
    (
        ANSC_HANDLE                         hThisObject,
        BOOL                                bInformAcs
    );

/**
 * @brief Notify the CPE Controller of system events.
 *
 * This function pointer type defines the signature for notifying the CPE Controller
 * about system events such as interface up/down, IP address changes, or other network events.
 *
 * @param[in] hThisObject    - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] ulEvent        - Event type identifier.
 * @param[in] hEventContext  - Handle to event-specific context data.
 *
 * @return void
 *
 */
typedef  void
(*PFN_CWMPCPECO_EVENT_NOTIFY)
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulEvent,
        ANSC_HANDLE                 hEventContext
    );

/**
 * @brief Get the root object name for the TR-069 data model.
 *
 * This function pointer type defines the signature for retrieving the root object
 * name of the TR-069 data model hierarchy.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 *
 * @return Pointer to the root object name string, or NULL if not set.
 * @retval Pointer to the root object name string on success.
 * @retval NULL if not set.
 *
 */
typedef  char*
(*PFN_CWMPCPECO_GET_ROBJ)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set the root object name for the TR-069 data model.
 *
 * This function pointer type defines the signature for setting the root object
 * name of the TR-069 data model hierarchy.
 *
 * @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] pRootObject  - Pointer to the root object name string.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the operation is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_SET_ROBJ)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRootObject
    );

/**
 * @brief Get parameter values from the data model.
 *
 * This function pointer type defines the signature for retrieving parameter values
 * from the TR-069 data model. Values are returned as CCSP_VARIABLE structures.
 *
 * @param[in]  hThisObject   - Handle to the CCSP CWMP CPE Controller object.
 * @param[in]  ppParamNames  - Array of parameter name strings to retrieve.
 * @param[in]  NumOfParams   - Number of parameters in the array.
 * @param[out] pParamValues  - Array of CCSP_VARIABLE structures to receive the parameter values.  
 *                             On successful return, it contains the values of the specified parameters.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if all parameters are successfully retrieved.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_GPV)
    (
        ANSC_HANDLE                 hThisObject,
        char**                      ppParamNames,
        int                         NumOfParams,
        PCCSP_VARIABLE              pParamValues
    );

/**
 * @brief Get parameter values as strings from the data model.
 *
 * This function pointer type defines the signature for retrieving parameter values
 * from the TR-069 data model as string values.
 *
 * @param[in]  hThisObject   - Handle to the CCSP CWMP CPE Controller object.
 * @param[in]  ppParamNames  - Array of parameter name strings to retrieve. This API only takes full parameter names.
 *                             If partial name is used, call GPV implemented by CCSP CWMP MPA interface.
 * @param[in]  NumOfParams   - Number of parameters in the array.
 * @param[out] pParamValues  - Array of string pointers to receive the parameter values.
 *                             On successful return, it contains the values of the specified parameters.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if all parameters are successfully retrieved.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_GPV2)
    (
        ANSC_HANDLE                 hThisObject,
        char**                      ppParamNames,
        int                         NumOfParams,
        char**                      pParamValues
    );

/**
 * @brief Get a single parameter value as a string from the data model.
 *
 * This function pointer type defines the signature for retrieving a single parameter
 * value from the TR-069 data model as a string.
 *
 * @param[in]  hThisObject  - Handle to the CCSP CWMP CPE Controller object.
 * @param[in]  pParamName   - Parameter name string to retrieve.
 * @param[out] pParamValue  - Pointer to receive the allocated string containing the parameter value.
 *                            On successful return, it contains the values of the specified parameters.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the parameter is successfully retrieved.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_GPV3)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName,
        char**                      pParamValue
    );

/**
 * @brief Set parameter values in the data model.
 *
 * This function pointer type defines the signature for setting parameter values
 * in the TR-069 data model.
 *
 * @param[in] hThisObject   - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] ppParamNames  - Array of parameter name strings to set.
 * @param[in] NumOfParams   - Number of parameters in the array.
 * @param[in] pParamValues  - Array of CCSP_VARIABLE structures containing the parameter values to set.
 *                            Specifies the values of specified parameters.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if all parameters are successfully set.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_SPV)
    (
        ANSC_HANDLE                 hThisObject,
        char**                      ppParamNames,
        int                         NumOfParams,
        PCCSP_VARIABLE              pParamValues
    );

/**
 * @brief Add object instances in the TR-069 data model.
 *
 * This function pointer type defines the signature for creating new instances of
 * multi-instance objects in the TR-069 data model.
 *
 * @param[in]  hThisObject   - Handle to the CCSP CWMP CPE Controller object.
 * @param[in]  pObjectName   - Name of the object to add instances to.
 * @param[in]  NumInstances  - Number of instances to create.
 * @param[out] pInsNumbers   - Array to receive the instance numbers of created objects.
 * @param[out] ppCwmpFault   - Pointer to receive SOAP fault information that indicate error if the operation fails.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if all instances are successfully created.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_AOS)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pObjectName,
        int                         NumInstances,
        PULONG                      pInsNumbers,
        PCCSP_CWMP_SOAP_FAULT*      ppCwmpFault
    );

/**
 * @brief Delete object instances from the TR-069 data model.
 *
 * This function pointer type defines the signature for deleting instances of
 * multi-instance objects in the TR-069 data model. Deletion can be immediate or delayed.
 *
 * @param[in]  hThisObject   - Handle to the CCSP CWMP CPE Controller object.
 * @param[in]  pObjectName   - Name of the object containing instances to delete.
 * @param[in]  NumInstances  - Number of instances to delete.
 * @param[in]  pInsNumbers   - Array of instance numbers to delete.
 * @param[out] ppCwmpFault   - Pointer to receive SOAP fault information if the operation fails.
 * @param[in]  DelaySeconds  - Number of seconds to delay before deletion, 0 for immediate.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if all instances are successfully deleted or scheduled for deletion.
 * @retval ANSC_STATUS_RESOURCES if memory allocation fails for the delayed task context.
 * @retval ANSC_STATUS_INTERNAL_ERROR if a SOAP fault is encountered during immediate deletion.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_DOS)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pObjectName,
        int                         NumInstances,
        PULONG                      pInsNumbers,
        PCCSP_CWMP_SOAP_FAULT*      ppCwmpFault,
        ULONG                       DelaySeconds
    );

/**
 * @brief Monitor operational state of object instances.
 *
 * This function pointer type defines the signature for monitoring the operational
 * state of object instances. This is used to track state changes of objects that
 * may take time to complete operations.
 *
 * @param[in]  hThisObject      - Handle to the CCSP CWMP CPE Controller object.
 * @param[in]  bMonitor         - TRUE to start monitoring, FALSE to stop monitoring.
 * @param[in]  pObjectName      - Name of the object containing instances to monitor.
 * @param[in]  NumInstances     - Number of instances to monitor.
 * @param[in]  pInsNumbers      - Array of instance numbers to monitor.
 * @param[in]  pStateParamName  - Name of the state parameter to monitor.
 * @param[out] ppCwmpFault      - Pointer to receive SOAP fault information if the operation fails.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if monitoring is successfully started or stopped.
 * @retval ANSC_STATUS_RESOURCES if memory allocation fails for parameter attributes.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_MONITOR_OPS)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bMonitor,
        char*                       pObjectName,
        int                         NumInstances,
        PULONG                      pInsNumbers,
        char*                       pStateParamName,
        PCCSP_CWMP_SOAP_FAULT*      ppCwmpFault
    );

/**
 * @brief Register or unregister the Protocol Agent with the Component Registrar.
 *
 * This function pointer type defines the signature for registering or unregistering
 * the TR-069 Protocol Agent with the CCSP Component Registrar for service discovery.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] bRegister   - TRUE to register the PA, FALSE to unregister.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if registration/unregistration is successful.
 * @retval ANSC_STATUS_FAILURE if registration/unregistration fails to communicate with the Component Registrar.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_REG)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bRegister
    );

/**
 * @brief Set a name/string attribute for the CPE Controller.
 *
 * This function pointer type defines the signature for setting various name or string attributes
 * such as PA Name, Subsystem Name, CR Name, Mapper File, SDM XML Filename, or Outbound Interface Name.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] pName       - Pointer to the string value to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the operation is successful.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_SETNAME)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
 * @brief Set a keyed name attribute for the CPE Controller.
 *
 * This function pointer type defines the signature for setting name attributes
 * that require a key, such as the CR Bus Path associated with a specific key.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] pKey        - Pointer to the key string.
 * @param[in] pName       - Pointer to the name/value string to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the operation is successful.
 * @retval ANSC_STATUS_RESOURCES if the maximum number of subsystems has been reached.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_SETNAME2)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pKey,
        char*                       pName
    );

/**
 * @brief Get a name/string attribute from the CPE Controller.
 *
 * This function pointer type defines the signature for retrieving various name or string
 * attributes such as PA Name, Subsystem Name, CR Name, SDM XML Filename, or Outbound Interface Name.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 *
 * @return Pointer to the requested string attribute, or NULL if not set.
 * @retval Pointer to the requested string attribute on success.
 * @retval NULL if not set.
 *
 */
typedef  char*
(*PFN_CWMPCPECO_GETNAME)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Get a keyed name attribute from the CPE Controller.
 *
 * This function pointer type defines the signature for retrieving name attributes
 * that require a key, such as the CR Bus Path associated with a specific key.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] pKey        - Pointer to the key string.
 *
 * @return Pointer to the requested string attribute, or NULL if not set.
 * @return Pointer to the requested string attribute on success.
 * @retval NULL if not set.
 *
 */
typedef  char*
(*PFN_CWMPCPECO_GETNAME2)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pKey
    );

/**
 * @brief Get the notification attribute of a parameter.
 *
 * This function pointer type defines the signature for retrieving the notification
 * attribute of a TR-069 parameter.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] pParamName  - Parameter name string.
 *
 * @return Notification attribute value:
 * @retval 0 - Notification off
 * @retval 1 - Passive notification
 * @retval 2 - Active notification
 *
 */
typedef  int
(*PFN_CWMPCPECO_GET_NOTIF)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName
    );

/**
 * @brief Set the notification attribute of a parameter.
 *
 * This function pointer type defines the signature for setting the notification
 * attribute of a TR-069 parameter.
 *
 * @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] pParamName   - Parameter name string.
 * @param[in] Notification - Notification attribute value to set:
 *                           0 - Notification off
 *                           1 - Passive notification
 *                           2 - Active notification
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the notification is successfully set.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_SET_NOTIF)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName,
        int                         Notification
    );

/**
 * @brief Get the data type of a parameter.
 *
 * This function pointer type defines the signature for retrieving the data type of a TR-069 parameter.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] pParamName  - Parameter name string.
 *
 * @return Data type identifier as defined by TR-069 specification.
 *
 */
typedef  int
(*PFN_CWMPCPECO_GET_PTYPE)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName
    );

/**
 * @brief Save a configuration value to Persistent Storage Manager (PSM).
 *
 * This function pointer type defines the signature for saving TR-069 configuration
 * values to PSM for persistence across reboots.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] pCfgKey     - Configuration key string identifying the setting.
 * @param[in] pCfgValue   - Configuration value string to save.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the configuration is successfully saved.
 * @retval ANSC_STATUS_FAILURE if fails to save the configuration.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_SAVE_CFG_PSM)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pCfgKey,
        char*                       pCfgValue
    );

/**
 * @brief Load a configuration value from Persistent Storage Manager (PSM).
 *
 * This function pointer type defines the signature for loading TR-069 configuration values from PSM.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] pCfgKey     - Configuration key string identifying the setting to load.
 *
 * @return Pointer to the allocated configuration value string, or NULL if not found.
 * @retval Pointer to the allocated configuration value string on success.
 * @retval NULL if not found.
 *
 */
typedef  char*
(*PFN_CWMPCPECO_LOAD_CFG_PSM)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pCfgKey
    );

/**
 * @brief Set the ParameterKey for tracking configuration changes.
 *
 * This function pointer type defines the signature for setting the TR-069 ParameterKey.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] pParamKey   - Parameter key string to set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the parameter key is successfully set.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_SET_PARAM_KEY)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamKey
    );

/**
 * @brief Acquire a Component Registrar (CR) session ID.
 *
 * This function pointer type defines the signature for acquiring a session ID from
 * the Component Registrar for accessing CCSP components with priority-based access control.
 *
 * @param[in] hThisObject - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] Priority    - Session priority level. Higher values indicate higher priority:
 *                          CCSP_TR069PA_SESSION_PRIORITY_READONLY (9) - Read-only access
 *                          CCSP_TR069PA_SESSION_PRIORITY_WRTIABLE (10) - Read-write access
 *
 * @return The acquired session ID.
 * @retval A non-zero ULONG value if a session ID is successfully acquired.
 * @retval 0 if acquisition failed.
 *
 */
typedef  ULONG
(*PFN_CWMPCPECO_ACQ_CR_SESSID)
    (
        ANSC_HANDLE                 hThisObject,
        int                         Priority
    );

/**
 * @brief Release a Component Registrar (CR) session ID.
 *
 * This function pointer type defines the signature for releasing a previously acquired
 * session ID from the Component Registrar, freeing resources and access rights.
 *
 * @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller object.
 * @param[in] CrSessionID  - The session ID to release, previously acquired via AcqCrSessionID.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS if the session is successfully released.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPCPECO_REL_CR_SESSID)
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       CrSessionID
    );

/*
 * The CPE WAN Management Protocol allows an ACS to provision a CPE or collection of CPE based on a
 * variety of criteria. The provisioning mechanism includes specific provisioning parameters and a
 * general mecahnism for adding vendor-specific provisioning capabilities as needed.
 *
 * The provisioning mechanism allows CPE provisioning at the time of initial connection to the
 * broadband access network, and the ability to re-provision at any subsequent time. This includes
 * support for asynchronous ACS-initiated re-provisioning of a CPE.
 */
#define  CCSP_CWMP_CPE_CONTROLLER_CLASS_CONTENT                                             \
    /* duplication of the base object class content */                                      \
    ANSCCO_CLASS_CONTENT                                                                    \
    /* start of object class content */                                                     \
    CCSP_CWMP_CPE_CONTROLLER_PROPERTY    Property;                                          \
    ANSC_HANDLE                     hCcspCwmpAcsBroker;                                     \
    ANSC_HANDLE                     hCcspCwmpProcessor;                                     \
    ANSC_HANDLE                     hCcspCwmpDatabase;                                      \
    ANSC_HANDLE                     hCcspCwmpSoapParser;                                    \
    ANSC_HANDLE                     hCcspCwmpTcpConnReqHandler;                             \
    ANSC_HANDLE                     hCcspCwmpStunManager;                                   \
    ANSC_HANDLE                     hMsgBusHandle;                                          \
    char*                           PAName;                                                 \
    char*                           SubsysName;                                             \
    char*                           CRName;                                                 \
    char*                           CRNameWithPrefix;                                       \
    char*                           PAMapperFile;                                           \
    char*                           PACustomMapperFile;                                     \
    char*                           PANameWithPrefix;                                       \
    char*                           SdmXmlFile;                                             \
    char*                           OutboundIfName;                                         \
                                                                                            \
    BOOL                            bBootstrapInformScheduled;                              \
    BOOL                            bBootInformScheduled;                                   \
    BOOL                            bDelayedInformCancelled;                                \
    CCSP_CWMP_STATISTICS            cwmpStats;                                              \
    BOOL                            bCWMPStarted;                                           \
    BOOL                            bCpeRebooting;                                          \
    BOOL                            bCWMPStopping;                                          \
    BOOL                            bBootInformSent;                                        \
    BOOL                            bRestartCWMP;                                           \
                                                                                            \
    ANSC_HANDLE                     hStartCwmpTimerObj;                                     \
    ANSC_HANDLE                     hStartCwmpTimerIf;                                      \
                                                                                            \
    ANSC_HANDLE                     hCcspCwmpCfgIf;                                         \
    ANSC_HANDLE                     hCcspCwmpStaIf;                                         \
    BOOL                            bActive;                                                \
                                                                                            \
    BOOL                            bBootEventAdded;                                        \
    char*                           pRootObject;                                            \
    CCSP_HANDLE                     hTr069PaMapper;                                         \
    char*                           Subsystem[CCSP_SUBSYSTEM_MAX_COUNT];                    \
    char*                           MBusPath [CCSP_SUBSYSTEM_MAX_COUNT];                    \
    int                             NumSubsystems;                                          \
                                                                                            \
    PFN_CWMPCPECO_GET_CONTEXT       GetCcspCwmpAcsBroker;                                   \
    PFN_CWMPCPECO_GET_CONTEXT       GetCcspCwmpProcessor;                                   \
    PFN_CWMPCPECO_GET_CONTEXT       GetCcspCwmpSoapParser;                                  \
    PFN_CWMPCPECO_GET_CONTEXT       GetCcspCwmpTcpConnReqHandler;                           \
    PFN_CWMPCPECO_GET_ROBJ          GetRootObject;                                          \
    PFN_CWMPCPECO_SET_ROBJ          SetRootObject;                                          \
                                                                                            \
    PFN_CWMPCPECO_GET_PROPERTY      GetProperty;                                            \
    PFN_CWMPCPECO_SET_PROPERTY      SetProperty;                                            \
    PFN_CWMPCPECO_RESET             ResetProperty;                                          \
    PFN_CWMPCPECO_RESET             Reset;                                                  \
                                                                                            \
    PFN_CWMPCPECO_GET_IF            GetCcspCwmpMcoIf;                                       \
    PFN_CWMPCPECO_GET_IF            GetCcspCwmpMsoIf;                                       \
                                                                                            \
    PFN_CWMPCPECO_ACTION            Engage;                                                 \
    PFN_CWMPCPECO_ACTION            Cancel;                                                 \
    PFN_CWMPCPECO_ACTION            SetupEnv;                                               \
    PFN_CWMPCPECO_ACTION            CloseEnv;                                               \
                                                                                            \
    PFN_CWMPCPECO_START_CWMP        StartCWMP;                                              \
    PFN_CWMPCPECO_ACTION            StopCWMP;                                               \
    PFN_CWMPCPECO_RESTART_CWMP      RestartCWMP;                                            \
    PFN_CWMPCPECO_GET_IF            GetCcspCwmpCfgIf;                                       \
    PFN_CWMPCPECO_SET_IF            SetCcspCwmpCfgIf;                                       \
                                                                                            \
    PFN_CWMPCPECO_ACTION            InformNow;                                              \
    PFN_CWMPCPECO_EVENT_NOTIFY      NotifyEvent;                                            \
    PFN_CWMPCPECO_ACQ_CR_SESSID     AcqCrSessionID;                                         \
    PFN_CWMPCPECO_REL_CR_SESSID     RelCrSessionID;                                         \
                                                                                            \
    PFN_CWMPCPECO_GPV               GetParamValues;                                         \
    PFN_CWMPCPECO_GPV2              GetParamStringValues;                                   \
    PFN_CWMPCPECO_GPV3              GetParamStringValue;                                    \
    /*PFN_CWMPCPECO_SPV               SetParamValues;*/                                     \
    PFN_CWMPCPECO_AOS               AddObjects;                                             \
    PFN_CWMPCPECO_DOS               DeleteObjects;                                          \
    PFN_CWMPCPECO_MONITOR_OPS       MonitorOpState;                                         \
    PFN_CWMPCPECO_REG               RegisterPA;                                             \
    PFN_CWMPCPECO_SETNAME           SetPAName;                                              \
    PFN_CWMPCPECO_GETNAME           GetPAName;                                              \
    PFN_CWMPCPECO_SETNAME           SetSubsysName;                                          \
    PFN_CWMPCPECO_GETNAME           GetSubsysName;                                          \
    PFN_CWMPCPECO_SETNAME           SetCRName;                                              \
    PFN_CWMPCPECO_GETNAME           GetCRName;                                              \
    PFN_CWMPCPECO_SETNAME2          SetCRBusPath;                                           \
    PFN_CWMPCPECO_GETNAME2          GetCRBusPath;                                           \
    PFN_CWMPCPECO_SETNAME           SetPAMapperFile;                                        \
    PFN_CWMPCPECO_SETNAME           SetPACustomMapperFile;                                  \
    PFN_CWMPCPECO_SETNAME           SetSDMXmlFilename;                                      \
    PFN_CWMPCPECO_GETNAME           GetOutboundIfName;                                      \
    PFN_CWMPCPECO_SETNAME           SetOutboundIfName;                                      \
    PFN_CWMPCPECO_GETNAME           GetSDMXmlFilename;                                      \
    PFN_CWMPCPECO_GET_CONTEXT       GetMsgBusHandle;                                        \
    PFN_CWMPCPECO_GET_NOTIF         GetParamNotification;                                   \
    PFN_CWMPCPECO_SET_NOTIF         SetParamNotification;                                   \
    PFN_CWMPCPECO_GET_PTYPE         GetParamDataType;                                       \
    PFN_CWMPCPECO_SAVE_CFG_PSM      SaveCfgToPsm;                                           \
    PFN_CWMPCPECO_LOAD_CFG_PSM      LoadCfgFromPsm;                                         \
    PFN_CWMPCPECO_SET_PARAM_KEY     SetParameterKey;                                        \
    /* end of object class content */                                                       \

typedef  struct
_CCSP_CWMP_CPE_CONTROLLER_OBJECT
{
    CCSP_CWMP_CPE_CONTROLLER_CLASS_CONTENT
}
CCSP_CWMP_CPE_CONTROLLER_OBJECT,  *PCCSP_CWMP_CPE_CONTROLLER_OBJECT;

#define  ACCESS_CCSP_CWMP_CPE_CONTROLLER_OBJECT(p)       \
         ACCESS_CONTAINER(p, CCSP_CWMP_CPE_CONTROLLER_OBJECT, Linkage)


#endif
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

    module: ccsp_cwmp_cpeco_internal_api.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the internal functions provided by the CCSP CWMP Cpe Controller
        Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Bin  Zhu
        Kang Quan

    ---------------------------------------------------------------

    revision:

        09/09/05    initial revision.
        02/12/09    add more statistics apis
        04/25/11    decouple TR-069 PA from Data Model Manager
                    and make it work with CCSP COSA 2.0 CDMMM.
        10/13/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_CPECO_INTERNAL_API_
#define  _CCSP_CWMP_CPECO_INTERNAL_API_


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_CPECO_STATES.C
***********************************************************/

/**
* @brief Get the CCSP CWMP ACS Broker handle.
*
* This function is called to retrieve the ACS (Auto-Configuration Server) Broker
* object handle associated with this CCSP CWMP CPE Controller object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP ACS Broker.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpCpecoGetCcspCwmpAcsBroker
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the CCSP CWMP Processor handle.
*
* This function is called to retrieve the CWMP Processor object handle
* associated with this CCSP CWMP CPE Controller object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP Processor.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpCpecoGetCcspCwmpProcessor
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the CCSP CWMP SOAP Parser handle.
*
* This function is called to retrieve the CWMP SOAP Parser object handle
* associated with this CCSP CWMP CPE Controller object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP SOAP Parser.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpCpecoGetCcspCwmpSoapParser
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the CCSP CWMP STUN Manager handle.
*
* This function is called to retrieve the CWMP STUN (Session Traversal Utilities for NAT)
* Manager object handle associated with this CCSP CWMP CPE Controller object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP STUN Manager.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpCpecoGetCcspCwmpStunManager
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the CCSP CWMP TCP Connection Request Handler handle.
*
* This function is called to retrieve the CWMP TCP Connection Request Handler object handle
* associated with this CCSP CWMP CPE Controller object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP TCP Connection Request Handler.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpCpecoGetCcspCwmpTcpConnReqHandler
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the root object name.
*
* This function is called to retrieve the root object name string for the
* TR-069 data model hierarchy.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the root object name string.
* @retval root object name string if the operation is successful.
*
*/
char*
CcspCwmpCpecoGetRootObject
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the root object name.
*
* This function is called to configure the root object name string for the
* TR-069 data model hierarchy. It frees any existing root object and clones the new one.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRootObject  - Pointer to the new root object name string.
*                    \n Can be NULL to clear the root object.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetRootObject
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRootObject
    );

/**
* @brief Retrieve the object property.
*
* This function is called to retrieve the property configuration of the
* CCSP CWMP CPE Controller object and copy it to the provided property structure.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[out] hProperty  - Handle to the property data structure to be filled.
*                    \n This structure will receive the current object property.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoGetProperty
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
* @brief Configure the object property.
*
* This function is called to configure the property of the CCSP CWMP CPE Controller
* object by copying the provided property structure to the object's internal property.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hProperty  - Handle to the property data structure to be copied.
*                    \n This structure will be copied to the object's property.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetProperty
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
* @brief Reset the object property.
*
* This function is called to reset the property of the CCSP CWMP CPE Controller
* object to its default state.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoResetProperty
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Reset the object states.
*
* This function is called to reset all internal states of the CCSP CWMP CPE Controller
* object to their default values.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoReset
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the CCSP CWMP Configuration Interface.
*
* This function is called to retrieve the CWMP Configuration Interface handle.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP Configuration Interface.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpCpecoGetCcspCwmpCfgIf
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the CCSP CWMP Configuration Interface.
*
* This function is called to configure the CWMP Configuration Interface handle.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hInterface  - Handle to the new CCSP CWMP Configuration Interface.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetCcspCwmpCfgIf
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hInterface
    );


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_CPECO_ACCESS.C
***********************************************************/

/**
* @brief Get the CCSP CWMP MCO Interface.
*
* This function is called to retrieve the CWMP MCO (Management Command Object) Interface
* handle by acquiring a CWMP session and getting its MCO interface.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP MCO Interface.
* @retval ANSC_HANDLE if the operation is successful.
* @retval NULL if no CWMP session is available.
*
*/
ANSC_HANDLE
CcspCwmpCpecoGetCcspCwmpMcoIf
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the CCSP CWMP MSO Interface.
*
* This function is called to retrieve the CWMP MSO (Management Service Object) Interface
* handle from the ACS Broker.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP MSO Interface.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpCpecoGetCcspCwmpMsoIf
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get parameter values from the data model.
*
* This function is called to retrieve the values of specified parameters from the TR-069
* data model. It only accepts full parameter names (no partial names).
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] ppParamNames  - Array of parameter name strings.
*                    \n Must be full parameter names.
* @param[in] NumOfParams  - Number of parameters in the array.
*                    \n Range: 1 to maximum supported parameters.
* @param[out] pParamValues  - Array to receive the parameter values.
*                    \n Memory must be pre-allocated by caller.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if the returned value count doesn't match.
*
*/
ANSC_STATUS
CcspCwmpCpecoGetParamValues
    (
        ANSC_HANDLE                 hThisObject,
        char**                      ppParamNames,
        int                         NumOfParams,
        PCCSP_VARIABLE              pParamValues
    );

/**
* @brief Get parameter string values from the data model.
*
* This function is called to retrieve the string values of specified parameters from the TR-069
* data model. It only accepts full parameter names. Only string-type parameters will have their
* values returned; others will be NULL.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] ppParamNames  - Array of parameter name strings.
*                    \n Must be full parameter names.
* @param[in] NumOfParams  - Number of parameters in the array.
*                    \n Range: 1 to maximum supported parameters.
* @param[out] pParamValues  - Array to receive the parameter string values.
*                    \n Memory must be pre-allocated by caller. Non-string parameters will be NULL.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_RESOURCES if memory allocation fails.
* @retval ANSC_STATUS_INTERNAL_ERROR if the returned value count doesn't match.
*
*/
ANSC_STATUS
CcspCwmpCpecoGetParamStringValues
    (
        ANSC_HANDLE                 hThisObject,
        char**                      ppParamNames,
        int                         NumOfParams,
        char**                      pParamValues
    );

/**
* @brief Get a single parameter string value from the data model.
*
* This function is called to retrieve the string value of a single specified parameter
* from the TR-069 data model. It internally calls GetParamStringValues with a single parameter.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamName  - Parameter name string.
*                    \n Must be a full parameter name.
* @param[out] pParamValue  - Pointer to receive the parameter string value.
*                    \n Memory is allocated by this function.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_RESOURCES if memory allocation fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoGetParamStringValue
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName,
        char**                      pParamValue
    );

/**
* @brief Set parameter values in the data model.
*
* This function is called to set the values of specified parameters in the TR-069 data model.
* It handles various data types and applies the values to the appropriate backend components.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] ppParamNames  - Array of parameter name strings.
*                    \n Must be full parameter names.
* @param[in] NumOfParams  - Number of parameters in the array.
*                    \n Range: 1 to maximum supported parameters.
* @param[in] pParamValues  - Array of parameter values to set.
*                    \n Each entry contains type and value information.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_RESOURCES if memory allocation fails.
* @retval ANSC_STATUS_FAILURE if parameter setting fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetParamValues
    (
        ANSC_HANDLE                 hThisObject,
        char**                      ppParamNames,
        int                         NumOfParams,
        PCCSP_VARIABLE              pParamValues
    );

/**
* @brief Add object instances to the data model.
*
* This function is called to add new instances of specified objects in the TR-069 data model.
* It handles creation of multiple instances and returns their assigned instance numbers.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pObjectName  - Object name string.
*                    \n Must be a valid multi-instance object path.
* @param[in] NumInstances  - Number of instances to create.
*                    \n Range: 1 to maximum supported instances.
* @param[out] pInsNumbers  - Array to receive the assigned instance numbers.
*                    \n Memory must be pre-allocated by caller.
* @param[out] ppCwmpFault  - Pointer to receive SOAP fault information if operation fails.
*                    \n Will be NULL if no fault occurs.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_RESOURCES if memory allocation fails.
* @retval ANSC_STATUS_FAILURE if object creation fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoAddObjects
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pObjectName,
        int                         NumInstances,
        PULONG                      pInsNumbers,
        PCCSP_CWMP_SOAP_FAULT*      ppCwmpFault
    );

/**
* @brief Delete object instances from the data model.
*
* This function is called to delete specified instances of objects in the TR-069 data model.
* It handles deletion of multiple instances with an optional delay.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pObjectName  - Object name string.
*                    \n Must be a valid object path.
* @param[in] NumInstances  - Number of instances to delete.
*                    \n Range: 1 to maximum supported instances.
* @param[in] pInsNumbers  - Array of instance numbers to delete.
*                    \n Each entry identifies a specific instance.
* @param[out] ppCwmpFault  - Pointer to receive SOAP fault information if operation fails.
*                    \n Will be NULL if no fault occurs.
* @param[in] DelaySeconds  - Delay in seconds before executing the deletion.
*                    \n Range: 0 (immediate) to maximum delay value.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_RESOURCES if memory allocation fails.
* @retval ANSC_STATUS_FAILURE if object deletion fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoDeleteObjects
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pObjectName,
        int                         NumInstances,
        PULONG                      pInsNumbers,
        PCCSP_CWMP_SOAP_FAULT*      ppCwmpFault,
        ULONG                       DelaySeconds
    );

/**
* @brief Monitor the operational state of object instances.
*
* This function is called to enable or disable monitoring of the operational state for
* specified object instances. It tracks state changes of parameters and reports them.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bMonitor  - Monitoring control flag.
*                    \n TRUE to enable monitoring, FALSE to disable.
* @param[in] pObjectName  - Object name string.
*                    \n Must be a valid object path.
* @param[in] NumInstances  - Number of instances to monitor.
*                    \n Range: 1 to maximum supported instances.
* @param[in] pInsNumbers  - Array of instance numbers to monitor.
*                    \n Each entry identifies a specific instance.
* @param[in] pStateParamName  - Name of the state parameter to monitor.
*                    \n Must be a valid parameter name.
* @param[out] ppCwmpFault  - Pointer to receive SOAP fault information if operation fails.
*                    \n Will be NULL if no fault occurs.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_RESOURCES if memory allocation fails.
* @retval ANSC_STATUS_FAILURE if monitoring operation fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoMonitorOpState
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
* @brief Register the Protocol Agent with the Component Registrar.
*
* This function is called to register or unregister the Protocol Agent (PA) with the
* Component Registrar (CR) on the message bus. It manages the PA namespace registration.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bRegister  - Registration control flag.
*                    \n TRUE to register, FALSE to unregister.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if registration fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoRegisterPA
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bRegister
    );

/**
* @brief Set the Protocol Agent name.
*
* This function is called to configure the name of the Protocol Agent component.
* It frees any existing name and clones the new one.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pName  - Pointer to the new PA name string.
*                    \n Can be NULL to clear the PA name.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetPAName
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
* @brief Get the Protocol Agent name.
*
* This function is called to retrieve the name of the Protocol Agent component.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the PA name string.
* @retval char* if the operation is successful.
*
*/
char*
CcspCwmpCpecoGetPAName
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the subsystem name.
*
* This function is called to configure the subsystem name for the CCSP component.
* It frees any existing name and clones the new one.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pName  - Pointer to the new subsystem name string.
*                    \n Can be NULL to clear the subsystem name.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetSubsysName
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
* @brief Get the subsystem name.
*
* This function is called to retrieve the subsystem name for the CCSP component.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the subsystem name string.
* @retval char* if the operation is successful.
*
*/
char*
CcspCwmpCpecoGetSubsysName
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the Component Registrar name.
*
* This function is called to configure the Component Registrar (CR) name.
* It frees any existing name and clones the new one.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pName  - Pointer to the new CR name string.
*                    \n Can be NULL to clear the CR name.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetCRName
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
* @brief Get the Component Registrar name.
*
* This function is called to retrieve the Component Registrar (CR) name.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the CR name string.
* @retval char* if the operation is successful.
*
*/
char*
CcspCwmpCpecoGetCRName
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the Component Registrar bus path.
*
* This function is called to configure the bus path for the Component Registrar (CR)
* for a specific subsystem. It manages the CR bus path mapping.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pSubsystem  - Pointer to the subsystem name string.
*                    \n Identifies the subsystem for this bus path.
* @param[in] pName  - Pointer to the bus path string.
*                    \n Can be NULL to clear the bus path.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetCRBusPath
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pSubsystem,
        char*                       pName
    );

/**
* @brief Get the Component Registrar bus path.
*
* This function is called to retrieve the bus path for the Component Registrar (CR)
* for a specific subsystem.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pSubsystem  - Pointer to the subsystem name string.
*                    \n Identifies the subsystem to query.
*
* @return Pointer to the CR bus path string.
* @retval char* if the operation is successful.
*
*/
char*
CcspCwmpCpecoGetCRBusPath
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pSubsystem
    );

/**
* @brief Set the Protocol Agent mapper file path.
*
* This function is called to configure the file path for the Protocol Agent mapper file.
* The mapper file defines the mapping between TR-069 and CCSP data models.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pName  - Pointer to the mapper file path string.
*                    \n Must be a valid file path.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetPAMapperFile
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
* @brief Set the Protocol Agent custom mapper file path.
*
* This function is called to configure the file path for the Protocol Agent custom mapper file.
* The custom mapper file provides additional or override mappings for the data model.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pName  - Pointer to the custom mapper file path string.
*                    \n Must be a valid file path.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetPACustomMapperFile
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
* @brief Set the Service Data Model (SDM) XML filename.
*
* This function is called to configure the filename for the Service Data Model XML file.
* The SDM XML file defines the structure and parameters of the TR-069 data model.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pName  - Pointer to the SDM XML filename string.
*                    \n Must be a valid filename.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetSDMXmlFilename
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
* @brief Get the Service Data Model (SDM) XML filename.
*
* This function is called to retrieve the filename for the Service Data Model XML file.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the SDM XML filename string.
* @retval char* if the operation is successful.
*
*/
char*
CcspCwmpCpecoGetSDMXmlFilename
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the outbound interface name.
*
* This function is called to configure the name of the outbound network interface
* to be used for ACS communications.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pName  - Pointer to the outbound interface name string.
*                    \n Must be a valid network interface name.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetOutboundIfName
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pName
    );

/**
* @brief Get the outbound interface name.
*
* This function is called to retrieve the name of the outbound network interface
* used for ACS communications.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the outbound interface name string.
* @retval char* if the operation is successful.
*
*/
char*
CcspCwmpCpecoGetOutboundIfName
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the message bus handle.
*
* This function is called to retrieve the handle to the CCSP message bus.
* The message bus is used for inter-component communications.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the message bus.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpCpecoGetMsgBusHandle
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the notification attribute of a parameter.
*
* This function is called to retrieve the notification attribute setting for a specified
* TR-069 parameter. The notification attribute determines how parameter changes are reported.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamName  - Parameter name string.
*                    \n Must be a full parameter name.
*
* @return The notification attribute value.
* @retval int representing the notification level (0=off, 1=passive, 2=active).
*
*/
int
CcspCwmpCpecoGetParamNotification
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName
    );

/**
* @brief Set the notification attribute of a parameter.
*
* This function is called to configure the notification attribute for a specified
* TR-069 parameter. The notification attribute determines how parameter changes are reported.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamName  - Parameter name string.
*                    \n Must be a full parameter name.
* @param[in] Notification  - Notification attribute value.
*                    \n Range: 0 (off), 1 (passive notification), 2 (active notification).
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetParamNotification
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName,
        int                         Notification
    );

/**
* @brief Get the data type of a parameter.
*
* This function is called to retrieve the TR-069 data type for a specified parameter.
* It maps CCSP data types to TR-069 data types using the mapper.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamName  - Parameter name string.
*                    \n Must be a full parameter name.
*
* @return The TR-069 data type identifier.
* @retval int representing the TR-069 data type (e.g., string, int, boolean, etc.).
*
*/
int
CcspCwmpCpecoGetParamDataType
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName
    );

/**
* @brief Save a configuration key-value pair to Persistent Storage Manager (PSM).
*
* This function is called to save a specific TR-069 configuration key-value pair to the
* Persistent Storage Manager for persistence across reboots.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pCfgKey  - Configuration key string.
*                    \n Must be a valid PSM key.
* @param[in] pCfgValue  - Configuration value string.
*                    \n Value to be stored.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSaveCfgToPsm
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pCfgKey,
        char*                       pCfgValue
    );

/**
* @brief Load a configuration value from Persistent Storage Manager (PSM).
*
* This function is called to load a specific TR-069 configuration value from the
* Persistent Storage Manager using the provided key.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pCfgKey  - Configuration key string.
*                    \n Must be a valid PSM key.
*
* @return Pointer to the loaded configuration value string.
* @retval char* if the operation is successful.
* @retval NULL if the key is not found.
*
*/
char*
CcspCwmpCpecoLoadCfgFromPsm
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pCfgKey
    );

/**
* @brief Set the TR-069 ParameterKey value.
*
* This function is called to set the ParameterKey value, which is used to track
* configuration changes made by the ACS during SetParameterValues operations.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParameterKey  - ParameterKey value string.
*                    \n Can be NULL to clear the ParameterKey.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetParameterKey
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParameterKey
    );

/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_CPECO_OPERATION.C
***********************************************************/

/**
* @brief Engage the CCSP CWMP CPE Controller.
*
* This function is called to engage (activate) the CCSP CWMP CPE Controller and its associated
* components. It initializes all child objects and prepares the system for TR-069 operations.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if engagement fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoEngage
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Cancel (disengage) the CCSP CWMP CPE Controller.
*
* This function is called to cancel (deactivate) the CCSP CWMP CPE Controller and its associated
* components. It stops all TR-069 operations and cleans up resources.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoCancel
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Setup the runtime environment for CWMP operations.
*
* This function is called to set up the runtime environment required for CWMP operations.
* It initializes necessary resources, loads configurations, and prepares the system.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if environment setup fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoSetupEnv
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Close the runtime environment for CWMP operations.
*
* This function is called to close and clean up the runtime environment used for CWMP operations.
* It releases resources and performs necessary cleanup.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoCloseEnv
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Start the CWMP timer invocation mechanism.
*
* This function is called to start the CWMP timer which manages periodic inform operations
* and other time-based CWMP activities.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if timer start fails.
*
*/
ANSC_STATUS
CcspCwmppoStartCwmpTimerInvoke
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_CPECO_CONTROL.C
***********************************************************/

/**
* @brief Load TR-069 events from saved state.
*
* This function is called to load TR-069 events from a saved event string.
* This is typically used during system initialization to restore pending events.
*
* @param[in] hCcspCwmpMsoIf  - Handle to the CCSP CWMP MSO Interface.
*                    \n Used for managing event queues.
* @param[in] pSavedEvents  - Saved events string.
*                    \n Contains serialized event data.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if event loading fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoLoadEvents
    (
        ANSC_HANDLE                 hCcspCwmpMsoIf,
        char*                       pSavedEvents
    );

/**
* @brief Start the CWMP protocol operation.
*
* This function is called to start the CWMP protocol, optionally triggering an inform
* to the ACS. It can be used for initial startup or restart scenarios.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bInformAcs  - Flag to trigger an inform to ACS.
*                    \n TRUE to send inform, FALSE otherwise.
* @param[in] bRestart  - Flag indicating if this is a restart operation.
*                    \n TRUE for restart, FALSE for initial start.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if CWMP start fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoStartCWMP
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bInformAcs,
        BOOL                        bRestart
    );

/**
* @brief Stop the CWMP protocol operation.
*
* This function is called to stop the CWMP protocol and halt all ACS communications.
* It terminates active sessions and stops the CWMP processor.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpCpecoStopCWMP
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Restart the CWMP protocol operation.
*
* This function is called to restart the CWMP protocol. It stops and then starts
* CWMP operations, optionally triggering an inform to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bInformAcs  - Flag to trigger an inform to ACS after restart.
*                    \n TRUE to send inform, FALSE otherwise.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if CWMP restart fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoRestartCWMP
    (
        ANSC_HANDLE                         hThisObject,
        BOOL                                bInformAcs
    );

/**
* @brief Trigger an immediate inform to the ACS.
*
* This function is called to immediately trigger an inform message to be sent to the ACS,
* bypassing the normal periodic inform schedule.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if inform triggering fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoInformNow
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Notify the CPE Controller of a TR-069 event.
*
* This function is called to notify the CPE Controller of a TR-069 event occurrence.
* It queues the event for inclusion in the next inform message to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] ulEvent  - Event identifier.
*                    \n TR-069 event code (e.g., 0 BOOTSTRAP, 1 BOOT, etc.).
* @param[in] hEventContext  - Handle to event-specific context data.
*                    \n Can be NULL if no context is required.
*
* @return void
*
*/
void
CcspCwmpCpecoNotifyEvent
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulEvent,
        ANSC_HANDLE                 hEventContext
    );

/**
* @brief Acquire a Component Registrar session ID.
*
* This function is called to acquire a session ID from the Component Registrar.
* Session IDs are used for priority-based access control to shared resources.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] Priority  - Priority level for the session.
*                    \n Higher priority sessions have precedence.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if session acquisition fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoAcqCrSessionID
    (
        ANSC_HANDLE                 hThisObject,
        int                         Priority
    );

/**
* @brief Release a Component Registrar session ID.
*
* This function is called to release a previously acquired session ID back to the
* Component Registrar, freeing it for use by other components.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] CrSessionID  - Session ID to release.
*                    \n Must be a valid session ID previously acquired.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_FAILURE if session release fails.
*
*/
ANSC_STATUS
CcspCwmpCpecoRelCrSessionID
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       CrSessionID
    );


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_CPECO_STAIF.C
***********************************************************/
/**
* @brief Record an ACS connection attempt.
*
* This function is called to record statistical information about an ACS connection attempt,
* including the timestamp and connection status.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return void
*
*/
void
CcspCwmpCpecoStatIfConnectAcs
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Increment the TCP failure counter.
*
* This function is called to increment the TCP connection failure counter,
* tracking failed TCP connection attempts to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The updated TCP failure count.
* @retval ULONG representing the current TCP failure count.
*
*/
ULONG
CcspCwmpCpecoStatIfIncTcpFailure
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Increment the TLS failure counter.
*
* This function is called to increment the TLS/SSL connection failure counter,
* tracking failed TLS handshake attempts to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The updated TLS failure count.
* @retval ULONG representing the current TLS failure count.
*
*/
ULONG
CcspCwmpCpecoStatIfIncTlsFailure
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Increment the TCP success counter.
*
* This function is called to increment the TCP connection success counter,
* tracking successful TCP connection attempts to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The updated TCP success count.
* @retval ULONG representing the current TCP success count.
*
*/
ULONG
CcspCwmpCpecoStatIfIncTcpSuccess
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the TCP success count.
*
* This function is called to retrieve the current count of successful TCP connections
* to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The TCP success count.
* @retval ULONG representing the current TCP success count.
*
*/
ULONG
CcspCwmpCpecoStatIfGetTcpSuccessCount
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the TCP failure count.
*
* This function is called to retrieve the current count of failed TCP connections
* to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The TCP failure count.
* @retval ULONG representing the current TCP failure count.
*
*/
ULONG
CcspCwmpCpecoStatIfGetTcpFailureCount
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the TLS failure count.
*
* This function is called to retrieve the current count of failed TLS/SSL handshakes
* with the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The TLS failure count.
* @retval ULONG representing the current TLS failure count.
*
*/
ULONG
CcspCwmpCpecoStatIfGetTlsFailureCount
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Reset all connection statistics.
*
* This function is called to reset all connection statistics counters to their initial state,
* including TCP/TLS success and failure counts.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status indicator.
* @retval ANSC_STATUS_SUCCESS on success.
*
*/
ULONG
CcspCwmpCpecoStatIfResetStats
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the last connection time to the ACS.
*
* This function is called to retrieve the timestamp of the last connection attempt
* to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Handle to the last connection time structure.
* @retval ANSC_HANDLE representing the time structure.
*
*/
ANSC_HANDLE
CcspCwmpCpecoStatIfGetLastConnectionTime
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the last connection status.
*
* This function is called to retrieve the status string of the last connection attempt
* to the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Pointer to the last connection status string.
* @retval char* describing the connection status.
*
*/
char*
CcspCwmpCpecoStatIfGetLastConnectionStatus
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the last InformResponse time from ACS.
*
* This function is called to retrieve the timestamp of the last InformResponse
* received from the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Handle to the last InformResponse time structure.
* @retval ANSC_HANDLE representing the time structure.
*
*/
ANSC_HANDLE
CcspCwmpCpecoStatIfGetLastInformResponseTime
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Get the last received SetParameterValues (SPV) time from ACS.
*
* This function is called to retrieve the timestamp of the last SetParameterValues
* RPC received from the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP CPE Controller Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return Handle to the last SPV time structure.
* @retval ANSC_HANDLE representing the time structure.
*
*/
ANSC_HANDLE
CcspCwmpCpecoStatIfGetLastReceivedSPVTime
    (
        ANSC_HANDLE                 hThisObject
    );

#endif
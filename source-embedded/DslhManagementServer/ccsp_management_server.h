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

    module: ccsp_management_server.h

        For CCSP management server component

    ---------------------------------------------------------------

    description:

        This file defines all data structures and macros for
        CCSP management server component.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Hui Ma

    ---------------------------------------------------------------

    revision:

        06/15/2011    initial revision.

**********************************************************************/

#ifndef  _CCSP_MANAGEMENT_SERVER_
#define  _CCSP_MANAGEMENT_SERVER_

#include "ccsp_types.h"
#include "ccsp_custom.h"
#include <pthread.h>
#include <ansc_wrapper_base.h>
#include "ccsp_message_bus.h"
#include "ccsp_base_api.h"
#include "stdio.h"
#include "string.h"

// may have multiple components, so this name may be dynamic
//#define CCSP_MANAGEMENT_SERVER_COMPONENT_NAME_BASE  "com.cisco.spvtg.ccsp.managementServer"
#define CCSP_MANAGEMENT_SERVER_COMPONENT_VERSION    (int)1

#define _DeviceObjectName DM_ROOTNAME
#define _ManagementServerObjectName DM_ROOTNAME"ManagementServer."
#define _AutonomousTransferCompletePolicyObjectName DM_ROOTNAME"ManagementServer.AutonomousTransferCompletePolicy."
#define _DUStateChangeComplPolicyObjectName DM_ROOTNAME"ManagementServer.DUStateChangeComplPolicy."
#define _ComObjectName "com."
#define _CiscoObjectName "com.cisco."
#define _SpvtgObjectName "com.cisco.spvtg."
#define _CcspObjectName "com.cisco.spvtg.ccsp."
#define _Tr069paObjectName "com.cisco.spvtg.ccsp.tr069pa."
#define _MemoryObjectName "com.cisco.spvtg.ccsp.tr069pa.Memory."
#define _LoggingObjectName "com.cisco.spvtg.ccsp.tr069pa.Logging."

#define TR69_INTERNAL_ERROR             9002
#define TR69_INVALID_ARGUMENTS          9003
#define TR69_INVALID_PARAMETER_NAME     9005
#define TR69_INVALID_PARAMETER_TYPE     9006
#define TR69_INVALID_PARAMETER_VALUE    9007
#define TR69_UPDATE_NON_WRITABLE_PARAMETER    9008

typedef struct _msParameterInfo{
    char * name; /* name without a path */
    char * value; /* always char * for all kinds of parameters */
    enum dataType_e type;
    //CCSP_BOOL writable;
    enum access_e access;
    unsigned int accessControlBitmask;
    unsigned int notification;
} msParameterInfo;

typedef struct _msObjectInfo{
    char * name; /* full name end with '.' */
    int numberOfChildObjects;
    unsigned int *childObjectIDs;
    int numberOfParameters;
    msParameterInfo *parameters;
    //CCSP_BOOL writable;
    enum access_e access;
} msObjectInfo;

/* each object has a fixed array ID. */
#define DeviceID                                0
#define ManagementServerID                      1
#define DeviceInfoID                            2
#define AutonomousTransferCompletePolicyID      3
#define DUStateChangeComplPolicyID              4
#define ComID                                   5
#define CiscoID                                 6
#define SpvtgID                                 7
#define CcspID                                  8
#define Tr069paID                               9
#define MemoryID                                10
#define LoggingID                               11

#define ServicesID                              12
#define STBServiceID                            13
#define STBService1ID                           14
#define X_CISCO_COM_DiagID                      15
#define CWMPID                                  16
/*  Place holder for STBService.{i}. */
#define SupportedDataModelID                    17    /* This has to be the last one since multiple instances are added based on it. */


/* each parameter has a fixed array ID. */
enum
{
    ManagementServerEnableCWMPID = 0,
    ManagementServerURLID,
    ManagementServerUsernameID,
    ManagementServerPasswordID,
    ManagementServerPeriodicInformEnableID,
    ManagementServerPeriodicInformIntervalID,
    ManagementServerPeriodicInformTimeID,
    ManagementServerParameterKeyID,
    ManagementServerConnectionRequestURLID,
    ManagementServerConnectionRequestUsernameID,
    ManagementServerConnectionRequestPasswordID,
    ManagementServerACSOverrideID,
    ManagementServerUpgradesManagedID,
    ManagementServerX_CISCO_COM_DiagCompleteID,
    ManagementServerKickURLID,
    ManagementServerDownloadProgressURLID,
    ManagementServerDefaultActiveNotificationThrottleID,
    ManagementServerCWMPRetryMinimumWaitIntervalID,
    ManagementServerCWMPRetryIntervalMultiplierID,
    ManagementServerUDPConnectionRequestAddressID,
    ManagementServerUDPConnectionRequestAddressNotificationLimitID,
    ManagementServerSTUNEnableID,
    ManagementServerSTUNServerAddressID,
    ManagementServerSTUNServerPortID,
    ManagementServerSTUNUsernameID,
    ManagementServerSTUNPasswordID,
    ManagementServerSTUNMaximumKeepAlivePeriodID,
    ManagementServerSTUNMinimumKeepAlivePeriodID,
    ManagementServerNATDetectedID,
    ManagementServerAliasBasedAddressingID,
    ManagementServerX_CISCO_COM_ConnectionRequestURLPortID,
    ManagementServerX_CISCO_COM_ConnectionRequestURLPathID,
    ManagementServerNumOfParameters
};

#define AutonomousTransferCompletePolicyEnableID                0
#define AutonomousTransferCompletePolicyTransferTypeFilterID    1
#define AutonomousTransferCompletePolicyResultTypeFilterID      2
#define AutonomousTransferCompletePolicyFileTypeFilterID        3
#define AutonomousTransferCompletePolicyNumOfParameters         4

#define DUStateChangeComplPolicyEnableID                0
#define DUStateChangeComplPolicyOperationTypeFilterID   1
#define DUStateChangeComplPolicyResultTypeFilterID      2
#define DUStateChangeComplPolicyFaultCodeFilterID       3
#define DUStateChangeComplPolicyNumOfParameters         4

#define Tr069paNameID           0
#define Tr069paVersionID        1
#define Tr069paAuthorID         2
#define Tr069paHealthID         3
#define Tr069paStateID          4
#define Tr069paDTXmlID          5
#define Tr069paNumOfParameters  6

#define MemoryMinUsageID        0
#define MemoryMaxUsageID        1
#define MemoryConsumedID        2
#define MemoryNumOfParameters   3

#define LoggingEnableID         0
#define LoggingLogLevelID       1
#define LoggingNumOfParameters  2

#define FALSE 0
#define TRUE  1

/* for msParameterValSetting.backupStatus */
#define NoBackup       0
#define BackupNewValue 1
#define BackupOldValue 2

typedef struct _msParameterValSetting
{
    int objectID;
    int parameterID;
    char *parameterValue;
    int type;
    unsigned char backupStatus;  /* cross compiler may set char as "unsigned char", so negative values cannot be assigned. */
} msParameterValSetting;

#define  CCSP_TR069PA_DFT_PARAM_VAL_SETTINGS_NUMBER     32

typedef struct _msParameterValSettingArray
{
    int                             sessionID;
    unsigned int                    writeID;
    int                             size;
    unsigned int                    currIndex;
    msParameterValSetting *         msParameterValSettings;
} msParameterValSettingArray;

/**
* @brief Called by init function to Fill in object information from persistent storage.
*
* This function initializes the object information structure with default values
* and reads parameter values from PSM. It sets up the data model hierarchy
* for ManagementServer and internal objects.
*
* @return None.
*
*/
CCSP_VOID CcspManagementServer_FillInObjectInfo();

/**
* @brief Initialize DBus connection for Management Server.
*
* This function initializes the DBus message bus connection for the Management Server component.
*
* @return None.
*
*/
CCSP_VOID CcspManagementServer_InitDBus();

/**
* @brief Register the Management Server namespace with the system.
*
* This function registers the data model namespace that the Management Server
* component provides, enabling other components to access its parameters.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if registration is successful.
*
*/
ANSC_STATUS CcspManagementServer_RegisterNameSpace();

/**
* @brief Discover PAM component information.
*
* This function discovers the PAM component's name and path for inter-component communication.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if discovery is successful.
*
*/
ANSC_STATUS CcspManagementServer_DiscoverComponent();

/**
* @brief Register WAN interface for communication.
*
* This function registers the WAN interface that will be used for with the ACS server.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if registration is successful.
*
*/
ANSC_STATUS CcspManagementServer_RegisterWanInterface();

/**
* @brief Generate the Connection Request URL.
*
* This function generates the Connection Request URL that the ACS uses to initiate
* connections to the CPE.
*
* @param[in] fromValueChangeSignal  - Boolean indicating if called from value change signal.
*                                     TRUE if triggered by parameter value change, FALSE otherwise.
* @param[in] newValue  - New value string when triggered by value change, or NULL.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if URL generation is successful.
* @retval ANSC_STATUS_FAILURE if URL generation fails.
*
*/
ANSC_STATUS CcspManagementServer_GenerateConnectionRequestURL(
    BOOL fromValueChangeSignal,
    char *newValue);

/**
* @brief Send parameter value change signal.
*
* This function sends a signal to notify other components when a parameter
* value has changed. Used for active notification and value change tracking.
*
* @param[in] objectID  - Object identifier containing the parameter.
* @param[in] parameterID  - Parameter identifier that changed.
* @param[in] oldValue  - Previous value of the parameter before change.
*
* @return The status of the operation.
* @retval 0 if signal sent successfully.
*
*/
int SendValueChangeSignal(
    int objectID,
    int parameterID,
    const char * oldValue);

/**
* @brief Get value of a single parameter.
*
* This function retrieves the current value of a specified parameter
* and populates the provided parameterValStruct_t structure.
*
* @param[in] objectID  - Object identifier containing the parameter.
* @param[in] parameterID  - Parameter identifier to retrieve.
* @param[out] val  - Pointer to parameterValStruct_t to populate with parameter value.
*
* @return None.
*
*/
void CcspManagementServer_GetSingleParameterValue(
        int objectID,
        int parameterID,
        parameterValStruct_t *val
    );


/**
* @brief Validate parameter values before commit.
*
* This function validates all parameter values that are being updated before commit.
*
* @param[in] sessionId  - Session identifier for the validation operation.
* @param[in] writeID  - Write operation identifier for tracking changes.
* @param[in] val  - Array of parameterValStruct_t structures containing values to validate.
* @param[in] size  - Number of parameters in the val array.
* @param[out] invalidParameterName  - Pointer to store the name of first invalid parameter if validation fails.
*
* @return The validation result.
* @retval 0 if all parameters are valid.
* @retval TR69_INVALID_PARAMETER_NAME if parameter name is invalid.
* @retval TR69_INVALID_PARAMETER_TYPE if parameter type is invalid.
* @retval TR69_INVALID_PARAMETER_VALUE if parameter value is invalid.
* @retval TR69_INVALID_ARGUMENTS if argument is invalid
* @retval TR69_UPDATE_NON_WRITABLE_PARAMETER if parameter is not writable.
* @retval TR69_INTERNAL_ERROR if internal error occurs or having insufficient resources.
*
*/
int CcspManagementServer_ValidateParameterValues(
    int sessionId,
    unsigned int writeID,
    parameterValStruct_t *val,
    int size,
    char ** invalidParameterName
    );


/**
* @brief Get the number of all parameters of this object and its children.
*
* This function recursively counts all parameters in an object and its child objects in the hierarchy.
*
* @param[in] objectID  - Root object identifier to count from.
*
* @return The number of parameters.
*
*/
int CcspManagementServer_GetParameterCount(
    int objectID
    );


/**
* @brief Set value of a single parameter.
*
* This function sets a new value for a specified parameter using the attribute structure provided.
*
* @param[in] sessionId  - Session identifier for the set operation.
* @param[in] objectID  - Object identifier containing the parameter.
* @param[in] parameterID  - Parameter identifier to set.
* @param[in] val  - Pointer to parameterAttributeStruct_t containing new value and attributes.
*
* @return None.
*
*/
void CcspManagementServer_SetSingleParameterValue(
    int sessionId,
    int objectID,
    int parameterID,
    parameterAttributeStruct_t *val
    );


/**
* @brief Set single object attributes for all parameters.
*
* This function sets attributes for all parameters that match the object path prefix.
*
* @param[in] sessionId  - Session identifier for the set operation.
* @param[in] objectID  - Object identifier whose parameters will be updated.
* @param[in] val  - Pointer to parameterAttributeStruct_t containing attributes to set.
*
* @return The number of parameters updated.
*
*/
int CcspManagementServer_SetSingleObjectAttributes(
    int sessionId,
    int objectID,
    parameterAttributeStruct_t *val
    );


/**
* @brief Get attributes for all parameters in an object.
*
* This function retrieves attributes for all parameters in the specified object,
* populating the attribute array. For each parameter, add one record item to attributes.
*
* @param[in] objectID  - Object identifier whose attributes will be retrieved.
* @param[in,out] attr  - Pointer to parameterAttributeStruct_t array to populate.
* @param[in] beginAttrID  - Starting index in the attribute array to begin populating.
*
* @return The number of records have been added to the array.
*
*/
int CcspManagementServer_GetSingleObjectAttributes(
    int objectID,
    parameterAttributeStruct_t **attr,
    int beginAttrID
    );


/**
* @brief Get attribute of one parameter.
*
* This function retrieves the  attributes for a specified parameter.
*
* @param[in] objectID  - Object identifier containing the parameter.
* @param[in] parameterID  - Parameter identifier whose attributes will be retrieved.
* @param[out] attr  - Pointer to parameterAttributeStruct_t to populate with attributes.
*
* @return None.
*
*/
void CcspManagementServer_GetSingleParameterAttributes(
    int objectID,
    int parameterID,
    parameterAttributeStruct_t *attr
    );


/**
* @brief Commit the parameter setting stored in parameterSetting.
*
* This function commits all validated parameter values that have been staged
* in the parameterSetting array, writing them to PSM database.
*
* @param[in] writeID  - Write operation identifier for tracking the commit.
*
* @return The commit result.
* @retval 0 if commit is successful.
*
*/
int CcspManagementServer_CommitParameterValues(unsigned int writeID);


/**
* @brief Roll back the parameters already being committed.
*
* This function restores parameter values to their previous state,
* undoing changes that were committed in the current session.
*
* @return The rollback result.
* @retval 0 if rollback is successful.
*
*/
int CcspManagementServer_RollBackParameterValues();


/**
* @brief Free parameter setting resources.
*
* The parameter setting values are stored in ParameterSetting before commit.
* After commit or cancel, ParameterSetting is freed by this function.
*
* @return The operation result.
* @retval 0 if resources freed successfully.
*
*/
int CcspManagementServer_FreeParameterSetting();


/**
* @brief Map Management Server object ID to PA object ID.
*
* This function translates between the Management Server's internal object ID
* and the Protocol Agent's object ID, handling the mismatch between the two
* numbering schemes. There is dismatch between objectID here and objectID in PA.
*
* @param[in] objectID  - Management Server object identifier to map.
*
* @return The corresponding Protocol Agent object identifier.
*
*/
int CcspManagementServer_GetPAObjectID
(
    int objectID
);


/**
* @brief Merge two strings with memory allocation.
*
* This function concatenates two strings, allocating Malloc memory that will be freed by other modules.
*
* @param[in] src1  - First source string to merge.
* @param[in] src2  - Second source string to merge.
*
* @return Pointer to newly allocated merged string.
* @retval Pointer to a null-terminated string containing the concatenation of src1 and src2 on success.
* @retval NULL if memory allocation fails or if both src1 and src2 are NULL/empty strings.
*
*/
char * CcspManagementServer_MergeString
    (
    const char * src1,
    const char * src2
    );

/**
* @brief Restore all parameters to default values.
*
* This function resets all Management Server parameters to their factory
* default values as defined in the data model.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if restore is successful.
*
*/
ANSC_STATUS
CcspManagementServer_RestoreDefaultValues
    (
        void
    );

/**
* @brief Store encrypted password value to database.
*
* This function encrypts and stores a Management Server password to the PSM database.
*
* @param[in] pString  - Plain text password string to encrypt and store.
* @param[in] parameterID  - Parameter identifier indicating which password field.
*
* @return The operation result.
* @retval 0 if password stored successfully.
* @retval TR69_INVALID_ARGUMENTS if invalid argument.
*
*/
int CcspManagementServer_StoreMGMTServerPasswordValuesintoDB
	(
		char *pString,
		int parameterID
	);

/**
* @brief Get decrypted password value from database.
*
* This function retrieves and decrypts a Management Server password from
* the PSM database or NVRAM storage.
*
* @param[in] parameterID  - Parameter identifier indicating which password field.
* @param[out] pOutputString  - Buffer to store the decrypted password string.
*
* @return The operation result.
* @retval 0 if password retrieved successfully.
* @retval TR69_INVALID_ARGUMENTS if invalid argument.
*
*/
int CcspManagementServer_GetMGMTServerPasswordValuesFromDB
	(
		int parameterID,
		char *pOutputString
	);

/**
* @brief Retrieve and decrypt password from NVRAM file.
*
* This function reads an encrypted password from a file in NVRAM storage
* and decrypts it using the platform's decryption key.
*
* @param[in] parameterID  - Parameter identifier indicating which password field.
* @param[in] pInputFile  - Path to the encrypted password file in NVRAM.
* @param[out] pOutputString  - Buffer to store the decrypted password string.
*
* @return The operation result.
* @retval 0 if password retrieved and decrypted successfully.
* @retval TR69_INTERNAL_ERROR if the input file does not exist, file operations fail, or secure system call fails.
*
*/
int CcspManagementServer_RetrievePassword
	(
        int parameterID,
		char *pInputFile,
		char *pOutputString
	);

/**
* @brief Check if encrypted password file exists in database.
*
* This function checks whether an encrypted password file exists in PSM
* database or NVRAM storage for the specified parameter.
*
* @param[in] parameterID  - Parameter identifier indicating which password field.
* @param[out] pIsEncryptFileAvailable  - Pointer to integer flag.
*
* @return The operation result.
* @retval 0 if check completed successfully.
* @retval TR69_INVALID_ARGUMENTS if invalid argument.
*
*/
int CcspManagementServer_IsEncryptedFileInDB
	(
		int parameterID,
		int *pIsEncryptFileAvailable
	);

/**
* @brief Get alias-based addressing string for a component.
*
* This function retrieves the alias-based addressing capability string for a specified CCSP component.
*
* @param[in] ComponentName  - Name of the CCSP component to query.
*
* @return Pointer to alias-based addressing string.
*
*/
CCSP_STRING
CcspManagementServer_GetAliasBasedAddressingStr
    (
        CCSP_STRING                 ComponentName
    );

/**
* @brief Utility function to get multiple parameter values.
*
* This function retrieves values for multiple parameters specified by name,
* allocating and populating an array of parameterValStruct_t structures.
*
* @param[in] parameterNames  - Array of parameter name strings to retrieve.
* @param[in] size  - Number of parameter names in the input array.
* @param[out] pval_size  - Pointer to store the number of values retrieved.
* @param[out] pppval  - Pointer to parameterValStruct_t array pointer to populate.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if values retrieved successfully.
* @retval ANSC_STATUS_FAILURE if component error occurs.
*
*/
ANSC_STATUS
CcspManagementServer_UtilGetParameterValues
    (
        char*                       parameterNames[],
        int                         size,
        int*                        pval_size,
        parameterValStruct_t***     pppval
    );

/**
* @brief Free parameter value structure array.
*
* This function frees memory allocated by UtilGetParameterValues, including
* the parameterValStruct_t array and all contained strings.
*
* @param[in] val_size  - Number of elements in the parameter value array.
* @param[in] ppval  - Pointer to parameterValStruct_t array to free.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if memory freed successfully.
*
*/
ANSC_STATUS
CcspManagementServer_UtilFreeParameterValStruct
    (
        int                         val_size,
        parameterValStruct_t**      ppval
    );

/**
* @brief Initialize DBus with custom callbacks.
*
* This function initializes the DBus connection with custom callback functions
* for handling component-specific operations.
*
* @param[in] cb  - Pointer to CCSP_Base_Func_CB structure containing callback functions.
*
* @return None.
*
*/
CCSP_VOID CcspManagementServer_InitDBusCustom(CCSP_Base_Func_CB *cb);

/**
* @brief Get object ID from parameter name.
*
* This function retrieves the internal object identifier from a full parameter
* or object name, returning both the object ID and the remaining name portion.
*
* @param[in] parameterName  - Full parameter or object name to parse.
*                             Must be a full object name ending with '.' or full parameter name.
* @param[out] name  - Pointer to store the remaining parameter name portion.
*                     Points into the input parameterName string.
*
* @return The object identifier.
* @retval object ID  on success.
* @retval -1 if object not found.
*
*/
int CcspManagementServer_GetObjectID(
    char *parameterName,   /* name has to be a full object name (ends with .) or full parameter name */
    char **name
    );

/**
* @brief Get parameter ID from parameter name.
*
* This function retrieves the internal parameter identifier for a given
* parameter name (without object path prefix) within a specified object.
*
* @param[in] objectID  - Object identifier to search within.
* @param[in] paraName  - Pure parameter name without object name prefix.
*
* @return The parameter identifier.
* @retval -1 if parameter not found.
*
*/
int CcspManagementServer_GetParameterID(
    int objectID,
    char *paraName   /* parameterName is the pure name without object name prefix. */
    );

/**
* @brief Get all parameter values for an object.
*
* This function retrieves all parameters and their values for a given object,
* populating a parameterValStruct_t array starting at a specified index.
*
* @param[in] objectID  - Object identifier to retrieve parameters from.
* @param[in,out] val  - Pointer to parameterValStruct_t array to populate.
* @param[in] beginValID  - Starting index in the value array to begin populating.
*
* @return The number of values added to the array.
*
*/
int CcspManagementServer_GetSingleObjectValues(
    int objectID,
    parameterValStruct_t **val,
    int beginValID
    );

/**
* @brief Set attributes of a single parameter.
*
* This function sets notification and access control attributes for a specified parameter.
*
* @param[in] sessionId  - Session identifier for the set operation.
* @param[in] objectID  - Object identifier containing the parameter.
* @param[in] parameterID  - Parameter identifier whose attributes will be set.
* @param[in] val  - Pointer to parameterAttributeStruct_t containing attributes to set.
*
* @return The number of attributes set.
* @retval ANSC_STATUS_SUCCESS if attribute set successfully.
*
*/
int CcspManagementServer_SetSingleParameterAttributes(
    int sessionId,
    int objectID,
    int parameterID,
    parameterAttributeStruct_t *val
    );
#endif
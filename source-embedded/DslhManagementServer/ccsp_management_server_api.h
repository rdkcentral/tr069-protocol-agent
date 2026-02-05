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

    module: ccsp_management_server_api.h

        For CCSP management server component

    ---------------------------------------------------------------

    description:

        This file defines all api functions of management server
        component.

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

#ifndef  _CCSP_MANAGEMENT_SERVER_API_DEC_
#define  _CCSP_MANAGEMENT_SERVER_API_DEC_

#include <pthread.h>
#include "ccsp_message_bus.h"
#include "ccsp_base_api.h"

/* The following functions implements DBus server side functions.
 */
/*typedef int  (*CCSPBASEIF_SETPARAMETERVALUES)( */

/**
* @brief Set parameter values for the Management Server.
*
* This function validates and sets parameter values in the Management Server component.
* If commit is TRUE, the changes are immediately committed; otherwise they are staged for later commit.
*
* @param[in] sessionId  - Session identifier for the operation.
* @param[in] writeID  - Write transaction identifier.
* @param[in] val  - Pointer to array of parameter value structures to be set.
* @param[in] size  - Number of parameters in the val array.
* @param[in] commit  - Boolean flag indicating whether to commit changes immediately.
*                      TRUE to commit, FALSE to stage changes.
* @param[out] invalidParameterName  - Pointer to string that will contain the name of
*                                     the first invalid parameter if validation fails.
* @param[in] user_data  - User-provided context data.
*
* @return The status of the operation or validation result.
* @retval CCSP_SUCCESS if the operation is successful.
* @retval Error code if the operation fails.
*
*/
int CcspManagementServer_SetParameterValues(
    int sessionId,
    unsigned int writeID,
    parameterValStruct_t *val,
    int size,
    dbus_bool commit,
    char ** invalidParameterName,
    void* user_data
);

/*typedef int  (*CCSPBASEIF_SETCOMMIT)(*/

/**
* @brief Commit staged parameter value changes.
*
* This function commits parameter values that were previously staged by SetParameterValues.
*
* @param[in] sessionId  - Session identifier for the operation.
* @param[in] writeID  - Write transaction identifier.
* @param[in] commit  - Boolean flag indicating whether to commit changes.
*                      TRUE to commit staged changes, FALSE to discard.
* @param[in] user_data  - User-provided context data.
*
* @return The status of the operation.
* @retval CCSP_SUCCESS if the operation is successful.
*
*/
int  CcspManagementServer_SetCommit(
    int sessionId,
    unsigned int writeID,
    dbus_bool commit,
    void* user_data
);

/*typedef int  (*CCSPBASEIF_GETPARAMETERVALUES)(*/
/*int  CcspManagementServer_GetParameterValues(
    char * parameterNames[],
    int size,
    parameterValStruct_t ***val
);*/

/**
* @brief Get parameter values from the Management Server.
*
* This function retrieves the values of specified parameters or all parameters under a given object path.
*
* @param[in] writeID  - Write transaction identifier.
* @param[in] parameterNames  - Array of parameter name strings to retrieve.
* @param[in] size  - Number of parameter names in the parameterNames array.
* @param[out] val_size  - Pointer to receive the number of parameter values returned.
* @param[out] param_val  - Pointer to receive allocated array of parameter value structures.
* @param[in] user_data  - User-provided context data.
*
* @return The status of the operation.
* @retval CCSP_SUCCESS if the operation is successful.
* @retval CCSP_FAILURE if no valid parameters found.
* @retval CCSP_ERR_MEMORY_ALLOC_FAIL if memory allocation fails.
*
*/
int  CcspManagementServer_GetParameterValues(
    unsigned int writeID,
    char * parameterNames[],
    int size,
    int *val_size,
    parameterValStruct_t ***param_val,
    void* user_data
    );


/*typedef int  (*CCSPBASEIF_SETPARAMETERATTRIBUTES)(*/

/**
* @brief Set parameter attributes for the Management Server.
*
* This function sets attributes for specified parameters or objects.
*
* @param[in] sessionId  - Session identifier for the operation.
* @param[in] val  - Pointer to array of parameter attribute structures to be set.
* @param[in] size  - Number of attribute entries in the val array.
* @param[in] user_data  - User-provided context data.
*
* @return The status of the operation.
* @retval CCSP_SUCCESS if the operation is successful.
* @retval CCSP_FAILURE if parameter or object not found.
*
*/
int  CcspManagementServer_SetParameterAttributes(
    int sessionId,
    parameterAttributeStruct_t *val,
    int size,
    void* user_data
);

/*typedef int  (*CCSPBASEIF_GETPARAMETERATTRIBUTES)(*/
/*int  CcspManagementServer_GetParameterAttributes(
    char * parameterNames[],
    int size,
    parameterAttributeStruct_t ***val
);*/

/**
* @brief Get parameter attributes from the Management Server.
*
* This function retrieves attributes for specified parameters or all parameters under a given object.
*
* @param[in] parameterNames  - Array of parameter name strings to query.
* @param[in] size  - Number of parameter names in the parameterNames array.
* @param[out] val_size  - Pointer to receive the number of attribute structures returned.
* @param[out] val  - Pointer to receive allocated array of parameter attribute structures.
* @param[in] user_data  - User-provided context data.
*
* @return The status of the operation.
* @retval CCSP_SUCCESS if the operation is successful.
* @retval CCSP_FAILURE if parameter not found or allocation fails.
*
*/
int  CcspManagementServer_GetParameterAttributes(
    char * parameterNames[],
    int size,
    int *val_size,
    parameterAttributeStruct_t ***val,  //??????????? miss return size.
    void* user_data
);


/*typedef int  (*CCSPBASEIF_ADDTBLROW)(*/

/**
* @brief Add a new row to a table object.
*
* This function adds a new instance to a multi-instance table object.
*
* @param[in] sessionId  - Session identifier for the operation.
* @param[in] objectName  - Name of the table object to add row to.
* @param[out] instanceNumber  - Pointer to receive the instance number of the new row.
* @param[in] user_data  - User-provided context data.
*
* @return The status of the operation.
* @retval CCSP_ERR_NOT_SUPPORT as this operation is not supported.
*
*/
int  CcspManagementServer_AddTblRow(
    int sessionId,
    char * objectName,
    int * instanceNumber,
    void* user_data
);

/*typedef int  (*CCSPBASEIF_DELETETBLROW)(*/

/**
* @brief Delete a row from a table object.
*
* This function removes an instance from a multi-instance table object.
*
* @param[in] sessionId  - Session identifier for the operation.
* @param[in] objectName  - Name of the table object to delete row from.
* @param[in] instanceNumber  - Pointer to the instance number of the row to delete.
* @param[in] user_data  - User-provided context data.
*
* @return The status of the operation.
* @retval CCSP_ERR_NOT_SUPPORT as this operation is not supported.
*
*/
int  CcspManagementServer_DeleteTblRow(
    int sessionId,
    char * objectName,
    int * instanceNumber,
    void* user_data
);

/*typedef int  (*CCSPBASEIF_GETPARAMETERNAMES)(*/

/**
* @brief Get parameter names and information from the Management Server.
*
* This function retrieves parameter names and their metadata for a given parameter or object path.
*
* @param[in] parameterName  - Parameter or object path to query.
* @param[in] nextLevel  - Boolean flag controlling traversal depth.
* @param[out] size  - Pointer to receive the number of parameter info structures returned.
* @param[out] val  - Pointer to receive allocated array of parameter info structures.
* @param[in] user_data  - User-provided context data.
*
* @return The status of the operation.
* @retval CCSP_SUCCESS if the operation is successful.
* @retval CCSP_FAILURE if parameter not found or allocation fails.
*
*/
int  CcspManagementServer_GetParameterNames(
    char * parameterName,
    int nextLevel,
    int *size ,
    parameterInfoStruct_t ***val,
    void* user_data
);



#endif
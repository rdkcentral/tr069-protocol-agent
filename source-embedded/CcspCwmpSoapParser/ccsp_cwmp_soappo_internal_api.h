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

    module: ccsp_cwmp_soappo_internal_api.h

        For CCSP CWMP protocol implementation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the internal functions provided by the CCSP CWMP SoapParser
        Parser Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Bin Zhu
        Kang Quan

    ---------------------------------------------------------------

    revision:

        09/06/05    initial revision.
        10/13/11    resolve name conflicts with DM library.

**********************************************************************/
#ifndef  _CCSP_CWMP_SOAPPO_INTERNAL_API_
#define  _CCSP_CWMP_SOAPPO_INTERNAL_API_

#include "ccsp_cwmp_definitions_soap.h"

/***********************************************************
         FUNCTIONS IMPLEMENTED IN CCSP_CWMP_SOAPPO_STATES.C
***********************************************************/

/**
* @brief Reset the CCSP CWMP SOAP Parser object.
*
* This function is called to reset the CCSP CWMP SOAP Parser object to its
* initial state, clearing all internal data structures.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpSoappoReset
    (
        ANSC_HANDLE                 hThisObject
    );

/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_SOAPPO_BUILD.C
***********************************************************/

/**
* @brief Build SOAP request for GetRPCMethods.
*
* This function builds a SOAP envelope containing a GetRPCMethods request
* to discover the RPC methods supported by the ACS.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Used to correlate request and response.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapReq_GetRpcMethods
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

/**
* @brief Build SOAP request for Inform.
*
* This function builds a SOAP envelope containing an Inform request which
* is sent by the CPE to notify the ACS of events, status, and parameter values.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hDeviceId  - Handle to DeviceIdStruct containing device identification.
*                    \n Manufacturer, OUI, ProductClass, SerialNumber.
* @param[in] hEventArray  - Handle to array of Event structures.
*                    \n Contains event codes and command keys.
* @param[in] ulEventCount  - Number of events in the event array.
*                    \n Range: [1-n]
* @param[in] ulMaxEnvelopes  - Maximum number of SOAP envelopes that can be handled.
*                    \n Used for flow control.
* @param[in] hCurrentTime  - Handle to ANSC_UNIVERSAL_TIME structure.
*                    \n Current timestamp for the Inform.
* @param[in] iTimeZoneOffset  - Time zone offset in seconds from UTC.
*                    \n Positive or negative offset.
* @param[in] ulRetryCount  - Number of times this Inform has been retried.
*                    \n Range: [0-n]
* @param[in] hParamValueArray  - Handle to array of ParameterValueStruct.
*                    \n Contains parameter names, values, and types.
* @param[in] ulArraySize  - Number of parameter values in the array.
*                    \n Range: [0-n]
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails or invalid input.
*
*/
char*
CcspCwmpSoappoBuildSoapReq_Inform
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hDeviceId,
        ANSC_HANDLE                 hEventArray,
        ULONG                       ulEventCount,
        ULONG                       ulMaxEnvelopes,
        ANSC_HANDLE                 hCurrentTime,
        int                         iTimeZoneOffset,
        ULONG                       ulRetryCount,
        ANSC_HANDLE                 hParamValueArray,
        ULONG                       ulArraySize
    );

/**
* @brief Build SOAP request for TransferComplete.
*
* This function builds a SOAP envelope containing a TransferComplete request
* which is sent by the CPE to notify the ACS that a file transfer has completed.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] pCommandKey  - Command key from the original Download or Upload request.
*                    \n Empty string if not provided in original request.
* @param[in] hFault  - Handle to CWMP Fault structure if transfer failed.
*                    \n NULL if transfer was successful.
* @param[in] hStartTime  - Handle to ANSC_UNIVERSAL_TIME when transfer started.
*                    \n Start timestamp of the transfer operation.
* @param[in] hCompleteTime  - Handle to ANSC_UNIVERSAL_TIME when transfer completed.
*                    \n Completion timestamp of the transfer operation.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapReq_TransferComplete
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pCommandKey,
        ANSC_HANDLE                 hFault,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime
    );

/**
* @brief Build SOAP request for Kicked.
*
* This function builds a SOAP envelope containing a Kicked request which
* is sent by the CPE to notify the ACS that a Kick operation was received.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] pCommand  - Command string received in the Kick request.
*                    \n Identifies the operation requested.
* @param[in] pReferer  - Referer URL from the Kick request.
*                    \n Identifies the source of the Kick.
* @param[in] pArg  - Argument string from the Kick request.
*                    \n Additional parameters for the operation.
* @param[in] pNext  - Next URL for redirection.
*                    \n URL to be accessed next.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapReq_Kicked
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pCommand,
        char*                       pReferer,
        char*                       pArg,
        char*                       pNext
    );

/**
* @brief Build SOAP request for RequestDownload.
*
* This function builds a SOAP envelope containing a RequestDownload request
* which is sent by the CPE to request the ACS to initiate a Download.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] pFileType  - Type of file being requested for download.
*                    \n e.g., "1 Firmware Upgrade Image", "2 Web Content".
* @param[in] hFileTypeArgArray  - Handle to array of FileTypeArg structures.
*                    \n Contains file type specific arguments.
* @param[in] ulArraySize  - Number of FileTypeArg elements in the array.
*                    \n Range: [0-n]
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapReq_RequestDownload
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pFileType,
        ANSC_HANDLE                 hFileTypeArgArray,
        ULONG                       ulArraySize
    );

/**
* @brief Build SOAP request for AutonomousTransferComplete.
*
* This function builds a SOAP envelope containing an AutonomousTransferComplete request
* which is sent by the CPE to notify the ACS that an autonomous file transfer has completed.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hFault  - Handle to CWMP Fault structure if transfer failed.
*                    \n NULL if transfer was successful.
* @param[in] hStartTime  - Handle to ANSC_UNIVERSAL_TIME when transfer started.
*                    \n Start timestamp of the transfer operation.
* @param[in] hCompleteTime  - Handle to ANSC_UNIVERSAL_TIME when transfer completed.
*                    \n Completion timestamp of the transfer operation.
* @param[in] bIsDownload  - Boolean flag indicating transfer direction.
*                    \n TRUE for download, FALSE for upload.
* @param[in] AnnounceURL  - URL announced for the transfer.
*                    \n URL used for announcing the transfer.
* @param[in] TransferURL  - Actual URL used for the file transfer.
*                    \n Source or destination URL.
* @param[in] FileType  - Type of file transferred.
*                    \n e.g., "1 Firmware Upgrade Image".
* @param[in] FileSize  - Size of the transferred file in bytes.
*                    \n Range: [0-n]
* @param[in] TargetFileName  - Target filename on the CPE.
*                    \n Destination filename for the transfer.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapReq_AutonomousTransferComplete
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hFault,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime,
		BOOL						bIsDownload,
        char*                       AnnounceURL,
        char*                       TransferURL,
        char*                       FileType,
        unsigned int                FileSize,
        char*                       TargetFileName
    );

/**
* @brief Build SOAP request for DUStateChangeComplete.
*
* This function builds a SOAP envelope containing a DUStateChangeComplete request
* which is sent by the CPE to notify the ACS that a deployment unit state change has completed.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hDsccReq  - Handle to DUStateChangeCompleteStruct.
*                    \n Contains operation results and fault information.
* @param[in] pCommandKey  - Command key from the original ChangeDUState request.
*                    \n Empty string if not provided in original request.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapReq_DUStateChangeComplete
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hDsccReq,
        char*                       pCommandKey
    );

/**
* @brief Build SOAP request for AutonomousDUStateChangeComplete.
*
* This function builds a SOAP envelope containing an AutonomousDUStateChangeComplete request
* which is sent by the CPE to notify the ACS of an autonomous deployment unit state change.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hAdsccReq  - Handle to AutonomousDUStateChangeCompleteStruct.
*                    \n Contains operation results and fault information.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapReq_AutonomousDUStateChangeComplete
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hAdsccReq
    );


/**
* @brief Build SOAP error response.
*
* This function builds a SOAP envelope containing an error response with fault
* information for a failed RPC method.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the request that caused the error.
* @param[in] pMethodName  - Name of the RPC method that failed.
*                    \n e.g., "SetParameterValues", "GetParameterValues".
* @param[in] hSoapFault  - Handle to CWMP Fault structure.
*                    \n Contains fault code and fault string.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_Error
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pMethodName,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for GetRPCMethods.
*
* This function builds a SOAP envelope containing a GetRPCMethods response
* with the list of RPC methods supported by the CPE.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] pMethodList  - Pointer to SLAP_STRING_ARRAY containing method names.
*                    \n List of supported RPC method names.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_GetRPCMethods
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        SLAP_STRING_ARRAY*          pMethodList
    );

/**
* @brief Build SOAP response for SetParameterValues.
*
* This function builds a SOAP envelope containing a SetParameterValues response
* indicating the result of parameter setting operation.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] iStatus  - Status code of the operation.
*                    \n 0 indicates all changes applied immediately, 1 indicates reboot required.
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_SetParameterValues
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        int                         iStatus,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for GetParameterValues.
*
* This function builds a SOAP envelope containing a GetParameterValues response
* with the requested parameter names, values, and types.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hParamValueArray  - Handle to array of CCSP_CWMP_PARAM_VALUE structures.
*                    \n Contains parameter names, values, and data types.
* @param[in] ulArraySize  - Number of parameter values in the array.
*                    \n Range: [0-n]
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_GetParameterValues
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hParamValueArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for GetParameterNames.
*
* This function builds a SOAP envelope containing a GetParameterNames response
* with the requested parameter information.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hParamInfoArray  - Handle to array of CCSP_CWMP_PARAM_INFO structures.
*                    \n Contains parameter names and writable flags.
* @param[in] ulArraySize  - Number of parameter info elements in the array.
*                    \n Range: [0-n]
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_GetParameterNames
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hParamInfoArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for SetParameterAttributes.
*
* This function builds a SOAP envelope containing a SetParameterAttributes response
* indicating the result of parameter attribute modification.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_SetParameterAttributes
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for GetParameterAttributes.
*
* This function builds a SOAP envelope containing a GetParameterAttributes response
* with the requested parameter attribute information.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hParamAttribArray  - Handle to array of CCSP_CWMP_PARAM_ATTRIB structures.
*                    \n Contains parameter attributes including notification and access control.
* @param[in] ulArraySize  - Number of parameter attribute elements in the array.
*                    \n Range: [0-n]
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_GetParameterAttributes
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hParamAttribArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for AddObject.
*
* This function builds a SOAP envelope containing an AddObject response
* with the instance number of the newly created object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] ulInstanceNumber  - Instance number assigned to the newly created object.
*                    \n Range: [1-n]
* @param[in] iStatus  - Status code of the operation.
*                    \n 0 indicates object created immediately, 1 indicates reboot required.
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_AddObject
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ULONG                       ulInstanceNumber,
        int                         iStatus,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for DeleteObject.
*
* This function builds a SOAP envelope containing a DeleteObject response
* indicating the result of object deletion.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] iStatus  - Status code of the operation.
*                    \n 0 indicates object deleted immediately, 1 indicates reboot required.
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_DeleteObject
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        int                         iStatus,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for Download.
*
* This function builds a SOAP envelope containing a Download response
* with status and timing information for the download operation.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] iStatus  - Status code of the operation.
*                    \n 0 indicates download completed, 1 indicates download in progress.
* @param[in] hStartTime  - Handle to ANSC_UNIVERSAL_TIME when download started.
*                    \n Start timestamp of the download operation.
* @param[in] hCompleteTime  - Handle to ANSC_UNIVERSAL_TIME when download completed.
*                    \n Completion timestamp of the download operation.
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_Download
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        int                         iStatus,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for Reboot.
*
* This function builds a SOAP envelope containing a Reboot response
* acknowledging the reboot request.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_Reboot
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for ChangeDUState.
*
* This function builds a SOAP envelope containing a ChangeDUState response
* acknowledging the deployment unit state change request.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_ChangeDUState
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for GetQueuedTransfers.
*
* This function builds a SOAP envelope containing a GetQueuedTransfers response
* with information about queued downloads and uploads.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hQueuedTransferArray  - Handle to array of CCSP_CWMP_QUEUED_TRANSFER structures.
*                    \n Contains command keys, states, and file types.
* @param[in] ulArraySize  - Number of queued transfer elements in the array.
*                    \n Range: [0-n]
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_GetQueuedTransfers
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hQueuedTransferArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for ScheduleInform.
*
* This function builds a SOAP envelope containing a ScheduleInform response
* acknowledging the scheduled inform request.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_ScheduleInform
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for SetVouchers.
*
* This function builds a SOAP envelope containing a SetVouchers response
* acknowledging the voucher setting request.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_SetVouchers
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for GetOptions.
*
* This function builds a SOAP envelope containing a GetOptions response
* with the requested option information.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hOptionArray  - Handle to array of CCSP_CWMP_OPTION structures.
*                    \n Contains option names, voucher serial numbers, and states.
* @param[in] ulArraySize  - Number of option elements in the array.
*                    \n Range: [0-n]
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_GetOptions
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hOptionArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for Upload.
*
* This function builds a SOAP envelope containing an Upload response
* with status and timing information for the upload operation.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] iStatus  - Status code of the operation.
*                    \n 0 indicates upload completed, 1 indicates upload in progress.
* @param[in] hStartTime  - Handle to ANSC_UNIVERSAL_TIME when upload started.
*                    \n Start timestamp of the upload operation.
* @param[in] hCompleteTime  - Handle to ANSC_UNIVERSAL_TIME when upload completed.
*                    \n Completion timestamp of the upload operation.
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_Upload
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        int                         iStatus,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP response for FactoryReset.
*
* This function builds a SOAP envelope containing a FactoryReset response
* acknowledging the factory reset request.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hSoapFault  - Handle to CWMP Fault structure if operation failed.
*                    \n NULL if operation was successful.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRep_FactoryReset
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/**
* @brief Build SOAP fault response.
*
* This function builds a SOAP envelope containing a SOAP:Fault element
* for reporting errors in SOAP message processing.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Matches the ID from the request.
* @param[in] hSoapFault  - Handle to CWMP Fault structure.
*                    \n Contains fault code, fault string, and detail.
*
* @return Pointer to the SOAP envelope string.
* @retval char* containing the XML SOAP fault envelope if successful.
* @retval NULL if memory allocation fails.
*
*/
char*
CcspCwmpSoappoBuildSoapRepFault
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_SOAPPO_PROCESS.C
***********************************************************/

/**
* @brief Process SOAP header element.
*
* This function processes the SOAP header element from an incoming SOAP envelope,
* extracting ID, HoldRequests, and NoMoreRequests information.
*
* @param[in,out] hCwmpSoapHeader  - Handle to CCSP_CWMP_SOAP_HEADER structure.
*                    \n Populated with extracted header information.
* @param[in] pNameSpace  - SOAP namespace prefix.
* @param[in] hXmlHandle  - Handle to XML DOM node of the SOAP envelope.
*                    \n Root node containing the SOAP message.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if header processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessSoapHeader
    (
        ANSC_HANDLE                 hCwmpSoapHeader,
        PCHAR                       pNameSpace,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process SetParameterValues request.
*
* This function processes a SetParameterValues SOAP request from the ACS,
* parsing parameter names, values, types, and parameter key.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke SetParameterValues on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the SetParameterValues element.
*                    \n Contains ParameterList and ParameterKey.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_SetParameterValues
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process GetParameterValues request.
*
* This function processes a GetParameterValues SOAP request from the ACS,
* parsing the list of parameter names to retrieve.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke GetParameterValues on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the GetParameterValues element.
*                    \n Contains ParameterNames array.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_GetParameterValues
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process GetParameterNames request.
*
* This function processes a GetParameterNames SOAP request from the ACS,
* parsing the parameter path and NextLevel flag.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke GetParameterNames on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the GetParameterNames element.
*                    \n Contains ParameterPath and NextLevel.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_GetParameterNames
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process SetParameterAttributes request.
*
* This function processes a SetParameterAttributes SOAP request from the ACS,
* parsing parameter names, notification settings, and access control lists.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke SetParameterAttributes on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the SetParameterAttributes element.
*                    \n Contains SetParameterAttributesList.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_SetParameterAttributes
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process GetParameterAttributes request.
*
* This function processes a GetParameterAttributes SOAP request from the ACS,
* parsing the list of parameter names whose attributes are to be retrieved.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke GetParameterAttributes on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the GetParameterAttributes element.
*                    \n Contains ParameterNames array.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_GetParameterAttributes
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process AddObject request.
*
* This function processes an AddObject SOAP request from the ACS,
* parsing the object name and parameter key.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke AddObject on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the AddObject element.
*                    \n Contains ObjectName and ParameterKey.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_AddObject
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process DeleteObject request.
*
* This function processes a DeleteObject SOAP request from the ACS,
* parsing the object name and parameter key.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke DeleteObject on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the DeleteObject element.
*                    \n Contains ObjectName and ParameterKey.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_DeleteObject
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process Reboot request.
*
* This function processes a Reboot SOAP request from the ACS,
* parsing the command key.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke Reboot on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the Reboot element.
*                    \n Contains CommandKey.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_Reboot
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process Download request.
*
* This function processes a Download SOAP request from the ACS,
* parsing file type, URL, credentials, file size, target filename, and other parameters.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke Download on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the Download element.
*                    \n Contains CommandKey, FileType, URL, Username, Password, FileSize, TargetFileName, DelaySeconds, SuccessURL, FailureURL.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_Download
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process Upload request.
*
* This function processes an Upload SOAP request from the ACS,
* parsing file type, URL, credentials, and delay parameters.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke Upload on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the Upload element.
*                    \n Contains CommandKey, FileType, URL, Username, Password, DelaySeconds.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_Upload
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process ScheduleInform request.
*
* This function processes a ScheduleInform SOAP request from the ACS,
* parsing the delay and command key parameters.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke ScheduleInform on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the ScheduleInform element.
*                    \n Contains DelaySeconds and CommandKey.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_ScheduleInform
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process SetVouchers request.
*
* This function processes a SetVouchers SOAP request from the ACS,
* parsing the voucher list.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke SetVouchers on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the SetVouchers element.
*                    \n Contains VoucherList.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_SetVouchers
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process GetOptions request.
*
* This function processes a GetOptions SOAP request from the ACS,
* parsing the option name.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke GetOptions on the CPE controller.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] hXmlHandle  - Handle to XML DOM node of the GetOptions element.
*                    \n Contains OptionName.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest_GetOptions
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        ANSC_HANDLE                 hXmlHandle
    );


/**
* @brief Process generic SOAP request.
*
* This function processes a generic SOAP request from the ACS by identifying
* the RPC method and dispatching to the appropriate handler.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to invoke methods on the CPE controller.
* @param[in] pNameSpace  - SOAP namespace prefix.
*                    \n e.g., "SOAP-ENV" or "soap".
* @param[in] hXmlHandle  - Handle to XML DOM node of the SOAP envelope.
*                    \n Contains the SOAP request message.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if request processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessRequest
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        PCHAR                       pNameSpace,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process GetRPCMethods response.
*
* This function processes a GetRPCMethods SOAP response from the ACS,
* parsing the list of supported RPC methods.
*
* @param[in] hXmlHandle  - Handle to XML DOM node of the GetRPCMethodsResponse element.
*                    \n Contains MethodList array.
*
* @return Handle to SLAP_STRING_ARRAY containing method names.
* @retval ANSC_HANDLE containing string array if successful.
* @retval NULL if parsing fails.
*
*/
ANSC_HANDLE
CcspCwmpSoappoProcessResponse_GetRPCMethods
    (
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process Inform response.
*
* This function processes an Inform SOAP response from the ACS,
* parsing the MaxEnvelopes value.
*
* @param[in] hXmlHandle  - Handle to XML DOM node of the InformResponse element.
*                    \n Contains MaxEnvelopes.
*
* @return The MaxEnvelopes value.
* @retval ULONG indicating maximum number of envelopes the ACS can handle.
* @retval 0 if parsing fails.
*
*/
ULONG
CcspCwmpSoappoProcessResponse_Inform
    (
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process Kicked response.
*
* This function processes a Kicked SOAP response from the ACS,
* parsing the NextURL value.
*
* @param[in] hXmlHandle  - Handle to XML DOM node of the KickedResponse element.
*                    \n Contains NextURL.
*
* @return Pointer to the NextURL string.
* @retval PCHAR containing the next URL to access.
* @retval NULL if parsing fails or NextURL is empty.
*
*/
PCHAR
CcspCwmpSoappoProcessResponse_Kicked
    (
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process generic SOAP response.
*
* This function processes a generic SOAP response from the ACS by identifying
* the RPC method response and dispatching to the appropriate handler.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to deliver responses to the CPE controller.
* @param[in] pNameSpace  - SOAP namespace prefix.
* @param[in] hXmlHandle  - Handle to XML DOM node of the SOAP envelope.
*                    \n Contains the SOAP response message.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if response processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessResponse
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        PCHAR                       pNameSpace,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process SOAP fault.
*
* This function processes a SOAP fault from the ACS, extracting fault code,
* fault string, and fault detail information.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to deliver fault information to the CPE controller.
* @param[in] pNameSpace  - SOAP namespace prefix.
* @param[in] hXmlHandle  - Handle to XML DOM node of the SOAP fault element.
*                    \n Contains faultcode, faultstring, and detail.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if fault processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessFault
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        PCHAR                       pNameSpace,
        ANSC_HANDLE                 hXmlHandle
    );

/**
* @brief Process a single SOAP envelope.
*
* This function processes a single SOAP envelope message, parsing the XML
* and dispatching to request, response, or fault handlers.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to deliver messages to the CPE controller.
* @param[in] pNameSpace  - SOAP namespace prefix.
* @param[in] pEnvelopeMessage  - Pointer to the SOAP envelope XML string.
*                    \n Contains the complete SOAP message.
* @param[in] uMsgSize  - Size of the envelope message in bytes.
*                    \n Length of the XML string.
* @param[out] pIsFault  - Pointer to boolean indicating if message is a fault.
*                    \n Set to TRUE if SOAP fault, FALSE otherwise.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if envelope processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessSingleEnvelope
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        PCHAR                       pNameSpace,
        PCHAR                       pEnvelopeMessage,
        ULONG                       uMsgSize,
        PBOOLEAN                    pIsFault
    );

/**
* @brief Process multiple SOAP envelopes.
*
* This function processes one or more SOAP envelopes from an HTTP message,
* parsing each envelope and enforcing MaxEnvelopes constraints.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP SOAP Parser Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pSoapEnvelopes  - Pointer to the SOAP envelopes string.
*                    \n May contain multiple concatenated SOAP envelopes.
* @param[in] uMaxEnvelope  - Maximum number of envelopes allowed.
*                    \n Range: [1-n]
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to deliver messages to the CPE controller.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if all envelopes processed successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoProcessSoapEnvelopes
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pSoapEnvelopes,      /* may contain multiple SOAP envelopes */
        ULONG                       uMaxEnvelope,
        ANSC_HANDLE                 hCcspCwmpMcoIf
    );

/***********************************************************
         FUNCTIONS IMPLEMENTED IN CCSP_CWMP_SOAPPO_UTILITY.C
***********************************************************/
/**
* @brief Get node name without namespace prefix.
*
* This function extracts the local name from a qualified XML node name
* by removing the namespace prefix.
*
* @param[in] pNodeName  - Pointer to the qualified node name string.
*                    \n Format: "prefix:localname" or "localname".
*
* @return Pointer to the local name.
* @retval char* pointing to the local name portion if successful.
* @retval NULL if input is NULL.
*
*/
char*
CcspCwmpSoappoUtilGetNodeNameWithoutNS
    (
        PCHAR                       pNodeName
    );

/**
* @brief Find child node by name.
*
* This function searches for a child XML node with a specified name,
* matching both with and without namespace prefixes.
*
* @param[in] hXmlNode  - Handle to the parent XML DOM node.
*                    \n Parent node to search within.
* @param[in] pInputName  - Pointer to the child node name to find.
*                    \n Can be with or without namespace prefix.
*
* @return Handle to the found child node.
* @retval ANSC_HANDLE pointing to the XML DOM node if found.
* @retval NULL if child node not found.
*
*/
ANSC_HANDLE
CcspCwmpSoappoUtilFindChildNode
    (
        ANSC_HANDLE                 hXmlNode,
        PCHAR                       pInputName
    );

/**
* @brief Get SOAP namespace prefix.
*
* This function extracts the SOAP namespace prefix from a SOAP envelope
* by parsing the envelope element name.
*
* @param[in] pEnvelopeMessage  - Pointer to the SOAP envelope XML string.
*                    \n Contains the complete SOAP message.
* @param[out] pOutNamespaceName  - Pointer to buffer for namespace prefix.
*                    \n Buffer to store the extracted namespace prefix.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if namespace extracted successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoUtilGetSoapNamespace
    (
        PCHAR                       pEnvelopeMessage,
        PCHAR                       pOutNamespaceName
    );

/**
* @brief Get CWMP method code from method name.
*
* This function converts a CWMP RPC method name string to its corresponding
* enumerated method code.
*
* @param[in] pMethodName  - Pointer to the RPC method name string.
* @param[in] bFromServer  - Boolean indicating message direction.
*                    \n TRUE for ACS-initiated RPCs, FALSE for CPE-initiated RPCs.
*
* @return The method code.
* @retval ULONG containing the CWMP method enumeration value.
* @retval 0 if method name not recognized.
*
*/
ULONG
CcspCwmpSoappoUtilGetCwmpMethod
    (
        PCHAR                       pMethodName,
        BOOL                        bFromServer
    );

/**
* @brief Get CWMP method name from method code.
*
* This function converts a CWMP method enumeration code to its corresponding
* RPC method name string.
*
* @param[in] uMethod  - Method code enumeration value.
*                    \n CWMP RPC method identifier.
* @param[in] bFromServer  - Boolean indicating message direction.
*                    \n TRUE for ACS-initiated RPCs, FALSE for CPE-initiated RPCs.
* @param[out] pOutBuffer  - Pointer to buffer for method name string.
*                    \n Buffer to store the method name.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if method name retrieved successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoUtilGetCwmpMethodName
    (
        ULONG                       uMethod,
        BOOL                        bFromServer,
        PCHAR                       pOutBuffer
    );

/**
* @brief Extract parameter value from XML node.
*
* This function extracts parameter name, value, and type from a
* ParameterValueStruct XML node.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used for data type conversion if needed.
* @param[in] hXmlHandle  - Handle to XML DOM node.
*                    \n Parent node containing ParameterValueStruct.
* @param[in,out] hParamHandle  - Handle to CCSP_CWMP_PARAM_VALUE structure.
*                    \n Populated with extracted parameter information.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if parameter value extracted successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoUtilGetParamValue
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        ANSC_HANDLE                 hXmlHandle,
        ANSC_HANDLE                 hParamHandle
    );

/**
* @brief Extract parameter attribute from XML node.
*
* This function extracts parameter name, notification, and access control
* information from a ParameterAttributeStruct XML node.
*
* @param[in] hXmlHandle  - Handle to XML DOM node.
*                    \n Parent node containing ParameterAttributeStruct.
* @param[in,out] hAttrHandle  - Handle to CCSP_CWMP_PARAM_ATTRIB structure.
*                    \n Populated with extracted attribute information.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if parameter attribute extracted successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoUtilGetParamAttribute
    (
        ANSC_HANDLE                 hXmlHandle,
        ANSC_HANDLE                 hAttrHandle
    );

/**
* @brief Add SOAP header to envelope.
*
* This function adds a SOAP header element with ID and other CWMP-specific
* header fields to a SOAP envelope.
*
* @param[in,out] hSoapEnvelopeHandle  - Handle to XML DOM node of SOAP envelope.
*                    \n SOAP envelope to add header to.
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Used to correlate request and response.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if header added successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoUtilAddSoapHeader
    (
        ANSC_HANDLE                 hSoapEnvelopeHandle,
        char*                       pRequestID
    );

/**
* @brief Create SOAP envelope handle.
*
* This function creates a new SOAP envelope XML DOM structure with proper
* namespace declarations and SOAP header.
*
* @param[in] pRequestID  - Request ID for the SOAP message.
*                    \n Used to correlate request and response.
*
* @return Handle to the created SOAP envelope.
* @retval ANSC_HANDLE pointing to XML DOM node if successful.
* @retval NULL if creation fails.
*
*/
ANSC_HANDLE
CcspCwmpSoappoUtilCreateSoapEnvelopeHandle
    (
        char*                       pRequestID
    );

/**
* @brief Process invalid argument request.
*
* This function handles a request with invalid arguments by generating
* an appropriate SOAP fault response.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to send fault response.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] pMethodName  - Name of the RPC method with invalid arguments.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if fault response sent successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoUtilProcessInvalidArgumentRequest
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        char*                       pMethodName
    );

/**
* @brief Process invalid argument for SetParameterValues request.
*
* This function handles a SetParameterValues request with invalid parameter
* arguments by generating an appropriate SOAP fault response.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to send fault response.
* @param[in] pRequestID  - Request ID from the SOAP message.
*                    \n Used to correlate request and response.
* @param[in] pParamName  - Name of the parameter with invalid argument.
*                    \n Parameter that caused the fault.
* @param[in] CwmpSpvFaultCode  - CWMP fault code for SetParameterValues.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if fault response sent successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoUtilProcessInvalidArgumentSPVRequest
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf,
        char*                       pRequestID,
        char*                       pParamName,
        ULONG                       CwmpSpvFaultCode
    );

/**
* @brief Process too many envelopes error.
*
* This function handles the case when more SOAP envelopes are received than
* the MaxEnvelopes limit by generating an appropriate error response.
*
* @param[in] hCcspCwmpMcoIf  - Handle to CCSP CWMP MCO Interface.
*                    \n Used to send error response.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if error response sent successfully.
*
*/
ANSC_STATUS
CcspCwmpSoappoUtilProcessTooManyEnvelopes
    (
        ANSC_HANDLE                 hCcspCwmpMcoIf
    );

#endif
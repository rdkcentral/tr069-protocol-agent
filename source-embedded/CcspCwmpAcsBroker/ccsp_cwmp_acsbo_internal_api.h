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

    module:	ccsp_cwmp_acsbo_internal_api.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This header file contains the prototype definition for all
        the internal functions provided by the CCSP CWMP Acs Broker
        Object.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Xuechen Yang

    ---------------------------------------------------------------

    revision:

        09/29/05    initial revision.

**********************************************************************/


#ifndef  _CCSP_CWMP_ACSBO_INTERNAL_API_
#define  _CCSP_CWMP_ACSBO_INTERNAL_API_


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_ACSBO_STATES.C
***********************************************************/

/**
* @brief Retrieve the CCSP CWMP MSO Interface.
*
* This function is called to retrieve the MSO (Management Service Object) interface
* handle associated with this CCSP CWMP ACS Broker object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP MSO Interface.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpAcsboGetCcspCwmpMsoIf
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Retrieve the CCSP CWMP CPE Controller.
*
* This function is called to retrieve the CPE Controller object handle
* associated with this CCSP CWMP ACS Broker object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The handle to the CCSP CWMP CPE Controller.
* @retval ANSC_HANDLE if the operation is successful.
*
*/
ANSC_HANDLE
CcspCwmpAcsboGetCcspCwmpCpeController
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Set the CCSP CWMP CPE Controller.
*
* This function is called to configure the CPE Controller object handle
* for this CCSP CWMP ACS Broker object.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hCpeController  - Handle to the CPE Controller object to be configured.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcsboSetCcspCwmpCpeController
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hCpeController
    );

/**
* @brief Retrieve the object property.
*
* This function is called to retrieve the property configuration of the
* CCSP CWMP ACS Broker object and copy it to the provided property structure.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[out] hProperty  - Handle to the property data structure to be filled.
*                    \n This structure will receive the current object property.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcsboGetProperty
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
* @brief Configure the object property.
*
* This function is called to configure the property of the CCSP CWMP ACS Broker
* object by copying the provided property structure to the object's internal property.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hProperty  - Handle to the property data structure to be copied.
*                    \n This structure will be copied to the object's property.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcsboSetProperty
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
* @brief Reset the object property.
*
* This function is called to reset the property of the CCSP CWMP ACS Broker
* object to its default state by zeroing out the property structure.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcsboResetProperty
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Reset the object states.
*
* This function is called to reset all internal states of the CCSP CWMP ACS Broker
* object to their default values.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcsboReset
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
       FUNCTIONS IMPLEMENTED IN CCSP_CWMP_ACSBO_OPERATION.C
***********************************************************/

/**
* @brief Engage the object activity.
*
* This function is called to activate the CCSP CWMP ACS Broker object and enable
* its operations. It verifies that the CPE Controller is ready and sets the object
* to active state.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_NOT_READY if the CPE Controller is not available.
*
*/
ANSC_STATUS
CcspCwmpAcsboEngage
    (
        ANSC_HANDLE                 hThisObject
    );

/**
* @brief Cancel the object activity.
*
* This function is called to deactivate the CCSP CWMP ACS Broker object and
* cancel its operations by setting the object to inactive state.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
*
*/
ANSC_STATUS
CcspCwmpAcsboCancel
    (
        ANSC_HANDLE                 hThisObject
    );


/***********************************************************
        FUNCTIONS IMPLEMENTED IN CCSP_CWMP_ACSBO_MSOIF.C
***********************************************************/

/**
* @brief Discover the set of RPC methods supported.
*
* This function is called to discover the set of RPC methods supported by the
* Server or CPE it is in communication with. It acquires a CWMP session and
* retrieves the list of available RPC methods.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[out] ppMethodList  - Pointer to an array of strings containing the names of
*                    \n each of the RPC methods supported.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if the CWMP session cannot be acquired.
*
*/
ANSC_STATUS
CcspCwmpAcsboMsoGetRpcMethods
    (
        ANSC_HANDLE                 hThisObject,
        SLAP_STRING_ARRAY**         ppMethodList
    );

/**
* @brief Initiate a transaction sequence with the ACS.
*
* This function is called to initiate a transaction sequence whenever a connection
* to an ACS is established. It creates a CWMP event and adds it to the session.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pEventCode  - Event code that caused the transaction session to be established.
* @param[in] pCommandKey  - Value of the CommandKey passed to the CPE by ACS in the previous request.
*                    \n Can be NULL if no command key is associated.
* @param[in] bConnectNow  - Specifies whether a connection to the ACS should be established immediately.
*                    \n TRUE to connect now, FALSE to queue the event.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if the CWMP session cannot be acquired.
* @retval ANSC_STATUS_RESOURCES if memory allocation fails.
*
*/
ANSC_STATUS
CcspCwmpAcsboMsoInform
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pEventCode,
        char*                       pCommandKey,
        BOOL                        bConnectNow
    );

/**
* @brief Inform the server of file transfer completion.
*
* This function is called to inform the server of the completion of a file transfer
* initiated by an earlier Download or Upload method call. It acquires the appropriate
* CWMP session and invokes the TransferComplete RPC method.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bIsDownload  - Indicates whether the transfer was a download or upload.
*                    \n TRUE for download, FALSE for upload.
* @param[in] pCommandKey  - CommandKey argument passed to CPE in the Download or Upload method call
*                    \n that initiated the transfer.
* @param[in] hFault  - Handle to fault structure. If transfer was successful, FaultCode is 0.
*                    \n Otherwise contains non-zero FaultCode and FaultString.
* @param[in] hStartTime  - Handle to the date and time when transfer was started in UTC.
* @param[in] hCompleteTime  - Handle to the date and time when transfer completed in UTC.
* @param[in] bNewSession  - Specifies if a new CWMP session shall be created to invoke this RPC.
*                    \n TRUE to create new session, FALSE to use active session.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if the CWMP session cannot be acquired.
*
*/
ANSC_STATUS
CcspCwmpAcsboMsoTransferComplete
    (
        ANSC_HANDLE                 hThisObject,
		BOOL						bIsDownload,
        char*                       pCommandKey,
        ANSC_HANDLE                 hFault,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime,
        BOOL                        bNewSession
    );

/**
* @brief Inform the server of autonomous file transfer completion.
*
* This function is called to inform the server of the completion of an autonomous
* file transfer (not initiated by ACS). It acquires the appropriate CWMP session
* and invokes the AutonomousTransferComplete RPC method.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] bIsDownload  - Indicates whether the transfer was a download or upload.
*                    \n TRUE for download, FALSE for upload.
* @param[in] AnnounceURL  - URL that the CPE used to announce the autonomous transfer.
* @param[in] TransferURL  - URL used for the file transfer.
* @param[in] FileType  - Type of the file that was transferred.
* @param[in] FileSize  - Size of the transferred file in bytes.
* @param[in] TargetFileName  - Name of the file as stored on the CPE.
* @param[in] hFault  - Handle to fault structure. If transfer was successful, FaultCode is 0.
*                    \n Otherwise contains non-zero FaultCode and FaultString.
* @param[in] hStartTime  - Handle to the date and time when transfer was started in UTC.
* @param[in] hCompleteTime  - Handle to the date and time when transfer completed in UTC.
* @param[in] bNewSession  - Specifies if a new CWMP session shall be created to invoke this RPC.
*                    \n TRUE to create new session, FALSE to use active session.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if the CWMP session cannot be acquired.
*
*/
ANSC_STATUS
CcspCwmpAcsboMsoAutonomousTransferComplete
    (
        ANSC_HANDLE                 hThisObject,
		BOOL						bIsDownload,
        char*                       AnnounceURL,
        char*                       TransferURL,
        char*                       FileType,
        unsigned int                FileSize,
        char*                       TargetFileName,
        ANSC_HANDLE                 hFault,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime,
        BOOL                        bNewSession
    );

/**
* @brief Inform the server of deployment unit state change completion.
*
* This function is called to inform the server of the completion of software package
* management operations initiated by an earlier ChangeDUState method call. It acquires
* the appropriate CWMP session and invokes the DUStateChangeComplete RPC method.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hDsccReq  - Handle to the DU State Change Complete request structure.
*                    \n Contains the results of the deployment unit state change operations.
* @param[in] bNewSession  - Specifies if a new CWMP session shall be created to invoke this RPC.
*                    \n TRUE to create new session, FALSE to use active session.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if the CWMP session cannot be acquired.
*
*/
ANSC_STATUS
CcspCwmpAcsboMsoDuStateChangeComplete
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hDsccReq,
        BOOL                        bNewSession
    );

/**
* @brief Inform the server of autonomous deployment unit state change completion.
*
* This function is called to inform the server of the completion of autonomous
* software package management operations (not initiated by ACS). It acquires the
* appropriate CWMP session and invokes the AutonomousDUStateChangeComplete RPC method.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] hAdsccReq  - Handle to the Autonomous DU State Change Complete request structure.
*                    \n Contains XML content of autonomous DU state change results as defined by PD-194.
* @param[in] bNewSession  - Specifies if a new CWMP session shall be created to invoke this RPC.
*                    \n TRUE to create new session, FALSE to use active session.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if the CWMP session cannot be acquired.
*
*/
ANSC_STATUS
CcspCwmpAcsboMsoAutonomousDuStateChangeComplete
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hAdsccReq,
        BOOL                        bNewSession
    );

/**
* @brief Handle CPE "kicked" event.
*
* This function is called whenever the CPE is "kicked" by the ACS. It acquires
* a new CWMP session and invokes the Kicked RPC method to process the kick request
* and determine the next URL for browser redirection.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pCommand  - Generic argument that may be used by the server for identification
*                    \n or other purposes.
* @param[in] pReferer  - Content of the "Referer" HTTP header sent to the CPE when it was kicked.
* @param[in] pArg  - Generic argument that may be used by the server for identification
*                    \n or other purposes.
* @param[in] pNext  - URL the server should return in the method response under normal conditions.
* @param[out] ppNextUrl  - Pointer to the next URL the user's browser should be redirected to.
*                    \n Memory for this string is allocated by the function.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if the CWMP session cannot be acquired.
*
*/
ANSC_STATUS
CcspCwmpAcsboMsoKicked
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pCommand,
        char*                       pReferer,
        char*                       pArg,
        char*                       pNext,
        char**                      ppNextUrl
    );

/**
* @brief Request a file download from the server.
*
* This function is called to request a file download from the server. On reception
* of this request, the server MAY call the Download method to initiate the download.
* It acquires the first available CWMP session and invokes the RequestDownload RPC method.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pFileType  - Type of file being requested.
* @param[in] hFileTypeArgArray  - Handle to array of zero or more additional arguments,
*                    \n where each argument is a structure of name-value pairs.
* @param[in] ulArraySize  - Number of name-value pairs in the hFileTypeArgArray argument.
*                    \n Range: 0 to maximum supported arguments.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if the CWMP session cannot be acquired.
*
*/
ANSC_STATUS
CcspCwmpAcsboMsoRequestDownload
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pFileType,
        ANSC_HANDLE                 hFileTypeArgArray,
        ULONG                       ulArraySize
    );

/**
* @brief Notify that a parameter value has been modified.
*
* This function is called by underlying modules to indicate the value of a specified
* parameter has been modified. It acquires an inactive CWMP session and adds the
* modified parameter to the session. Connection timing is controlled by bConnectNow
* and considers scheduled inform states.
*
* @param[in] hThisObject  - Handle to the CCSP CWMP ACS Broker Object.
*                    \n This handle is actually the pointer of this object itself.
* @param[in] pParamName  - Name of the parameter whose value has been modified.
*                    \n Must be a valid TR-069 data model parameter path.
* @param[in] pParamValue  - New value of the parameter.
*                    \n String representation of the parameter value.
* @param[in] CwmpDataType  - CWMP data type of the parameter.
*                    \n Indicates the type per TR-069 specification.
* @param[in] bConnectNow  - Specifies whether a connection to the ACS should be established immediately.
*                    \n TRUE to connect now, FALSE to queue the notification. May be overridden
*                    \n if delayed inform is scheduled or session has retry count.
*
* @return The status of the operation.
* @retval ANSC_STATUS_SUCCESS if the operation is successful.
* @retval ANSC_STATUS_INTERNAL_ERROR if the CWMP session cannot be acquired.
*
*/
ANSC_STATUS
CcspCwmpAcsboMsoValueChanged
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName,
        char*                       pParamValue,
        ULONG                       CwmpDataType,
        BOOL                        bConnectNow
    );


#endif

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

    module:	ccsp_cwmp_soappo_interface.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This wrapper file defines all the platform-independent
        functions and macros for the CCSP CWMP Soap Parser Object.

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
        01/02/11    Kang added support of following RPCs
                        AutonomousTransferComplete
                        DUStateChangeComplete
                        AutonomousDUStateChangeComplete
        10/12/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_SOAPPO_INTERFACE_
#define  _CCSP_CWMP_SOAPPO_INTERFACE_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_co_interface.h"
#include "ansc_co_external_api.h"
#include "ccsp_cwmp_properties.h"


/***********************************************************
         CCSP CWMP SOAP PARSER COMPONENT OBJECT DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the object mapper object definition.
 */

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support),
 * we have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */

/**
 * @brief Get a context handle from the CWMP SOAP Parser object.
 *
 * This function pointer typedef defines the callback interface for retrieving context handles
 * from the CWMP SOAP Parser. Used to get handles to associated objects or components.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 *
 * @return Handle to the requested context object.
 * @retval Non-NULL Handle to the requested context object.
 * @retval NULL if not available.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPSOAPPO_GET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set a context handle in the CWMP SOAP Parser object.
 *
 * This function pointer typedef defines the callback interface for setting context handles
 * in the CWMP SOAP Parser. Used to associate handles to related objects or components.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] hContext    - Handle to the context object to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Context handle set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSOAPPO_SET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hContext
    );

/**
 * @brief Get an interface handle from the CWMP SOAP Parser object.
 *
 * This function pointer typedef defines the callback interface for retrieving interface handles
 * from the CWMP SOAP Parser. Used to get handles to interface objects.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 *
 * @return Handle to the requested interface object.
 * @retval Non-NULL Handle to the requested interface object on success.
 * @retval NULL if not available.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPSOAPPO_GET_IF)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set an interface handle in the CWMP SOAP Parser object.
 *
 * This function pointer typedef defines the callback interface for setting interface handles
 * in the CWMP SOAP Parser. Used to associate interface objects with the parser.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] hInterface  - Handle to the interface object to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Interface handle set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSOAPPO_SET_IF)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hInterface
    );

/**
 * @brief Get the property configuration from the CWMP SOAP Parser object.
 *
 * This function pointer typedef defines the callback interface for retrieving the property
 * configuration structure from the CWMP SOAP Parser.
 *
 * @param[in]  hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[out] hProperty   - Handle to the property structure to be filled with current property values.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Property configuration retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSOAPPO_GET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Set the property configuration in the CWMP SOAP Parser object.
 *
 * This function pointer typedef defines the callback interface for setting the property
 * configuration structure in the CWMP SOAP Parser.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] hProperty   - Handle to the property structure containing new property values to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Property configuration set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSOAPPO_SET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Reset the CWMP SOAP Parser object to initial state.
 *
 * This function pointer typedef defines the callback interface for resetting the CWMP SOAP Parser object.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Parser reset successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSOAPPO_RESET)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Process TR-069 SOAP envelopes received from the ACS.
 *
 * This function pointer typedef defines the callback interface for processing SOAP envelopes
 * received from the ACS.
 *
 * @param[in] hThisObject     - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pSoapEnvelopes  - String containing one or more SOAP envelopes to process.
 * @param[in] ulMaxEnvelopes  - Maximum number of envelopes to process.
 * @param[in] hCcspCwmpMcoIf  - Handle to the MCO interface for dispatching parsed RPC calls.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - SOAP envelopes processed successfully.
 * @retval ANSC_STATUS_FAILURE - Failed to process soap messages
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPSOAPPO_PROCESS)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pSoapEnvelopes,     /* may contain multiple SOAP envelopes */
        ULONG                       ulMaxEnvelopes,
        ANSC_HANDLE                 hCcspCwmpMcoIf
    );

/**
 * @brief Build a GetRPCMethods SOAP request message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP request message
 * for the GetRPCMethods RPC method. This method requests the list of RPC methods supported by the CPE.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 *
 * @return Pointer to the allocated SOAP envelope string.
 * @retval Pointer to the allocated SOAP envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REQ1)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID
    );

/**
 * @brief Build an Inform SOAP request message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP request message
 * for the Inform RPC method.
 *
 * @param[in] hThisObject      - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID       - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hDeviceId        - Handle to device ID structure.
 * @param[in] hEventArray      - Handle to array of event structures to be reported.
 * @param[in] ulEventCount     - Number of events in the event array.
 * @param[in] ulMaxEnvelopes   - Maximum envelopes CPE can accept.
 * @param[in] hCurrentTime     - Handle to current time structure (UTC).
 * @param[in] iTimeZoneOffset  - Time zone offset from UTC in minutes.
 * @param[in] ulRetryCount     - Inform retry count.
 * @param[in] hParamValueArray - Handle to array of parameter value structures to be reported.
 * @param[in] ulArraySize      - Number of parameters in the parameter value array.
 *
 * @return Pointer to the allocated SOAP envelope string.
 * @retval Pointer to the allocated SOAP envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REQ2)
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
 * @brief Build a TransferComplete SOAP request message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP request message
 * for the TransferComplete RPC method.
 *
 * @param[in] hThisObject   - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID    - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] pCommandKey   - Command key string from the original Download or Upload request.
 * @param[in] hFault        - Handle to fault structure if transfer failed, or NULL on success.
 * @param[in] hStartTime    - Handle to start time structure (date and time transfer was started in UTC).
 * @param[in] hCompleteTime - Handle to completion time structure (date and time transfer completed in UTC).
 *
 * @return Pointer to the allocated SOAP envelope string.
 * @retval Pointer to the allocated SOAP envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REQ3)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pCommandKey,
        ANSC_HANDLE                 hFault,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime
    );

/**
 * @brief Build a Kicked SOAP request message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP request message
 * for the Kicked RPC method.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] pCommand    - Command string that initiated the kick operation.
 * @param[in] pReferer    - Referer string identifying the source of the kick request.
 * @param[in] pArg        - Argument string with additional kick operation parameters.
 * @param[in] pNext       - Next action string indicating what should follow the kick.
 *
 * @return Pointer to the allocated SOAP envelope string.
 * @retval Pointer to the allocated SOAP envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REQ4)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pCommand,
        char*                       pReferer,
        char*                       pArg,
        char*                       pNext
    );

/**
 * @brief Build a RequestDownload SOAP request message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP request message
 * for the RequestDownload RPC method.
 *
 * @param[in] hThisObject       - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID        - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] pFileType         - File type string identifier (e.g., "1 Firmware Upgrade Image").
 * @param[in] hFileTypeArgArray - Handle to array of file type argument structures, or NULL if none.
 * @param[in] ulArraySize       - Size of the file type argument array. Valid range: 0 to MAX_ULONG.
 *
 * @return Pointer to the allocated SOAP envelope string.
 * @retval Pointer to the allocated SOAP envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REQ5)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pFileType,
        ANSC_HANDLE                 hFileTypeArgArray,
        ULONG                       ulArraySize
    );

/**
 * @brief Build an AutonomousTransferComplete SOAP request message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP request message
 * for the AutonomousTransferComplete RPC method.
 *
 * @param[in] hThisObject    - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID     - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hFault         - Handle to fault structure if transfer failed, or NULL on success.
 * @param[in] hStartTime     - Handle to start time structure (date and time transfer was started in UTC).
 * @param[in] hCompleteTime  - Handle to completion time structure (date and time transfer completed in UTC).
 * @param[in] bIsDownload    - Boolean flag indicating transfer direction.
 *                             TRUE = Autonomous download, FALSE = Autonomous upload.
 * @param[in] AnnounceURL    - Announce URL where CPE discovered the file.
 * @param[in] TransferURL    - Actual URL from which file was transferred.
 * @param[in] FileType       - File type identifier.
 * @param[in] FileSize       - Size of transferred file in bytes..
 * @param[in] TargetFileName - Target filename on CPE filesystem.
 *
 * @return Pointer to the allocated SOAP envelope string.
 * @retval Pointer to the allocated SOAP envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REQ6)
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
 * @brief Build a DUStateChangeComplete SOAP request message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP request message
 * for the DUStateChangeComplete RPC method.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hDsccReq    - Handle to DU State Change Complete request structure.
 * @param[in] pCommandKey - Command key string from the original ChangeDUState request.
 *
 * @return Pointer to the allocated SOAP envelope string.
 * @retval Pointer to the allocated SOAP envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REQ7)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hDsccReq,
        char*                       pCommandKey
    );

/**
 * @brief Build an AutonomousDUStateChangeComplete SOAP request message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP request message
 * for the AutonomousDUStateChangeComplete RPC method.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hAdsccReq   - Handle to Autonomous DU State Change Complete request structure.
 *
 * @return Pointer to the allocated SOAP envelope string.
 * @retval Pointer to the allocated SOAP envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REQ8)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hAdsccReq
    );


/**
 * @brief Build a SOAP fault response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP fault response
 * message when an error occurs processing an RPC method.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] pMethodName - Name of the RPC method that encountered the fault.
 * @param[in] hSoapFault  - Handle to SOAP fault structure.
 *
 * @return Pointer to the allocated SOAP fault envelope string.
 * @retval Pointer to the allocated SOAP fault envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP0)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        char*                       pMethodName,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a GetRPCMethods SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the GetRPCMethods RPC method. Returns the list of RPC methods supported by the CPE, such as
 * GetParameterValues, SetParameterValues, Download, Upload, Reboot, etc.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] pMethodList - Pointer to SLAP string array containing supported CPE RPC method names.
 *
 * @return Pointer to the allocated SOAP fault envelope string.
 * @retval Pointer to the allocated SOAP fault envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP1)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        SLAP_STRING_ARRAY*          pMethodList
    );

/**
 * @brief Build a SetParameterValues SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the SetParameterValues RPC method.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] iStatus     - Status code: 0 = Changes applied successfully, 1 = Changes require CPE reboot.
 * @param[in] hSoapFault  - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP2)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        int                         iStatus,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a GetParameterValues SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the GetParameterValues RPC method.
 *
 * @param[in] hThisObject      - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID       - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hParamValueArray - Handle to array of parameter value structures.
 * @param[in] ulArraySize      - Number of parameters in the array.
 * @param[in] hSoapFault       - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP3)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hParamValueArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a GetParameterNames SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the GetParameterNames RPC method.
 *
 * @param[in] hThisObject     - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID      - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hParamInfoArray - Handle to array of parameter info structures.
 * @param[in] ulArraySize     - Number of parameters in the array.
 * @param[in] hSoapFault      - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP4)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hParamInfoArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a SetParameterAttributes SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the SetParameterAttributes RPC method.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hSoapFault  - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP5)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a GetParameterAttributes SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the GetParameterAttributes RPC method.
 *
 * @param[in] hThisObject        - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID         - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hParamAttribArray  - Handle to array of parameter attribute structures.
 * @param[in] ulArraySize        - Number of parameters in the array.
 * @param[in] hSoapFault         - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP6)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hParamAttribArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build an AddObject SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the AddObject RPC method.
 *
 * @param[in] hThisObject      - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID       - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] ulInstanceNumber - Instance number of the newly created object. Valid range: 1 to MAX_ULONG.
 * @param[in] iStatus          - Status code: 0 = Object added successfully, 1 = Changes require CPE reboot.
 * @param[in] hSoapFault       - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP7)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ULONG                       ulInstanceNumber,
        int                         iStatus,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a DeleteObject SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the DeleteObject RPC method.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] iStatus     - Status code: 0 = Object deleted successfully, 1 = Changes require CPE reboot.
 * @param[in] hSoapFault  - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP8)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        int                         iStatus,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a Download SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the Download RPC method.
 *
 * @param[in] hThisObject   - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID    - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] iStatus       - Status code: 0 = Download deferred, 1 = Download completed immediately.
 * @param[in] hStartTime    - Handle to start time structure (date and time download started in UTC).
 * @param[in] hCompleteTime - Handle to estimated completion time structure in UTC.
 * @param[in] hSoapFault    - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP9)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        int                         iStatus,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a Reboot or ChangeDUState SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the Reboot RPC method (initiates CPE reboot) or ChangeDUState RPC method (changes deployment unit state).
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hSoapFault  - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP10)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a GetQueuedTransfers SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the GetQueuedTransfers RPC method.
 *
 * @param[in] hThisObject           - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID            - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hQueuedTransferArray  - Handle to array of queued transfer structures.
 * @param[in] ulArraySize           - Number of queued transfers in the array..
 * @param[in] hSoapFault            - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP11)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hQueuedTransferArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a ScheduleInform SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the ScheduleInform RPC method.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hSoapFault  - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP12)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a SetVouchers SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the SetVouchers RPC method.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hSoapFault  - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP13)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a GetOptions SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the GetOptions RPC method.
 *
 * @param[in] hThisObject   - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID    - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hOptionArray  - Handle to array of option structures.
 * @param[in] ulArraySize   - Number of options in the array.
 * @param[in] hSoapFault    - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP14)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hOptionArray,
        ULONG                       ulArraySize,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build an Upload SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the Upload RPC method.
 *
 * @param[in] hThisObject   - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID    - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] iStatus       - Status code: 0 = Upload deferred, 1 = Upload completed immediately.
 * @param[in] hStartTime    - Handle to start time structure (date and time upload started in UTC).
 * @param[in] hCompleteTime - Handle to estimated completion time structure in UTC.
 * @param[in] hSoapFault    - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope string on success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP15)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        int                         iStatus,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime,
        ANSC_HANDLE                 hSoapFault
    );

/**
 * @brief Build a FactoryReset SOAP response message.
 *
 * This function pointer typedef defines the callback interface for building a SOAP response message
 * for the FactoryReset RPC method.
 *
 * @param[in] hThisObject - Handle to the CWMP SOAP Parser object instance.
 * @param[in] pRequestID  - Unique request identifier string to be included in the SOAP envelope.
 * @param[in] hSoapFault  - Handle to SOAP fault structure if operation failed, or NULL on success.
 *
 * @return Pointer to the allocated SOAP response envelope string.
 * @retval Pointer to the allocated SOAP response envelope stringon success.
 * @retval NULL if build fails.
 *
 */
typedef  char*
(*PFN_CWMPSOAPPO_BUILD_REP16)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pRequestID,
        ANSC_HANDLE                 hSoapFault
    );

/*
 * The CPE WAN Management Protocol defines SOAP 1.1 as the encoding syntax to transport the RPC
 * method calls and responses. The following describes the mapping of RPC methods to SOAP encoding:
 *
 *      - The encoding must use the standard SOAP 1.1 envelope and serialization
 *        namespaces.
 *      - All elements and attributes defined as part of this version of the CPE WAN
 *        Management Protocol are associated with the following namespace identifier:
 *        "urn:dslforum-org:cwmp-1-0".
 *      - The data types used correspond directly to the data types defined in the SOAP
 *        1.1 serialization namespace.
 *      - For an array argument, the given argument name corresponds to the name of the
 *        overall array element.
 *      - .....
 */
#define  CCSP_CWMP_SOAP_PARSER_CLASS_CONTENT                                                     \
    /* duplication of the base object class content */                                      \
    ANSCCO_CLASS_CONTENT                                                                    \
    /* start of object class content */                                                     \
    PFN_CWMPSOAPPO_RESET            Reset;                                                  \
                                                                                            \
    PFN_CWMPSOAPPO_PROCESS          ProcessSoapEnvelopes;                                   \
                                                                                            \
    PFN_CWMPSOAPPO_BUILD_REQ1       BuildSoapReq_GetRpcMethods;                             \
    PFN_CWMPSOAPPO_BUILD_REQ2       BuildSoapReq_Inform;                                    \
    PFN_CWMPSOAPPO_BUILD_REQ3       BuildSoapReq_TransferComplete;                          \
    PFN_CWMPSOAPPO_BUILD_REQ4       BuildSoapReq_Kicked;                                    \
    PFN_CWMPSOAPPO_BUILD_REQ5       BuildSoapReq_RequestDownload;                           \
    PFN_CWMPSOAPPO_BUILD_REQ6       BuildSoapReq_AutonomousTransferComplete;                \
    PFN_CWMPSOAPPO_BUILD_REQ7       BuildSoapReq_DUStateChangeComplete;                     \
    PFN_CWMPSOAPPO_BUILD_REQ8       BuildSoapReq_AutonomousDUStateChangeComplete;           \
                                                                                            \
    PFN_CWMPSOAPPO_BUILD_REP0       BuildSoapRep_Error;                                     \
    PFN_CWMPSOAPPO_BUILD_REP1       BuildSoapRep_GetRpcMethods;                             \
    PFN_CWMPSOAPPO_BUILD_REP2       BuildSoapRep_SetParameterValues;                        \
    PFN_CWMPSOAPPO_BUILD_REP3       BuildSoapRep_GetParameterValues;                        \
    PFN_CWMPSOAPPO_BUILD_REP4       BuildSoapRep_GetParameterNames;                         \
    PFN_CWMPSOAPPO_BUILD_REP5       BuildSoapRep_SetParameterAttributes;                    \
    PFN_CWMPSOAPPO_BUILD_REP6       BuildSoapRep_GetParameterAttributes;                    \
    PFN_CWMPSOAPPO_BUILD_REP7       BuildSoapRep_AddObject;                                 \
    PFN_CWMPSOAPPO_BUILD_REP8       BuildSoapRep_DeleteObject;                              \
    PFN_CWMPSOAPPO_BUILD_REP9       BuildSoapRep_Download;                                  \
    PFN_CWMPSOAPPO_BUILD_REP10      BuildSoapRep_Reboot;                                    \
    PFN_CWMPSOAPPO_BUILD_REP10      BuildSoapRep_ChangeDUState;                             \
    PFN_CWMPSOAPPO_BUILD_REP11      BuildSoapRep_GetQueuedTransfers;                        \
    PFN_CWMPSOAPPO_BUILD_REP12      BuildSoapRep_ScheduleInform;                            \
    PFN_CWMPSOAPPO_BUILD_REP13      BuildSoapRep_SetVouchers;                               \
    PFN_CWMPSOAPPO_BUILD_REP14      BuildSoapRep_GetOptions;                                \
    PFN_CWMPSOAPPO_BUILD_REP15      BuildSoapRep_Upload;                                    \
    PFN_CWMPSOAPPO_BUILD_REP16      BuildSoapRep_FactoryReset;                              \
    /* end of object class content */                                                       \

typedef  struct
_CCSP_CWMP_SOAP_PARSER_OBJECT
{
    CCSP_CWMP_SOAP_PARSER_CLASS_CONTENT
}
CCSP_CWMP_SOAP_PARSER_OBJECT,  *PCCSP_CWMP_SOAP_PARSER_OBJECT;

#define  ACCESS_CCSP_CWMP_SOAP_PARSER_OBJECT(p)          \
         ACCESS_CONTAINER(p, CCSP_CWMP_SOAP_PARSER_OBJECT, Linkage)


#endif
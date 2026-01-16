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

    module:	ccsp_cwmp_helper_api.h

        For CCSP CWMP protocol implementation

    ---------------------------------------------------------------

    description:

        This file defines helper APIs that faciliates CWMP
        migration to CCSP new architecture.

    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Kang Quan

    ---------------------------------------------------------------

    revision:

        07/12/2011  initial revision.

**********************************************************************/

#ifndef  _CCSP_CWMP_HELPER_API_DEF_
#define  _CCSP_CWMP_HELPER_API_DEF_

#include "ansc_time.h"
#include "ccsp_base_api.h"
#include "dslh_definitions_database.h"
#include "ccsp_cwmp_definitions_cwmp.h"
#include "ccsp_tr069pa_wrapper_api.h"

#define  CCSP_TR069PA_WRITE_ID                      DSLH_MPA_ACCESS_CONTROL_ACS

#define  CCSP_NS_ACCESS_ACSONLY                     0x00000000
#define  CCSP_NS_ACCESS_SUBSCRIBER                  0xFFFFFFFF

#define  CCSP_TR069PA_PARAM_NOTIF_ATTR              "PmNotif"


/**
 * @brief Set SOAP fault structure based on CWMP fault code.
 *
 * This inline function populates a CCSP_CWMP_SOAP_FAULT structure with appropriate
 * SOAP and CWMP fault codes and strings corresponding to the provided fault code.
 * It maps CWMP protocol fault codes to their standard SOAP fault representations.
 *
 * @param[out] pCwmpSoapFault  Pointer to CCSP_CWMP_SOAP_FAULT structure to be populated.
 *                              Must be a valid, allocated structure.
 * @param[in]  faultCode       CWMP fault code to convert. Valid values include:
 *                              - CCSP_CWMP_CPE_CWMP_FaultCode_methodUnsupported (9000)
 *                              - CCSP_CWMP_CPE_CWMP_FaultCode_requestDenied (9001)
 *                              - CCSP_CWMP_CPE_CWMP_FaultCode_internalError (9002)
 *                              - CCSP_CWMP_CPE_CWMP_FaultCode_invalidArgs (9003)
 *                              - CCSP_CWMP_CPE_CWMP_FaultCode_resources (9004)
 *                              - CCSP_CWMP_CPE_CWMP_FaultCode_invalidParamName (9005)
 *                              - CCSP_CWMP_CPE_CWMP_FaultCode_invalidParamType (9006)
 *                              - CCSP_CWMP_CPE_CWMP_FaultCode_invalidParamValue (9007)
 *                              - CCSP_CWMP_CPE_CWMP_FaultCode_notWritable (9008)
 *                              - CCSP_CWMP_CPE_CWMP_FaultCode_notifyRejected (9009)
 *                              - And other CWMP-defined fault codes (9010-9026)
 *
 * @return None.
 *
 */
__inline static
void
CCSP_CWMP_SET_SOAP_FAULT
    (
        PCCSP_CWMP_SOAP_FAULT       pCwmpSoapFault,
        ULONG                       faultCode
    )
{
    switch (faultCode)
    {
        case    CCSP_CWMP_CPE_CWMP_FaultCode_methodUnsupported:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_methodUnsupported);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_methodUnsupported);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_methodUnsupported;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_methodUnsupported);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_requestDenied:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_requestDenied);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_requestDenied);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_requestDenied;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_requestDenied);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_internalError:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_internalError);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_internalError);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_internalError;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_internalError);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_invalidArgs:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_invalidArgs);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_invalidArgs);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_invalidArgs;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_invalidArgs);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_resources:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_resources);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_resources);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_resources;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_resources);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_invalidParamName:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_invalidParamName);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_invalidParamName);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_invalidParamName;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_invalidParamName);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_invalidParamType:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_invalidParamType);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_invalidParamType);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_invalidParamType;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_invalidParamType);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_invalidParamValue:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_invalidParamValue);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_invalidParamValue);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_invalidParamValue;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_invalidParamValue);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_notWritable:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_notWritable);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_notWritable);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_notWritable;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_notWritable);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_notifyRejected:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_notifyRejected);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_notifyRejected);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_notifyRejected;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_notifyRejected);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_downloadFailure:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_downloadFailure);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_downloadFailure);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_downloadFailure;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_downloadFailure);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_uploadFailure:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_uploadFailure);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_uploadFailure);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_uploadFailure;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_uploadFailure);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_authFailure:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_authFailure);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_authFailure);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_authFailure;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_authFailure);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_protUnsupported:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_protUnsupported);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_protUnsupported);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_protUnsupported;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_protUnsupported);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_mcastJoinFailed:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_mcastJoinFailed);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_mcastJoinFailed);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_mcastJoinFailed;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_mcastJoinFailed);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_notReachFileServer:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_notReachFileServer);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_notReachFileServer);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_notReachFileServer;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_notReachFileServer);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_noAccessToFile:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_noAccessToFile);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_noAccessToFile);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_noAccessToFile;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_noAccessToFile);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_downloadIncomplete:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_downloadIncomplete);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_downloadIncomplete);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_downloadIncomplete;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_downloadIncomplete);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_dlfileCorrputed:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_dlfileCorrputed);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_dlfileCorrputed);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_dlfileCorrputed;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_dlfileCorrputed);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_fileAuthFailure:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_fileAuthFailure);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_fileAuthFailure);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_fileAuthFailure;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_fileAuthFailure);

                break;


        case    CCSP_CWMP_CPE_CWMP_FaultCode_dlFailureWindow:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_dlFailureWindow);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_dlFailureWindow);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_dlFailureWindow;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_dlFailureWindow);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_cancelXferFailure:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_cancelXferFailure);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_cancelXferFailure);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_cancelXferFailure;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_cancelXferFailure);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_invalidUUID:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_invalidUUID);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_invalidUUID);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_invalidUUID;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_invalidUUID);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_UnknownExecEnv:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_UnknownExecEnv);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_UnknownExecEnv);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_UnknownExecEnv;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_UnknownExecEnv);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_ExecEnvDisabled:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_ExecEnvDisabled);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_ExecEnvDisabled);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_ExecEnvDisabled;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_ExecEnvDisabled);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_DUMismatchEE:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_DUMismatchEE);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_DUMismatchEE);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_DUMismatchEE;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_DUMismatchEE);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_DuplicateDU:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_DuplicateDU);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_DuplicateDU);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_DuplicateDU;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_DuplicateDU);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_NoResToInstall:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_NoResToInstall);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_NoResToInstall);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_NoResToInstall;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_NoResToInstall);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_UnknownDU:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_UnknownDU);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_UnknownDU);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_UnknownDU;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_UnknownDU);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_InvalidDUState:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_InvalidDUState);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_InvalidDUState);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_InvalidDUState;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_InvalidDUState);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_DUNoDowngrade:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_DUNoDowngrade);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_DUNoDowngrade);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_DUNoDowngrade;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_DUNoDowngrade);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_DUUpdateNoVersion:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_DUUpdateNoVersion);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_DUUpdateNoVersion);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_DUUpdateNoVersion;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_DUUpdateNoVersion);

                break;

        case    CCSP_CWMP_CPE_CWMP_FaultCode_DUUpdateVerExist:

                pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_DUUpdateVerExist);
                pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_DUUpdateVerExist);
                pCwmpSoapFault->Fault.FaultCode     = CCSP_CWMP_CPE_CWMP_FaultCode_DUUpdateVerExist;
                pCwmpSoapFault->Fault.FaultString   = AnscCloneString(CCSP_CWMP_CPE_CWMP_FaultText_DUUpdateVerExist);

                break;

        default:

                CcspTr069PaTraceWarning(("Faultcode %u not caught\n", (unsigned int)faultCode));
                if ( TRUE )
                {
                    char            buf[32];

                    _ansc_sprintf(buf, "Falult Code: %u", (unsigned int)faultCode);

                    pCwmpSoapFault->soap_faultcode      = AnscCloneString(CCSP_CWMP_CPE_SOAP_faultcode_internalError);
                    pCwmpSoapFault->soap_faultstring    = AnscCloneString(CCSP_CWMP_CPE_SOAP_faulttext_internalError);
                    pCwmpSoapFault->Fault.FaultCode     = faultCode;
                    pCwmpSoapFault->Fault.FaultString   = AnscCloneString(buf);
                }

                break;
    }
}


/**
 * @brief Free memory allocated for a string array.
 *
 * This inline function releases memory allocated for an array of strings.
 * It can optionally free individual string elements and/or the array itself.
 *
 * @param[in,out] pStringArray      Pointer to array of string pointers to free.
 *                                   Each element is freed if non-NULL.
 * @param[in]     ulArraySize        Number of elements in the string array.
 *                                   Valid range: 0 to maximum array size.
 * @param[in]     bFreeArrayAsWell   Flag indicating whether to free the array pointer itself.
 *                                   - TRUE: Free both individual strings and the array
 *                                   - FALSE: Free only individual strings, keep array
 *
 * @return None.
 *
 */
__inline static
void
CcspTr069FreeStringArray
    (
        char**                      pStringArray,
        ULONG                       ulArraySize,
        BOOL                        bFreeArrayAsWell
    )
{
    ULONG                           i;

    if ( !pStringArray )
    {
        return;
    }

    for ( i = 0; i < ulArraySize; i ++ )
    {
        if ( pStringArray[i] )
        {
            AnscFreeMemory(pStringArray[i]);
        }
    }

    if ( bFreeArrayAsWell )
    {
        AnscFreeMemory(pStringArray);
    }
}

// String list/queue definitions
typedef
struct
_CCSP_TR069PA_STRING_SLIST_ENTRY
{
    SINGLE_LINK_ENTRY               Linkage;
    char*                           Value;
}
CCSP_TR069PA_STRING_SLIST_ENTRY, *PCCSP_TR069PA_STRING_SLIST_ENTRY;

#define ACCESS_CCSP_TR069PA_STRING_SLIST_ENTRY(p) ACCESS_CONTAINER(p, CCSP_TR069PA_STRING_SLIST_ENTRY, Linkage)

typedef
struct
_CCSP_TR069PA_PARAM_ATTR_SLIST_ENTRY
{
    SINGLE_LINK_ENTRY               Linkage;
    PCCSP_CWMP_SET_PARAM_ATTRIB     ParamAttr;
}
CCSP_TR069PA_PARAM_ATTR_SLIST_ENTRY, *PCCSP_TR069PA_PARAM_ATTR_SLIST_ENTRY;

#define ACCESS_CCSP_TR069PA_PARAM_ATTR_SLIST_ENTRY(p) ACCESS_CONTAINER(p, CCSP_TR069PA_PARAM_ATTR_SLIST_ENTRY, Linkage)

/**
 * @brief Free all string entries in a queue.
 *
 * This inline function removes and frees all CCSP_TR069PA_STRING_SLIST_ENTRY
 * elements from a queue. It can optionally free the string values contained
 * within each entry.
 *
 * @param[in,out] pQueueHeader  Pointer to queue header containing string entries.
 *                               All entries are removed and freed.
 * @param[in]     bFreeValue    Flag indicating whether to free the string values.
 *                               - TRUE: Free both entry structures and string values
 *                               - FALSE: Free only entry structures, preserve values
 *
 * @return None.
 *
 */
inline static
void
CcspTr069FreeStringQueue(PQUEUE_HEADER pQueueHeader, BOOL bFreeValue)
{
    PSINGLE_LINK_ENTRY              pLink;
    PCCSP_TR069PA_STRING_SLIST_ENTRY pSListEntry;

    while ( (pLink = AnscQueuePopEntry(pQueueHeader)))
    {
        pSListEntry = ACCESS_CCSP_TR069PA_STRING_SLIST_ENTRY(pLink);

        if ( bFreeValue )
        {
            AnscFreeMemory(pSListEntry->Value);
        }

        AnscFreeMemory(pSListEntry);
    }
}

/**
 * @brief Free all parameter attribute entries in a queue.
 *
 * This inline function removes and frees all CCSP_TR069PA_PARAM_ATTR_SLIST_ENTRY
 * elements from a queue, including the parameter attribute structures they contain.
 *
 * @param[in,out] pQueueHeader  Pointer to queue header containing parameter attribute entries.
 *                               All entries and their ParamAttr structures are freed.
 *
 * @return None.
 *
 */
inline static
void
CcspTr069FreeParamAttrQueue(PQUEUE_HEADER pQueueHeader)
{
    PSINGLE_LINK_ENTRY              pLink;
    PCCSP_TR069PA_PARAM_ATTR_SLIST_ENTRY pSListEntry;

    while ( (pLink = AnscQueuePopEntry(pQueueHeader)))
    {
        pSListEntry = ACCESS_CCSP_TR069PA_PARAM_ATTR_SLIST_ENTRY(pLink);

        AnscFreeMemory(pSListEntry);
    }
}

/**
 * @brief Free all string entries in a single-linked list.
 *
 * This inline function removes and frees all CCSP_TR069PA_STRING_SLIST_ENTRY
 * elements from a single-linked list. It can optionally free the string values
 * contained within each entry.
 *
 * @param[in,out] pSListHeader  Pointer to single-linked list header containing string entries.
 *                               All entries are removed and freed.
 * @param[in]     bFreeValue    Flag indicating whether to free the string values.
 *                               - TRUE: Free both entry structures and string values
 *                               - FALSE: Free only entry structures, preserve values
 *
 * @return None.
 *
 */
inline static
void
CcspTr069FreeStringSList(PSLIST_HEADER pSListHeader, BOOL bFreeValue)
{
    PSINGLE_LINK_ENTRY              pLink;
    PCCSP_TR069PA_STRING_SLIST_ENTRY pSListEntry;

    while ( (pLink = AnscSListPopEntry(pSListHeader)) )
    {
        pSListEntry = ACCESS_CCSP_TR069PA_STRING_SLIST_ENTRY(pLink);

        if ( pSListEntry )
        {
            if ( bFreeValue )
            {
                AnscFreeMemory(pSListEntry->Value);
            }

            AnscFreeMemory(pSListEntry);
        }
    }
}

/*
 * The following data structures are defined to cover normalized
 * actions - GPN, GPA, SPA, GPV, SPV. They are used as intermediate
 * data structures in order for PA to dispatch calls to all matching
 * FCs and aggregate results from FCs accordingly.
 */
#define  CCSP_NORMALIZED_ACTION_TYPE_GPN            1
#define  CCSP_NORMALIZED_ACTION_TYPE_SPV            2
#define  CCSP_NORMALIZED_ACTION_TYPE_GPV            3
#define  CCSP_NORMALIZED_ACTION_TYPE_SPA            4
#define  CCSP_NORMALIZED_ACTION_TYPE_GPA            5

typedef  parameterInfoStruct_t                      CCSP_PARAM_NAME_INFO, *PCCSP_PARAM_NAME_INFO;
typedef  parameterValStruct_t                       CCSP_PARAM_VALUE_INFO, *PCCSP_PARAM_VALUE_INFO;
typedef  parameterAttributeStruct_t                 CCSP_PARAM_ATTR_INFO, *PCCSP_PARAM_ATTR_INFO;

typedef  union
_CCSP_TR069_NA_ARGS
{
    CCSP_PARAM_NAME_INFO            paramInfo;
    CCSP_PARAM_VALUE_INFO           paramValueInfo;
    CCSP_PARAM_ATTR_INFO            paramAttrInfo;
}
CCSP_TR069_NA_ARGS, *PCCSP_TR069_NA_ARGS;

typedef  struct
_CCSP_TR069PA_NSLIST
{
    SINGLE_LINK_ENTRY               Linkage;
    int                             NaType;             /* normalized action type - one of CCSP_NORMALIZED_ACTION_TYPE_xxx */
    CCSP_TR069_NA_ARGS              Args;               /* input or output arguments */
}
CCSP_TR069PA_NSLIST, *PCCSP_TR069PA_NSLIST;

#define  ACCESS_CCSP_TR069PA_NSLIST(p)                                                                  \
         ACCESS_CONTAINER(p, CCSP_TR069PA_NSLIST, Linkage)

/* API CcspTr069PaIsGpnNsInQueue checks if a given namespace returned in GPN response
 * has already been added, meaning another FC returns the same namespace. PA checks duplicate
 * in case FC (or CCSP FC supporting library) does not handle this case well or easily.
 * This feature can be turned off if there's no such problems in future.
 */
#ifndef  _NO_CCSP_TR069PA_GPN_RESULT_FILTERING
/**
 * @brief Check if a parameter name already exists in GPN (GetParameterNames) result queue.
 *
 * This inline function verifies whether a parameter name has already been added to
 * the namespace list queue, preventing duplicate entries when multiple Functional
 * Components return the same namespace. Used to filter GPN response results.
 *
 * @param[in] pNsListQueue  Pointer to queue header containing namespace list entries.
 * @param[in] pParamName    Pointer to parameter name string to check for duplicates.
 *                           NULL or empty string returns TRUE.
 *
 * @return Boolean indicating whether parameter name exists in queue.
 * @retval TRUE if parameter name already exists in queue or pParamName is NULL/empty.
 * @retval FALSE if parameter name does not exist in queue.
 *
 */
__inline static BOOL
CcspTr069PaIsGpnNsInQueue
    (
        PQUEUE_HEADER               pNsListQueue,
        char*                       pParamName
    )
{
    PSINGLE_LINK_ENTRY              pSLinkEntry;
    PCCSP_TR069PA_NSLIST            pNsList;
    PCCSP_PARAM_NAME_INFO           pParamInfo;

    if ( !pParamName || *pParamName == 0 ) return TRUE;

    pSLinkEntry = AnscQueueGetFirstEntry(pNsListQueue);
    while ( pSLinkEntry )
    {
        pNsList = ACCESS_CCSP_TR069PA_NSLIST(pSLinkEntry);
        pSLinkEntry = AnscQueueGetNextEntry(pSLinkEntry);

        pParamInfo = &pNsList->Args.paramInfo;

        if ((pParamInfo->parameterName != NULL) &&
            (strcmp(pParamName, pParamInfo->parameterName) == 0))
        {
            return TRUE;
        }
    }

    return FALSE;
}
#endif

#define  CcspTr069PaPushGpvNsInQueue(pNsListQueue, pParamName, pParamValue, ccspType, pNsList)          \
    do {                                                                                                \
        PCCSP_PARAM_VALUE_INFO   pParamValueInfo;                                                       \
        pNsList =                                                                                       \
            (PCCSP_TR069PA_NSLIST)AnscAllocateMemory                                                    \
                (sizeof(CCSP_TR069PA_NSLIST));                                                          \
                                                                                                        \
        if ( pNsList )                                                                                  \
        {                                                                                               \
            pNsList->NaType  = CCSP_NORMALIZED_ACTION_TYPE_GPV;                                         \
            pParamValueInfo  = &pNsList->Args.paramValueInfo;                                           \
                                                                                                        \
            pParamValueInfo->parameterName  = pParamName;                                               \
            pParamValueInfo->parameterValue = pParamValue;                                              \
            pParamValueInfo->type           = ccspType;                                                 \
                                                                                                        \
            AnscQueuePushEntry(pNsListQueue, &pNsList->Linkage);                                        \
        }                                                                                               \
    } while (0)


#define  CcspTr069PaPushGpnNsInQueue(pNsListQueue, pParamName, bWritable, pNsList)                      \
    do {                                                                                                \
        PCCSP_PARAM_NAME_INFO    pParamNameInfo;                                                        \
        pNsList =                                                                                       \
            (PCCSP_TR069PA_NSLIST)AnscAllocateMemory                                                    \
                (sizeof(CCSP_TR069PA_NSLIST));                                                          \
                                                                                                        \
        if ( pNsList )                                                                                  \
        {                                                                                               \
            pNsList->NaType = CCSP_NORMALIZED_ACTION_TYPE_GPN;                                          \
            pParamNameInfo  = &pNsList->Args.paramInfo;                                                 \
                                                                                                        \
            pParamNameInfo->parameterName = pParamName;                                                 \
            pParamNameInfo->writable      = bWritable;                                                  \
                                                                                                        \
            AnscQueuePushEntry(pNsListQueue, &pNsList->Linkage);                                        \
        }                                                                                               \
    } while (0)


#define  CcspTr069PaPushGpaNsInQueue(pNsListQueue, pParamName, notif, accessControl, pNsList)           \
    do {                                                                                                \
        PCCSP_PARAM_ATTR_INFO    pParamAttrInfo;                                                        \
        pNsList =                                                                                       \
            (PCCSP_TR069PA_NSLIST)AnscAllocateMemory                                                    \
                (sizeof(CCSP_TR069PA_NSLIST));                                                          \
                                                                                                        \
        if ( pNsList )                                                                                  \
        {                                                                                               \
            pNsList->NaType  = CCSP_NORMALIZED_ACTION_TYPE_GPA;                                         \
            pParamAttrInfo   = &pNsList->Args.paramAttrInfo;                                            \
                                                                                                        \
            pParamAttrInfo->parameterName        = pParamName;                                          \
            pParamAttrInfo->notification         = notif;                                               \
            pParamAttrInfo->accessControlBitmask = accessControl;                                       \
                                                                                                        \
            AnscQueuePushEntry(pNsListQueue, &pNsList->Linkage);                                        \
        }                                                                                               \
    } while (0)


#define  CcspTr069PaFreeNsList(pNsList)                                                                 \
    do {                                                                                                \
            switch ( (pNsList)->NaType )                                                                \
            {                                                                                           \
                case    CCSP_NORMALIZED_ACTION_TYPE_GPN:                                                \
                                                                                                        \
                        {                                                                               \
                            CCSP_PARAM_NAME_INFO* pInfo;                                                \
                            pInfo = &(pNsList)->Args.paramInfo;                                         \
                            if ( pInfo->parameterName )                                                 \
                                AnscFreeMemory(pInfo->parameterName);                                   \
                        }                                                                               \
                                                                                                        \
                        break;                                                                          \
            }                                                                                           \
            AnscFreeMemory(pNsList);                                                                    \
    } while (0)


typedef  struct
_CCSP_TR069PA_FC_NSLIST
{
    SINGLE_LINK_ENTRY               Linkage;
    char*                           Subsystem;          /* Subsystem name */
    char*                           FCName;             /* FC name */
    char*                           DBusPath;           /* FC DBus path */
    QUEUE_HEADER                    NsList;             /* namespace list, varied from action to action */
}
CCSP_TR069PA_FC_NSLIST, *PCCSP_TR069PA_FC_NSLIST;

#define  ACCESS_CCSP_TR069PA_FC_NSLIST(p)                                                               \
         ACCESS_CONTAINER(p, CCSP_TR069PA_FC_NSLIST, Linkage)

#define  CcspTr069PaFreeFcNsList(pFcNsList)                                                             \
    do {                                                                                                \
        PSINGLE_LINK_ENTRY          pSLinkEntry;                                                        \
        PCCSP_TR069PA_NSLIST        pNsList;                                                            \
                                                                                                        \
        if ( (pFcNsList)->Subsystem )                                                                   \
        {                                                                                               \
            AnscFreeMemory((pFcNsList)->Subsystem);                                                     \
        }                                                                                               \
                                                                                                        \
        if ( (pFcNsList)->FCName )                                                                      \
        {                                                                                               \
            AnscFreeMemory((pFcNsList)->FCName);                                                        \
        }                                                                                               \
                                                                                                        \
        if ( (pFcNsList)->DBusPath )                                                                    \
        {                                                                                               \
            AnscFreeMemory((pFcNsList)->DBusPath);                                                      \
        }                                                                                               \
                                                                                                        \
        pSLinkEntry = AnscQueuePopEntry((&((pFcNsList)->NsList)));                                      \
        while ( pSLinkEntry )                                                                           \
        {                                                                                               \
            pNsList = ACCESS_CCSP_TR069PA_NSLIST(pSLinkEntry);                                          \
            pSLinkEntry = AnscQueuePopEntry((&((pFcNsList)->NsList)));                                  \
                                                                                                        \
            CcspTr069PaFreeNsList(pNsList);                                                             \
        }                                                                                               \
        AnscFreeMemory(pFcNsList);                                                                      \
    } while (0)


#define  CcspTr069PaFreeAllFcNsList(pFcNsListQueue)                                                     \
    do {                                                                                                \
        PSINGLE_LINK_ENTRY          pSLinkEntry;                                                        \
        PCCSP_TR069PA_FC_NSLIST     pFcNsList;                                                          \
                                                                                                        \
        pSLinkEntry = AnscQueuePopEntry(pFcNsListQueue);                                                \
        while ( pSLinkEntry )                                                                           \
        {                                                                                               \
            pFcNsList = ACCESS_CCSP_TR069PA_FC_NSLIST(pSLinkEntry);                                     \
            pSLinkEntry = AnscQueuePopEntry(pFcNsListQueue);                                            \
                                                                                                        \
            CcspTr069PaFreeFcNsList(pFcNsList);                                                         \
        }                                                                                               \
    } while (0)


/**
 * @brief Find a Functional Component namespace list entry in a queue.
 *
 * This inline function searches for a CCSP_TR069PA_FC_NSLIST entry in a queue
 * that matches the specified subsystem and functional component name.
 *
 * @param[in] pFcNsListQueue  Pointer to queue header containing FC namespace list entries.
 * @param[in] pSubSystem      Pointer to subsystem name string to match.
 *                             NULL matches entries with NULL subsystem.
 * @param[in] pFcName         Pointer to functional component name string to match.
 *                             NULL matches entries with NULL FC name.
 *
 * @return Pointer to matching CCSP_TR069PA_FC_NSLIST entry.
 * @retval PCCSP_TR069PA_FC_NSLIST pointer to matching entry if found.
 * @retval NULL if no matching entry is found.
 *
 */
__inline static PCCSP_TR069PA_FC_NSLIST
CcspTr069PaFindFcNsList
    (
        PQUEUE_HEADER               pFcNsListQueue,
        char*                       pSubSystem,
        char*                       pFcName
    )
{
    PSINGLE_LINK_ENTRY          pSLinkEntry;
    PCCSP_TR069PA_FC_NSLIST     pFcNsList, pFcNsListFound;

    pFcNsListFound = NULL;

    pSLinkEntry = AnscQueueGetFirstEntry(pFcNsListQueue);
    while ( pSLinkEntry )
    {
        pFcNsList = ACCESS_CCSP_TR069PA_FC_NSLIST(pSLinkEntry);

        if (((pFcName == NULL) && (pFcNsList->FCName == NULL)) ||
            ((pFcName != NULL) && (pFcNsList->FCName != NULL) &&
             (strcmp(pFcName, pFcNsList->FCName) == 0)))
        {
            if (((pSubSystem == NULL) && (pFcNsList->Subsystem == NULL)) ||
                ((pSubSystem != NULL) && (pFcNsList->Subsystem != NULL) &&
                 (strcmp(pSubSystem, pFcNsList->Subsystem) == 0)))
            {
                pFcNsListFound = pFcNsList;
                break;
            }
        }

        pSLinkEntry = AnscQueueGetNextEntry(pSLinkEntry);
    }

    return pFcNsListFound;
}


#define  CcspTr069PaAddFcIntoFcNsList(pFcNsListQueue, pSubSystem, pFcName, pDbusPath, pFcNsList)        \
    do {                                                                                                \
        /*CcspTr069PaFindFcNsList(pFcNsListQueue, pSubSystem, pFcName, pFcNsList);*/                    \
        pFcNsList = CcspTr069PaFindFcNsList(pFcNsListQueue, pSubSystem, pFcName);                       \
                                                                                                        \
        if ( !pFcNsList )                                                                               \
        {                                                                                               \
            pFcNsList =                                                                                 \
                (PCCSP_TR069PA_FC_NSLIST)AnscAllocateMemory                                             \
                    (                                                                                   \
                        sizeof(CCSP_TR069PA_FC_NSLIST)                                                  \
                    );                                                                                  \
                                                                                                        \
            if ( pFcNsList )                                                                            \
            {                                                                                           \
                pFcNsList->Subsystem= pSubSystem ? AnscCloneString(pSubSystem) : NULL;                  \
                pFcNsList->FCName   = pFcName? AnscCloneString(pFcName) : NULL;                         \
                pFcNsList->DBusPath = pDbusPath ? AnscCloneString(pDbusPath) : NULL;                    \
                AnscQueueInitializeHeader(&pFcNsList->NsList);                                          \
                                                                                                        \
                AnscQueuePushEntry(pFcNsListQueue, &pFcNsList->Linkage);                                \
            }                                                                                           \
        }                                                                                               \
    } while (0)


/**
 * @brief Convert ISO 8601 date-time string to ANSC_UNIVERSAL_TIME structure.
 *
 * This inline function parses an ISO 8601 formatted date-time string and converts
 * it into an ANSC_UNIVERSAL_TIME structure. Supports formats like \"2001-01-01\" and
 * \"2005-09-28T18:20:41\" as recommended by RFC 3339 and W3C date/time formats.
 *
 * @param[in] calendar_time  Pointer to ISO 8601 formatted date-time string.
 *                            Expected format: \"YYYY-MM-DDTHH:MM:SS\" or \"YYYY-MM-DD\".
 *                            Must be a valid, null-terminated string.
 *
 * @return Pointer to newly allocated ANSC_UNIVERSAL_TIME structure.
 * @retval PANSC_UNIVERSAL_TIME pointer to time structure with parsed fields.
 * @retval NULL if memory allocation fails or parsing errors occur.
 *
 */
__inline static
PANSC_UNIVERSAL_TIME
CcspStringToCalendarTime
    (
        char*                       calendar_time
    )
{
    PANSC_UNIVERSAL_TIME            pUniversalTime = (PANSC_UNIVERSAL_TIME      )NULL;
    ULONG                           ulFieldIndex   = 0;
    char                            temp_char [5];

    pUniversalTime = (PANSC_UNIVERSAL_TIME)AnscAllocateMemory(sizeof(ANSC_UNIVERSAL_TIME));

    if ( !pUniversalTime )
    {
        return  (SLAP_HANDLE)NULL;
    }

    /*
     * The ISO 8601 notation is today the commonly recommended format of representing date and time
     * as human-readable strings in new plain-text communication protocols and file formats.
     * Several standards and profiles have been derived from ISO 8601, including RFC 3339 and a W3C
     * note on date and time formats.
     *
     *      - e.g. 2001-01-01
     *      - e.g. 2005-09-28T18:20:41
     */

    /*
     * Convert 'Year'...
     */
    ulFieldIndex = 0;

    if ( TRUE )
    {
        AnscZeroMemory(temp_char, 5);

        temp_char[0] = calendar_time[ulFieldIndex++];
        temp_char[1] = calendar_time[ulFieldIndex++];
        temp_char[2] = calendar_time[ulFieldIndex++];
        temp_char[3] = calendar_time[ulFieldIndex++];

        pUniversalTime->Year = (USHORT)AnscGetStringUlong(temp_char);
    }

    /*
     * Convert 'Month'...
     */
    ulFieldIndex++;

    if ( TRUE )
    {
        AnscZeroMemory(temp_char, 5);

        temp_char[0] = calendar_time[ulFieldIndex++];
        temp_char[1] = calendar_time[ulFieldIndex++];

        pUniversalTime->Month = (USHORT)AnscGetStringUlong(temp_char);
    }

    /*
     * Convert 'Day'...
     */
    ulFieldIndex++;

    if ( TRUE )
    {
        AnscZeroMemory(temp_char, 5);

        temp_char[0] = calendar_time[ulFieldIndex++];
        temp_char[1] = calendar_time[ulFieldIndex++];

        pUniversalTime->DayOfMonth = (USHORT)AnscGetStringUlong(temp_char);
    }

    /*
     * Convert 'Hour'...
     */
    ulFieldIndex++;

    if ( TRUE )
    {
        AnscZeroMemory(temp_char, 5);

        temp_char[0] = calendar_time[ulFieldIndex++];
        temp_char[1] = calendar_time[ulFieldIndex++];

        pUniversalTime->Hour = (USHORT)AnscGetStringUlong(temp_char);
    }

    /*
     * Convert 'Minute'...
     */
    ulFieldIndex++;

    if ( TRUE )
    {
        AnscZeroMemory(temp_char, 5);

        temp_char[0] = calendar_time[ulFieldIndex++];
        temp_char[1] = calendar_time[ulFieldIndex++];

        pUniversalTime->Minute = (USHORT)AnscGetStringUlong(temp_char);
    }

    /*
     * Convert 'Second'...
     */
    ulFieldIndex++;

    if ( TRUE )
    {
        AnscZeroMemory(temp_char, 5);

        temp_char[0] = calendar_time[ulFieldIndex++];
        temp_char[1] = calendar_time[ulFieldIndex++];

        pUniversalTime->Second = (USHORT)AnscGetStringUlong(temp_char);
    }

    return  pUniversalTime;
}


/**
 * @brief Convert ANSC_UNIVERSAL_TIME structure to ISO 8601 date-time string.
 *
 * This inline function converts an ANSC_UNIVERSAL_TIME structure into an
 * ISO 8601 formatted date-time string with the format \"YYYY-MM-DDTHH:MM:SSZ\".
 * The returned string is dynamically allocated and must be freed by the caller.
 *
 * @param[in] pUniversalTime  Pointer to ANSC_UNIVERSAL_TIME structure containing date/time values.
 *                             Must contain valid Year, Month, DayOfMonth, Hour, Minute, Second fields.
 *
 * @return Pointer to newly allocated ISO 8601 formatted string.
 * @retval char* pointer to formatted string on success.
 * @retval NULL if memory allocation fails.
 *
 */
__inline static
char*
CcspCalendarTimeToString
    (
        PANSC_UNIVERSAL_TIME        pUniversalTime
    )
{
    char*                           var_string     = (char*)AnscAllocateMemory(32);

    if ( !var_string )
    {
        return  NULL;
    }

    _ansc_sprintf
        (
            var_string,
            "%04d-%02d-%02dT%02d:%02d:%02dZ",
            pUniversalTime->Year,
            pUniversalTime->Month,
            pUniversalTime->DayOfMonth,
            pUniversalTime->Hour,
            pUniversalTime->Minute,
            pUniversalTime->Second
        );

    return  var_string;
}


/**
 * @brief Find first unused instance number from 1.
 *
 * This inline function searches for the first available instance number that is
 * not present in the provided array of existing instance numbers. Useful for
 * allocating new TR-069 object instances.
 *
 * @param[in] NumInstances   Number of existing instance numbers in the array.
 *                            Valid range: 0 to MaxInsNumber.
 * @param[in] pInsNumbers    Pointer to array of existing instance numbers to check against.
 *                            Can be NULL if NumInstances is 0.
 * @param[in] MaxInsNumber   Maximum allowed instance number.
 *                            Valid range: 1 to UINT_MAX.
 *
 * @return First available instance number.
 * @retval unsigned int (1 to MaxInsNumber) for first unused instance number.
 * @retval 0 if no unused instance number is available (NumInstances >= MaxInsNumber).
 * @retval 1 if no instances exist (NumInstances == 0).
 */
__inline static
unsigned int
CcspFindUnusedInsNumber
    (
        unsigned int                NumInstances,
        unsigned int*               pInsNumbers,
        unsigned int                MaxInsNumber
    )
{
    unsigned int                    InsNumber   = 1;
    unsigned int                    i;

    if ( NumInstances == 0 )
    {
        return  1;
    }
    else if ( NumInstances >= MaxInsNumber )
    {
        return  0;
    }

    while ( InsNumber != 0 )
    {
        for ( i = 0; i < NumInstances; i ++ )
        {
            if ( InsNumber == pInsNumbers[i] )
            {
                break;
            }
        }

        if ( i >= NumInstances )
        {
            return  InsNumber;
        }

        InsNumber ++;
        if ( InsNumber >= MaxInsNumber )
        {
            return 0;
        }
    }

    return  0;
}


/**
 * @brief Search for a pattern in a memory buffer.
 *
 * This inline function searches for a specified byte pattern within a memory buffer.
 * Supports both case-sensitive and case-insensitive searches for ASCII characters.
 * Used for parsing HTTP headers and other protocol messages.
 *
 * @param[in] pBuf            Pointer to memory buffer to search within.
 *                             Must point to valid memory of at least ulSize bytes.
 * @param[in] ulSize          Size of the memory buffer in bytes.
 *                             Valid range: ulPatternLen to ULONG_MAX.
 * @param[in] pPattern        Pointer to pattern to search for.
 *                             Must point to valid memory of ulPatternLen bytes.
 * @param[in] ulPatternLen    Length of the pattern in bytes.
 *                             Valid range: 1 to ulSize.
 * @param[in] bCaseSensitive  Flag indicating case sensitivity for ASCII characters.
 *                             - TRUE: Perform case-sensitive search
 *                             - FALSE: Perform case-insensitive search (ASCII only)
 *
 * @return Pointer to first occurrence of pattern in buffer.
 * @retval char* pointer to start of pattern match within pBuf.
 * @retval NULL if pattern is not found in buffer.
 *
 */
__inline static
char*
CcspMemorySearch
    (
        PUCHAR                      pBuf,
        ULONG                       ulSize,
        PUCHAR                      pPattern,
        ULONG                       ulPatternLen,
        BOOL                        bCaseSensitive
    )
{
    PUCHAR                          pBufEnd     = pBuf + ulSize - 1;
    PUCHAR                          pNext, pNext1;
    UCHAR                           fc          = *pPattern;
    UCHAR                           fc1         = 0;

    if ( fc >= 'a' && fc <= 'z')
    {
        fc1 = fc - 'a' + 'A';
    }
    else if ( fc >= 'A' && fc <= 'Z' )
    {
        fc1 = fc - 'A' + 'a';
    }

    pNext1 = NULL;

    while ( pBuf && pBuf <= pBufEnd )
    {
        pNext = _ansc_memchr(pBuf, fc, pBufEnd - pBuf + 1);
        if ( fc1 != 0 )
        {
            pNext1 = _ansc_memchr(pBuf, fc, pBufEnd - pBuf + 1);
        }

        if ( !pNext )
        {
            pNext = pNext1;
        }
        else if ( pNext1 && pNext1 < pNext )
        {
            pNext = pNext1;
        }

        if ( !pNext )
        {
            return  NULL;
        }

        if ( pBufEnd - pNext + 1ul >= ulPatternLen &&
             AnscEqualString2((char*)pNext, (char*)pPattern, ulPatternLen, bCaseSensitive) )
        {
            return  (char*)pNext;
        }

        pBuf = pNext + 1;
    }

    return  NULL;
}


/**
 * @brief Prefix a PSM (Persistent Storage Manager) key with subsystem prefix.
 *
 * This inline function constructs a complete PSM key by prepending a subsystem
 * prefix to a base PSM key. If no prefix is provided, the base key is copied
 * unchanged. The caller must ensure the output buffer is large enough.
 *
 * @param[out] pPsmKeyWithPrefix  Pointer to output buffer for prefixed PSM key.
 *                                 Must be pre-allocated with sufficient size.
 * @param[in]  pSubsysPrefix      Pointer to subsystem prefix string to prepend.
 *                                 NULL or empty string results in no prefix.
 * @param[in]  psmKey              Pointer to base PSM key string.
 *                                 Must be a valid, null-terminated string.
 *
 * @return None.
 *
 */
__inline static
void
CcspCwmpPrefixPsmKey
    (
        char*                       pPsmKeyWithPrefix,
        char*                       pSubsysPrefix,
        char*                       psmKey

    )
{
    /* we don't check buffer size, caller should make sure the buffer is big enough */

    if ( pSubsysPrefix && AnscSizeOfString(pSubsysPrefix) > 0 )
    {
        _ansc_sprintf(pPsmKeyWithPrefix, "%s%s", pSubsysPrefix, psmKey);
    }
    else
    {
        AnscCopyString(pPsmKeyWithPrefix, psmKey);
    }
}


#endif
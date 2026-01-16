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

#ifndef  _CCSP_TR069PA_SSP_DEF_
#define  _CCSP_TR069PA_SSP_DEF_

#include <time.h>

#include "ansc_platform.h"
#include "ansc_string.h"

#include "ccsp_cwmp_cpeco_interface.h"
#include "ccsp_cwmp_cpeco_exported_api.h"

#include "ccsp_cwmp_proco_interface.h"
#include "ccsp_cwmp_proco_exported_api.h"

#ifdef   _CCSP_CWMP_TCP_CONNREQ_HANDLER
#include "ccsp_cwmp_tcpcrho_interface.h"
#include "ccsp_cwmp_tcpcrho_exported_api.h"
#endif

#include "web_ifo_acm.h"

#include "ccsp_cwmp_ifo_mso.h"
#include "ccsp_cwmp_ifo_cfg.h"
#include "ccsp_cwmp_ifo_sta.h"
#include "ccsp_cwmp_ifo_mpa.h"

#include "ssp_web_acm.h"

#include "ssp_ccsp_cwmp_cfg.h"


#include "ccsp_management_server_pa_api.h"
#include "ccsp_tr069pa_wrapper_api.h"
#include "ccsp_base_api.h"
#include "ccsp_trace.h"

#include "dslh_dmagnt_interface.h"

/*
 *  Define custom trace module ID
 */
#ifdef   ANSC_TRACE_MODULE_ID
    #undef  ANSC_TRACE_MODULE_ID
#endif

#define  ANSC_TRACE_MODULE_ID                       ANSC_TRACE_ID_SSP

/**
 * @brief Dispatches TR-069 PA SSP commands for interactive control and testing.
 *
 * This function processes single-character command codes to control the TR-069 PA SSP
 * operation and invoke test/debug functions.
 *
 * @param[in] command  Single character command code.
 *
 * @return The status of the command execution.
 * @retval 0  Command executed successfully.
 *
 */
int  cmd_dispatch(int  command);

/**
 * @brief Initializes the TR-069 PA SSP interfaces.
 *
 * This function initializes the various interfaces required by the TR-069 PA SSP including
 * the CCSP CWMP configuration interface and web ACM interface.
 *
 * @return The status of the initialization.
 * @retval 0  Interfaces initialized successfully.
 *
 */
int  init_interfaces();

/**
 * @brief Engages and starts the TR-069 Protocol Agent.
 *
 * This function loads the TR-069 PA configuration file, initializes the CCSP CWMP configuration
 * and web ACM interfaces, creates and configures the CCSP CWMP CPE Controller object, and
 * engages all TR-069 PA components.
 *
 * @return The status of the engagement operation.
 * @retval 0  TR-069 PA successfully engaged and started.
 *
 */
int  engage_tr069pa();

/**
 * @brief Cancels and stops the TR-069 Protocol Agent.
 *
 * This function disengages the TR-069 PA by canceling and removing the CCSP CWMP CPE Controller
 * object, freeing the DSLH data model agent resources, and resetting the engagement flag.
 *
 * @return The status of the cancellation operation.
 * @retval 0  TR-069 PA successfully canceled and stopped.
 *
 */
int  cancel_tr069pa();


/* some unit test functions */
#ifdef   _DEBUG
#include "ccsp_types.h"
#include "ccsp_tr069pa_mapper_api.h"
#include "slap_definitions.h"
#include "slap_vho_exported_api.h"
#include "ccsp_cwmp_helper_api.h"

/**
 * @brief Dumps the TR-069 PA parameter information tree for debugging.
 *
 * This debug function traverses and prints both the visible and invisible parameter information
 * trees to the console.
 *
 * @return None.
 *
 */
void ssp_dumpPiTree();

/**
 * @brief Simulates reception of systemReady signal for testing namespace synchronization.
 *
 * This external function is used for testing purposes to simulate the reception of a systemReady
 * signal from the CCSP message bus. It triggers the TR-069 PA to synchronize namespaces with
 * the Component Registrar and update the parameter information tree.
 *
 * @param[in] user_data  User-provided context data.
 *
 * @return None.
 *
 */
extern void CcspCwmppoSysReadySignalCB(void* user_data); /* for simulating reception of systemReady signal */

/**
 * @brief Processes the systemReady signal to synchronize namespaces with Component Registrar.
 *
 * This function handles the systemReady signal by querying the Component Registrar for all
 * registered CCSP components and their supported namespaces, then updating the TR-069 PA's
 * parameter information tree accordingly.
 *
 * @param[in] cbContext  Callback context pointer.
 *
 * @return None.
 *
 */
extern void CcspCwmppoProcessSysReadySignal (void*	cbContext);

/**
 * @brief Tests namespace synchronization with Component Registrar.
 *
 * This debug function simulates the systemReady signal reception to test the TR-069 PA's
 * namespace synchronization mechanism with the CCSP Component Registrar.
 *
 * @return None.
 *
 */
void ssp_testNsSyncWithCR();

/**
 * @brief Tests namespace support against the mapper file configuration.
 *
 * This debug function prompts the user to input a namespace and subsystem name, then queries
 * the TR-069 PA mapper to check if the namespace is supported and whether it's visible or
 * invisible to the ACS.
 *
 * @return None.
 *
 */
void ssp_testNsAgainstMapper();

/**
 * @brief Tests the TR-069 GetParameterNames RPC method.
 *
 * This debug function prompts the user to input a namespace and next-level flag, then invokes
 * the CCSP CWMP MPA interface GetParameterNames method to retrieve parameter information.
 * It displays the parameter names, writable flags, and counts returned by the operation.
 * This is useful for testing GPN functionality and parameter discovery.
 *
 * @return None.
 *
 */
void ssp_testGPN();
/**
 * @brief Tests the TR-069 GetParameterValues RPC method.
 *
 * This debug function prompts the user to input parameter names, then invokes the CCSP CWMP
 * MPA interface GetParameterValues method to retrieve parameter values. It displays the
 * parameter names, values, and data types returned by the operation. This is useful for
 * testing GPV functionality and parameter value retrieval.
 *
 * @return None.
 *
 */
void ssp_testGPV();

/**
 * @brief Tests the TR-069 SetParameterValues RPC method.
 *
 * This debug function prompts the user to input parameter name-value pairs, then invokes
 * the CCSP CWMP MPA interface SetParameterValues method to modify parameter values.
 * It displays the operation status and any faults returned. This is useful for testing
 * SPV functionality and parameter value modification.
 *
 * @return None.
 *
 */
void ssp_testSPV();

/**
 * @brief Tests the TR-069 GetParameterAttributes RPC method.
 *
 * This debug function prompts the user to input parameter names, then invokes the CCSP CWMP
 * MPA interface GetParameterAttributes method to retrieve parameter attributes including
 * notification settings and access control. It displays the parameter names, notification
 * values, and access lists returned. This is useful for testing GPA functionality.
 *
 * @return None.
 *
 */
void ssp_testGPA();

/**
 * @brief Tests the TR-069 SetParameterAttributes RPC method.
 *
 * This debug function prompts the user to input parameter names and attribute values, then
 * invokes the CCSP CWMP MPA interface SetParameterAttributes method to modify parameter
 * attributes such as notification settings. It displays the operation status and any faults
 * returned. This is useful for testing SPA functionality.
 *
 * @return None.
 *
 */
void ssp_testSPA();

/**
 * @brief Tests the TR-069 ChangeDUState RPC method.
 *
 * This debug function tests the ChangeDUState RPC method used for Deployment Unit (DU)
 * state management in TR-069 Amendment 3. It allows testing of DU installation, update,
 * and uninstallation operations. This is useful for validating ChangeDUState implementation.
 *
 * @return None.
 *
 */
void ssp_testCDS();

/**
 * @brief Tests TR-069 firmware download functionality.
 *
 * This debug function tests the firmware download capability of the TR-069 PA by simulating
 * a Download RPC with firmware file type. It allows validation of firmware download, storage,
 * and installation procedures.
 *
 * @return None.
 *
 */
void ssp_testFirmwareDownload();

/**
 * @brief Tests retrieval of supported TR-069 RPC methods.
 *
 * This debug function tests the GetRPCMethods functionality to retrieve the list of TR-069
 * RPC methods supported by the CPE. It displays all supported method names reported by the
 * TR-069 PA.
 *
 * @return None
 *
 */
void ssp_testGetMethods();

/**
 * @brief Tests the TR-069 AddObject RPC method.
 *
 * This debug function prompts the user to input an object path, then invokes the CCSP CWMP
 * MPA interface AddObject method to create a new object instance in a multi-instance table.
 * It displays the new instance number and operation status. This is useful for testing
 * AddObject functionality and dynamic object creation.
 *
 * @return None.
 *
 */
void ssp_testAddObject();

/**
 * @brief Tests the TR-069 DeleteObject RPC method.
 *
 * This debug function prompts the user to input an object instance path, then invokes the
 * CCSP CWMP MPA interface DeleteObject method to remove the object instance from a
 * multi-instance table. It displays the operation status and any faults returned. This is
 * useful for testing DeleteObject functionality.
 *
 * @return None.
 *
 */
void ssp_testDeleteObject();

/**
 * @brief Tests SetParameterValues operation not originating from the TR-069 PA.
 *
 * This debug function tests the SetParameterValues functionality when invoked from a source
 * other than the TR-069 PA. It validates that parameter value changes work correctly regardless
 * of the originating component.
 *
 * @return None.
 *
 */
void ssp_testSPV_notFromPA();

/**
 * @brief Sets the logging level for TR-069 PA components.
 *
 * This debug function prompts the user to select a logging level and updates the trace level
 * for TR-069 PA components. This allows dynamic log level adjustment for debugging purposes.
 *
 * @return None.
 *
 */
void ssp_setLogLevel();

/**
 * @brief Checks cached parameter attributes in the TR-069 PA.
 *
 * This debug function retrieves and displays the cached parameter attributes maintained by
 * the TR-069 PA, including notification settings and access control lists. This is useful
 * for debugging attribute caching mechanisms and verifying attribute synchronization.
 *
 * @return None.
 *
 */
void ssp_checkCachedParamAttr();

/**
 * @brief Toggles the invisible namespace check flag.
 *
 * This debug function flips the flag that controls whether invisible namespaces are checked
 * during parameter operations. This allows testing parameter access with and without invisible
 * namespace filtering enabled.
 *
 * @return None.
 *
 */
void ssp_flipInvNamespaceChkFlag();

/**
 * @brief Sends a parameter value change signal for testing.
 *
 * This debug function simulates sending a CCSP parameter value change signal to test the
 * TR-069 PA's value change notification mechanism. It allows validation of active notification
 * handling and Inform message generation for parameter value changes.
 *
 * @return None.
 *
 */
void ssp_sendValueChangeSignal();

/**
 * @brief Sends a diagnostics complete signal for testing.
 *
 * This debug function simulates sending a CCSP diagnostics complete signal to test the
 * TR-069 PA's diagnostics completion notification mechanism. It allows validation of
 * DiagnosticsComplete event handling and Inform message generation.
 *
 * @return None.
 *
 */
void ssp_sendDiagCompleteSignal();
#endif

#endif /* _CCSP_TR069PA_SSP_DEF_ */
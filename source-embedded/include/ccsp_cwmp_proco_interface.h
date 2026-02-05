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

    module:	ccsp_cwmp_proco_interface.h

        For CCSP CWMP protocol implemenation

    ---------------------------------------------------------------

    description:

        This wrapper file defines all the platform-independent
        functions and macros for the CCSP CWMP Processor Object.

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
        04/25/11    decouple TR-069 PA from Data Model Manager
                    and make it work with CCSP COSA 2.0 CDMMM.
        10/12/11    resolve name conflicts with DM library.

**********************************************************************/


#ifndef  _CCSP_CWMP_PROCO_INTERFACE_
#define  _CCSP_CWMP_PROCO_INTERFACE_


/*
 * This object is derived a virtual base object defined by the underlying framework. We include the
 * interface header files of the base object here to shield other objects from knowing the derived
 * relationship between this object and its base class.
 */
#include "ansc_co_interface.h"
#include "ansc_co_external_api.h"
#include "ccsp_cwmp_properties.h"

#include "ccsp_cwmp_ifo_mco.h"
#include "ccsp_management_server_pa_api.h"

/***********************************************************
        CCSP CWMP WMP PROCESSOR COMPONENT OBJECT DEFINITION
***********************************************************/

/*
 * Define some const values that will be used in the object mapper object definition.
 */
#define  CCSP_CWMPPO_DEF_INFORM_INTERVAL                24 * 3600 * 1000    /* in milli-seconds */
#define  CCSP_CWMPPO_DEF_INFORM_DELAY                   30 * 1000           /* in milli-seconds */
#define  CCSP_CWMPPO_DEF_PENDING_INFORM_DELAY           5 * 1000            /* in milli-seconds */

#define  CCSP_CWMPPO_REMOTE_CR_RESYNC_INTERVAL          30                  /* in seconds */

/*
 * Since we write all kernel modules in C (due to better performance and lack of compiler support),
 * we have to simulate the C++ object by encapsulating a set of functions inside a data structure.
 */
/**
 * @brief Get a context handle from the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for retrieving context handles
 * from the CWMP Processor. Used to get handles to associated objects such as the CPE Controller
 * or other internal components.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return Handle to the requested context object
 * @retval Handle to the requested context object on success.
 * @retval NULL if not available.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPPROCO_GET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set a context handle in the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for setting context handles
 * in the CWMP Processor. Used to associate handles to related objects such as the CPE Controller
 * or other internal components.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] hContext     - Handle to the context object to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Context handle set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SET_CONTEXT)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hContext
    );

/**
 * @brief Get an interface handle from the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for retrieving interface handles
 * from the CWMP Processor. Used to get handles to interface objects such as MPA interface.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return Handle to the requested interface object.
 * @retval Handle to the requested interface object on success.
 * @retval NULL if not available.
 */
typedef  ANSC_HANDLE
(*PFN_CWMPPROCO_GET_IF)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set an interface handle in the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for setting interface handles
 * in the CWMP Processor. Used to associate interface objects with the processor.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] hInterface   - Handle to the interface object to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Interface handle set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SET_IF)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hInterface
    );

/**
 * @brief Get a string value from the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for retrieving string values
 * from the CWMP Processor configuration. Used to get values such as ACS URL, username, password,
 * or other string-based configuration parameters.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return Pointer to the string value
 * @retval Non-NULL pointer to the string value on success.
 * @retval NULL if not available.
 *
 */
typedef  char*
(*PFN_CWMPPROCO_GET_STRING)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set a string value in the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for setting string values
 * in the CWMP Processor configuration. Used to set values such as ACS URL, username, password,
 * or other string-based configuration parameters.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] pString      - Pointer to the string value to set. The processor makes a copy of the string.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - String value set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SET_STRING)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pString
    );

/**
 * @brief Set a string value with DHCP acquisition flag in the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for setting string values with an
 * additional flag indicating whether the value was acquired from DHCP. Typically used for setting
 * the ACS URL with DHCP acquisition status.
 *
 * @param[in] hThisObject        - Handle to the CWMP Processor object instance.
 * @param[in] pString            - Pointer to the string value to set. The processor makes a copy of the string.
 * @param[in] bAcquiredFromDhcp  - Boolean flag indicating if the value was acquired from DHCP.
 *                                  \n TRUE = Acquired from DHCP, FALSE = Manually configured or from other source.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - String value set successfully with DHCP flag.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SET_STRING2)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pString,
        BOOL                        bAcquiredFromDhcp
    );

/**
 * @brief Get a boolean value from the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for retrieving boolean values
 * from the CWMP Processor configuration. Used to get values such as InitialContact flag,
 * PeriodicInformEnabled, or CWMP enabled status.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The boolean value.
 * @retval TRUE  - Feature is enabled or flag is set.
 * @retval FALSE - Feature is disabled or flag is not set.
 *
 */
typedef  BOOL
(*PFN_CWMPPROCO_GET_BOOL)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set a boolean value in the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for setting boolean values
 * in the CWMP Processor configuration. Used to set values such as InitialContact flag,
 * PeriodicInformEnabled, or other boolean configuration parameters.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] bEnabled     - Boolean value to set.
 *                            \n TRUE = Enable feature or set flag, FALSE = Disable feature or clear flag.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Boolean value set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SET_BOOL)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bEnabled
    );

/**
 * @brief Get an unsigned long value from the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for retrieving unsigned long values
 * from the CWMP Processor configuration. Used to get values such as PeriodicInformInterval (in seconds),
 * session counts, or other numeric configuration parameters.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The unsigned long value.
 *
 */
typedef  ULONG
(*PFN_CWMPPROCO_GET_ULONG)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set an unsigned long value in the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for setting unsigned long values
 * in the CWMP Processor configuration. Used to set values such as PeriodicInformInterval (in seconds),
 * timeouts, or other numeric configuration parameters.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] ulValue      - Unsigned long value to set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Unsigned long value set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SET_ULONG)
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulValue
    );

/**
 * @brief Get a handle value from the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for retrieving handle values
 * from the CWMP Processor. Used to get handles such as PeriodicInformTime (ANSC_UNIVERSAL_TIME)
 * or other time-based handles.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return Handle to the requested value
 * @retval Handle to the requested value on success.
 * @retval NULL if not available.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPPROCO_GET_HANDLE)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Set a handle value in the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for setting handle values
 * in the CWMP Processor. Used to set handles such as PeriodicInformTime (ANSC_UNIVERSAL_TIME)
 * or other time-based handles.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] hTime        - Handle to the time structure or other handle value to set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Handle value set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SET_HANDLE)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hTime
    );

/**
 * @brief Get the property configuration from the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for retrieving the entire
 * property configuration structure from the CWMP Processor. The properties include all
 * TR-069 Management Server settings such as ACS URL, credentials, periodic inform settings,
 * and other configuration parameters.
 *
 * @param[in]  hThisObject  - Handle to the CWMP Processor object instance.
 * @param[out] hProperty    - Handle to the property structure (CCSP_CWMP_PROCESSOR_PROPERTY)
 *                             to be filled with current property values.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Property configuration retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_GET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Set the property configuration in the CWMP Processor object.
 *
 * This function pointer typedef defines the callback interface for setting the entire
 * property configuration structure in the CWMP Processor. The properties include all
 * TR-069 Management Server settings such as ACS URL, credentials, periodic inform settings,
 * and other configuration parameters. This typically updates internal state and may trigger
 * reconfiguration of timers or connections.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] hProperty    - Handle to the property structure (CCSP_CWMP_PROCESSOR_PROPERTY)
 *                            containing the new property values to be set.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Property configuration set successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SET_PROPERTY)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hProperty
    );

/**
 * @brief Reset the CWMP Processor object to default state.
 *
 * This function pointer typedef defines the callback interface for resetting the CWMP Processor
 * object. This operation resets properties to default values, clears session state, and prepares
 * the processor for clean reinitialization. Used for ResetProperty or Reset operations.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Processor reset successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_RESET)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Engage the CWMP Processor to start active operation.
 *
 * This function pointer typedef defines the callback interface for engaging the CWMP Processor
 * and starting active operation. This includes initializing timers (periodic inform, schedule,
 * pending inform), setting up the runtime environment, and starting TR-069 protocol operations.
 * The bRestart flag indicates whether this is a restart after previous cancellation.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] bRestart     - Boolean flag indicating if this is a restart operation.
 *                            \n TRUE = Restarting after previous Cancel, FALSE = Initial engagement.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Processor engaged successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_ENGAGE)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bRestart
    );

/**
 * @brief Cancel active operation of the CWMP Processor.
 *
 * This function pointer typedef defines the callback interface for canceling the CWMP Processor's
 * active operation. This stops all timers, terminates active sessions, and brings the processor
 * to an inactive state. Typically called before system shutdown or reconfiguration.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Processor canceled successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_CANCEL)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Setup the runtime environment for the CWMP Processor.
 *
 * This function pointer typedef defines the callback interface for setting up the CWMP Processor's
 * runtime environment. This includes initializing internal data structures, creating timer objects,
 * loading persistent configuration and event data, and preparing for active operation. The bRestart
 * flag indicates whether this is environment setup after a restart.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] bRestart     - Boolean flag indicating if this is a restart operation.
 *                            \n TRUE = Setting up after restart, FALSE = Initial environment setup.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Environment setup successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SETUP_ENV)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bRestart
    );

/**
 * @brief Close the runtime environment of the CWMP Processor.
 *
 * This function pointer typedef defines the callback interface for closing the CWMP Processor's
 * runtime environment. This includes destroying timer objects, cleaning up internal data structures,
 * persisting necessary state, and releasing allocated resources. Typically called during shutdown
 * or before reconfiguration.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Environment closed successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_CLOSE_ENV)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Invoke a timer callback in the CWMP Processor.
 *
 * This function pointer typedef defines the callback interface for timer invocation operations.
 * Used for periodic inform timer callbacks (PeriodicTimerInvoke), schedule timer callbacks
 * (ScheduleTimerInvoke), and pending inform timer callbacks (PendingInformTimerInvoke).
 * When invoked, triggers the corresponding timer action such as initiating an Inform session.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Timer callback invoked successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_INVOKE)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Acquire a WMP Session object from the CWMP Processor.
 *
 * This function pointer typedef defines the callback interface for acquiring (creating or retrieving)
 * a WMP (Web Management Protocol) Session object. The session manages a single TR-069 session with
 * the ACS, including SOAP message exchange, RPC method handling, and connection state. This is the
 * primary variant used for standard session acquisition.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return Handle to the acquired WMP Session object.
 * @retval Handle to the acquired WMP Session object on success.
 * @retval NULL if acquisition failed.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPPROCO_ACQ_WMPSO)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Acquire a WMP Session object with alternate parameters (variant 2).
 *
 * This function pointer typedef defines an alternate callback interface for acquiring a WMP Session
 * object. This variant may support different acquisition strategies, priorities, or session types
 * compared to the primary AcqWmpSession function.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return Handle to the acquired WMP Session object
 * @retval Handle to the acquired WMP Session object on success.
 * @retval NULL if acquisition failed.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPPROCO_ACQ_WMPSO2)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Acquire a WMP Session object with alternate parameters (variant 3).
 *
 * This function pointer typedef defines a third variant callback interface for acquiring a WMP
 * Session object. This variant may support additional acquisition strategies or special-purpose
 * session types compared to the primary and secondary variants.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return Handle to the acquired WMP Session object
 * @return Handle to the acquired WMP Session object on success.
 * @retval NULL if acquisition failed.
 *
 */
typedef  ANSC_HANDLE
(*PFN_CWMPPROCO_ACQ_WMPSO3)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Release a WMP Session object back to the CWMP Processor.
 *
 * This function pointer typedef defines the callback interface for releasing a WMP Session object.
 * When a TR-069 session completes (successfully or with errors), the session is released back to
 * the processor. The session may be reused for future TR-069 communications or destroyed based on
 * resource management policies.
 *
 * @param[in] hThisObject   - Handle to the CWMP Processor object instance.
 * @param[in] hWmpSession   - Handle to the WMP Session object to be released.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Session released successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_REL_WMPSO)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
 * @brief Delete a WMP Session object from the CWMP Processor.
 *
 * This function pointer typedef defines the callback interface for deleting a WMP Session object.
 * Unlike release, delete permanently destroys the session
 * and frees all associated resources. Typically called when a session becomes invalid or during
 * cleanup operations.
 *
 * @param[in] hThisObject   - Handle to the CWMP Processor object instance.
 * @param[in] hWmpSession   - Handle to the WMP Session object to be deleted.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Session deleted successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_DEL_WMPSO)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
 * @brief Delete all WMP Session objects from the CWMP Processor.
 *
 * This function pointer typedef defines the callback interface for deleting all active WMP Session
 * objects. This bulk deletion operation destroys all TR-069 sessions and frees all session-related
 * resources. Typically called during processor shutdown, reconfiguration, or error recovery.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - All sessions deleted successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_DEL_ALL)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Configure the periodic inform mechanism in the CWMP Processor.
 *
 * This function pointer typedef defines the callback interface for configuring the periodic inform
 * timer based on current settings (PeriodicInformEnabled, PeriodicInformInterval, PeriodicInformTime).
 * This reconfigures or starts the periodic inform timer to send Inform RPCs to the ACS at regular
 * intervals as specified in the TR-069 ManagementServer.PeriodicInformInterval parameter.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Periodic inform configured successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_CONFIG_PER)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Schedule an Inform RPC to be sent after a specified delay.
 *
 * This function pointer typedef defines the callback interface for scheduling a one-time Inform
 * RPC to be sent to the ACS after the specified delay. Typically used in response to ScheduleInform
 * RPC from the ACS, which requests the CPE to initiate a session at a specific future time.
 * The CommandKey parameter identifies this scheduled inform request.
 *
 * @param[in] hThisObject     - Handle to the CWMP Processor object instance.
 * @param[in] ulDelaySeconds  - Delay in seconds before sending the Inform RPC. Valid range: 0 to MAX_ULONG.
 *                               \n 0 = Send immediately, positive value = Delay for specified seconds.
 * @param[in] pCommandKey     - Command key string associated with this scheduled inform request.
 *                               Returned in the Inform RPC to identify the request.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Inform scheduled successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SCHEDULE)
    (
        ANSC_HANDLE                 hThisObject,
        ULONG                       ulDelaySeconds,
        char*                       pCommandKey
    );

/**
 * @brief Signal a WMP Session to proceed with its operation.
 *
 * This function pointer typedef defines the callback interface for signaling a WMP Session object
 * to proceed with its TR-069 session operation. This may be used to notify a waiting session that
 * required resources or conditions are available, allowing the session to continue processing.
 *
 * @param[in] hThisObject   - Handle to the CWMP Processor object instance.
 * @param[in] hWmpSession   - Handle to the WMP Session object to be signaled.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Session signaled successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SIGNAL)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
 * @brief Execute asynchronous connection task to the ACS.
 *
 * This function pointer typedef defines the callback interface for initiating an asynchronous
 * connection task to the ACS. This task runs in the background and establishes a TR-069 session
 * with the ACS, typically triggered by events requiring immediate CPE-to-ACS communication such
 * as connection requests, value change notifications, or bootstrap operations.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Async connection task initiated successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_ASYNC_CONNECT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Retrieve ACS information from external sources.
 *
 * This function pointer typedef defines the callback interface for retrieving ACS configuration
 * information from external sources such as DHCP (Option 43/125), DNS, or configuration files.
 * This operation populates the ACS URL, username, and other connection parameters if they are not
 * already configured or need to be refreshed.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - ACS information retrieved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_GET_INFO)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Save a TransferComplete event for later delivery to the ACS.
 *
 * This function pointer typedef defines the callback interface for saving a TransferComplete event
 * when it cannot be immediately delivered to the ACS. The event is persisted to non-volatile storage
 * and will be redelivered in the next successful Inform session. Used for both Download and Upload
 * operations as specified in TR-069.
 *
 * @param[in] hThisObject    - Handle to the CWMP Processor object instance.
 * @param[in] pCommandKey    - Command key string that identifies the Download or Upload RPC request.
 * @param[in] hStartTime     - Handle to ANSC_UNIVERSAL_TIME structure containing the transfer start time.
 * @param[in] hCompleteTime  - Handle to ANSC_UNIVERSAL_TIME structure containing the transfer completion time.
 * @param[in] bIsDownload    - Boolean flag indicating the transfer direction.
 *                              \n TRUE = Download operation, FALSE = Upload operation.
 * @param[in] pFault         - Pointer to CCSP_CWMP_FAULT structure containing fault information if the
 *                              transfer failed, or NULL if the transfer completed successfully.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - TransferComplete event saved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SAVE_TC)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pCommandKey,
        ANSC_HANDLE                 hStartTime,
        ANSC_HANDLE                 hCompleteTime,
        BOOL                        bIsDownload,
        PCCSP_CWMP_FAULT            pFault
    );

/**
 * @brief Save a ValueChange event for later delivery to the ACS.
 *
 * This function pointer typedef defines the callback interface for saving a ValueChange event
 * when a parameter configured with active notification changes value but cannot be immediately
 * reported to the ACS. The event is persisted to non-volatile storage and will be included in
 * the next Inform session with "4 VALUE CHANGE" event code.
 *
 * @param[in] hThisObject    - Handle to the CWMP Processor object instance.
 * @param[in] pParameterName - Parameter name (full path) of the parameter that changed value.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - ValueChange event saved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SAVE_VC)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParameterName
    );

/**
 * @brief Discard a specific ValueChange event.
 *
 * This function pointer typedef defines the callback interface for discarding a saved ValueChange
 * event for a specific parameter. This removes the event from persistent storage, typically called
 * after the event has been successfully delivered to the ACS or when the notification attribute
 * for the parameter has been changed to passive.
 *
 * @param[in] hThisObject    - Handle to the CWMP Processor object instance.
 * @param[in] pParameterName - Parameter name (full path) of the ValueChange event to discard.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - ValueChange event discarded successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_DSC_VC)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParameterName
    );

/**
 * @brief Load all saved ValueChange events from persistent storage.
 *
 * This function pointer typedef defines the callback interface for loading all saved ValueChange
 * events from non-volatile storage. Typically called during processor initialization or when
 * preparing an Inform RPC to include all pending VALUE CHANGE event codes.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - ValueChange events loaded successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_LOAD_VC)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Remove a specific TransferComplete event from persistent storage.
 *
 * This function pointer typedef defines the callback interface for removing a saved TransferComplete
 * event from persistent storage. Typically called after the event has been successfully delivered to
 * the ACS in an Inform RPC or when the event needs to be canceled.
 *
 * @param[in] hThisObject   - Handle to the CWMP Processor object instance.
 * @param[in] bIsDownload   - Boolean flag indicating the transfer direction.
 *                             \n TRUE = Download operation, FALSE = Upload operation.
 * @param[in] pCommandKey   - Command key string that identifies the Download or Upload RPC request.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - TransferComplete event removed successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_REMOVE_TC)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bIsDownload,
        char*                       pCommandKey
    );

/**
 * @brief Load all saved TransferComplete events from persistent storage.
 *
 * This function pointer typedef defines the callback interface for loading all saved TransferComplete
 * events (both Download and Upload) from non-volatile storage. Typically called during processor
 * initialization or when preparing an Inform RPC to include all pending TRANSFER COMPLETE event codes.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - TransferComplete events loaded successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_LOAD_TC)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Save an AutonomousTransferComplete event for later delivery to the ACS.
 *
 * This function pointer typedef defines the callback interface for saving an AutonomousTransferComplete
 * event when it cannot be immediately delivered to the ACS. This event type reports file transfers
 * initiated by the CPE autonomously (not by ACS Download/Upload RPCs), as specified in TR-069 Amendment 3.
 * The event is persisted to non-volatile storage and will be included in the next successful Inform session.
 *
 * @param[in] hThisObject      - Handle to the CWMP Processor object instance.
 * @param[in] bIsDownload      - Boolean flag indicating the transfer direction.
 *                                \n TRUE = Autonomous download, FALSE = Autonomous upload.
 * @param[in] AnnounceURL      - URL to which the CPE sent the TransferComplete notification.
 * @param[in] TransferURL      - URL from which the file was downloaded or to which it was uploaded.
 * @param[in] FileType         - Type identifier of the transferred file (e.g., firmware image type).
 * @param[in] FileSize         - Size of the transferred file in bytes.
 * @param[in] TargetFileName   - Name of the file on the CPE after the transfer.
 * @param[in] hFault           - Handle to CCSP_CWMP_FAULT structure containing fault information if the
 *                                transfer failed, or NULL if the transfer completed successfully.
 * @param[in] hStartTime       - Handle to ANSC_UNIVERSAL_TIME structure containing the transfer start time.
 * @param[in] hCompleteTime    - Handle to ANSC_UNIVERSAL_TIME structure containing the transfer completion time.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - AutonomousTransferComplete event saved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SAVE_ATC)
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
        ANSC_HANDLE                 hCompleteTime
    );

/**
 * @brief Load all saved AutonomousTransferComplete events from persistent storage.
 *
 * This function pointer typedef defines the callback interface for loading all saved
 * AutonomousTransferComplete events from non-volatile storage. Typically called during processor
 * initialization or when preparing an Inform RPC to include all pending AUTONOMOUS TRANSFER COMPLETE
 * event codes.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - AutonomousTransferComplete events loaded successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_LOAD_ATC)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Save a DUStateChangeComplete event for later delivery to the ACS.
 *
 * This function pointer typedef defines the callback interface for saving a DUStateChangeComplete
 * event when it cannot be immediately delivered to the ACS. This event type reports software module
 * (Deployment Unit) state changes initiated by ACS ChangeDUState RPC, as specified in TR-069 Amendment 2.
 * The event is persisted to non-volatile storage and will be included in the next successful Inform session.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] hDsccReq     - Handle to the DUStateChangeComplete request structure containing operation
 *                            results, command key, and deployment unit state change information.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - DUStateChangeComplete event saved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SAVE_DSCC)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hDsccReq
    );

/**
 * @brief Load all saved DUStateChangeComplete events from persistent storage.
 *
 * This function pointer typedef defines the callback interface for loading all saved
 * DUStateChangeComplete events from non-volatile storage. Typically called during processor
 * initialization or when preparing an Inform RPC to include all pending DU STATE CHANGE COMPLETE
 * event codes.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - DUStateChangeComplete events loaded successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_LOAD_DSCC)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Save an AutonomousDUStateChangeComplete event for later delivery to the ACS.
 *
 * This function pointer typedef defines the callback interface for saving an AutonomousDUStateChangeComplete
 * event when it cannot be immediately delivered to the ACS. This event type reports software module state
 * changes initiated autonomously by the CPE (not by ACS ChangeDUState RPC), as specified in TR-069 Amendment 2.
 * The event is persisted to non-volatile storage and will be included in the next successful Inform session.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] hAdsccReq    - Handle to the AutonomousDUStateChangeComplete request structure containing
 *                            operation results and deployment unit autonomous state change information.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - AutonomousDUStateChangeComplete event saved successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SAVE_ADSCC)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hAdsccReq
    );

/**
 * @brief Load all saved AutonomousDUStateChangeComplete events from persistent storage.
 *
 * This function pointer typedef defines the callback interface for loading all saved
 * AutonomousDUStateChangeComplete events from non-volatile storage. Typically called during processor
 * initialization or when preparing an Inform RPC to include all pending AUTONOMOUS DU STATE CHANGE COMPLETE
 * event codes.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - AutonomousDUStateChangeComplete events loaded successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_LOAD_ADSCC)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Redeliver all undelivered events to the ACS.
 *
 * This function pointer typedef defines the callback interface for redelivering all undelivered
 * events (TransferComplete, AutonomousTransferComplete, DUStateChangeComplete, AutonomousDUStateChangeComplete,
 * ValueChange) that were previously saved to persistent storage. Typically called during processor initialization
 * or when reestablishing communication with the ACS after a connection failure.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Events redelivered successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_REDELIVER_EVT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Get undelivered events and populate a WMP Session.
 *
 * This function pointer typedef defines the callback interface for retrieving all undelivered
 * events and populating them into a WMP Session object for inclusion in the next Inform RPC.
 * This loads events from persistent storage and prepares them for delivery to the ACS.
 * Used by GetUndeliveredEvents, GetUndeliveredTcEvents, GetUndeliveredAtcEvents,
 * GetUndeliveredDscEvents, and GetUndeliveredAdscEvents.
 *
 * @param[in]     hThisObject   - Handle to the CWMP Processor object instance.
 * @param[in,out] hWmpSession   - Handle to the WMP Session object to be populated with undelivered events.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Undelivered events retrieved and populated successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_GET_UNDEL_EVT)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hWmpSession
    );

/**
 * @brief Discard all undelivered events.
 *
 * This function pointer typedef defines the callback interface for discarding all undelivered
 * events from persistent storage. This removes all saved TransferComplete, AutonomousTransferComplete,
 * DUStateChangeComplete, AutonomousDUStateChangeComplete, and ValueChange events. Typically called
 * after successful delivery to the ACS or when events need to be cleared due to policy or error conditions.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Undelivered events discarded successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_DSC_UNDEL_EVT)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Initialize the Parameter Attribute Cache.
 *
 * This function pointer typedef defines the callback interface for initializing the Parameter
 * Attribute Cache (PAC). The PAC stores parameter notification attributes (passive/active) to
 * optimize attribute queries and change tracking. Initialization loads persistent attribute
 * settings and prepares the cache for operation.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Parameter Attribute Cache initialized successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_INIT_PAC)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Update the Parameter Attribute Cache with new attribute values.
 *
 * This function pointer typedef defines the callback interface for updating the Parameter Attribute
 * Cache with new parameter attribute values. Typically called after SetParameterAttributes RPC to
 * update cached notification settings (passive/active) and access control attributes. This keeps
 * the cache synchronized with actual parameter attribute changes.
 *
 * @param[in] hThisObject       - Handle to the CWMP Processor object instance.
 * @param[in] hParamAttrArray   - Handle to an array of parameter attribute structures containing
 *                                 updated attribute values for one or more parameters.
 * @param[in] ulParamCount      - Number of parameter attributes in the array. Valid range: 0 to MAX_ULONG.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Parameter Attribute Cache updated successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_UPD_PAC)
    (
        ANSC_HANDLE                 hThisObject,
        ANSC_HANDLE                 hParamAttrArray,
        ULONG                       ulParamCount
    );

/**
 * @brief Check the Parameter Attribute Cache for a parameter's notification attribute.
 *
 * This function pointer typedef defines the callback interface for checking the Parameter Attribute
 * Cache to retrieve a parameter's notification attribute. This provides fast lookup of notification
 * settings without querying the backend data model provider.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] pParamName   - Parameter name (full path) to check in the cache.
 *
 * @return The notification attribute value from the cache.
 * @retval 0 - Passive notification (or parameter not in cache).
 * @retval 1 - Active notification.
 * @retval 2 - Active lightweight notification.
 *
 */
typedef  ULONG
(*PFN_CWMPPROCO_CHK_PAC)
    (
        ANSC_HANDLE                 hThisObject,
        char*                       pParamName
    );

/**
 * @brief Synchronize namespaces with the Component Registrar (CR).
 *
 * This function pointer typedef defines the callback interface for synchronizing data model
 * namespaces between the CWMP Processor and the CCSP Component Registrar. This discovers or
 * updates the list of available data model namespaces and their component mappings. The
 * bRemoteOnly flag controls whether to sync only remotely accessible components or all components.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 * @param[in] bRemoteOnly  - Boolean flag controlling synchronization scope.
 *                            \n TRUE = Sync only remotely accessible components, FALSE = Sync all components.
 *
 * @return The status of the operation.
 * @retval ANSC_STATUS_SUCCESS - Namespace synchronization completed successfully.
 *
 */
typedef  ANSC_STATUS
(*PFN_CWMPPROCO_SYNC_CR)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bRemoteOnly
    );

/**
 * @brief Check if there is a pending Inform to be sent to the ACS.
 *
 * This function pointer typedef defines the callback interface for checking whether the CWMP
 * Processor has a pending Inform RPC that needs to be sent to the ACS. This includes checking
 * for scheduled informs, pending periodic informs, or other queued inform events.
 *
 * @param[in] hThisObject  - Handle to the CWMP Processor object instance.
 *
 * @return Boolean indicating if there is a pending Inform.
 * @retval TRUE  - Pending Inform exists and needs to be sent.
 * @retval FALSE - No pending Inform.
 *
 */
typedef  BOOL
(*PFN_CWMPPROCO_FS_PEND)
    (
        ANSC_HANDLE                 hThisObject
    );

/**
 * @brief Get the active WMP Session count.
 *
 * This function pointer typedef defines the callback interface for retrieving the number of
 * currently active WMP Sessions. This count represents the number of
 * ongoing TR-069 sessions with the ACS. The bQueueLockAcquired flag indicates if the caller
 * has already acquired the session queue lock.
 *
 * @param[in] hThisObject         - Handle to the CWMP Processor object instance.
 * @param[in] bQueueLockAcquired  - Boolean flag indicating if the session queue lock is already held.
 *                                   \n TRUE = Lock already acquired, FALSE = Function should acquire lock.
 *
 * @return The number of active WMP Sessions.
 *
 */
typedef  ULONG
(*PFN_CWMPPROCO_GET_ASC)
    (
        ANSC_HANDLE                 hThisObject,
        BOOL                        bQueueLockAcquired
    );

/*
 * SOAP messages are carried between a CPE and an ACS using HTTP 1.1, where the CPE acts as the
 * HTTP client and the ACS acts as the HTTP server. The encoding of SOAP over HTTP extends the
 * basic HTTP profile for SOAP, as follows:
 *
 *      - A SOAP request from an ACS to a CPE is sent over a HTTP response, while the
 *        CPE's SOAP response to an ACS request is sent over a subsequent HTTP post.
 *      - Each HTTP post or response may contain more than one SOAP envelope (within the
 *        negotiated limits). Each envelope may contain a SOAP request or response,
 *        independent from any other envelope.
 *      - When there is more than one envelope in a single HTTP Request, the SOAPAction
 *        header in the HTTP Request MUST have no value (with no quotes), indicating that
 *        this header provides no information as to the intent of the message.
 */
#define  CCSP_CWMP_PROCESSOR_CLASS_CONTENT                                                  \
    /* duplication of the base object class content */                                      \
    ANSCCO_CLASS_CONTENT                                                                    \
    /* start of object class content */                                                     \
    CCSP_CWMP_PROCESSOR_PROPERTY    Property;                                               \
    ANSC_HANDLE                     hPeriodicTimerObj;                                      \
    ANSC_HANDLE                     hPeriodicTimerIf;                                       \
    ANSC_HANDLE                     hScheduleTimerObj;                                      \
    ANSC_HANDLE                     hScheduleTimerIf;                                       \
    ANSC_HANDLE                     hPendingInformTimerObj;                                 \
    ANSC_HANDLE                     hPendingInformTimerIf;                                  \
    char*                           SecheduledCommandKey;                                   \
    ANSC_HANDLE                     hCcspCwmpCpeController;                                 \
    ULONG                           AsyncTaskCount;                                         \
    ANSC_HANDLE                     hParamAttrCache;                                        \
    ANSC_HANDLE                     hCcspNamespaceMgr;                                      \
    ANSC_HANDLE                     CcspNamespaceMgrLock;                                   \
    ANSC_HANDLE                     hCcspCwmpMpaIf;                                         \
    BOOL                            bRemoteCRsSyncDone;                                     \
    ULONG                           LastRemoteCrSyncTime;                                   \
    BOOL                            bActive;                                                \
    BOOL                            MsFcInitDone;                                           \
    BOOL                            bAcsInfoRetrieved;                                      \
                                                                                            \
    QUEUE_HEADER                    WmpsoQueue;                                             \
    ANSC_LOCK                       WmpsoQueueLock;                                         \
    ANSC_EVENT                      AsyncConnectEvent;                                      \
                                                                                            \
    PFN_CWMPPROCO_GET_CONTEXT       GetCcspCwmpCpeController;                               \
    PFN_CWMPPROCO_SET_CONTEXT       SetCcspCwmpCpeController;                               \
    PFN_CWMPPROCO_GET_BOOL          GetInitialContact;                                      \
    PFN_CWMPPROCO_SET_BOOL          SetInitialContact;                                      \
    PFN_CWMPPROCO_GET_BOOL          GetInitialContactFactory;                               \
    PFN_CWMPPROCO_SET_BOOL          SetInitialContactFactory;                               \
    PFN_CWMPPROCO_GET_BOOL          IsCwmpEnabled;                                          \
    PFN_CWMPPROCO_GET_STRING        GetAcsUrl;                                              \
    PFN_CWMPPROCO_GET_STRING        GetAcsUsername;                                         \
    PFN_CWMPPROCO_GET_STRING        GetAcsPassword;                                         \
    PFN_CWMPPROCO_GET_BOOL          GetPeriodicInformEnabled;                               \
    PFN_CWMPPROCO_GET_ULONG         GetPeriodicInformInterval;                              \
    PFN_CWMPPROCO_GET_HANDLE        GetPeriodicInformTime;                                  \
                                                                                            \
    PFN_CWMPPROCO_GET_IF            GetCcspCwmpMpaIf;                                       \
    PFN_CWMPPROCO_GET_PROPERTY      GetProperty;                                            \
    PFN_CWMPPROCO_SET_PROPERTY      SetProperty;                                            \
    PFN_CWMPPROCO_RESET             ResetProperty;                                          \
    PFN_CWMPPROCO_RESET             Reset;                                                  \
                                                                                            \
    PFN_CWMPPROCO_ENGAGE            Engage;                                                 \
    PFN_CWMPPROCO_CANCEL            Cancel;                                                 \
    PFN_CWMPPROCO_SETUP_ENV         SetupEnv;                                               \
    PFN_CWMPPROCO_CLOSE_ENV         CloseEnv;                                               \
    PFN_CWMPPROCO_INVOKE            PeriodicTimerInvoke;                                    \
    PFN_CWMPPROCO_INVOKE            ScheduleTimerInvoke;                                    \
    PFN_CWMPPROCO_INVOKE            PendingInformTimerInvoke;                               \
    PFN_CWMPPROCO_SAVE_TC           SaveTransferComplete;                                   \
    PFN_CWMPPROCO_LOAD_TC           LoadTransferComplete;                                   \
    PFN_CWMPPROCO_SAVE_ATC          SaveAutonomousTransferComplete;                         \
    PFN_CWMPPROCO_LOAD_ATC          LoadAutonomousTransferComplete;                         \
    PFN_CWMPPROCO_SAVE_DSCC         SaveDUStateChangeComplete;                              \
    PFN_CWMPPROCO_LOAD_DSCC         LoadDUStateChangeComplete;                              \
    PFN_CWMPPROCO_SAVE_ADSCC        SaveAutonDUStateChangeComplete;                         \
    PFN_CWMPPROCO_LOAD_ADSCC        LoadAutonDUStateChangeComplete;                         \
    PFN_CWMPPROCO_REDELIVER_EVT     RedeliverEvents;                                        \
    PFN_CWMPPROCO_LOAD_VC           LoadValueChanged;                                       \
    PFN_CWMPPROCO_SAVE_VC           SaveValueChanged;                                       \
    PFN_CWMPPROCO_DSC_VC            DiscardValueChanged;                                    \
    PFN_CWMPPROCO_GET_UNDEL_EVT     GetUndeliveredEvents;                                   \
    PFN_CWMPPROCO_GET_UNDEL_EVT     GetUndeliveredTcEvents;                                 \
    PFN_CWMPPROCO_GET_UNDEL_EVT     GetUndeliveredAtcEvents;                                \
    PFN_CWMPPROCO_GET_UNDEL_EVT     GetUndeliveredDscEvents;                                \
    PFN_CWMPPROCO_GET_UNDEL_EVT     GetUndeliveredAdscEvents;                               \
    PFN_CWMPPROCO_DSC_UNDEL_EVT     DiscardUndeliveredEvents;                               \
                                                                                            \
    PFN_CWMPPROCO_ACQ_WMPSO         AcqWmpSession;                                          \
    PFN_CWMPPROCO_ACQ_WMPSO2        AcqWmpSession2;                                         \
    PFN_CWMPPROCO_ACQ_WMPSO3        AcqWmpSession3;                                         \
    PFN_CWMPPROCO_REL_WMPSO         RelWmpSession;                                          \
    PFN_CWMPPROCO_DEL_WMPSO         DelWmpSession;                                          \
    PFN_CWMPPROCO_DEL_ALL           DelAllSessions;                                         \
    PFN_CWMPPROCO_GET_ASC           GetActiveWmpSessionCount;                               \
    PFN_CWMPPROCO_FS_PEND           HasPendingInform;                                       \
                                                                                            \
    PFN_CWMPPROCO_CONFIG_PER        ConfigPeriodicInform;                                   \
    PFN_CWMPPROCO_SCHEDULE          ScheduleInform;                                         \
    PFN_CWMPPROCO_SIGNAL            SignalSession;                                          \
    PFN_CWMPPROCO_ASYNC_CONNECT     AsyncConnectTask;                                       \
                                                                                            \
    PFN_CWMPPROCO_GET_INFO          GetAcsInfo;                                             \
    PFN_CCSPMS_VALUECHANGE          MsValueChanged;                                         \
                                                                                            \
    PFN_CWMPPROCO_SYNC_CR           SyncNamespacesWithCR;                                   \
    PFN_CWMPPROCO_INIT_PAC          InitParamAttrCache;                                     \
    PFN_CWMPPROCO_INIT_PAC          PushAllVcToBackend;                                     \
    PFN_CWMPPROCO_UPD_PAC           UpdateParamAttrCache;                                   \
    PFN_CWMPPROCO_CHK_PAC           CheckParamAttrCache;                                    \
    /* end of object class content */                                                       \

typedef  struct
_CCSP_CWMP_PROCESSOR_OBJECT
{
    CCSP_CWMP_PROCESSOR_CLASS_CONTENT
}
CCSP_CWMP_PROCESSOR_OBJECT,  *PCCSP_CWMP_PROCESSOR_OBJECT;

#define  ACCESS_CCSP_CWMP_PROCESSOR_OBJECT(p)        \
         ACCESS_CONTAINER(p, CCSP_CWMP_PROCESSOR_OBJECT, Linkage)


#endif
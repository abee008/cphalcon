
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/string.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2013 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 |          Rack Lin <racklin@gmail.com>                                  |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Dispatcher
 *
 * This is the base class for Phalcon\Mvc\Dispatcher and Phalcon\CLI\Dispatcher.
 * This class can"t be instantiated directly, you can use it to create your own dispatchers
 */
ZEPHIR_INIT_CLASS(Phalcon_Dispatcher) {

	ZEPHIR_REGISTER_CLASS(Phalcon, Dispatcher, phalcon, dispatcher, phalcon_dispatcher_method_entry, 0);

	zend_declare_property_null(phalcon_dispatcher_ce, SL("_dependencyInjector"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_eventsManager"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_activeHandler"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_finished"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_bool(phalcon_dispatcher_ce, SL("_forwarded"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_moduleName"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_namespaceName"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_handlerName"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_actionName"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_params"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_returnedValue"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_lastHandler"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_defaultNamespace"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_dispatcher_ce, SL("_defaultHandler"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(phalcon_dispatcher_ce, SL("_defaultAction"), "", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(phalcon_dispatcher_ce, SL("_handlerSuffix"), "", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_string(phalcon_dispatcher_ce, SL("_actionSuffix"), "Action", ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_dispatcher_ce, SL("EXCEPTION_NO_DI"), 0 TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_dispatcher_ce, SL("EXCEPTION_CYCLIC_ROUTING"), 1 TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_dispatcher_ce, SL("EXCEPTION_HANDLER_NOT_FOUND"), 2 TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_dispatcher_ce, SL("EXCEPTION_INVALID_HANDLER"), 3 TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_dispatcher_ce, SL("EXCEPTION_INVALID_PARAMS"), 4 TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_dispatcher_ce, SL("EXCEPTION_ACTION_NOT_FOUND"), 5 TSRMLS_CC);

	return SUCCESS;

}

/**
 * Sets the dependency injector
 *
 * @param Phalcon\DiInterface dependencyInjector
 */
PHP_METHOD(Phalcon_Dispatcher, setDI) {

	zval *dependencyInjector;

	zephir_fetch_params(0, 1, 0, &dependencyInjector);



	zephir_update_property_this(this_ptr, SL("_dependencyInjector"), dependencyInjector TSRMLS_CC);

}

/**
 * Returns the internal dependency injector
 *
 * @return Phalcon\DiInterface
 */
PHP_METHOD(Phalcon_Dispatcher, getDI) {


	RETURN_MEMBER(this_ptr, "_dependencyInjector");

}

/**
 * Sets the events manager
 *
 * @param Phalcon\Events\ManagerInterface eventsManager
 */
PHP_METHOD(Phalcon_Dispatcher, setEventsManager) {

	zval *eventsManager;

	zephir_fetch_params(0, 1, 0, &eventsManager);



	zephir_update_property_this(this_ptr, SL("_eventsManager"), eventsManager TSRMLS_CC);

}

/**
 * Returns the internal event manager
 *
 * @return Phalcon\Events\ManagerInterface
 */
PHP_METHOD(Phalcon_Dispatcher, getEventsManager) {


	RETURN_MEMBER(this_ptr, "_eventsManager");

}

/**
 * Sets the default action suffix
 *
 * @param string actionSuffix
 */
PHP_METHOD(Phalcon_Dispatcher, setActionSuffix) {

	zval *actionSuffix;

	zephir_fetch_params(0, 1, 0, &actionSuffix);



	zephir_update_property_this(this_ptr, SL("_actionSuffix"), actionSuffix TSRMLS_CC);

}

/**
 * Sets the module where the controller is (only informative)
 *
 * @param string moduleName
 */
PHP_METHOD(Phalcon_Dispatcher, setModuleName) {

	zval *moduleName;

	zephir_fetch_params(0, 1, 0, &moduleName);



	zephir_update_property_this(this_ptr, SL("_moduleName"), moduleName TSRMLS_CC);

}

/**
 * Gets the module where the controller class is
 *
 * @return string
 */
PHP_METHOD(Phalcon_Dispatcher, getModuleName) {


	RETURN_MEMBER(this_ptr, "_moduleName");

}

/**
 * Sets the namespace where the controller class is
 *
 * @param string namespaceName
 */
PHP_METHOD(Phalcon_Dispatcher, setNamespaceName) {

	zval *namespaceName;

	zephir_fetch_params(0, 1, 0, &namespaceName);



	zephir_update_property_this(this_ptr, SL("_namespaceName"), namespaceName TSRMLS_CC);

}

/**
 * Gets a namespace to be prepended to the current handler name
 *
 * @return string
 */
PHP_METHOD(Phalcon_Dispatcher, getNamespaceName) {


	RETURN_MEMBER(this_ptr, "_namespaceName");

}

/**
 * Sets the default namespace
 *
 * @param string namespaceName
 */
PHP_METHOD(Phalcon_Dispatcher, setDefaultNamespace) {

	zval *namespaceName;

	zephir_fetch_params(0, 1, 0, &namespaceName);



	zephir_update_property_this(this_ptr, SL("_defaultNamespace"), namespaceName TSRMLS_CC);

}

/**
 * Returns the default namespace
 *
 * @return string
 */
PHP_METHOD(Phalcon_Dispatcher, getDefaultNamespace) {


	RETURN_MEMBER(this_ptr, "_defaultNamespace");

}

/**
 * Sets the default action name
 *
 * @param string actionName
 */
PHP_METHOD(Phalcon_Dispatcher, setDefaultAction) {

	zval *actionName;

	zephir_fetch_params(0, 1, 0, &actionName);



	zephir_update_property_this(this_ptr, SL("_defaultAction"), actionName TSRMLS_CC);

}

/**
 * Sets the action name to be dispatched
 *
 * @param string actionName
 */
PHP_METHOD(Phalcon_Dispatcher, setActionName) {

	zval *actionName;

	zephir_fetch_params(0, 1, 0, &actionName);



	zephir_update_property_this(this_ptr, SL("_actionName"), actionName TSRMLS_CC);

}

/**
 * Gets the lastest dispatched action name
 *
 * @return string
 */
PHP_METHOD(Phalcon_Dispatcher, getActionName) {


	RETURN_MEMBER(this_ptr, "_actionName");

}

/**
 * Sets action params to be dispatched
 *
 * @param array params
 */
PHP_METHOD(Phalcon_Dispatcher, setParams) {

	zval *params, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &params);



	if (Z_TYPE_P(params) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(_0);
		ZVAL_STRING(_0, "Parameters must be an Array", 1);
		zephir_call_method_p1_noret(this_ptr, "_throwdispatchexception", _0);
		RETURN_MM_NULL();
	}
	zephir_update_property_this(this_ptr, SL("_params"), params TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Gets action params
 *
 * @return array
 */
PHP_METHOD(Phalcon_Dispatcher, getParams) {


	RETURN_MEMBER(this_ptr, "_params");

}

/**
 * Set a param by its name or numeric index
 *
 * @param  mixed param
 * @param  mixed value
 */
PHP_METHOD(Phalcon_Dispatcher, setParam) {

	zval *param, *value;

	zephir_fetch_params(0, 2, 0, &param, &value);



	zephir_update_property_array(this_ptr, SL("_params"), param, value TSRMLS_CC);

}

/**
 * Gets a param by its name or numeric index
 *
 * @param  mixed param
 * @param  string|array filters
 * @param  mixed defaultValue
 * @return mixed
 */
PHP_METHOD(Phalcon_Dispatcher, getParam) {

	zval *param, *filters = NULL, *defaultValue = NULL, *params, *filter, *paramValue, *dependencyInjector, *_0 = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &param, &filters, &defaultValue);

	if (!filters) {
		ZEPHIR_CPY_WRT(filters, ZEPHIR_GLOBAL(global_null));
	}
	if (!defaultValue) {
		ZEPHIR_CPY_WRT(defaultValue, ZEPHIR_GLOBAL(global_null));
	}


	ZEPHIR_OBS_VAR(params);
	zephir_read_property_this(&params, this_ptr, SL("_params"), PH_NOISY_CC);
	if (zephir_array_isset(params, param)) {
		ZEPHIR_OBS_VAR(paramValue);
		zephir_array_fetch(&paramValue, params, param, PH_NOISY);
		if ((Z_TYPE_P(filters) != IS_NULL)) {
			ZEPHIR_OBS_VAR(dependencyInjector);
			zephir_read_property_this(&dependencyInjector, this_ptr, SL("_dependencyInjector"), PH_NOISY_CC);
			if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
				ZEPHIR_INIT_VAR(_0);
				ZEPHIR_INIT_NVAR(_0);
				ZVAL_LONG(_0, 0);
				ZEPHIR_INIT_VAR(_1);
				ZVAL_STRING(_1, "A dependency injection object is required to access the 'filter' service", 1);
				zephir_call_method_p2_noret(this_ptr, "_throwdispatchexception", _1, _0);
			}
			ZEPHIR_INIT_NVAR(_0);
			ZVAL_STRING(_0, "filter", 1);
			ZEPHIR_INIT_VAR(filter);
			zephir_call_method_p1(filter, dependencyInjector, "getshared", _0);
			zephir_call_method_p2(return_value, filter, "sanitize", paramValue, filters);
			RETURN_MM();
		} else {
			RETURN_CCTOR(paramValue);
		}
	}
	RETURN_CCTOR(defaultValue);

}

/**
 * Returns the current method to be/executed in the dispatcher
 *
 * @return string
 */
PHP_METHOD(Phalcon_Dispatcher, getActiveMethod) {

	zval *_0, *_1;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("_actionName"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property_this(&_1, this_ptr, SL("_actionSuffix"), PH_NOISY_CC);
	concat_function(return_value, _0, _1);
	RETURN_MM();

}

/**
 * Checks if the dispatch loop is finished or has more pendent controllers/tasks to dispatch
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Dispatcher, isFinished) {


	RETURN_MEMBER(this_ptr, "_finished");

}

/**
 * Sets the latest returned value by an action manually
 *
 * @param mixed value
 */
PHP_METHOD(Phalcon_Dispatcher, setReturnedValue) {

	zval *value;

	zephir_fetch_params(0, 1, 0, &value);



	zephir_update_property_this(this_ptr, SL("_returnedValue"), value TSRMLS_CC);

}

/**
 * Returns value returned by the lastest dispatched action
 *
 * @return mixed
 */
PHP_METHOD(Phalcon_Dispatcher, getReturnedValue) {


	RETURN_MEMBER(this_ptr, "_returnedValue");

}

/**
 * Dispatches a handle action taking into account the routing parameters
 *
 * @return object
 */
PHP_METHOD(Phalcon_Dispatcher, dispatch) {

	zval *value, *handler = NULL, *dependencyInjector, *namespaceName = NULL, *handlerName = NULL, *actionName = NULL, *camelizedClass = NULL, *hasService = NULL, *params = NULL, *eventsManager, *handlerSuffix, *actionSuffix, *handlerClass = NULL, *status = NULL, *actionMethod = NULL, *_0 = NULL, *_1 = NULL, *_2, *_3 = NULL, *_4 = NULL, *_5, *_6 = NULL, *_7 = NULL, *_8 = NULL, *_9 = NULL, *_10 = NULL, *_11 = NULL, *_12, _13 = zval_used_for_init, *_14 = NULL;
	int numberDispatches;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(dependencyInjector);
	zephir_read_property_this(&dependencyInjector, this_ptr, SL("_dependencyInjector"), PH_NOISY_CC);
	if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
		ZEPHIR_INIT_VAR(_0);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_LONG(_0, 0);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "A dependency injection container is required to access related dispatching services", 1);
		zephir_call_method_p2_noret(this_ptr, "_throwdispatchexception", _1, _0);
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_OBS_VAR(eventsManager);
	zephir_read_property_this(&eventsManager, this_ptr, SL("_eventsManager"), PH_NOISY_CC);
	if (Z_TYPE_P(eventsManager) == IS_OBJECT) {
		ZEPHIR_INIT_NVAR(_0);
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "dispatch:beforeDispatchLoop", 1);
		zephir_call_method_p2(_0, eventsManager, "fire", _1, this_ptr);
		if (ZEPHIR_IS_FALSE(_0)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_INIT_VAR(value);
	ZVAL_NULL(value);
	ZEPHIR_INIT_VAR(handler);
	ZVAL_NULL(handler);
	numberDispatches = 0;
	ZEPHIR_OBS_VAR(handlerSuffix);
	zephir_read_property_this(&handlerSuffix, this_ptr, SL("_handlerSuffix"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(actionSuffix);
	zephir_read_property_this(&actionSuffix, this_ptr, SL("_actionSuffix"), PH_NOISY_CC);
	zephir_update_property_this(this_ptr, SL("_finished"), ZEPHIR_GLOBAL(golbal_false) TSRMLS_CC);
	while (1) {
		_2 = zephir_fetch_nproperty_this(this_ptr, SL("_finished"), PH_NOISY_CC);
		if (!(!(zend_is_true(_2)))) {
			break;
		}
		numberDispatches++;
		if ((numberDispatches == 256)) {
			ZEPHIR_INIT_NVAR(_0);
			ZEPHIR_INIT_NVAR(_0);
			ZVAL_LONG(_0, 1);
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "Dispatcher has detected a cyclic routing causing stability problems", 1);
			zephir_call_method_p2_noret(this_ptr, "_throwdispatchexception", _1, _0);
			break;
		}
		zephir_update_property_this(this_ptr, SL("_finished"), ZEPHIR_GLOBAL(golbal_true) TSRMLS_CC);
		ZEPHIR_OBS_NVAR(namespaceName);
		zephir_read_property_this(&namespaceName, this_ptr, SL("_namespaceName"), PH_NOISY_CC);
		if (!(zend_is_true(namespaceName))) {
			ZEPHIR_OBS_NVAR(_3);
			zephir_read_property_this(&_3, this_ptr, SL("_defaultNamespace"), PH_NOISY_CC);
			zephir_update_property_this(this_ptr, SL("_namespaceName"), _3 TSRMLS_CC);
		}
		ZEPHIR_OBS_NVAR(handlerName);
		zephir_read_property_this(&handlerName, this_ptr, SL("_handlerName"), PH_NOISY_CC);
		if (!(zend_is_true(handlerName))) {
			ZEPHIR_OBS_NVAR(_3);
			zephir_read_property_this(&_3, this_ptr, SL("_defaultHandler"), PH_NOISY_CC);
			zephir_update_property_this(this_ptr, SL("_handlerName"), _3 TSRMLS_CC);
		}
		ZEPHIR_OBS_NVAR(actionName);
		zephir_read_property_this(&actionName, this_ptr, SL("_actionName"), PH_NOISY_CC);
		if (!(zend_is_true(actionName))) {
			ZEPHIR_OBS_NVAR(_3);
			zephir_read_property_this(&_3, this_ptr, SL("_defaultAction"), PH_NOISY_CC);
			zephir_update_property_this(this_ptr, SL("_actionName"), _3 TSRMLS_CC);
		}
		if (Z_TYPE_P(eventsManager) == IS_OBJECT) {
			ZEPHIR_INIT_NVAR(_1);
			ZEPHIR_INIT_NVAR(_4);
			ZVAL_STRING(_4, "dispatch:beforeDispatch", 1);
			zephir_call_method_p2(_1, eventsManager, "fire", _4, this_ptr);
			if (ZEPHIR_IS_FALSE(_1)) {
				continue;
			}
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("_finished"), PH_NOISY_CC);
			if (ZEPHIR_IS_FALSE(_5)) {
				continue;
			}
		}
		if (!(zephir_memnstr_str(handlerName, SL("\\")))) {
			ZEPHIR_INIT_NVAR(camelizedClass);
			zephir_camelize(camelizedClass, handlerName);
		} else {
			ZEPHIR_CPY_WRT(camelizedClass, handlerName);
		}
		if (zend_is_true(namespaceName)) {
			ZEPHIR_INIT_NVAR(handlerClass);
			if (zephir_end_with_str(namespaceName, SL("\\"))) {
				ZEPHIR_INIT_LNVAR(_6);
				concat_function(_6, namespaceName, camelizedClass);
				concat_function(handlerClass, _6, handlerSuffix);
			} else {
				ZEPHIR_INIT_LNVAR(_6);
				ZEPHIR_CONCAT_VS(_6, namespaceName, "\\");
				ZEPHIR_INIT_LNVAR(_7);
				concat_function(_7, _6, camelizedClass);
				concat_function(handlerClass, _7, handlerSuffix);
			}
		} else {
			ZEPHIR_INIT_NVAR(handlerClass);
			concat_function(handlerClass, camelizedClass, handlerSuffix);
		}
		ZEPHIR_INIT_NVAR(hasService);
		zephir_call_method_p1(hasService, dependencyInjector, "has", handlerClass);
		if (zend_is_true(hasService)) {
			ZEPHIR_INIT_NVAR(hasService);
			zephir_call_func_p1(hasService, "class_exists", handlerClass);
		}
		if (!(zend_is_true(hasService))) {
			ZEPHIR_INIT_LNVAR(_6);
			ZEPHIR_CONCAT_VS(_6, handlerClass, " handler class cannot be loaded");
			ZEPHIR_INIT_NVAR(_4);
			ZEPHIR_INIT_NVAR(_4);
			ZVAL_LONG(_4, 2);
			ZEPHIR_INIT_NVAR(status);
			zephir_call_method_p2(status, this_ptr, "_throwdispatchexception", _6, _4);
			if (ZEPHIR_IS_FALSE(status)) {
				_5 = zephir_fetch_nproperty_this(this_ptr, SL("_finished"), PH_NOISY_CC);
				if (ZEPHIR_IS_FALSE(_5)) {
					continue;
				}
			}
			break;
		}
		ZEPHIR_INIT_NVAR(handler);
		zephir_call_method_p1(handler, dependencyInjector, "getshared", handlerClass);
		if (Z_TYPE_P(handler) != IS_OBJECT) {
			ZEPHIR_INIT_NVAR(_4);
			ZEPHIR_INIT_NVAR(_4);
			ZVAL_LONG(_4, 3);
			ZEPHIR_INIT_NVAR(_8);
			ZVAL_STRING(_8, "Invalid handler returned from the services container", 1);
			ZEPHIR_INIT_NVAR(status);
			zephir_call_method_p2(status, this_ptr, "_throwdispatchexception", _8, _4);
			if (ZEPHIR_IS_FALSE(status)) {
				_5 = zephir_fetch_nproperty_this(this_ptr, SL("_finished"), PH_NOISY_CC);
				if (ZEPHIR_IS_FALSE(_5)) {
					continue;
				}
			}
			break;
		}
		zephir_update_property_this(this_ptr, SL("_activeHandler"), handler TSRMLS_CC);
		ZEPHIR_OBS_NVAR(params);
		zephir_read_property_this(&params, this_ptr, SL("_params"), PH_NOISY_CC);
		if (Z_TYPE_P(params) != IS_ARRAY) {
			ZEPHIR_INIT_NVAR(_4);
			ZEPHIR_INIT_NVAR(_4);
			ZVAL_LONG(_4, 4);
			ZEPHIR_INIT_NVAR(_8);
			ZVAL_STRING(_8, "Action parameters must be an Array", 1);
			ZEPHIR_INIT_NVAR(status);
			zephir_call_method_p2(status, this_ptr, "_throwdispatchexception", _8, _4);
			if (ZEPHIR_IS_FALSE(status)) {
				_5 = zephir_fetch_nproperty_this(this_ptr, SL("_finished"), PH_NOISY_CC);
				if (ZEPHIR_IS_FALSE(_5)) {
					continue;
				}
			}
			break;
		}
		ZEPHIR_INIT_NVAR(actionMethod);
		concat_function(actionMethod, actionName, actionSuffix);
		ZEPHIR_INIT_NVAR(_4);
		zephir_call_func_p2(_4, "method_exists", handler, actionMethod);
		if (!(zend_is_true(_4))) {
			if (Z_TYPE_P(eventsManager) == IS_OBJECT) {
				ZEPHIR_INIT_NVAR(_8);
				ZEPHIR_INIT_NVAR(_9);
				ZVAL_STRING(_9, "dispatch:beforeNotFoundAction", 1);
				zephir_call_method_p2(_8, eventsManager, "fire", _9, this_ptr);
				if (ZEPHIR_IS_FALSE(_8)) {
					continue;
				}
				_5 = zephir_fetch_nproperty_this(this_ptr, SL("_finished"), PH_NOISY_CC);
				if (ZEPHIR_IS_FALSE(_5)) {
					continue;
				}
			}
			ZEPHIR_INIT_LNVAR(_6);
			ZEPHIR_CONCAT_SV(_6, "Action '", actionName);
			ZEPHIR_INIT_LNVAR(_7);
			ZEPHIR_CONCAT_VS(_7, _6, "' was not found on handler '");
			ZEPHIR_INIT_LNVAR(_10);
			concat_function(_10, _7, handlerName);
			ZEPHIR_INIT_LNVAR(_11);
			ZEPHIR_CONCAT_VS(_11, _10, "'");
			ZEPHIR_INIT_NVAR(_9);
			ZEPHIR_INIT_NVAR(_9);
			ZVAL_LONG(_9, 5);
			ZEPHIR_INIT_NVAR(status);
			zephir_call_method_p2(status, this_ptr, "_throwdispatchexception", _11, _9);
			if (ZEPHIR_IS_FALSE(status)) {
				_12 = zephir_fetch_nproperty_this(this_ptr, SL("_finished"), PH_NOISY_CC);
				if (ZEPHIR_IS_FALSE(_12)) {
					continue;
				}
			}
			break;
		}
		if (Z_TYPE_P(eventsManager) == IS_OBJECT) {
			ZEPHIR_INIT_NVAR(_4);
			ZEPHIR_INIT_NVAR(_8);
			ZVAL_STRING(_8, "dispatch:beforeExecuteRoute", 1);
			zephir_call_method_p2(_4, eventsManager, "fire", _8, this_ptr);
			if (ZEPHIR_IS_FALSE(_4)) {
				continue;
			}
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("_finished"), PH_NOISY_CC);
			if (ZEPHIR_IS_FALSE(_5)) {
				continue;
			}
		}
		ZEPHIR_SINIT_NVAR(_13);
		ZVAL_STRING(&_13, "beforeExecuteRoute", 0);
		ZEPHIR_INIT_NVAR(_4);
		zephir_call_func_p2(_4, "method_exists", handler, &_13);
		if (zend_is_true(_4)) {
			ZEPHIR_INIT_NVAR(_8);
			zephir_call_method_p1(_8, handler, "beforeexecuteroute", this_ptr);
			if (ZEPHIR_IS_FALSE(_8)) {
				continue;
			}
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("_finished"), PH_NOISY_CC);
			if (ZEPHIR_IS_FALSE(_5)) {
				continue;
			}
		}
		ZEPHIR_INIT_NVAR(_4);
		zephir_call_method(_4, dependencyInjector, "wasfreshinstance");
		if (ZEPHIR_IS_TRUE(_4)) {
			ZEPHIR_SINIT_NVAR(_13);
			ZVAL_STRING(&_13, "initialize", 0);
			ZEPHIR_INIT_NVAR(_8);
			zephir_call_func_p2(_8, "method_exists", handler, &_13);
			if (zend_is_true(_8)) {
				zephir_call_method_noret(handler, "initialize");
			}
		}
		ZEPHIR_INIT_NVAR(_4);
		array_init(_4);
		zephir_array_append(&_4, handler, 0);
		zephir_array_append(&_4, actionMethod, 0);
		ZEPHIR_INIT_NVAR(_8);
		zephir_call_func_p2(_8, "call_user_func_array", _4, params);
		zephir_update_property_this(this_ptr, SL("_returnedValue"), _8 TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("_lastHandler"), handler TSRMLS_CC);
		if (Z_TYPE_P(eventsManager) == IS_OBJECT) {
			ZEPHIR_INIT_NVAR(_9);
			ZEPHIR_INIT_NVAR(_14);
			ZVAL_STRING(_14, "dispatch:afterExecuteRoute", 1);
			zephir_call_method_p3(_9, eventsManager, "fire", _14, this_ptr, value);
			if (ZEPHIR_IS_FALSE(_9)) {
				continue;
			}
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("_finished"), PH_NOISY_CC);
			if (ZEPHIR_IS_FALSE(_5)) {
				continue;
			}
			ZEPHIR_INIT_NVAR(_9);
			ZVAL_STRING(_9, "dispatch:afterDispatch", 1);
			zephir_call_method_p2_noret(eventsManager, "fire", _9, this_ptr);
		}
		ZEPHIR_SINIT_NVAR(_13);
		ZVAL_STRING(&_13, "afterExecuteRoute", 0);
		ZEPHIR_INIT_NVAR(_4);
		zephir_call_func_p2(_4, "method_exists", handler, &_13);
		if (zend_is_true(_4)) {
			ZEPHIR_INIT_NVAR(_8);
			zephir_call_method_p2(_8, handler, "afterexecuteroute", this_ptr, value);
			if (ZEPHIR_IS_FALSE(_8)) {
				continue;
			}
			_5 = zephir_fetch_nproperty_this(this_ptr, SL("_finished"), PH_NOISY_CC);
			if (ZEPHIR_IS_FALSE(_5)) {
				continue;
			}
		}
	}
	if (Z_TYPE_P(eventsManager) == IS_OBJECT) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "dispatch:afterDispatchLoop", 1);
		zephir_call_method_p2_noret(eventsManager, "fire", _0, this_ptr);
	}
	RETURN_CCTOR(handler);

}

/**
 * Forwards the execution flow to another controller/action
 * Dispatchers are unique per module. Forwarding between modules is not allowed
 *
 *<code>
 *  $this->dispatcher->forward(array("controller" => "posts", "action" => "index"));
 *</code>
 *
 * @param array forward
 */
PHP_METHOD(Phalcon_Dispatcher, forward) {

	zval *forward, *namespaceName, *controllerName, *params, *actionName, *taskName, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &forward);



	if (Z_TYPE_P(forward) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(_0);
		ZVAL_STRING(_0, "Forward parameter must be an Array", 1);
		zephir_call_method_p1_noret(this_ptr, "_throwdispatchexception", _0);
		RETURN_MM_NULL();
	}
	ZEPHIR_OBS_VAR(namespaceName);
	if (zephir_array_isset_string_fetch(&namespaceName, forward, SS("namespace"))) {
		zephir_update_property_this(this_ptr, SL("_namespaceName"), namespaceName TSRMLS_CC);
	}
	ZEPHIR_OBS_VAR(controllerName);
	if (zephir_array_isset_string_fetch(&controllerName, forward, SS("controller"))) {
		zephir_update_property_this(this_ptr, SL("_handlerName"), controllerName TSRMLS_CC);
	} else {
		ZEPHIR_OBS_VAR(taskName);
		if (zephir_array_isset_string_fetch(&taskName, forward, SS("task"))) {
			zephir_update_property_this(this_ptr, SL("_handlerName"), taskName TSRMLS_CC);
		}
	}
	ZEPHIR_OBS_VAR(actionName);
	if (zephir_array_isset_string_fetch(&actionName, forward, SS("action"))) {
		zephir_update_property_this(this_ptr, SL("_actionName"), actionName TSRMLS_CC);
	}
	ZEPHIR_OBS_VAR(params);
	if (zephir_array_isset_string_fetch(&params, forward, SS("params"))) {
		zephir_update_property_this(this_ptr, SL("_params"), params TSRMLS_CC);
	}
	zephir_update_property_this(this_ptr, SL("_finished"), ZEPHIR_GLOBAL(golbal_false) TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("_forwarded"), ZEPHIR_GLOBAL(golbal_true) TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Check if the current executed action was forwarded by another one
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Dispatcher, wasForwarded) {


	RETURN_MEMBER(this_ptr, "_forwarded");

}

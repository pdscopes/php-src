/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_rs.h"
#include "ext/spl/spl_exceptions.h"

/* If you declare any globals in php_rs.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(rs)
*/

/* True global resources - no need for thread safety here */
static int le_rs;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("rs.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_rs_globals, rs_globals)
    STD_PHP_INI_ENTRY("rs.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_rs_globals, rs_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_rs_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_rs_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "rs", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ proto bool rs_array_keys_exist(array $keys, array $search)
   Checks if the given array of keys exist in the array */
PHP_FUNCTION(rs_array_keys_exist)
{
	/* keys to check for  */
	zval *keys, **key;
	HashTable *keys_hash;
	HashPosition pointer;

	/* array to check in */
	HashTable *array;

	if(zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_DC, "aH", &keys, &array) == FAILURE) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Invalid arguments. the first argument must be an array of keys, the second argument must be an array to search.");
		return;
	}

	keys_hash = Z_ARRVAL_P(keys);

	for(zend_hash_internal_pointer_reset_ex(keys_hash, &pointer); zend_hash_get_current_data_ex(keys_hash, (void**) &key, &pointer) == SUCCESS; zend_hash_move_forward_ex(keys_hash, &pointer)) {
		switch(Z_TYPE_PP(key)) {
			case IS_STRING:
				if(!zend_symtable_exists(array, Z_STRVAL_PP(key), Z_STRLEN_PP(key) + 1)) {
					RETURN_FALSE;
				}
				break;
			case IS_LONG:
				if(!zend_hash_index_exists(array, Z_LVAL_PP(key))) {
					RETURN_FALSE;
				}
				break;
			case IS_NULL:
				if(!zend_hash_exists(array, "", 1)) {
					RETURN_FALSE;
				}
				break;

			default:
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "The first argument should be an array of strings or integers");
				RETURN_FALSE;
		}
	}

	RETURN_TRUE;
}
/* }}} */


/* {{{ php_rs_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_rs_init_globals(zend_rs_globals *rs_globals)
{
	rs_globals->global_value = 0;
	rs_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(rs)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(rs)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(rs)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(rs)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(rs)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "rs support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ rs_functions[]
 *
 * Every user visible function must have an entry in rs_functions[].
 */
const zend_function_entry rs_functions[] = {
	PHP_FE(confirm_rs_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(rs_array_keys_exist,	NULL)
	PHP_FE_END	/* Must be the last line in rs_functions[] */
};
/* }}} */

/* {{{ rs_module_entry
 */
zend_module_entry rs_module_entry = {
	STANDARD_MODULE_HEADER,
	"rs",
	rs_functions,
	PHP_MINIT(rs),
	PHP_MSHUTDOWN(rs),
	PHP_RINIT(rs),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(rs),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(rs),
	PHP_RS_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_RS
ZEND_GET_MODULE(rs)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

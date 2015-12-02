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

#ifndef PHP_RS_H
#define PHP_RS_H

extern zend_module_entry rs_module_entry;
#define phpext_rs_ptr &rs_module_entry

#define PHP_RS_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_RS_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_RS_API __attribute__ ((visibility("default")))
#else
#	define PHP_RS_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(rs);
PHP_MSHUTDOWN_FUNCTION(rs);
PHP_RINIT_FUNCTION(rs);
PHP_RSHUTDOWN_FUNCTION(rs);
PHP_MINFO_FUNCTION(rs);

PHP_FUNCTION(confirm_rs_compiled); /* For testing, remove later */
PHP_FUNCTION(rs_array_keys_exist);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(rs)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(rs)
*/

/* In every utility function you add that needs to use variables 
   in php_rs_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as RS_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define RS_G(v) TSRMG(rs_globals_id, zend_rs_globals *, v)
#else
#define RS_G(v) (rs_globals.v)
#endif

#endif	/* PHP_RS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

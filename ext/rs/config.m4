dnl $Id$
dnl config.m4 for extension rs

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(rs, for rs support,
dnl Make sure that the comment is aligned:
dnl [  --with-rs             Include rs support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(rs, whether to enable rs support,
dnl Make sure that the comment is aligned:
[  --enable-rs           Enable rs support])

if test "$PHP_RS" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-rs -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/rs.h"  # you most likely want to change this
  dnl if test -r $PHP_RS/$SEARCH_FOR; then # path given as parameter
  dnl   RS_DIR=$PHP_RS
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for rs files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       RS_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$RS_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the rs distribution])
  dnl fi

  dnl # --with-rs -> add include path
  dnl PHP_ADD_INCLUDE($RS_DIR/include)

  dnl # --with-rs -> check for lib and symbol presence
  dnl LIBNAME=rs # you may want to change this
  dnl LIBSYMBOL=rs # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $RS_DIR/$PHP_LIBDIR, RS_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_RSLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong rs lib version or lib not found])
  dnl ],[
  dnl   -L$RS_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(RS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(rs, rs.c, $ext_shared)
fi

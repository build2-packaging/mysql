/* Copyright Abandoned 1996,1999 TCX DataKonsult AB & Monty Program KB
   & Detron HB, 1996, 1999-2004, 2007 MySQL AB.
   This file is public domain and comes with NO WARRANTY of any kind
*/

/* Version numbers for protocol & mysqld */

#ifndef _mysql_version_h
#define _mysql_version_h

#define PROTOCOL_VERSION            10
#define MYSQL_SERVER_VERSION       "5.7.20-a.0.z"
#define MYSQL_BASE_VERSION         "mysqld-5.7"
#define MYSQL_SERVER_SUFFIX_DEF    ""
#define FRM_VER                     6
#define MYSQL_VERSION_ID            (10000 * 5 + 100 * 7 + 20)
#define MYSQL_PORT                  3306
#define MYSQL_PORT_DEFAULT          0
#define MYSQL_UNIX_ADDR            "/tmp/mysql.sock"
#define MYSQL_CONFIG_NAME          "my"
#define MYSQL_COMPILATION_COMMENT  "Source distribution"
#define LIBMYSQL_VERSION           "5.7.20-a.0.z"
#define LIBMYSQL_VERSION_ID         (10000 * 5 + 100 * 7 + 20)
#define SYS_SCHEMA_VERSION         "1.5.1"

#ifndef LICENSE
#define LICENSE                     GPL
#endif /* LICENSE */

/*
 * These macro definitions are added to the original ones during packaging the
 * project for build2.
 */
#define MYSQL_VERSION_MAJOR  5
#define MYSQL_VERSION_MINOR  7
#define MACHINE_TYPE         "x86_64"
#define SYSTEM_TYPE          "linux"
#define DEFAULT_BASEDIR      "/tmp/mys"
#define DEFAULT_CHARSET_HOME DEFAULT_BASEDIR
#define PLUGINDIR            "/tmp/mys/lib/mysql/plugin"
#define SHAREDIR             "/tmp/mys/share/mysql"

#endif /* _mysql_version_h */

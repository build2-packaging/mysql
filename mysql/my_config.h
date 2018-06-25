/* file      : mysql/my_config.h -*- C -*-
 * copyright : Copyright (c) 2016-2018 Code Synthesis Ltd
 * license   : GPLv2 with FOSS License Exception; see accompanying COPYING file
 */

#ifndef MYSQL_MY_CONFIG_H
#define MYSQL_MY_CONFIG_H

/*
 * For the semantics of the following macros refer to
 * mysql/config.h.cmake.orig file.
 *
 * Note that we will explicitly undefine macros that are present in the
 * libmysqlclient source code but should not be defined. While this is not
 * technically required, it simplifies the change tracking (see README-DEV).
 * As a bonus we also make sure that they are not get eventually defined by
 * some system headers.
 */

/*
 * The version header defines the following macros:

#define PROTOCOL_VERSION
#define MYSQL_VERSION_MAJOR
#define MYSQL_VERSION_MINOR
#define MACHINE_TYPE
#define SYSTEM_TYPE
#define DEFAULT_BASEDIR      "/usr/local/mysql"
#define DEFAULT_CHARSET_HOME "/usr/local/mysql"
#define PLUGINDIR            "/usr/local/mysql/lib/plugin"
#define SHAREDIR             "/usr/local/mysql/share"

  * Keep all the macros listed (in this exact form) for the change tracking
  * (see README-DEV).
  */
#include <mysql/version.h>

#define PACKAGE_VERSION MYSQL_SERVER_VERSION
#define VERSION         MYSQL_SERVER_VERSION

/*
 * Endianess.
 */
#ifdef __FreeBSD__
#  include <sys/endian.h> /* BYTE_ORDER */
#else
#  if defined(_WIN32)
#    ifndef BYTE_ORDER
#      define BIG_ENDIAN    4321
#      define LITTLE_ENDIAN 1234
#      define BYTE_ORDER    LITTLE_ENDIAN
#    endif
#  else
#    include <sys/param.h>  /* BYTE_ORDER/__BYTE_ORDER */
#    ifndef BYTE_ORDER
#      ifdef __BYTE_ORDER
#        define BYTE_ORDER    __BYTE_ORDER
#        define BIG_ENDIAN    __BIG_ENDIAN
#        define LITTLE_ENDIAN __LITTLE_ENDIAN
#      else
#        error no BYTE_ORDER/__BYTE_ORDER define
#      endif
#    endif
#  endif
#endif

#if BYTE_ORDER == BIG_ENDIAN
# define WORDS_BIGENDIAN 1
#endif

/*
 * Types and type sizes.
 */
#ifndef _WIN32
#  define SIZEOF_VOIDP     __SIZEOF_POINTER__
#  define SIZEOF_CHARP     __SIZEOF_POINTER__
#  define SIZEOF_INT       __SIZEOF_INT__
#  define SIZEOF_LONG      __SIZEOF_LONG__
#  define SIZEOF_LONG_LONG __SIZEOF_LONG_LONG__

/*
 * Is always 8 bytes, thanks to the -D_FILE_OFFSET_BITS=64 preprocessor option
 * passed (see buildfile). We also check this at the compile time using
 * _Static_assert() (see mysql/libmysql/assert.c).
 */
#  define SIZEOF_OFF_T     8

/*
 * There is no way to exactly tell the time_t type size at the preprocessing
 * time, so we define it as the most probable one. We check this assumption
 * at the compile time using _Static_assert() (see mysql/libmysql/assert.c).
 */
#  define SIZEOF_TIME_T __SIZEOF_LONG__
#else
#  define SIZEOF_INT       4
#  define SIZEOF_LONG      4
#  define SIZEOF_LONG_LONG 8
#   define SIZEOF_OFF_T    4
#  ifdef _WIN64
#    define SIZEOF_VOIDP   8
#    define SIZEOF_TIME_T  8
#  else
#    define SIZEOF_VOIDP   4
#    define SIZEOF_TIME_T  8
#  endif
#  define SIZEOF_CHARP     SIZEOF_VOIDP
#endif

#define HAVE_STRUCT_TIMESPEC

/*
 * Hard to even find any records of these types.
 */
#undef HAVE_UINT
#undef HAVE_ULONG

/*
 * Usage of libc++.
 */
#ifdef  _LIBCPP_VERSION
#  define HAVE_LLVM_LIBCPP 1
#endif

/*
 * Specific for Linux.
 */
#ifdef __linux__
#  define HAVE_MMAP64         1
#  define HAVE_POSIX_TIMERS   1

/*
 * The fdatasync() system call appeared in FreeBSD more recently (11.1), so we
 * disable it's usage on FreeBSD.
 */
#  define HAVE_DECL_FDATASYNC 1
#  define HAVE_FDATASYNC      1

/*
 * Irrelevant for the client.
 */
#  undef HAVE_LINUX_LARGE_PAGES
#endif

/*
 * Specific for FreeBSD.
 */
#ifdef __FreeBSD__
#  define HAVE_IEEEFP_H 1
#endif

/*
 * Specific for FreeBSD and Linux.
 */
#if defined(__FreeBSD__) || defined(__linux__)
#  define HAVE_CLOCK_GETTIME   1
#  define HAVE_CUSERID         1
#  define HAVE_SIGEV_THREAD_ID 1
#endif

/*
 * Specific for FreeBSD and Mac OS.
 */
#if defined(__FreeBSD__) || defined(__APPLE__)
#  define FIONREAD_IN_SYS_FILIO      1
#  define HAVE_KQUEUE_TIMERS         1
#  define HAVE_SOCKADDR_IN_SIN_LEN   1
#  define HAVE_SOCKADDR_IN6_SIN6_LEN 1
#endif

/*
 * Specific for POSIX.
 */
#ifndef _WIN32
#  define HAVE_DLFCN_H          1
#  define HAVE_LANGINFO_H       1
#  define HAVE_POLL_H           1
#  define HAVE_POLL             1
#  define HAVE_PWD_H            1
#  define HAVE_SYS_IOCTL_H      1
#  define HAVE_SYS_MMAN_H       1
#  define HAVE_SYS_RESOURCE_H   1
#  define HAVE_SYS_SELECT_H     1
#  define HAVE_SYS_SOCKET_H     1
#  define HAVE_TERMIOS_H        1
#  define HAVE_UNISTD_H         1
#  define HAVE_SYS_UN_H         1
#  define HAVE_BACKTRACE        1
#  define HAVE_FTRUNCATE        1
#  define HAVE_DLOPEN           1
#  define HAVE_FCNTL            1
#  define HAVE_FSEEKO           1
#  define HAVE_FSYNC            1
#  define HAVE_GETPASS          1
#  define HAVE_GETPWNAM         1
#  define HAVE_GETPWUID         1
#  define HAVE_GETRLIMIT        1
#  define HAVE_GETRUSAGE        1
#  define HAVE_LSTAT            1
#  define HAVE_READLINK         1
#  define HAVE_REALPATH         1
#  define HAVE_STPCPY           1
#  define HAVE_STPNCPY          1
#  define HAVE_NL_LANGINFO      1
#  define HAVE_SYS_TIME_H       1
#  define HAVE_SYS_TIMES_H      1
#  define HAVE_TIMES            1
#  define HAVE_GETTIMEOFDAY     1
#  define FIONREAD_IN_SYS_IOCTL 1
#  define TIME_WITH_SYS_TIME    1
#  define DEFAULT_TMPDIR        P_tmpdir

/*
 * Not POSIX but are present on Linux and BSDs.
 */
#  define HAVE_EXECINFO_H 1

/*
 * Support for tagging symbols with __attribute__((visibility("hidden")))
 */
#  define HAVE_VISIBILITY_HIDDEN 1

/*
 * Compiler builtins.
 */
#  define HAVE_BUILTIN_UNREACHABLE 1
#  define HAVE_BUILTIN_EXPECT      1
#  define HAVE_BUILTIN_STPCPY      1
#  define HAVE_GCC_ATOMIC_BUILTINS 1
#  define HAVE_GCC_SYNC_BUILTINS   1

/*
 * Specific for Windows.
 */
#else
#  define WITH_PERFSCHEMA_STORAGE_ENGINE 1
#  define HAVE_TELL                      1
#  define DEFAULT_TMPDIR                 ""
#endif

/*
 * Common for all supported OSes/compilers.
 */
#define HAVE_COMPRESS 1
#define HAVE_STRNLEN  1
#define HAVE_ISINF    1
#define HAVE_IPV6     1
#define MAX_INDEXES   64U

/*
 * Collations are added for the enabled character sets.
 */
#define MYSQL_DEFAULT_CHARSET_NAME   "latin1"
#define MYSQL_DEFAULT_COLLATION_NAME "latin1_swedish_ci"
#define HAVE_CHARSET_armscii8        1
#define HAVE_CHARSET_ascii           1
#define HAVE_CHARSET_big5            1
#define HAVE_CHARSET_cp1250          1
#define HAVE_CHARSET_cp1251          1
#define HAVE_CHARSET_cp1256          1
#define HAVE_CHARSET_cp1257          1
#define HAVE_CHARSET_cp850           1
#define HAVE_CHARSET_cp852           1
#define HAVE_CHARSET_cp866           1
#define HAVE_CHARSET_cp932           1
#define HAVE_CHARSET_dec8            1
#define HAVE_CHARSET_eucjpms         1
#define HAVE_CHARSET_euckr           1
#define HAVE_CHARSET_gb18030         1
#define HAVE_CHARSET_gb2312          1
#define HAVE_CHARSET_gbk             1
#define HAVE_CHARSET_geostd8         1
#define HAVE_CHARSET_greek           1
#define HAVE_CHARSET_hebrew          1
#define HAVE_CHARSET_hp8             1
#define HAVE_CHARSET_keybcs2         1
#define HAVE_CHARSET_koi8r           1
#define HAVE_CHARSET_koi8u           1
#define HAVE_CHARSET_latin1          1
#define HAVE_CHARSET_latin2          1
#define HAVE_CHARSET_latin5          1
#define HAVE_CHARSET_latin7          1
#define HAVE_CHARSET_macce           1
#define HAVE_CHARSET_macroman        1
#define HAVE_CHARSET_sjis            1
#define HAVE_CHARSET_swe7            1
#define HAVE_CHARSET_tis620          1
#define HAVE_CHARSET_ucs2            1
#define HAVE_CHARSET_ujis            1
#define HAVE_CHARSET_utf16           1
#define HAVE_CHARSET_utf32           1
#define HAVE_CHARSET_utf8            1
#define HAVE_CHARSET_utf8mb4         1
#define HAVE_UCA_COLLATIONS          1

#undef DISABLE_PSI_THREAD
#undef DISABLE_PSI_MUTEX
#undef DISABLE_PSI_RWLOCK
#undef DISABLE_PSI_COND
#undef DISABLE_PSI_FILE
#undef DISABLE_PSI_TABLE
#undef DISABLE_PSI_SOCKET
#undef DISABLE_PSI_STAGE
#undef DISABLE_PSI_STATEMENT
#undef DISABLE_PSI_SP
#undef DISABLE_PSI_PS
#undef DISABLE_PSI_IDLE
#undef DISABLE_PSI_STATEMENT_DIGEST
#undef DISABLE_PSI_METADATA
#undef DISABLE_PSI_MEMORY
#undef DISABLE_PSI_TRANSACTION

/*
 * Obsolete headers and functions.
 */
#undef HAVE_TERMIO_H

/*
 * Specific for unsupported OSes (Solaris, SunOS, HP-UX...).
 */
#undef HAVE_PRINTSTACK
#undef HAVE_GETHRTIME
#undef HAVE_GETPASSPHRASE
#undef HAVE_SIGEV_PORT
#undef HAVE_SOLARIS_ATOMIC

/*
 * The upstream package undefines it for all supported compilers.
 */
#undef HAVE_ABI_CXA_DEMANGLE

/*
 * The upstream package defines it only for MacOS. Let's disable tracing for it
 * as well.
 */
#undef HAVE_DTRACE

/*
 * We don't assume any instrumentation.
 */
#undef HAVE_VALGRIND
#undef HAVE_ASAN

/*
 * Usage of alloca() is discouraged on Linux and BSDs, so let's not use it.
 */
#undef HAVE_ALLOCA_H

#undef ss_family
#undef ENABLED_LOCAL_INFILE
#undef WITH_NDBCLUSTER_STORAGE_ENGINE
#undef EXTRA_DEBUG

#endif // MYSQL_MY_CONFIG_H

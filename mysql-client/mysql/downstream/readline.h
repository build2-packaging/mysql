/* file      : mysql/downstream/readline.h
 * license   : GPLv2 with Universal FOSS Exception; see accompanying LICENSE file
 */

#ifndef MYSQL_DOWNSTREAM_READLINE_H
#define MYSQL_DOWNSTREAM_READLINE_H

/*
 * Reduced implementation of the libedit library based on libisocline.
 *
 * Specially, only the basic line editing functionality is supported (no
 * completion, history, etc).
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Thin wrapper around libisocline's ic_readline().
 */
char*
readline (const char* prompt);

/*
 * Reading function stubs.
 */
typedef char** rl_completion_func_t (const char*, int, int);
typedef char*  rl_compentry_func_t (const char*, int);
typedef int    rl_command_func_t (int, int);
typedef char*  rl_compentry_func_t (const char*, int);

int    rl_insert (int, int);
int    rl_add_defun (const char*, rl_command_func_t*, int);
char** rl_completion_matches (const char*, rl_compentry_func_t*);

extern char*                 rl_readline_name;
extern rl_completion_func_t* rl_attempted_completion_function;
extern rl_compentry_func_t*  rl_completion_entry_function;

/*
 * Hstory function stubs.
 */
typedef struct _hist_entry {
  const char *line;
  const char *data;
} HIST_ENTRY;

int         add_history (const char*);
int         read_history (const char*);
int         write_history (const char*);
HIST_ENTRY* history_get (int);

extern int history_length;

#ifdef __cplusplus
}
#endif

#endif /* MYSQL_DOWNSTREAM_READLINE_H */

/* file      : mysql/downstream/readline.h
 * license   : GPLv2 with Universal FOSS Exception; see accompanying LICENSE file
 */

#include <downstream/readline.h>

#include <isocline.h>

char*                 rl_readline_name = NULL;
rl_completion_func_t* rl_attempted_completion_function = NULL;
rl_compentry_func_t*  rl_completion_entry_function = NULL;

int history_length = 0;

/* Perform some basic libisocline initialization on the first readline() call.
 */
static int init = 1;

#define UNUSED(x) (void)(x)

char*
readline (const char* prompt)
{
  if (init)
  {
    init = 0;

    ic_set_prompt_marker("" /* prompt_marker */,
                         NULL /* continuation_prompt_marker */);

  }

  return ic_readline (prompt);
}

int
add_history (const char* command)
{
  UNUSED (command);
  return 1; /* Unsupported */
}

int
read_history (const char* file)
{
  UNUSED (file);
  return 1; /* Unsupported */
}

int
write_history (const char* command)
{
  UNUSED (command);
  return 1; /* Unsupported */
}

HIST_ENTRY*
history_get (int offset)
{
  UNUSED (offset);
  return NULL;
}

int
rl_insert (int count, int chr)
{
  UNUSED (count);
  UNUSED (chr);
  return 1; /* Unsupported */
}

int
rl_add_defun (const char* name, rl_command_func_t* f, int chr)
{
  UNUSED (name);
  UNUSED (f);
  UNUSED (chr);
  return 1; /* Unsupported */
}

char**
rl_completion_matches (const char* str, rl_compentry_func_t* f)
{
  UNUSED (str);
  UNUSED (f);
  return NULL;
}

/*!
   \file amash.h
   \brief Contains all the major struct, union, and API function definitions.
   \author Sumeet Padavala
   \date "16"/"March"/"2018"
*/
#ifndef AMASH_H
#define AMASH_H 1

/**
 *  \struct ParsedInput
 *  \brief Represents one line of input after parsing(by the parse function).
 */
typedef struct ParsedInput{
    char** exec_strings;    /*!< List of executables to pipe to each other in sequence */
    int exec_strings_count; /*!< Number of executables */
    Redirect* redirects;    /*!< List of file redirects to apply to the executable chain */
    int redirects_count;    /*!< Number of executables */
//    char* env;              /*!< Environment variables to apply */
//    int env_count;          /*!< Number of environment variables */
} ParsedInput;

/**
 *  \union Target
 *  \brief This union represents a target of a redirection.
 *         This can be either a file handle or a path name(relative or absolute)
 */
typedef union Target {
    char* path;             /*!< Path to the file */
    int file_handle;        /*!< file handle of the target */
} Target;


typedef struct Redirect{
    int file_handle;        /*!< source file handle to redirect to the target */
    bool target_is_path;    /*!< Is the target a path or file handle? */
    Target target;          /*!< target of the redirection (a union) */
} Redirect;

typedef struct ExecutableOptions{
    char* exec_string;      /*!< string of the exectuable to run */
    Redirect* redirects;    /*!< list of redirects to apply */
    int redirects_count;    /*!< Number of redirects to apply */
} ExecutableOptions;

/**
 *  Parse the received input, and produce a ParsedInput object
 *  @param  input input string
 *  @return       An object representing a breakdown of the given command
 */
ParsedInput* parse(char* input);

/**
 *  Executes parsed input, delegates most of the work to exec. Mostly concerned
 *  with pipes and stuff.
 *  @param i Parsed input
 */
void exec_input(ParsedInput* i);

/**
 *  Executes a single program in a new process(after forking). Uses execp to search PATH, if necessary.
 *  @param e Details of the executable
 */
void exec(ExecutableOptions* e);

/**
 *  Starts the main event loop
 *  @return exit code
 */
int run_event_loop();


#endif

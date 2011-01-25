/*
 *  ODBC Shell
 *  Copyright (C) 2011 Bindle Binaries <syzdek@bindlebinaries.com>.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_START@
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Bindle Binaries nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_END@
 */
/**
 *  @file src/odbcshell-commands.c ODBC Shell commands
 */
#include "odbcshell-commands.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark Headers

#include "odbcshell.h"

#include <stdio.h>

#include "odbcshell-commands.h"
#include "odbcshell-variables.h"


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark -
#pragma mark Functions

/// displays usage information
/// @param[in]  cnf      pointer to configuration struct
/// @param[in]  argc     number of arguments passed to command
/// @param[in]  argv     array of arguments passed to command
int odbcshell_cmd_help(ODBCShell * cnf, int argc, char ** argv)
{
   unsigned          u;
   ODBCShellOption * cmd;

   if (!(cnf))
      return(0);
   if (!(argv))
      return(0);

   // prints list of help topics
   if (argc == 1)
   {
      printf("This is %s version %s\n", PROGRAM_NAME, PACKAGE_VERSION);
      printf("Topics:\n");
      for(u = 0; odbcshell_cmd_strings[u].name; u++)
      {
         if ((u%5) == 0)
            printf("       ");
         printf("%-12s", odbcshell_cmd_strings[u].name);
         if ((u%5) == 4)
            printf("\n");
      };
      if ((u%5) != 0)
         printf("\n");

      printf("For more info use \"HELP <topic>;\".\n");
      printf("End of HELP info.\n");
      return(0);
   };

   if (!(cmd = odbcshell_lookup_opt_by_name(odbcshell_cmd_strings, argv[1])))
   {
      printf("HELP topic \"%s\" unknown.\n", argv[1]);
      return(0);
   };
   if (!(cmd->name))
   {
      printf("HELP topic \"%s\" unknown.\n", argv[1]);
      return(0);
   };

   printf("%s Command:\n", cmd->name);
   if (cmd->desc)
   {
      printf("Description:\n");
      printf("       %s\n", cmd->desc);
   };
   if (cmd->usage)
   {
      printf("Usage:\n");
      for(u = 0; cmd->usage[u]; u++)
         printf("       %s%s\n", cmd->name, cmd->usage[u]);
   };
   if ( (!(cmd->usage)) && (!(cmd->desc)) )
      printf("       Help information for this topic is unavailable.\n");
   printf("End of HELP info.\n");

   return(0);
}


/// displays information stating the function is incomplete
/// @param[in]  cnf      pointer to configuration struct
/// @param[in]  argc     number of arguments passed to command
/// @param[in]  argv     array of arguments passed to command
/// @param[in]  line     unmodified line sent to ODBC shell
int odbcshell_cmd_incomplete(ODBCShell * cnf, int argc, char ** argv, char * line)
{
   printf("WARNING: \"%s\" is not implemented.\n", argv[0]);
   if ( (!(argc)) || (!(cnf)) || (!(argv)) || (!(line)) )
      return(0);
   return(0);
}


/// exits from shell
/// @param[in]  cnf      pointer to configuration struct
int odbcshell_cmd_quit(ODBCShell * cnf)
{
   if (!(cnf))
      return(1);

   if (!(cnf->silent))
      printf("bye.\n");

   return(1);
}


/// displays version information
/// @param[in]  cnf      pointer to configuration struct
int odbcshell_cmd_version(ODBCShell * cnf)
{
   if (!(cnf))
      return(0);
   odbcshell_version();
   return(0);
}

/* end of source */

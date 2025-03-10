/******************************************************************
*
*   file:     cmds.c
*   author:   betty o'neil
*   date:     ?
*
*   semantic actions for commands called by tutor (cs341, hw2)
*
*   revisions:
*      9/90  eb   cleanup, convert function declarations to ansi
*      9/91  eb   changes so that this can be used for hw1
*      9/02  re   minor changes to quit command
*/
/* the Makefile arranges that #include <..> searches in the right
   places for these headers-- 200920*/

#include <stdio_1.h>
#include "slex.h"

/*===================================================================*
*
*   Command table for tutor program -- an array of structures of type
*   cmd -- for each command provide the token, the function to call when
*   that token is found, and the help message.
*
*   slex.h contains the typdef for struct cmd, and declares the
*   cmds array as extern to all the other parts of the program.
*   Code in slex.c parses user input command line and calls the
*   requested semantic action, passing a pointer to the cmd struct
*   and any arguments the user may have entered.
*
*===================================================================*/

PROTOTYPE int stop(Cmd *cp, char *arguments);
PROTOTYPE int mem_display(Cmd *cp, char *arguments);
PROTOTYPE int mem_set(Cmd *cp, char *arguments);
PROTOTYPE int help(Cmd *cp, char *arguments);
PROTOTYPE unsigned int atox(char **arguments);
/* command table */

Cmd cmds[] = {{"md",  mem_display, "Memory display: MD <addr>"},
              {"ms",  mem_set, "Memory set: MS <addr> <value>"},
              {"h",   help, "Help: H <command>"},
              {"s",   stop,        "Stop" },
              {NULL,  NULL,        NULL}};  /* null cmd to flag end of table */

char xyz = 6;  /* test global variable  */
char *pxyz = &xyz;  /* test pointer to xyz */
/*===================================================================*
*		command			routines
*
*   Each command routine is called with 2 args, the remaining
*   part of the line to parse and a pointer to the struct cmd for this
*   command. Each returns 0 for continue or 1 for all-done.
*
*===================================================================*/

int stop(Cmd *cp, char *arguments)
{
  return 1;			/* all done flag */
}

/*===================================================================*
*
*   mem_display: display contents of 16 bytes in hex
*
*/

int mem_display(Cmd *cp, char *arguments)
{
  unsigned int address;
  int value = 0;
  unsigned char *address_pointer;
  sscanf(arguments, "%x", &address);
  address_pointer = (char *)address;
  printf("Here is the address: %08x \n", address);
  for(value = 0; value < 16; value++)
  	printf("%02x ", *address_pointer++);
  address_pointer = (unsigned char *)address;
  for(value = 0; value < 16; value++) {
  	if(*address_pointer > 0x20 && *address_pointer < 0x7f) {
    printf("%c", *address_pointer++);
  }
	else {
		printf(".");
		address_pointer++;
    }
  }

  printf("\n");	  
  printf("Reached mem_display, passed argument string: |%s|\n", arguments);
  printf("        help message: %s\n", cp->help);
  return 0;			/* not done */

}


int mem_set(Cmd *cp, char *arguments)
{
  int val = 0, address;
  char *address_pointer;
  sscanf(arguments,"%x %x", &address, &val );
  address_pointer = (char *)address;
  *address_pointer = val;
  return 0;
}


int help(Cmd *cp, char *arguments)
{
  char size[6];
  int num = 0;
  int length = sizeof(cmds)/sizeof(Cmd);
  sscanf(arguments, "%s", size);
while (num < length){
  if ((strcmp(cmds[num].cmdtoken, size)) == 0) {
		printf("%s\n", cmds[num].help);
    break;
} else num++ ;
}
return 0;
  
}
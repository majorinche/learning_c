#include "lib/command_comm.h"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <pwd.h>

static int pr_whoami()
{
    struct passwd   *pass = getpwuid(geteuid());
    printf("%s is current user\n", pass->pw_name);
    printf("%s is current user's shell path\n", pass->pw_shell);
    return 0;
}

int main(int argc, char *argv[])
{
    program_name = argv[0];
    exit_status = pr_whoami();
    exit(exit_status);
}


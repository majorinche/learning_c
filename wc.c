#include "lib/command_comm.h"
#include "lib/err_msg.h"
#include "lib/file_isexist.h"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <sys/vfs.h>
#include <errno.h>
#include <math.h>

struct wc_option
{
    unsigned char           c;      
    unsigned char           l;      
    unsigned char           w;      
};

struct wc_count
{
    unsigned int            c;
    unsigned int            l;
    unsigned int            w;
};

struct wc_option            g_option; //this is a required step, or variable undeclared error will happen
struct wc_count             g_count;

static void init_option()
{
    memset(&g_option, 0, sizeof(g_option));
}

static void pr_wc(const char *file)
{
    if(g_option.c == 0 && g_option.l == 0)
    {
        printf("%u\t%u\t%s\n", g_count.l, g_count.c, file);
        return;
    }

    if(g_option.l != 0)
        printf("%u\t", g_count.l);

    printf("%s\n", file);
}

static int wc(const char *file)
{
    FILE            *fp;
    char            buf[MAX_LINE_BUF_SIZE];

    if(!file_isreg(file))
    {
        pr_msg("file [%s] is not access or is not a simple file\n", file);
        return 1;
    }

    if((fp = fopen(file, "r")) == NULL)
    {
        pr_msg("open file [%s] error [%s]\n", file, strerror(errno));
        return 1;
    }

    memset(&g_count, 0, sizeof(g_count)); //we can consider it is used to prepare some memory resouces!
    while(fgets(buf, MAX_LINE_BUF_SIZE, fp) != NULL)
    {
        ++g_count.l; //can count line number
        g_count.c += strlen(buf); //can count character number
    }

    pr_wc(file);
    return 0;
}

int main(int argc, char *argv[])
{
    int                 c;
    static struct option const long_options[] =
    {
        {"lines", 0, NULL, 'l'},
        {"chars", 0, NULL, 'c'},
        {NULL, 0, NULL, 0}
    };
    exit_status = 0;
    program_name = argv[0];
    init_option();
    while((c = getopt_long(argc, argv,"lc", long_options, NULL)) != -1)
    {
        switch(c)
        {
            case 'l':
                g_option.l = 1;
                break;
            case 'c':
                g_option.c = 1;
                break;
            default:
                break;
        }
    }

    while(optind < argc)
        if(wc(argv[optind++]) != 0)
            exit_status = 0;

    exit(exit_status);
}


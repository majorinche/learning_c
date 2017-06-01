#include <stdio.h>     
#include <stdlib.h>   
#include <fcntl.h>
#include <unistd.h>
#define     MAX_BUF_SIZE            1024
static char             *infile = NULL;         
static int              input_desc = -1;       
static void _cat(int fileno)
{
    char                buf[MAX_BUF_SIZE];
    int                 n;
    n = read(fileno, buf, MAX_BUF_SIZE);
    write(STDOUT_FILENO, buf, n);
    exit(0);
}
static void simple_cat(char *file)
{
    input_desc = open(file, O_RDONLY);
    _cat(input_desc);
    close(input_desc);
}
int main(int argc,char *argv[])
{
    infile = argv[1];
    simple_cat(infile);
}

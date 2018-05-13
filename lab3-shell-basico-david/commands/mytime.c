#include <stdio.h>
#include <stdlib.h>         //exit
#include <unistd.h>
#include <sys/syscall.h>    //syscall  
#include <time.h>

int main(int argc, char *argv[]) {

    time_t rawTime;
    struct tm *info;

    syscall(SYS_time, &rawTime);
    info = localtime(&rawTime);
    
    printf("%s",asctime(info));    
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>         //exit
#include <unistd.h>
#include <sys/syscall.h>    //syscall  

int main(int argc, char *argv[]) {
    
    char *buffer = (char *)malloc(1000);
    
    syscall(SYS_getcwd, buffer);
    printf("%s", buffer);
    printf("\n");

    free(buffer);
    exit(0);
}

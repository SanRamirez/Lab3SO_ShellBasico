#include <stdio.h>
#include <stdlib.h>         //exit
#include <unistd.h>
#include <sys/syscall.h>    //syscall  

int main(int argc, char *argv[]) {

    for (int i = 0; i < argc-1; i++) {
        printf("%s ", argv[i+1]);
    }

    printf("\n");
    exit(0);
}

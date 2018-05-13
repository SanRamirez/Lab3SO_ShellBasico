#define _GNU_SOURCE
#include <dirent.h>     /* Defines DT_* constants */
#include <fcntl.h>      // R_RDONLY, O_DIRECTORY flags
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

#define BUF_SIZE 1024

struct linux_dirent {
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

int main(int argc, char *argv[]) {

    int fileDescriptor, bytes;
    char buf[BUF_SIZE];
    struct linux_dirent *directoryEntity;
    int bytePosition;

    fileDescriptor = open("/proc", O_RDONLY | O_DIRECTORY);

    if (fileDescriptor == -1) {
        printf("error al abrir el archivo");
        exit(1);
    }        

    for(;;) {

        bytes = syscall(SYS_getdents, fileDescriptor, buf, BUF_SIZE); 

         if (bytes == -1) {
            printf("error al intentar de acceder a la informacion del directorio");
            exit(1);
         }            

        if (bytes == 0)
            break;

        for (bytePosition = 0; bytePosition < bytes;) {

            directoryEntity = (struct linux_dirent *) (buf + bytePosition);
            printf("%s \n", directoryEntity->d_name);

            bytePosition += directoryEntity->d_reclen;
        }
    }

    exit(0);
}

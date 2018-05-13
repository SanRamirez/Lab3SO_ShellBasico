#include <stdio.h>
#include <stdlib.h>         //exit
#include <unistd.h>
#include <sys/syscall.h>    //syscall  
#include <errno.h>

int main(int argc, char *argv[]) {

    // signal list: http://www.comptechdoc.org/os/linux/programming/linux_pgsignals.html
    // error list:  http://www-numi.fnal.gov/offline_software/srt_public_context/WebDocs/Errors/unix_system_errors.html

    int signal = atoi(argv[1]);
    int processId = atoi(argv[2]);

    int resultCode = syscall(SYS_kill, processId, signal);
    
    if (resultCode == -1) {
        
        switch(errno) {
            
            case EINVAL:
                printf("Señal invalida");
                break;
        
            case EPERM:
                printf("El proceso actual no tiene los permisos para enviar dicha señal al proceso objetivo");
                break;
            
            case ESRCH:
                printf("El proceso no existe");
                break;  
        }
    }  
        
    exit(0);
}

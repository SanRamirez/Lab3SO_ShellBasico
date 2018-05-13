#include <stdio.h>
#include <string.h>
#include <stdlib.h>    
#include <unistd.h>    
#include <sys/types.h> 
#include <sys/wait.h>  
#include <sys/types.h> 
#include <errno.h>

// definicion de comandos para el shell
#define outercall -1
#define mypwd 1
#define mycp 2
#define myecho 3
#define myclear 4
#define mykill 5
#define mytime 6
#define myps 7
#define myexit 8


void handleError(int resultCode) {

    if (resultCode == -1) {
        printf("El programa no se pudo ejecutar y ha generado el siguiente error: %d\n", errno);
    }
}

void createChild(char* path, char** items, int background) {

    int estado, resultCode;
    pid_t childProcess;

    childProcess = fork();

    if (childProcess == 0){
        
        resultCode = execv(path, items);                
        handleError(resultCode);

    } else {    

        if (background == 0) {
            wait(&estado);
        }
    }
}


// Definición de struct
typedef struct {
    char *key;
    int val;
} shellDictionary;

static shellDictionary table[] = {
    {"mypwd", mypwd}, 
    {"mycp", mycp},
    {"myecho", myecho},
    {"myclear", myclear},
    {"mykill", mykill},
    {"mytime", mytime}, 
    {"myps", myps},
    {"myexit", myexit}
};

int getComandosShell(char *key) {

    long dictionarySize = (sizeof(table)/ sizeof(shellDictionary));
    
    for (int i = 0; i < dictionarySize; i++) {  

        if (strcmp(table[i].key, key) == 0)
            return table[i].val;            
    }
    return outercall;
}


void atentionCallShell(char *expresion, char** items , int background) {

    char* program;
    char path[300];

    getcwd(path, sizeof(path));

    switch(getComandosShell(items[0])) {     

        case mypwd:         
            program = "/commands/mypwd.o";
            strcat(path, program);            
            createChild(path, items, background);
            break;        

        case myecho:
            program = "/commands/myecho.o";
            strcat(path, program);            
            createChild(path, items, background);       
            break;

        case myclear:            
            program = "/commands/myclear.o";
            strcat(path, program);            
            createChild(path, items, background);       
            break;

        case mykill:
            program = "/commands/mykill.o";
            strcat(path, program);            
            createChild(path, items, background);       
            break;

        case mytime:
            program = "/commands/mytime.o";
            strcat(path, program);            
            createChild(path, items, background);       
            break;    

        case myps:
            program = "/commands/myps.o";
            strcat(path, program);            
            createChild(path, items, background);       
            break;   

        case myexit: 
            exit(0);

        case outercall:
            program = items[0];                        
            createChild(program, items, background);
            break;  
    }
}


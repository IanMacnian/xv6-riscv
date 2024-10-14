#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
    for(int i = 0; i < 20; i++){
        if(fork() == 0){
            printf("Ejecutando proceso %d %d\n", i, getpid());
            sleep(10); // Simula trabajo con sleep
            exit(0);
        }
    }
    while(wait(0) > 0); // Espera a que todos los procesos terminen
    exit(0);
}

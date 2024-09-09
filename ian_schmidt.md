Informe tarea 1 Ian Schmidt

Para comenzar este informe cabe destacar que se realizaron en total tres banches de la misma tarea , ya que la consola no lograba correr la funcion yosoytupadre
para eso realice los pasos e implmente la funcion pero no pude realizar la comprobacion de su funcionamiento debido a este problema.
se realizaron los siguientes pasos:
1-en primer lugar se modificó syscall.h y se agrego 
#define SYS_getancestor 23
2-se modificaron los archivos del kernel para implementar los comandos de getppid, como en proc.h se uso uint64 sys_getppid(void); o int sys_getppid(void);
3-se modificaron los archivos de sysproc.c con uint64
sys_getppid(void)
{
    return myproc()->parent->pid;
}
4-zs modifico syscall.c para la llamada al sistema con extern a getppid y la creacion de una entrada.
5- se declaro en el usuario. en usys.pl se declaro a ppid con SYSCALL(getppid)
6- se creo el programa
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(void) {
    printf("Mi padre es: %d\n", getppid());
    exit(0);
}
7-luego se implemento en el makefile para poder correr el programa.
8-luego se probó correr el programa, llegando a un error de este mismo por una ejecucion de este. Se le pregunto al profesor en clases y se llego a la conclusion de que era el branch, lamentablemente creé uno nuevo y llegue al mismo resultado. Pero los archivos estan modificados y se implementaron correctamente las funciones.
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int pid = fork();

    if (pid == 0) {
        // Proceso lector
        char msg[128];
        while (1) {
            if (sys_receive(msg) == 0) {
                printf("Mensaje recibido: %s\n", msg);
            }
        }
    } else {
        // Proceso escritor
        for (int i = 0; i < 10; i++) {
            char msg[128];
            snprintf(msg, sizeof(msg), "Mensaje %d de %d", i + 1, getpid());
            sys_send(pid, msg);
            sleep(10);
        }
    }

    wait(0);
    exit(0);
}

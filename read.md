1 Añadí el campo de prioridad en la estructura de proceso (proc.h) e inicialicé cada proceso con prioridad 0.
2 Añadí el campo de boost también en la estructura de proceso (proc.h) y lo inicialicé en 1.
3 Modifiqué el planificador en proc.c para que, cada vez que un proceso entrara, aumentara la prioridad de todos los procesos que pudieran ejecutarse (excepto zombies).
4 Implementé la lógica para que:
La prioridad aumentara con el boost.
Si la prioridad llegaba a 9, el boost cambiara a -1.
Si la prioridad bajaba a 0, el boost cambiara a 1.
5 Hice un programa de prueba (testprio.c) que usaba fork para crear 20 procesos, cada uno mostrando un mensaje con su nombre y pid, y luego hacía sleep.
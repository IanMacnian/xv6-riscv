README: Implementación de un Sistema de Comunicación entre Procesos (IPC) en xv6
Este documento describe los pasos necesarios para implementar un sistema de colas de mensajes en xv6, los archivos nuevos, las modificaciones requeridas, y los posibles problemas o errores que pueden surgir durante la implementación.

1. Crear una estructura de datos para los mensajes
Archivo nuevo: message_queue.h
Define la estructura de un mensaje y la cola de mensajes.
Contiene atributos como el contenido del mensaje, el ID del remitente, y los controles para manejar la cola.
Incluye la función de inicialización de la cola.
2. Implementar la inicialización de la cola de mensajes
Archivo nuevo: message_queue.c

Implementa la cola de mensajes como una estructura global en el kernel.
Proporciona una función para inicializar la cola, definiendo índices de lectura/escritura y un spinlock.
Modificación en main.c:

Llama a la función de inicialización de la cola desde la función principal del kernel.
3. Implementar la llamada al sistema sys_send
Archivo modificado: sysproc.c

Se implementa la lógica de la llamada al sistema para que un proceso pueda enviar un mensaje a la cola.
Verifica el tamaño de la cola, copia el mensaje, actualiza los índices y despierta a los procesos bloqueados.
Archivos modificados:

syscall.c: Registra la nueva llamada al sistema.
syscall.h: Define un identificador único para la llamada.
4. Implementar la llamada al sistema sys_receive
Archivo modificado: sysproc.c

Implementa la lógica para que un proceso reciba mensajes desde la cola.
Si la cola está vacía, bloquea el proceso hasta que haya un nuevo mensaje disponible.
Archivos modificados:

syscall.c: Registra la nueva llamada al sistema.
syscall.h: Define un identificador único para la llamada.
5. Sincronización y bloqueo
Se utiliza un spinlock para asegurar que solo un proceso acceda a la cola a la vez.
Las funciones sleep y wakeup del kernel permiten bloquear procesos lectores cuando la cola está vacía.
6. Crear un programa de prueba
Archivo nuevo: user/send_receive.c

Luego se compila y se ejecuta el programa de prueba

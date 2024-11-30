Implementación de Permisos Básicos en xv6 (RISC-V)
Este documento describe los pasos realizados para implementar un sistema de permisos básicos en el sistema operativo xv6 (RISC-V). La funcionalidad permite gestionar permisos de solo lectura, escritura o ambos para archivos, además de agregar una nueva syscall para modificar estos permisos.

1. Modificación de la estructura del inode
Se añadió un campo en la estructura dinode llamado perm. Este campo permite definir los permisos de los archivos usando un número entero:

0: Sin acceso.
1: Solo lectura.
2: Solo escritura.
3: Lectura y escritura (por defecto al crear un archivo).
Esto permite al sistema distinguir entre los diferentes niveles de acceso que los archivos pueden tener.

2. Validación de permisos en sys_open
La función sys_open fue modificada para respetar los permisos definidos en el inode al momento de abrir un archivo. Se realizaron verificaciones para que:

Si el archivo está marcado como solo lectura, no se pueda abrir en modo escritura.
Si está marcado como sin acceso, se deniegue cualquier intento de apertura.
Cualquier operación que viole estos permisos devuelve un error al usuario.

3. Creación de la syscall chmod
Se implementó una nueva llamada al sistema, chmod, que permite a los usuarios cambiar los permisos de un archivo. Esta syscall toma como parámetros:

El nombre del archivo.
El nuevo modo de permisos (0, 1, 2 o 3).
La syscall actualiza los permisos directamente en el inode del archivo y persiste los cambios en el disco.

4. Programa de prueba
Se creó un programa de prueba que realiza las siguientes acciones:

Crea un archivo con permisos de lectura/escritura.
Escribe en el archivo para verificar que los permisos iniciales funcionan correctamente.
Cambia los permisos a solo lectura usando la syscall chmod.
Intenta abrir el archivo en modo escritura (lo cual debe fallar).
Restaura los permisos a lectura/escritura y verifica que la escritura es posible nuevamente.
Este programa asegura que los permisos se gestionan de forma correcta en diferentes escenarios.

Problemas Encontrados
1. Errores con SYS_chmod:
Inicialmente, el sistema arrojaba errores porque no se había registrado correctamente la nueva syscall. Fue necesario:

Añadir la constante SYS_chmod en los archivos de configuración de syscalls.
Registrar la función en la tabla de syscalls.
2. Campo perm no inicializado:
Al crear nuevos inodes, no se inicializaba el campo perm. Esto causaba comportamientos impredecibles. Se corrigió asegurando que el valor inicial sea 3 (lectura y escritura).

3. Validación incorrecta en sys_open:
En algunos casos, los permisos no se respetaban porque las verificaciones no cubrían todos los modos de apertura posibles. Se revisaron y ajustaron las condiciones para garantizar un comportamiento robusto.

validar la implementación:
chmodtest
El programa debería mostrar mensajes que confirmen si las operaciones se comportaron como se esperaba según los permisos asignados.

Conclusión
Esta implementación amplía las capacidades de xv6 al agregar un sistema de permisos más completo y personalizable. Los cambios realizados incluyen la modificación de estructuras, funciones clave y la creación de una nueva syscall. Con estas mejoras, el sistema es capaz de gestionar el acceso a los archivos de manera más segura y controlada.

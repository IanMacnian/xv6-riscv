1. Cambios en la estructura de archivos
Archivo: kernel/fs.h
Modifiqué la estructura dinode añadiendo un campo llamado perm para guardar los permisos de los archivos.
También agregué un campo de relleno (padding) para evitar problemas de alineación en disco.
2. Implementación de la llamada al sistema chmod
Archivo principal: kernel/sysfile.c
Creé la función sys_chmod, que:
Valida el nombre del archivo y los permisos nuevos.
Bloquea el inode, actualiza los permisos y guarda los cambios.
Luego, hice los ajustes necesarios para que el sistema reconozca esta nueva llamada:
Añadí referencias a sys_chmod en:
kernel/syscall.c
kernel/syscall.h
user/user.h
user/usys.pl
3. Comando de usuario chmod
Archivo: user/chmod.c
Creé un programa que permite cambiar los permisos de un archivo desde la terminal de xv6. Solo necesitas pasar el nombre del archivo y los permisos como argumentos.
4. Pruebas
Archivo: user/chmodtest.c
Escribí un programa de prueba para verificar que todo funciona correctamente. Este programa:
Crea un archivo.
Cambia sus permisos usando chmod.
Valida que los cambios se aplicaron.
5. Ajustes en la compilación
Archivo: Makefile
Añadí el nuevo comando chmod y el archivo de pruebas al sistema de compilación.
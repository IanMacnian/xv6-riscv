Implementación de Permisos Básicos en xv6 (RISC-V)
Este documento describe cómo se implementó un sistema básico de permisos en el sistema operativo educativo xv6. Los permisos permiten controlar si un archivo puede ser leído, escrito, o ambos, e incluyen la posibilidad de definir archivos como inmutables.

Requisitos Previos
Antes de comenzar, asegúrate de contar con lo siguiente:

Un entorno funcional de xv6 (RISC-V) configurado.
Familiaridad con la estructura del código de xv6, incluyendo los módulos de syscall, fs, y proc.
Herramientas como qemu y make para compilar y ejecutar xv6.
Modificaciones Realizadas
1. Estructura del Inode
Se añadió un campo llamado perm a la estructura dinode en fs.h. Este campo almacena los permisos del archivo:

0: Sin acceso.
1: Solo lectura.
2: Solo escritura.
3: Lectura y escritura.
Archivo modificado: fs.h

c
Copiar código
struct dinode {
  short type;            // Tipo de archivo
  short major;           // Número mayor (T_DEV solo)
  short minor;           // Número menor (T_DEV solo)
  short nlink;           // Número de enlaces
  uint size;             // Tamaño del archivo
  uint addrs[NDIRECT+1]; // Direcciones de bloques de datos
  int perm;              // Permisos (0 = sin acceso, 1 = lectura, 2 = escritura, 3 = lectura/escritura)
};
2. Validaciones en sys_open
Se modificó la función sys_open en sysfile.c para validar los permisos al abrir archivos. Dependiendo de los permisos del archivo (perm en el inode), se permite o deniega la operación.

Archivo modificado: sysfile.c

c
Copiar código
if ((omode & O_WRONLY) && !(ip->perm & 2)) {
  iunlockput(ip);
  end_op();
  return -1; // Error: No hay permisos de escritura
}

if ((omode & O_RDONLY) && !(ip->perm & 1)) {
  iunlockput(ip);
  end_op();
  return -1; // Error: No hay permisos de lectura
}
3. Nueva Llamada al Sistema: chmod
Se implementó una nueva syscall, chmod, para permitir a los usuarios modificar los permisos de un archivo.

Definición de chmod
Archivo modificado: sysproc.c

c
Copiar código
uint64 sys_chmod(void) {
  char path[MAXPATH];
  int mode;

  if (argstr(0, path, MAXPATH) < 0 || argint(1, &mode) < 0)
    return -1;

  return chmod(path, mode); // Lógica en fs.c
}
Archivo modificado: fs.c

c
Copiar código
int chmod(char *path, int mode) {
  struct inode *ip;

  begin_op();
  if ((ip = namei(path)) == 0) {
    end_op();
    return -1; // Error: Archivo no encontrado
  }
  ilock(ip);
  ip->perm = mode;
  iupdate(ip);
  iunlock(ip);
  end_op();
  return 0; // Éxito
}
Actualización de Archivos Relacionados
syscall.h: Añade la constante SYS_chmod.
c
Copiar código
#define SYS_chmod 22 // Asegúrate de usar un número único
syscall.c: Añade la entrada en la tabla de syscalls.
c
Copiar código
[SYS_chmod] sys_chmod,
usys.pl: Genera el wrapper para la syscall.
plaintext
Copiar código
entry("chmod");
4. Programa de Prueba
Se creó un programa en el espacio de usuario para validar los cambios. Este programa realiza las siguientes operaciones:

Crea un archivo con permisos de lectura/escritura (O_RDWR).
Escribe datos en el archivo.
Cambia los permisos a solo lectura (chmod).
Intenta escribir y verifica que falle.
Cambia los permisos a lectura/escritura y verifica que funcione.
Archivo de prueba: chmodtest.c

c
Copiar código
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main() {
  int fd;
  char *filename = "testfile";

  // Crear archivo con permisos de lectura/escritura
  fd = open(filename, O_CREATE | O_RDWR);
  write(fd, "test", 4);
  close(fd);

  // Cambiar permisos a solo lectura
  chmod(filename, 1);

  // Intentar abrir en modo escritura (debe fallar)
  fd = open(filename, O_WRONLY);
  if (fd < 0) {
    printf("Error al abrir para escritura: permisos insuficientes\n");
  } else {
    printf("Error: debería haber fallado\n");
    close(fd);
  }

  // Restaurar permisos de lectura/escritura
  chmod(filename, 3);

  // Escribir nuevamente
  fd = open(filename, O_WRONLY);
  if (fd >= 0) {
    write(fd, "test2", 5);
    close(fd);
    printf("Escritura restaurada correctamente\n");
  }
  exit(0);
}
Compila y ejecuta el programa:

bash
Copiar código
$ make qemu
# Dentro de xv6:
$ chmodtest
Inconvenientes y Soluciones
1. Errores en syscall.h
Problema: Las constantes de SYS_* no estaban definidas, causando errores de compilación.
Solución: Asegúrate de añadir SYS_chmod en syscall.h y actualizar syscall.c y usys.pl.
2. Validación Incorrecta en sys_open
Problema: Los permisos no se respetaban correctamente en los modos de apertura.
Solución: Se añadieron condiciones específicas para verificar si el archivo tiene permisos de lectura y/o escritura antes de permitir su apertura.
3. Valores Iniciales de Permisos
Problema: Los permisos del inode no se inicializaban correctamente al crear nuevos archivos.
Solución: Se estableció el valor por defecto 3 (lectura/escritura) en el campo perm al crear un nuevo inode.
Conclusión
Esta implementación añade una capa de control de acceso a los archivos en xv6, permitiendo gestionar sus permisos dinámicamente.
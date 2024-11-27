#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main() {
  int fd;
  char *filename = "testfile";

  // 1. Crear archivo con permisos de lectura/escritura
  fd = open(filename, O_CREATE | O_RDWR);
  if (fd < 0) {
    printf("Error creando el archivo\n");
    exit(1);
  }
  write(fd, "prueba", 6);
  close(fd);

  // 2. Cambiar permisos a solo lectura
  if (chmod(filename, 1) < 0) {
    printf("Error cambiando permisos\n");
    exit(1);
  }

  // 3. Intentar abrir en modo escritura (debe fallar)
  fd = open(filename, O_WRONLY);
  if (fd >= 0) {
    printf("Error: se permitió abrir en modo escritura con solo lectura\n");
    close(fd);
    exit(1);
  }

  // 4. Cambiar permisos de vuelta a lectura/escritura
  if (chmod(filename, 3) < 0) {
    printf("Error restaurando permisos\n");
    exit(1);
  }

  // 5. Escribir de nuevo
  fd = open(filename, O_RDWR);
  if (fd < 0) {
    printf("Error reabriendo archivo\n");
    exit(1);
  }
  write(fd, "final", 5);
  close(fd);

  printf("Pruebas completadas exitosamente\n");
  exit(0);
}

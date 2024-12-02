#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Uso: chmod <archivo> <permisos>\n");
    exit(1);
  }

  if (chmod(argv[1], atoi(argv[2])) < 0) {
    printf("Error: No se pudo cambiar los permisos de %s\n", argv[1]);
    exit(1);
  }

  printf("Permisos modificados correctamente para %s\n", argv[1]);
  exit(0);
}
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main() {
  int fd = open("testfile", O_CREATE | O_RDWR);
  if (fd < 0) {
    printf("Error al crear el archivo.\n");
    exit(1);
  }
  printf("Archivo creado exitosamente.\n");

  if (chmod("testfile", 1) < 0) {
    printf("Error al cambiar los permisos.\n");
    exit(1);
  }
  printf("Permisos modificados correctamente.\n");

  exit(0);
}

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(void) {
    printf("mi padre es %d\n", getppid());
    exit(0);
}
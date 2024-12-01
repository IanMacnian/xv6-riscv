#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_send(void) {
    int pid;
    char *msg;

    if (argint(0, &pid) < 0 || argptr(1, &msg, 128) < 0)
        return -1;

    acquire(&mq.lock);

    if (mq.size >= MAX_MESSAGES) {
        release(&mq.lock);
        return -1;  // Cola llena
    }

    message *m = &mq.messages[mq.tail];
    m->sender_pid = myproc()->pid;
    safestrcpy(m->content, msg, sizeof(m->content));

    mq.tail = (mq.tail + 1) % MAX_MESSAGES;
    mq.size++;

    wakeup(&mq); // Despertar procesos bloqueados
    release(&mq.lock);

    return 0; // Enviado con éxito
}

int sys_receive(void) {
    char *msg;

    if (argptr(0, &msg, 128) < 0)
        return -1;

    acquire(&mq.lock);

    while (mq.size == 0) {
        sleep(&mq, &mq.lock); // Bloquear si la cola está vacía
    }

    message *m = &mq.messages[mq.head];
    safestrcpy(msg, m->content, sizeof(m->content));

    mq.head = (mq.head + 1) % MAX_MESSAGES;
    mq.size--;

    release(&mq.lock);

    return 0; // Recibido con éxito
}

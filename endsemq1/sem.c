#include "types.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"

struct sem {
  int val;
  int used;
};

struct {
    struct spinlock lk;
  struct sem s[8];
} semtab;

void seminit(void)
{
  int i;
  initlock(&semtab.lk, "sem");
  for(i=0; i<8; i++){
      semtab.s[i].val = 0;
      semtab.s[i].used = 0;
  }
}

int
sem_init(int id, int value)
{
  if(id < 0 || id >= 8 || value < 0)
      return -1;

  acquire(&semtab.lk);
  semtab.s[id].val = value;
  semtab.s[id].used = 1;
  release(&semtab.lk);

  return 0;
}

int sem_wait(int id)
{
    if(id<0 || id>=8) return -1;

    acquire(&semtab.lk);
    if(!semtab.s[id].used){
      release(&semtab.lk);
      return -1;
    }

    while(semtab.s[id].val == 0){
        sleep(&semtab.s[id], &semtab.lk);
    }
    semtab.s[id].val--;
    release(&semtab.lk);
    return 0;
}

int
sem_post(int id)
{
  if (id < 0 || id >= 8)
    return -1;

  acquire(&semtab.lk);
  if(semtab.s[id].used == 0){
      release(&semtab.lk);
      return -1;
  }
  semtab.s[id].val++;
  wakeup(&semtab.s[id]);
  release(&semtab.lk);
  return 0;
}

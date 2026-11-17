#include "types.h"
#include "stat.h"
#include "user.h"

int gvar = 42;

int main(int argc, char *argv[])
{
  printf(1, "freepages at start-up: %d\n", freepages());

  sbrk(10 * 4096);
  printf(1, "freepages after sbrk(10*4096): %d\n", freepages());

  printf(1, "global var va: 0x%x, pa: 0x%x\n", (uint)&gvar, va2pa((int)&gvar));
  printf(1, "va2pa(0x7FFFFFFF): %d\n", va2pa(0x7FFFFFFF));

  int pid = fork();
  if(pid == 0){
      printf(1, "child global var va: 0x%x, pa: 0x%x\n", (uint)&gvar, va2pa((int)&gvar));
      printf(1, "freepages after fork: %d\n", freepages());
      exit();
  } else {
    wait();
    printf(1, "parent global var va: 0x%x, pa: 0x%x\n", (uint)&gvar, va2pa((int)&gvar));
    printf(1, "freepages after wait: %d\n", freepages());
  }

  exit();
}

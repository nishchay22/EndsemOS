#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
  sem_init(0, 1);
  sem_init(1, 0);
  sem_init(2, 0);

  int p1 = fork();
  if(p1 == 0){
      int i;
      for(i=0; i<5; i++){
        sem_wait(0);
        printf(1, "A ");
        sem_post(1);
      }
      exit();
  }

  int p2 = fork();
  if (p2 == 0) {
    int i;
    for(i = 0; i < 5; i++){
        sem_wait(1);
        printf(1, "B ");
        sem_post(2);
    }
    exit();
  }

  int p3 = fork();
  if(p3 == 0){
    int i;
    for (i=0; i<5; i++) {
      sem_wait(2);
      printf(1, "C ");
      sem_post(0);
    }
    exit();
  }

  wait();
  wait();
  wait();
  printf(1, "\nDone\n");
  exit();
}

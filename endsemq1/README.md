Changes made:

- sem.c: added semaphore table (size 8) with spinlock and implemented seminit, sem_init, sem_wait, and sem_post using sleep/wakeup.
- main.c: called seminit() on boot.
- defs.h: added function declarations for seminit, sem_init, sem_wait, sem_post.
- syscall.h, syscall.c, sysproc.c, user.h, usys.S: added system calls for sem_init, sem_wait, sem_post.
- synctest.c: user program that uses 3 semaphores to print A B C 5 times in order across 3 child processes.
- Makefile: added sem.o to OBJS and _synctest to UPROGS.
- Nishchay, 2401MC22, everyone got the same set.

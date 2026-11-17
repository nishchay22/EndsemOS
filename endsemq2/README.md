Changes made:

- kalloc.c: added nfree counter to kmem struct, updated it in kfree() and kalloc(), and implemented freepages().
- vm.c: implemented va2pa(int va) using walkpgdir() to return physical address or -1 if not present or PTE_U not set.
- defs.h: added declarations for freepages() and va2pa().
- syscall.h, syscall.c, sysproc.c, user.h, usys.S: wired up freepages and va2pa system calls.
- memtest.c: user program testing freepages(), sbrk(10*4096), va2pa() on a global variable and 0x7FFFFFFF, and comparing parent/child physical addresses and free page counts across fork() and wait().
- Makefile: added _memtest to UPROGS.
- Nishchay, 2401MC22, everyone got the same set.

jscherman@jscherman:~/ClionProjects/algo2-t3-abb$ g++ Conjunto.hpp tests.cpp && valgrind --leak-check=yes --show-leak-kinds=all --gen-suppressions=yes ./a.out
==4860== Memcheck, a memory error detector
==4860== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==4860== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==4860== Command: ./a.out
==4860== 
test_remover...ok
==4860== 
==4860== HEAP SUMMARY:
==4860==     in use at exit: 72,728 bytes in 2 blocks
==4860==   total heap usage: 18 allocs, 16 frees, 76,068 bytes allocated
==4860== 
==4860== 24 bytes in 1 blocks are definitely lost in loss record 1 of 2
==4860==    at 0x4C2E118: operator new(unsigned long) (vg_replace_malloc.c:333)
==4860==    by 0x40353A: Conjunto<int>::insertar(int const&) (in /home/jscherman/ClionProjects/algo2-t3-abb/a.out)
==4860==    by 0x4024EF: test_remover() (in /home/jscherman/ClionProjects/algo2-t3-abb/a.out)
==4860==    by 0x402D07: main (in /home/jscherman/ClionProjects/algo2-t3-abb/a.out)
==4860== 
==4860== 
==4860== ---- Print suppression ? --- [Return/N/n/Y/y/C/c] ---- n
==4860== 72,704 bytes in 1 blocks are still reachable in loss record 2 of 2
==4860==    at 0x4C2DC10: malloc (vg_replace_malloc.c:299)
==4860==    by 0x4EC3EFF: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
==4860==    by 0x40104E9: call_init.part.0 (dl-init.c:72)
==4860==    by 0x40105FA: call_init (dl-init.c:30)
==4860==    by 0x40105FA: _dl_init (dl-init.c:120)
==4860==    by 0x4000CF9: ??? (in /lib/x86_64-linux-gnu/ld-2.23.so)
==4860== 
==4860== 
==4860== ---- Print suppression ? --- [Return/N/n/Y/y/C/c] ---- n
==4860== LEAK SUMMARY:
==4860==    definitely lost: 24 bytes in 1 blocks
==4860==    indirectly lost: 0 bytes in 0 blocks
==4860==      possibly lost: 0 bytes in 0 blocks
==4860==    still reachable: 72,704 bytes in 1 blocks
==4860==         suppressed: 0 bytes in 0 blocks
==4860== 
==4860== For counts of detected and suppressed errors, rerun with: -v
==4860== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)






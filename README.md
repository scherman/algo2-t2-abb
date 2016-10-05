jscherman@jscherman:~/ClionProjects/algo2-t3-abb$ g++ Conjunto.hpp tests.cpp && valgrind --leak-check=yes --show-leak-kinds=all ./a.out
==2986== Memcheck, a memory error detector
==2986== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==2986== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==2986== Command: ./a.out
==2986== 
test_mleak...ok
==2986== 
==2986== HEAP SUMMARY:
==2986==     in use at exit: 72,704 bytes in 1 blocks
==2986==   total heap usage: 4 allocs, 3 frees, 73,776 bytes allocated
==2986== 
==2986== 72,704 bytes in 1 blocks are still reachable in loss record 1 of 1
==2986==    at 0x4C2DC10: malloc (vg_replace_malloc.c:299)
==2986==    by 0x4EC3EFF: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
==2986==    by 0x40104E9: call_init.part.0 (dl-init.c:72)
==2986==    by 0x40105FA: call_init (dl-init.c:30)
==2986==    by 0x40105FA: _dl_init (dl-init.c:120)
==2986==    by 0x4000CF9: ??? (in /lib/x86_64-linux-gnu/ld-2.23.so)
==2986== 
==2986== LEAK SUMMARY:
==2986==    definitely lost: 0 bytes in 0 blocks
==2986==    indirectly lost: 0 bytes in 0 blocks
==2986==      possibly lost: 0 bytes in 0 blocks
==2986==    still reachable: 72,704 bytes in 1 blocks
==2986==         suppressed: 0 bytes in 0 blocks
==2986== 
==2986== For counts of detected and suppressed errors, rerun with: -v
==2986== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

jscherman@jscherman:~/ClionProjects/algo2-t3-abb$ valgrind --leak-check=yes --track-origins=yes ./a.out 
==22453== Memcheck, a memory error detector
==22453== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==22453== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==22453== Command: ./a.out
==22453== 
test_insertar...ok
test_cardinal...ok
test_remover...ok
test_maximo...{-460, -46, 42, 43, 44, 104, 130, 450}ok
test_minimo...ok
==22453== 
==22453== HEAP SUMMARY:
==22453==     in use at exit: 72,728 bytes in 2 blocks
==22453==   total heap usage: 42 allocs, 40 frees, 78,600 bytes allocated
==22453== 
==22453== 24 bytes in 1 blocks are definitely lost in loss record 1 of 2
==22453==    at 0x4C2E118: operator new(unsigned long) (vg_replace_malloc.c:333)
==22453==    by 0x403679: Conjunto<int>::insertar(int const&) (in /home/jscherman/ClionProjects/algo2-t3-abb/a.out)
==22453==    by 0x40220F: test_remover() (in /home/jscherman/ClionProjects/algo2-t3-abb/a.out)
==22453==    by 0x4028E4: main (in /home/jscherman/ClionProjects/algo2-t3-abb/a.out)
==22453== 
==22453== LEAK SUMMARY:
==22453==    definitely lost: 24 bytes in 1 blocks
==22453==    indirectly lost: 0 bytes in 0 blocks
==22453==      possibly lost: 0 bytes in 0 blocks
==22453==    still reachable: 72,704 bytes in 1 blocks
==22453==         suppressed: 0 bytes in 0 blocks
==22453== Reachable blocks (those to which a pointer was found) are not shown.
==22453== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==22453== 
==22453== For counts of detected and suppressed errors, rerun with: -v
==22453== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)


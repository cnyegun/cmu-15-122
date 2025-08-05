15-122 Principles of Imperative Computation
Lab 05: Fibonacci has Bad Internet

==========================================================

Files you won't modify:
   LFtest.c0         - Tests for LF
   memotest.c0       - Tests for fast_lf
   Makefile          - Compiles your code

Files you will modify:
   lf.c0             - Implement is_memo_table, lf_memo,
                       and fast_lf

==========================================================

Running your code in coin with contracts:
   % coin -d lf.c0

Running your code in coin without contracts:
   % coin lf.c0

Compiling and running LF with timing:
   % cc0 -o LFtest lf.c0 LFtest.c0
   % time ./LFtest <input>

Compiling and running fast_lf with timing:
   % cc0 -o memotest lf.c0 memotest.c0
   % time ./memotest <input>

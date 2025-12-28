15-122 Principles of Imperative Computation
Huffman coding

==========================================================

Files you won't modify:
   lib/contracts.h     - Contracts for C
   lib/xalloc.h        - NULL-checking allocation
   lib/file_io.h       - basic file I/O
   lib/pq.h            - Priority queues
   lib/*.o             - machine-specific object files

   data/source/*       - sample source files
   data/freq/*         - sample frequency files
   data/htree/*        - sample Huffman trees
   data/binascii/*     - sample Huffman codes
   data/compressed/*   - sample compressed files

   freqtable.h         - frequency table definitions and operations
   htree.h             - Huffman tree definitions and operations
   encode.h            - top-level text encoding/decoding
   bitpacking.h        - bit packing utilities
   compress.h          - top-level file compression/uncompression
   *.o                 - machine-specific object files
   Makefile            - Utility for building executables

Files you may extend:
   huffman.c           - Tasks 1-7
   test-htree.c        - test file for is_htree functions (no need to submit)
   test-pack.c         - test file for pack and and unpack (no need to submit)

Files you will submit:
EITHER (if doing Tasks 8)
  huffman.c.hip
OR (if not doing Task 8)
  huffman.c

==========================================================

NOTE: This starter code contains object files (ending in a .o
      extension) that will work only on unix.andrew.cmu.edu

Compiling your is_htree functions and tests
   % make htree
   % ./test-htree

Compiling and running your other functions (with -DDEBUG)
   % make
   % ./huff-safe <parameters>
   % valgrind ./huff-safe <parameters>

Compiling and running your other functions (without -DDEBUG)
   % make fast
   % ./huff-fast <parameters>
   % valgrind ./huff-fast <parameters>

For a summary of the valid parameters, run
  % ./huff-safe
(huff-fast accepts the same parameters)
See writeup for which <parameters> to supply to test each function.

Compiling your pack/unpack functions and tests
   % make pack
   % ./test-pack

==========================================================

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
EITHER (task 8)
   % tar -czvf handin.tgz huffman.c.hip
OR (NO task 8)
   % tar -czvf handin.tgz huffman.c

15-122 Principles of Imperative Computation
Speller

==========================================================

Files you will modify:
   speller-test.c0      - test your speller code

Files you won't modify:
   lib/arrayutil.o0     - A version of arrayutil.c0 for strings
   lib/readfile.o0      - File reading library
   speller.c0           - Starter code for tasks 1 to 6
   speller-awful.c0     - Badly broken implementation
   echo.c0              - Example of using the C0 args library

Files that don't exist yet:
   analysis.c0          - Using the speller code to answer questions

Data: (described on page 3 of the handout)
   texts/dict.txt
   texts/small-dict.txt
   texts/scott-tweet.txt
   texts/sloth.txt
   texts/shakespeare.txt

   You can create more data files if you would like to use them in
   your tests: just hand these in along with your other files.

==========================================================

Displaying the library interfaces
   % cc0 -i lib/arrayutil.o0
   % cc0 -i lib/readfile.o0

Loading all the libraries in coin to play with them:
   % coin lib/*.o0

Compiling speller.c0 and tests:
   % cc0 -d -W -w -o speller lib/*.o0 speller.c0 speller-test.c0
   % ./speller

Compiling speller-awful.c0 and tests:
   % cc0 -d -W -w -o speller-bad lib/*.o0 speller-awful.c0 speller-test.c0
   % ./speller-bad

Compiling analysis.c0:
   % cc0 -W -w -o analysis lib/*.o0 speller.c0 analysis.c0
   % ./analysis texts/dict.txt texts/shakespeare.txt

==========================================================

Creating a tarball to submit with autolab.andrew.cmu.edu web interface:
   % tar -czvf handin.tgz speller.c0 speller-test.c0 analysis.c0

If you want to hand in additional data files, just append their path
to the command.  Do not handin data files given to you as part of
the handout.

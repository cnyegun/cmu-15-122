15-122 Principles of Imperative Computation
Bloom Filters

==========================================================

Files you won't modify:
   bloom-worst.c0     - Sets that always return "true" for membership tests
   bloom-expensive.c0 - Memory and time expensive "perfect" sets
   lib/*              - Hash function visualizer (no interface)
   data/*             - Test data for the hash function visualizer and for
                        the password checker

Files that don't exist yet
   bloom1.c0          - Bloom filters as arrays of bool, single hash (Task 2)
   bloom2.c0          - Bloom filters as arrays of int, 3 hashes (Tasks 3-5)

Files you will modify:
   bloom-test.c0      - Unit tests, performance test (Task 1)
   test-pack.c0       - Test for get_bit and set_bit (optional, Task 4)
   pwd.c0             - Password checker (Task 6)
   test-pwd.c0        - Test for the password checker (optional, Task 6)

==========================================================

Running your test cases against the various implementations:
   % cc0 -d -W -w -x bloom-worst.c0 bloom-test.c0
   % cc0 -d -W -w -x bloom-expensive.c0 bloom-test.c0
   % cc0 -d -W -w -x bloom1.c0 bloom-test.c0
   % cc0 -d -W -w -x bloom2.c0 bloom-test.c0

Testing get_bit and set_bit:
   % cc0 -d -W -w -x bloom2.c0 test-pack.c0

Checking how good your hash functions are in bloom2
   % cc0 -dx bloom2.c0 lib/h1.o0 lib/visualizer.o0
   % cc0 -dx bloom2.c0 lib/h2.o0 lib/visualizer.o0
   % cc0 -dx bloom2.c0 lib/h3.o0 lib/visualizer.o0
then display the resulting collision graphs using any image viewer

Testing your password checker
   % cc0 -d -W -w -x bloom2.c0 pwd.c0 test-pwd.c0

==========================================================

Submitting to the unofficial test case checker from autolab web interface:
   % tar -czvf handin.tgz bloom-test.c0

Submitting officially by creating a tarball to submit with autolab web interface:
   % tar -czvf handin.tgz bloom-test.c0 bloom1.c0 bloom2.c0 pwd.c0

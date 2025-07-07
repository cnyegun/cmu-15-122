Test mergesort/quicksort on a random array of about 500 elements and
repeat this 10 times.  This will be slow since contracts are checked
dynamically, testing your code.

Compile and run with:
	% cc0 -dxW arrayutil.c0 mergesort.c0 sort-test.c0
	% cc0 -dxW arrayutil.c0 quicksort.c0 sort-test.c0


Time mergesort/quicksort sorting a random array of size <size>,
repeating <repeat> times.  Doubling the input size should roughly
four-fold increase the running time, since selecting sort has
quadratic asymptotic complexity.

Compile with:
	% cc0 -W arrayutil.c0 mergesort.c0 sort-time.c0
OR
	% cc0 -W arrayutil.c0 quicksort.c0 sort-time.c0

Run with
time ./a.out -r number of runs> -exp <log_2 of number_of_element>

E.g.
	% time ./a.out -r 200 -exp 10
	% time ./a.out -r 200 -exp 11
	% time ./a.out -r 200 -exp 12

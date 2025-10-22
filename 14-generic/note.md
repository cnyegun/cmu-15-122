# Generic data structures

- There are limitations of the previous implementation of libraries.
- We can use void pointers to avoid that.
- C1 supports void pointers.

- Goals: * Modify data contained in a pointer to a struct
		 * Generic hash dictionaries
		 * Void pointers and function pointers
	
1. Generic pointers: `void*`

- A void pointer can used to hold a pointer to anything
- Any pointer p can be turned into a void pointer by a cast `(void*)p`
- It can only be turned back to original type by casting `(int*)p`

2. Generic data structures:

- Make our library generic by choosing `void*` as the type elem
	```c
	typedef void* elem;
	```

3. Generic hash dict
	...
4. Memory model
- Computer contains a single entity called `memory`
- Think of it as array of bytes indexed by address
- Length is 2^64
- There are sections of the computer memory:
		1. OS: belongs to the operating system. restricted
		2. Stack: local variable, get removed when function exits
		3. Heap: allocated memory, need to GC-ed or free()
		4. DATA: contains all string literals in our program "dog", "cat"
		5. TEXT: compiled code

5. Function pointers
- use & to get the address of the function in C1
- need to define function data type
	```
	typedef int hash_string_fn(string s);
	```
	this type can store all the function 
	that receive a string and output an int
- declare variable and store the function
	```
	hash_string_fn* F = &hash_string;
	```
- to call it: `(*F)("hello")` 
- can be NULL;

6. Generic data structures III


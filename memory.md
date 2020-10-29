
# Overview of memory management problems

## Memory Leaks
Memory leaks occur when data is allocated on the heap at runtime, but not properly deallocated. A program that forgets to clear a memory block is said to have a memory leak - this may be a serious problem or not, depending on the circumstances and on the nature of the program. For a program that runs, computes something, and quits immediately, memory leaks are usually not a big concern. Memory leaks are mostly problematic for programs that run for a long time and/or use large data structures. In such a case, memory leaks can gradually fill the heap until allocation requests can no longer be properly met and the program stops responding or crashes completely. We will look at an example further down in this section.

## Buffer Overrun 
Buffer overruns occur when memory outside the allocated limits is overwritten and thus corrupted. One of the resulting problems is that this effect may not become immediately visible. When a problem finally does occur, cause and effect are often hard to discern.
In this example, the allocated stack memory is too small to hold the entire string, which results in a segmentation fault:

```
char str[5];
strcpy(str,"BufferOverrun");
printf("%s",str);
```

## Uninitialized Memeory
 Depending on the C++ compiler, data structures are sometimes initialized (most often to zero) and sometimes not. So when allocating memory on the heap without proper initialization, it might sometimes contain garbage that can cause problems.

Generally, a variable will be automatically initialized in these cases:

 - it is a class instance where the default constructor initializes all primitive types
 - array initializer syntax is used, such as int a[10] = {}
 - it is a global or extern variable
 - it is defined static
 
 ## Incorrect pairing of allocation and deallocation 
 
Freeing a block of memory more than once will cause a program to crash. This can happen when a block of memory is freed that has never been allocated or has been freed before. Such behavior could also occur when improper pairings of allocation and deallocation are used such as using malloc() with delete or new with free().

In this first example, the wrong new and delete are paired
```
double *pDbl=new double[5];
delete pDbl;
```

In this second example, the pairing is correct but a double deletion is performed:

```
char *pChr=new char[5];
delete[] pChr;
delete[] pChr;
```

## Invalid memory access

Invalid memory access This error occurs then trying to access a block of heap memory that has not yet or has already been deallocated.

In this example, the heap memory has already been deallocated at the time when strcpy() tries to access it:

```
char *pStr=new char[25];
delete[] pStr;
strcpy(pStr, "Invalid Access");
```

# Resource Copying Policy 

he default behavior of both copy constructor and assignment operator is to perform a shallow copy as with the example above. The following figure illustrates the concept:

![image](https://r859981c931118xjupyterlcavzqg6q.udacity-student-workspaces.com/files/images/C41-FIG1.png?_xsrf=2%7C97dfdc98%7C484e13c6cd07379a6045fa618dc43e09%7C1603897224&1603948489838)

Fortunately, in C++, the copying process can be controlled by defining a tailored copy constructor as well as a copy assignment operator. The copying process must be closely linked to the respective resource release mechanism and is often referred to as copy-ownership policy. Tailoring the copy constructor according to your memory management policy is an important choice you often need to make when designing a class. In the following, we will closely examine several well-known copy-ownership policies.

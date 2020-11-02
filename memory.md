
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

Fortunately, in C++, the copying process can be controlled by defining a tailored copy constructor as well as a copy assignment operator. The copying process must be closely linked to the respective resource release mechanism and is often referred to as copy-ownership policy. Tailoring the copy constructor according to your memory management policy is an important choice you often need to make when designing a class. In the following, we will closely examine several well-known copy-ownership policies.

## No copying policy

The simplest policy of all is to forbid copying and assigning class instances all together. This can be achieved by declaring, but not defining a private copy constructor and assignment operator (see NoCopyClass1 below) or alternatively by making both public and assigning the delete operator (see NoCopyClass2 below). The second choice is more explicit and makes it clearer to the programmer that copying has been actively forbidden.

```
class NoCopyClass1
{
private:
    // Declared as private in the class but not defined, actually its disallowing the copy and assigning
    NoCopyClass1(const NoCopyClass1 &); 
    NoCopyClass1 &operator=(const NoCopyClass1 &);

public:
    NoCopyClass1(){};
};

class NoCopyClass2
{
public:
    NoCopyClass2(){}
    NoCopyClass2(const NoCopyClass2 &) = delete;
    NoCopyClass2 &operator=(const NoCopyClass2 &) = delete;
};

int main()
{
    NoCopyClass1 original1;
    NoCopyClass1 copy1a(original1); // copy c’tor
    NoCopyClass1 copy1b = original1; // assigment operator

    NoCopyClass2 original2;
    NoCopyClass2 copy2a(original2); // copy c’tor
    NoCopyClass2 copy2b = original2; // assigment operator

    return 0;
}
```

##  Exclusive ownership policy

This policy states that whenever a resource management object is copied, the resource handle is transferred from the source pointer to the destination pointer. In the process, the source pointer is set to nullptr to make ownership exclusive. At any time, the resource handle belongs only to a single object, which is responsible for its deletion when it is no longer needed.

```
#include <iostream>

class ExclusiveCopy
{
private:
    int *_myInt;

public:
    ExclusiveCopy()
    {
        _myInt = (int *)malloc(sizeof(int));
        std::cout << "resource allocated" << std::endl;
    }
    ~ExclusiveCopy()
    {
        if (_myInt != nullptr)
        {
            free(_myInt);
            std::cout << "resource freed" << std::endl;
        }
            
    }
    ExclusiveCopy(ExclusiveCopy &source)
    {
        _myInt = source._myInt;
        source._myInt = nullptr;
    }
    ExclusiveCopy &operator=(ExclusiveCopy &source)
    {
        _myInt = source._myInt;
        source._myInt = nullptr;
        return *this;
    }
};

int main()
{
    ExclusiveCopy source;
    ExclusiveCopy destination(source);

    return 0;
}
```

The output is :
```
root@4a8772811e00:/home/workspace# g++ exclusive_ownership.cpp 
root@4a8772811e00:/home/workspace# ./a.out
resource allocated
resource freed
```

 One problem in this implementation is that for a short time there are effectively two valid handles to the same resource - after the handle has been copied and before it is set to nullptr. In concurrent programs, this would cause a data race for the resource. A much better alternative to handle exclusive ownership in C++ would be to use move semantics.
 
 ## Deep Copying Policy

With this policy, copying and assigning class instances to each other is possible without the danger of resource conflicts. The idea is to allocate proprietary memory in the destination object and then to copy the content to which the source object handle is pointing into the newly allocated block of memory. This way, the content is preserved during copy or assignment. However, this approach increases the memory demands and the uniqueness of the data is lost: After the deep copy has been made, two versions of the same resource exist in memory.

## Shared ownership policy

The last ownership policy we will be discussing in this course implements a shared ownership behavior. The idea is to perform a copy or assignment similar to the default behavior, i.e. copying the handle instead of the content (as with a shallow copy) while at the same time keeping track of the number of instances that also point to the same resource. Each time an instance goes out of scope, the counter is decremented. Once the last object is about to be deleted, it can safely deallocate the memory resource. We will see later in this course that this is the central idea of unique_ptr, which is a representative of the group of smart pointers.

## What are lvalues and rvalues ? 

Lvalues have an address that can be accessed. They are expressions whose evaluation by the compiler determines the identity of objects or functions.

Prvalues do not have an address that is accessible directly. They are temporary expressions used to initialize objects or compute the value of the operand of an operator.

```
int i = 42;  // lvalue = rvalue;
```

With many other operators, however, this right-left view is not entirely correct. In more general terms, an lvalue is an entity that points to a specific memory location. An rvalue is usually a short-lived object, which is only needed in a narrow local scope. To simplify things a little, one could think of lvalues as named containers for rvalues.

In the example above, the value 42 is an rvalue. It does not have a specific memory address which we know about. The rvalue is assigned to a variable i with a specific memory location known to us, which is what makes it an lvalue in this example.

Using the address operator & we can generate an lvalue from an rvalue and assign it to another lvalue:

```
int *j = &i;
```

In this small example, the expression &i generates the address of i as an rvalue and assigns it to j, which is an lvalue now holding the memory location of i.

### Lvalue references

An lvalue reference can be considered as alternative name of an object. It is a reference that binds to an lvalue and is declared using an optional list of specifiers by reference declarator &. 

```
#include <iostream>

int main()
{
    int i = 1; 
    int &j = i; 
    ++i;
    ++j;

    std::cout << "i = " << i << ", j = " << j << std::endl;

    return 0;
}
```

The output of the program is 
```
i = 3, j = 3
```

We can see that the lvalue reference j can be used just as i can. A change to either i or j will affect the same memory location on the stack.

One of the primary use case for lvalue refernce is the pass-by-reference semantics in function call. 

The function myFunction has an lvalue reference as a parameter, which establishes an alias to the integer i which is passed to it in main.

### Rvalue references

Since C++11, there is a new type available called rvalue reference, which can be identified from the double ampersand && after a type name. With this operator, it is possible to store and even modify an rvalue, i.e. a temporary object which would otherwise be lost quickly.

```
#include <iostream>

int main()
{
    int i = 1; 
    int j = 2; 
    int k = i + j; 
    int &&l = i + j; 

    std::cout << "k = " << k << ", l = " << l << std::endl;

    return 0; 
}
```

The output is :

```
root@06ac7e01c509:/home/workspace# g++ r_value_references_2.cpp 
root@06ac7e01c509:/home/workspace# ./a.out 
k = 3, l = 3
```

### what do we need this for?

After creating the integers i and j on the stack, the sum of both is added to a third integer k. Let us examine this simple example a little more closely. In the first and second assignment, i and j are created as lvalues, while 1 and 2 are rvalues, whose value is copied into the memory location of i and j. Then, a third lvalue, k, is created. The sum i+j is created as an rvalue, which holds the result of the addition before being copied into the memory location of k. This is quite a lot of copying and holding of temporary values in memory. With an rvalue reference, this can be done more efficiently.

The expression int &&l creates an rvalue reference, to which the address of the temporary object is assigned, that holds the result of the addition. So instead of first creating the rvalue i+j , then copying it and finally deleting it, we can now hold the temporary object in memory. This is much more efficient than the first approach, even though saving a few bytes of storage in the example might not seem like much at first glance. One of the most important aspects of rvalue references is that they pave the way for move semantics, which is a mighty technique in modern C++ to optimize memory usage and processing speed. Move semantics and rvalue references make it possible to write code that transfers resources such as dynamically allocated memory from one object to another in a very efficient manner and also supports the concept of exclusive ownership, as we will shortly see when discussing smart pointers.

## Move Semantics

The function std::move converts an lvalue into an rvalue. which makes it possible to use the lvalue as an argument for the function.

```
#include <iostream>

void myFunction(int &&val)
{
    std::cout << "val = " << val << std::endl;
}

int main()
{
    myFunction(42);

    return 0; 
}
```


we cannot pass an lvalue to myFunction, because an rvalue reference cannot bind to an lvalue. The code would result in a compiler error. 

```
int i = 23;
myFunction(i)
```
We can use it like this:

```
int i = 23; 
myFunction(std::move(i));
```

### The Rule Of Three

The rule of three (also known as the Law of The Big Three or The Big Three) is a rule of thumb in C++ (prior to C++11) that claims that if a class defines any of the following then it should probably explicitly define all three: 

 - destructor
 - copy constructor
 - copy assignment operator

Note that when a function returns an object by value, the compiler creates a temporary object as an rvalue. 

```
#include <stdlib.h>
#include <iostream>

class MyMovableClass
{
private:
    int _size;
    int *_data;

public:
    MyMovableClass(size_t size) // constructor
    {
        _size = size;
        _data = new int[_size];
        std::cout << "CREATING instance of MyMovableClass at " << this << " allocated with size = " << _size*sizeof(int)  << " bytes" << std::endl;
    }

    MyMovableClass(const MyMovableClass &source) // 2 : copy constructor
    {
        _size = source._size;
        _data = new int[_size];
        *_data = *source._data;
        std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
    }
    
    MyMovableClass &operator=(const MyMovableClass &source) // 3 : copy assignment operator
    {
        std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
        if (this == &source)
            return *this;
        delete[] _data;
        _data = new int[source._size];
        *_data = *source._data;
        _size = source._size;
        return *this;
    }
    
    ~MyMovableClass() // 1 : destructor
    {
        std::cout << "DELETING instance of MyMovableClass at " << this << std::endl;
        delete[] _data;
    }
};

MyMovableClass createObject(int size)
{
    MyMovableClass obj(size);
    return obj; // return MyMovableClass object as value
}
int main()
{
    MyMovableClass obj1(10); // Regular Constructor
    MyMovableClass obj2(obj1); // Copy Constructor
    obj2 = obj1;
    
    MyMovableClass obj3 = obj1;
    // Here we are instantiating obj3 in the same statement , hence the copy assignment operator would not be called
    
    MyMovableClass obj4 = createObject(10);
    // 
    
    return 0;  
    
}
```
and the output is :
```
root@178daecdc2cc:/home/workspace# g++ rule_of_three.cpp 
root@178daecdc2cc:/home/workspace# ./a.out
CREATING instance of MyMovableClass at 0x7ffca33b7e00 allocated with size = 40 bytes
COPYING content of instance 0x7ffca33b7e00 to instance 0x7ffca33b7e10
ASSIGNING content of instance 0x7ffca33b7e00 to instance 0x7ffca33b7e10
COPYING content of instance 0x7ffca33b7e00 to instance 0x7ffca33b7e20
CREATING instance of MyMovableClass at 0x7ffca33b7e30 allocated with size = 40 bytes
DELETING instance of MyMovableClass at 0x7ffca33b7e30
DELETING instance of MyMovableClass at 0x7ffca33b7e20
DELETING instance of MyMovableClass at 0x7ffca33b7e10
DELETING instance of MyMovableClass at 0x7ffca33b7e00
```

In below case :

```
MyMovableClass obj4 = createObject(10);
```

The function ``` createobject(10)``` returns an instance of MyMovableClass by value. In such a case, compiler creates a temporary copy of the object as an ravalue, which is passed to the copy constructor. The problem here is 2 expensive memory operation are performed. First occuring during the creation of temporary rvalue and second during the execution of copy constructor.  


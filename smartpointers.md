
# Problem associated with new and delete
  - Proper pairing of new and delete.
  - Correct operator pairing. 
  - Memory ownership.
  
  ## Resource Acquisition Is Initialization
  The RAII is a widespread programming paradigm, that can be used to protect a resource such as a file stream, a network connection or a block of memory which need proper management.
  
  ### The problem of reliable resource release
  
 - The program might throw an exception during resource use and thus the point of release might never be reached.

 - There might be several points where the resource could potentially be released, making it hard for a programmer to keep track of all eventualities.

 - We might simply forget to release the resource again.
  
The major idea of RAII revolves around object ownership and information hiding: Allocation and deallocation are hidden within the management class, so a programmer using the class does not have to worry about memory management responsibilities. If he has not directly allocated a resource, he will not need to directly deallocate it - whoever owns a resource deals with it. In the case of RAII this is the management class around the protected resource. The overall goal is to have allocation and deallocation (e.g. with new and delete) disappear from the surface level of the code you write.

RAII can be used to leverage - among others - the following advantages:

Use class destructors to perform resource clean-up tasks such as proper memory deallocation when the RAII object gets out of scope
Manage ownership and lifetime of dynamically allocated objects
Implement encapsulation and information hiding due to resource acquisition and release being performed within the same object.
In the following, let us look at RAII from the perspective of memory management. There are three major parts to an RAII class:

- A resource is allocated in the constructor of the RAII class.
- The resource is deallocated in the destructor.
- All instances of the RAII class are allocated on the stack to reliably control the lifetime via the object scope.

## Smart pointer overview

C++11 has introduced three types of smart pointers, which are defined in the header of the standard library:

1. The unique pointer **std::unique_ptr** is a smart pointer which exclusively owns a dynamically allocated resource on the heap. There must not be a second unique pointer to the same resource.

2. The shared pointer **std::shared_ptr** points to a heap resource but does not explicitly own it. There may even be several shared pointers to the same resource, each of which will increase an internal reference count. As soon as this count reaches zero, the resource will automatically be deallocated.

3. The weak pointer **std::weak_ptr** behaves similar to the shared pointer but does not increase the reference counter.

## The Unique pointer

![Unique Ownership](https://r859981c931308xjupyterlqe3a4k79.udacity-student-workspaces.com/files/images/C52-FIG1.png?_xsrf=2%7C629a40f4%7C4c56f2c867a6f7aef2001b1e43366403%7C1604664472&1604669934062)

The function RawPointer contains the familiar steps of (1) allocating memory on the heap with new and storing the address in a pointer variable, (2) assigning a value to the memory block using the dereferencing operator * and (3) finally deleting the resource on the heap. As we already know, forgetting to call delete will result in a memory leak.

```

void RawPointer()
{
    int *raw = new int; // create a raw pointer on the heap
    *raw = 1; // assign a value
    delete raw; // delete the resource again
}
```

The function UniquePointer shows how to achieve the same goal using a smart pointer from the standard library. As can be seen, a smart pointer is a class template that is declared on the stack and then initialized by a raw pointer (returned by new ) to a heap-allocated object. The smart pointer is now responsible for deleting the memory that the raw pointer specifies - which happens as soon as the smart pointer goes out of scope. Note that smart pointers always need to be declared on the stack, otherwise the scoping mechanism would not work.

The smart pointer destructor contains the call to delete, and because the smart pointer is declared on the stack, its destructor is invoked when the smart pointer goes out of scope, even if an exception is thrown.

```
void UniquePointer()
{
    std::unique_ptr<int> unique(new int); // create a unique pointer on the stack
    *unique = 2; // assign a value
    // delete is not neccessary
}
```
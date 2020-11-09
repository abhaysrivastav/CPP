
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

### Unique Pointers Example

```
#include <iostream>
#include <memory>
#include <string>

class MyClass
{
private:
    std::string _text;

public:
    MyClass() {}
    MyClass(std::string text) { _text = text; }
    ~MyClass() { std::cout << _text << " destroyed" << std::endl; }
    void setText(std::string text) { _text = text; }
};

int main()
{
    // create unique pointer to proprietary class
    std::unique_ptr<MyClass> myClass1(new MyClass());
    std::unique_ptr<MyClass> myClass2(new MyClass("String 2"));

    // call member function using ->
    myClass1->setText("String 1");

    // use the dereference operator * 
    //*myClass1 = *myClass2;

    // use the .get() function to retrieve a raw pointer to the object
    std::cout << "Objects have stack addresses " << myClass1.get() << " and " << myClass2.get() << std::endl;

    return 0;
}
```

The output is :
```
root@d59618d2fedc:/home/workspace# g++ unique_pointer_2.cpp 
root@d59618d2fedc:/home/workspace# ./a.out 
Objects have stack addresses 0x1cf9c20 and 0x1cf9c50
String 2 destroyed
String 1 destroyed
```

class MyClass has two constructors, one without arguments and one with a string to be passed, which initializes a member variable _text that lives on the stack. Also, once an object of this class gets destroyed, a message to the console is printed, along with the value of _text. In main, two unique pointers are created with the address of a MyClass object on the heap as arguments. With myClass2, we can see that constructor arguments can be passed just as we would with raw pointers. After both pointers have been created, we can use the -> operator to access members of the class, such as calling the function setText. From looking at the function call alone you would not be able to tell that myClass1 is in fact a smart pointer. Also, we can use the dereference operator * to access the value of myClass1 and myClass2 and assign the one to the other. Finally, the . operator gives us access to proprietary functions of the smart pointer, such as retrieving the internal raw pointer with get().

**The Unique Pointer allow a single owner of the underlying internal raw pointer. Unique Pointer should be default choice unless you know for certain that sharing is required at later stage.** 

### The Shared Pointer 

Just as the unique pointer, a shared pointer owns the resource it points to. The main difference between the two smart pointers is that shared pointers keep a reference counter on how many of them point to the same memory resource. Each time a shared pointer goes out of scope, the counter is decreased. When it reaches zero (i.e. when the last shared pointer to the resource is about to vanish). the memory is properly deallocated. This smart pointer type is useful for cases where you require access to a memory location on the heap in multiple parts of your program and you want to make sure that whoever owns a shared pointer to the memory can rely on the fact that it will be accessible throughout the lifetime of that pointer.

![Shared Pointers](https://raw.githubusercontent.com/abhaysrivastav/CPP/master/docs/C52-FIG2.png)

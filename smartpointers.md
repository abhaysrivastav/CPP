
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

![Unique Ownership](https://raw.githubusercontent.com/abhaysrivastav/CPP/master/docs/C52-FIG1.png)

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


A shared pointer can also be redirected by using the reset() function. 

### Problem with Shared Pointer : Circular Reference 

```
#include <iostream>
#include <memory>

class MyClass
{
public:
    std::shared_ptr<MyClass> _member;
    ~MyClass() { std::cout << "Destructor of MyClass called" << std::endl; }
};

int main()
{
    std::shared_ptr<MyClass> myClass1(new MyClass);
    std::shared_ptr<MyClass> myClass2(new MyClass);
    
    myClass1->_member = myClass2;
    myClass2->_member = myClass1;
    
    std::cout << "myClass1 use Count test: " << myClass1.use_count() << std::endl;
     std::cout << "myClass2 use Count test: " << myClass2.use_count() << std::endl;
    return 0;
}
```

 When myClass1 goes out of scope at the end of main, its destructor can’t clean up memory as there is still a reference count of 1 in the smart pointer, which is caused by the shared pointer _member in myClass2. The same holds true for myClass2, which can not be properly deleted as there is still a shared pointer to it in myClass1.
 
 ## The Weak Pointer
 
Similar to shared pointers, there can be multiple weak pointers to the same resource. The main difference though is that weak pointers do not increase the reference count. Weak pointers hold a non-owning reference to an object that is managed by another shared pointer.

The following rule applies to weak pointers: You can only create weak pointers out of shared pointers or out of another weak pointer. The code on the right shows a few examples of how to use and how not to use weak pointers.

```
#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> mySharedPtr(new int);
    std::cout << "shared pointer count = " << mySharedPtr.use_count() << std::endl;

    std::weak_ptr<int> myWeakPtr1(mySharedPtr);
    std::weak_ptr<int> myWeakPtr2(myWeakPtr1);
    std::cout << "shared pointer count = " << mySharedPtr.use_count() << std::endl;

    // std::weak_ptr<int> myWeakPtr3(new int); // COMPILE ERROR

    return 0;
}
```

The output is 

```
root@d59618d2fedc:/home/workspace# g++ weak_pointer.cpp 
root@d59618d2fedc:/home/workspace# ./a.out 
shared pointer count = 1
shared pointer count = 1
```

 ## Conversion between Smart Pointers 
 
 Lets consider 
 
 ```
  std::unique_ptr<int> uniquePtr(new int);
 ```
 
 A conversion from unique pointer to shared pointer can be  performed. You can see that this can be achieved by using std::move, which calls the move assignment operator on sharedPtr1 and steals the resource from uniquePtr while at the same time invalidating its resource handle on the heap-allocated integer.
 
 ```
 std::shared_ptr<int> sharedPtr1 = std::move(uniquePtr);
 ```
Imagine that you have been passed a weak pointer to a memory object which you want to work on. To avoid invalid memory access, you want to make sure that the object will not be deallocated before your work on it has been finished. To do this, you can convert a weak pointer to a shared pointer by calling the lock() function on the weak pointer.

```
    // (2) shared pointer from weak pointer
    std::weak_ptr<int> weakPtr(sharedPtr1);
    std::shared_ptr<int> sharedPtr2 = weakPtr.lock();
```

A raw pointer can be extracted from a shared pointer. However, this operation does not decrease the reference count within sharedPtr2. This means that calling delete on rawPtr in the last line before main returns will generate a runtime error as a resource is trying to be deleted which is managed by sharedPtr2 and has already been removed.

```
int *rawPtr = sharedPtr2.get();
```
**no options for converting away from a shared pointer**

## Passing smart pointers to function 

### R.30 Take smart pointers as parameters only to explicitly express lifetime semantics 

 A function that does not manipulate the lifetime or ownership should use raw pointers or references instead. A function should take smart pointers as parameter only if it examines or manipulates the smart pointer itself.
 
 **pass-by-value types that lend the ownership**
```
 1. void f(std::unique_ptr<MyObject> ptr)

 2. void f(std::shared_ptr<MyObject> ptr)

 3. void f(std::weak_ptr<MyObject> ptr)
 ```
 
 ```
 #include <iostream>
#include <memory>

class MyClass
{
private:
    int _member;

public:
    MyClass(int val) : _member{val} {}
    void printVal() { std::cout << ", managed object " << this << " with val = " << _member << std::endl; }
};

void f(std::unique_ptr<MyClass> ptr)
{
    std::cout << "unique_ptr from f " << &ptr;
    ptr->printVal();
}

int main()
{
    std::unique_ptr<MyClass> uniquePtr = std::make_unique<MyClass>(23);
    std::cout << "unique_ptr " << &uniquePtr;
    uniquePtr->printVal();

    f(std::move(uniquePtr));

    if (uniquePtr)
        uniquePtr->printVal();

    return 0;
}

```

And the output is :

```
root@7568250c71b3:/home/workspace# g++ r_32.cpp 
root@7568250c71b3:/home/workspace# ./a.out 
unique_ptr 0x7ffea90f3328, managed object 0xdc9c20 with val = 23
unique_ptr from f 0x7ffea90f3330, managed object 0xdc9c20 with val = 23
```
he class MyClass has a private object _member and a public function printVal() which prints the address of the managed object (this) as well as the member value to the console. In main, an instance of MyClass is created by the factory function make_unique() and assigned to a unique pointer instance uniquePtr for management. Then, the pointer instance is moved into the function f using move semantics. As we have not overloaded the move constructor or move assignment operator in MyClass, the compiler is using the default implementation. In f, the address of the copied / moved unique pointer ptr is printed and the function printVal() is called on it. When the path of execution returns to main(), the program checks for the validity of uniquePtr and, if valid, calls the function printVal() on it again.

### R.34: Take a shared_ptr parameter to express that a function is part owner

```
#include <iostream>
#include <memory>

class MyClass
{
private:
    int _member;

public:
    MyClass(int val) : _member{val} {}
    void printVal() { std::cout << ", managed object " << this << " with val = " << _member << std::endl; }
};

void f(std::shared_ptr<MyClass> ptr)
{
    std::cout << "shared_ptr (ref_cnt= " << ptr.use_count() << ") " << &ptr;
    ptr->printVal();
}

int main()
{
    std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>(23);
    std::cout << "shared_ptr (ref_cnt= " << sharedPtr.use_count() << ") " << &sharedPtr;
    sharedPtr->printVal();

    f(sharedPtr);

    std::cout << "shared_ptr (ref_cnt= " << sharedPtr.use_count() << ") " << &sharedPtr;
    sharedPtr->printVal();

    return 0;
}
```

The output is :

```
root@7568250c71b3:/home/workspace# g++ r_34.cpp 
root@7568250c71b3:/home/workspace# ./a.out 
shared_ptr (ref_cnt= 1) 0x7ffc65522d50, managed object 0x964c30 with val = 23
shared_ptr (ref_cnt= 2) 0x7ffc65522d60, managed object 0x964c30 with val = 23
shared_ptr (ref_cnt= 1) 0x7ffc65522d50, managed object 0x964c30 with val = 23
```

### R.33: Take a unique_ptr& parameter to express that a function reseats the widget

and

### R.35: Take a shared_ptr& parameter to express that a function might reseat the shared pointer

Smart pointers should always be returned by value. This is not only simpler but also has the following advantages:

The overhead usually associated with return-by-value due to the expensive copying process is significantly mitigated by the built-in move semantics of smart pointers. They only hold a reference to the managed object, which is quickly switched from destination to source during the move process.

Since C++17, the compiler used Return Value Optimization (RVO) to avoid the copy usually associated with return-by-value. This technique, together with copy-elision, is able to optimize even move semantics and smart pointers (not in call cases though, they are still an essential part of modern C++).

When returning a shared_ptr by value, the internal reference counter is guaranteed to be properly incremented. This is not the case when returning by pointer or by reference .

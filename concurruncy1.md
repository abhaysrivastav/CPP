# Passing Data Between the Threads

## Promises and Futures

### Promise future communication channel

The methods for passing data to a thread we have discussed so far are both useful during thread construction: We can either pass arguments to the thread function using variadic templates or we can use a Lambda to capture arguments by value or by reference.
A drawback of these two approaches is that the information flows from the parent thread (main) to the worker threads (t1 and t2). In this section, we want to look at a way to pass data in the opposite direction - that is from the worker threads back to the parent thread.

In order to achieve this, the threads need to adhere to a strict synchronization protocol. There is a such a mechanism available in the C++ standard that we can use for this purpose. This mechanism acts as a single-use channel between the threads. The sending end of the channel is called "promise" while the receiving end is called "future".

In the C++ standard, the class template std::promise provides a convenient way to store a value or an exception that will acquired asynchronously at a later time via a std::future object. Each std::promise object is meant to be used only a single time.

In the C++ standard, the class template std::promise provides a convenient way to store a value or an exception that will acquired asynchronously at a later time via a std::future object. Each std::promise object is meant to be used only a single time.

```
#include <iostream>
#include <thread>
#include <future>

void modifyMessage(std::promise<std::string> && prms, std::string message)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // simulate work
    std::string modifiedMessage = message + " has been modified"; 
    prms.set_value(modifiedMessage);
}

int main()
{
    // define message
    std::string messageToThread = "My Message";

    // create promise and future
    std::promise<std::string> prms;
    std::future<std::string> ftr = prms.get_future();

    // start thread and pass promise as argument
    std::thread t(modifyMessage, std::move(prms), messageToThread);

    // print original message to console
    std::cout << "Original message from main(): " << messageToThread << std::endl;

    // retrieve modified message via future and print to console
    std::string messageFromThread = ftr.get();
    std::cout << "Modified message from thread(): " << messageFromThread << std::endl;

    // thread barrier
    t.join();

    return 0;
}

```

The output is :

```
root@1194b5492067:/home/workspace# ./a.out
Original message from main(): My Message
Modified message from thread(): My Message has been modified
```

In the following example, we want to declare a promise which allows for transmitting a string between two threads and modifying it in the process.
```
#include <iostream>
#include <thread>
#include <future>

void modifyMessage(std::promise<std::string> && prms, std::string message)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // simulate work
    std::string modifiedMessage = message + " has been modified"; 
    prms.set_value(modifiedMessage);
}

int main()
{
    // define message
    std::string messageToThread = "My Message";

    // create promise and future
    std::promise<std::string> prms;
    std::future<std::string> ftr = prms.get_future();

    // start thread and pass promise as argument
    std::thread t(modifyMessage, std::move(prms), messageToThread);

    // print original message to console
    std::cout << "Original message from main(): " << messageToThread << std::endl;

    // retrieve modified message via future and print to console
    std::string messageFromThread = ftr.get();
    std::cout << "Modified message from thread(): " << messageFromThread << std::endl;

    // thread barrier
    t.join();

    return 0;
}

```

The output is :

```
root@fc68e7188d16:/home/workspace# g++ example_2.cpp -pthread
root@fc68e7188d16:/home/workspace# ./a.out
4Original message from main(): My Message
Modified message from thread(): My Message has been modified

```

After defining a message, we have to create a suitable promise that can take a string object. To obtain the corresponding future, we need to call the method get_future() on the promise. Promise and future are the two types of the communication channel we want to use to pass a string between threads. The communication channel set up in this manner can only pass a string.

We can now create a thread that takes a function and we will pass it the promise as an argument as well as the message to be modified. Promises can not be copied, because the promise-future concept is a two-point communication channel for one-time use. Therefore, we must pass the promise to the thread function using std::move. The thread will then, during its execution, use the promise to pass back the modified message.

The thread function takes the promise as an rvalue reference in accordance with move semantics. After waiting for several seconds, the message is modified and the method set_value() is called on the promise.

Back in the main thread, after starting the thread, the original message is printed to the console. Then, we start listening on the other end of the communication channel by calling the function get() on the future. This method will block until data is available - which happens as soon as set_value has been called on the promise (from the thread). If the result is movable (which is the case for std::string), it will be moved - otherwise it will be copied instead. After the data has been received (with a considerable delay), the modified message is printed to the console.
It is also possible that the worker value calls set_value on the promise before get() is called on the future. In this case, get() returns immediately without any delay. After get() has been called once, the future is no longer usable. This makes sense as the normal mode of data exchange between promise and future works with.

## Passing exceptions [:innocent:]
The future-promise communication channel may also be used for passing exceptions. To do this, the worker thread simply sets an exception rather than a value in the promise. In the parent thread, the exception is then re-thrown once **get()** is called on the future.

```
#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

void divideByNumber(std::promise<double> &&prms, double num, double denom)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
    try
    {
        if (denom == 0)
            throw std::runtime_error("Exception from thread: Division by zero!");
        else
            prms.set_value(num / denom);
    }
    catch (...)
    {
        prms.set_exception(std::current_exception());
    }
}

int main()
{
    // create promise and future
    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    // start thread and pass promise as argument
    double num = 42.0, denom = 0.0;
    std::thread t(divideByNumber, std::move(prms), num, denom);

    // retrieve result within try-catch-block
    try
    {
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }

    // thread barrier
    t.join();

    return 0;
}

```

The output is :

```
root@b73b536b8fa4:/home/workspace# g++ example_4.cpp -pthread
root@b73b536b8fa4:/home/workspace# ./a.out
Exception from thread: Division by zero!
```
In the thread function, we need to implement a try-catch block which can be set to catch a particular exception or - as in our case - to catch all exceptions. Instead of setting a value, we now want to throw a std::exception along with a customized error message. In the catch-block, we catch this exception and throw it to the parent thread using the promise with set_exception. The function std::current_exception allows us to easily retrieve the exception which has been thrown.

On the parent side, we now need to catch this exception. In order to do this, we can use a try-block around the call to get(). We can set the catch-block to catch all exceptions or - as in this example - we could also catch a particular one such as the standard exception. Calling the method what() on the exception allows us to retrieve the message from the exception - which is the one defined on the promise side of the communication channel.

When we run the program, we can see that the exception is being thrown in the worker thread with the main thread printing the corresponding error message to the console.

So a promise future pair can be used to pass either values or exceptions between threads.

## Thread vs Task

### Starting threads with async

n the last section we have seen how data can be passed from a worker thread to the parent thread using promises and futures. A disadvantage of the promise-future approach however is that it is very cumbersome (and involves a lot of boilerplate code) to pass the promise to the thread function using an rvalue reference and std::move. For the straight-forward task of returning data or exceptions from a worker thread to the parent thread however, there is a simpler and more convenient way using ***std::async()*** instead of std::thread().

```
#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

double divideByNumber(double num, double denom)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work

    if (denom == 0)
        throw std::runtime_error("Exception from thread: Division by zero!");

    return num / denom;
}


int main()
{
    // use async to start a task
    double num = 42.0, denom = 2.0;
    std::future<double> ftr = std::async(divideByNumber, num, denom);

    // retrieve result within try-catch-block
    try
    {
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
```
The output is 
```
root@4a245aa8980a:/home/workspace# g++ example_1.cpp -pthread
root@4a245aa8980a:/home/workspace# ./a.out
Result = 21

Below result is the test case with exception
root@4a245aa8980a:/home/workspace# g++ example_1.cpp -pthread
root@4a245aa8980a:/home/workspace# ./a.out
Exception from thread: Division by zero!
root@4a245aa8980a:/home/workspace#
```

The first change we are making is in the thread function: We are removing the promise from the argument list as well as the try-catch block. Also, the return type of the function is changed from void to double as the result of the computation will be channeled back to the main thread using a simple return. After these changes, the function has no knowledge of threads, nor of futures or promises - it is a simple function that takes two doubles as arguments and returns a double as a result. Also, it will throw an exception when a division by zero is attempted.

In the main thread, we need to replace the call to std::thread with std::async. Note that async returns a future, which we will use later in the code to retrieve the value that is returned by the function. A promise, as with std::thread, is no longer needed, so the code becomes much shorter. In the try-catch block, nothing has changed - we are still calling get() on the future in the try-block and exception-handling happens unaltered in the catch-block. Also, we do not need to call join() any more. With async, the thread destructor will be called automatically - which reduces the risk of a concurrency bug.

## Task-based concurrency

Determining the optimal number of threads to use is a hard problem. It usually depends on the number of available cores wether it makes sense to execute code as a thread or in a sequential manner. The use of std::async (and thus tasks) take the burden of this decision away from the user and let the system decide wether to execute the code sequentially or as a thread. With tasks, the programmer decides what CAN be run in parallel in principle and the system then decides at runtime what WILL be run in parallel.

Internally, this is achieved by using thread-pools wich represent the number of available threads based on the cores/processors as well as by using work-stealing queues, where tasks are re-distributed among the available processors dynamically. The following diagram shows the principal of task distribution on a multi-core system using work stealing queues.

![](https://r845225c860122xjupyterlej7g1gt6.udacity-student-workspaces.com/files/images/C3-3-A3a.png?_xsrf=2%7Cc282f043%7C60e491802916f5b5b4d3047c0cffc5ef%7C1602510022&1602510029287)

As can be seen, the first core in the example is heavily oversubscribed with several tasks that are waiting to be executed. The other cores however are running idle. The idea of a work-stealing queue is to have a watchdog program running in the background that regularly monitors the amount of work performed by each processor and redistributes it as needed. For the above example this would mean that tasks waiting for execution on the first core would be shifted (or "stolen") from busy cores and added to available free cores such that idle time is reduced. After this rearranging procedire, the task distribution in our example could look as shown in the following diagram.

![](https://r845225c860122xjupyterlej7g1gt6.udacity-student-workspaces.com/files/images/C3-3-A3b.png?_xsrf=2%7Cc282f043%7C60e491802916f5b5b4d3047c0cffc5ef%7C1602510022&1602510029287)

A work distribution in this manner can only work, when parallelism is explicitly described in the program by the programmer. If this is not the case, work-stealing will not perform effectively.

To conclude this section, a general comparison of task-based and thread-based programming is given in the following:

With tasks, the system takes care of many details (e.g. join). With threads, the programmer is responsible for many details. As far as resources go, threads are usually more heavy-weight as they are generated by the operating system (OS). It takes time for the OS to be called and to allocate memory / stack / kernel data structures for the thread. Also, destroying the thread is expensive. Tasks on the other hand are more light-weight as they will be using a pool of already created threads (the "thread pool").

Threads and tasks are used for different problems. Threads have more to do with latency. When you have functions that can block (e.g. file input, server connection), threads can avoid the program to be blocked, when e.g. the server is waiting for a response. Tasks on the other hand focus on throughput, where many operations are executed in parallel.

### Assessing the advantage of parallel execution

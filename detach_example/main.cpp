#include <iostream>
#include <thread>

/*
  There are some situations however, where it might make
  sense to not wait for a thread to finish its work. This
  can be achieved by "detaching" the thread, by which the
  internal state variable "joinable" is set to "false". This
  works by calling the detach() method on the thread.
*/
void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // simulate work
    std::cout << "Finished work in thread\n";
}

int main()
{
    // create thread
    std::thread t(threadFunction);

    // detach thread and continue with main
    t.detach();

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // simulate work
    std::cout << "Finished work in main\n";

    return 0;
}

#include <iostream>
#include <thread>

using namespace std;

int main()
{
    unsigned int nCore = std::thread::hardware_concurrency ();
    cout << "The machine suppports the concurruncy with " << nCore <<endl;
    return 0;
}

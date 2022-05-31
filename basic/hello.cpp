#include <thread>
#include <iostream>

void threadHandler(void)
{
    std::cout << "hello from a thread\n";
}

int main()
{
    std::thread myThread(threadHandler);

    myThread.join();

    std::cout << "the thread is joined, the program is to exit\n";

    exit(EXIT_SUCCESS);
}
#include <iostream>
#include <thread>
#include <vector>

class ThreadGuard
{
public:
    ThreadGuard(std::thread &t)
        : m_thread(t)
    {
    }

    ThreadGuard(ThreadGuard &) = delete;
    ThreadGuard &operator=(ThreadGuard &) = delete;

    ~ThreadGuard()
    {
        std::cout << "trying to deconstruct the thread\n";
        if (m_thread.joinable())
        {
            m_thread.join();
            std::cout << "the thread is deconstructed\n";
        }
    }

private:
    std::thread &m_thread;
};

void threadHandler(void)
{
    std::cout << "the thread is going to exit the main process with failure\n";
}

void foo()
{
    std::thread myThread(threadHandler);
    ThreadGuard tg(myThread);
}

int main()
{
    foo();

    return 0;
}
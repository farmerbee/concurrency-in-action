#include <mutex>
#include <list>
#include <algorithm>

std::list<int>  myList;
std::mutex listMutex;

void addToList(int val)
{
    std::lock_guard<std::mutex> lock(listMutex);
    myList.push_back(val);
}

bool containInList(int val)
{
    std::lock_guard<std::mutex> lock(listMutex);
    return std::find(myList.begin(), myList.end(), val) != myList.end();
}
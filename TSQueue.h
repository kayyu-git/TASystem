#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <memory>
#include <functional>

template<typename T>
class TSQueue
{
public:
    // ctors/dtor
    TSQueue() : myIsExiting(false) {}

    ~TSQueue() {}

    // append data item to a Q
    void push(const T& source);

    // get the FRONT item and remove it from the Q
    // return TRUE if target is UPDATED otherwise false (q it empty)
    bool pop(T& target);

    // attributes
    size_t size() const;

    // close the Q
    // allow graceful exit for threads that wait on this Q object
    void close();

private:
    std::queue<T>           myDataQ;
    mutable std::mutex      myMutex;
    std::condition_variable myCondition;
    bool                    myIsExiting;

    TSQueue(const TSQueue&) = delete;
    TSQueue& operator=(const TSQueue&) = delete;
};

template<typename T>
size_t TSQueue<T>::size() const
{
    std::unique_lock<std::mutex> lock(myMutex);

    return myDataQ.size();
}

template<typename T>
void TSQueue<T>::close()
{
    std::unique_lock<std::mutex> lock(myMutex);
    
    myIsExiting = true;

    lock.unlock();

    myCondition.notify_all();
}

template<typename T>
void TSQueue<T>::push(const T& source)
{
    std::unique_lock<std::mutex> lock(myMutex);
    if (!myIsExiting)
    {
        myDataQ.push(source);
    }

    lock.unlock();

    myCondition.notify_one();
}

template<typename T>
bool TSQueue<T>::pop(T& target)
{
    bool isTargetUpdated = false;

    std::unique_lock<std::mutex> lock(myMutex);
    myCondition.wait(lock, [&] { return myIsExiting || !myDataQ.empty(); });
    
    if (!myDataQ.empty())
    {
        target = myDataQ.front();
        myDataQ.pop();
        isTargetUpdated = true;
    }

    return isTargetUpdated;
}
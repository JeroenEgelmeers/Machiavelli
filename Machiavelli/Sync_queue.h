//
//  Sync_queue.h
//  adapted from an example from Bjarne Stroustrup
//

#ifndef __Sync_queue__
#define __Sync_queue__

#include <mutex>
#include <condition_variable>
#include <list>
#include <future>
#include <thread>

template<typename T>
class Sync_queue {
public:
	void put(const T& val)
	{
		std::lock_guard<std::mutex> lck {mtx};
		q.push_back(val);
		cond.notify_one();
	}

	T get()
	{
		std::unique_lock<std::mutex> lck {mtx};
		cond.wait(lck, [this]{ return !q.empty(); });
		T val {q.front()};
		q.pop_front();
		return val;
	}

private:
    std::mutex mtx;
    std::condition_variable cond;
    std::list<T> q;
};

#endif /* defined(__Sync_queue__) */

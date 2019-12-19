#pragma once

#include <mutex>
#include <iostream>

class ThreadSafeCout {

public:
	static ThreadSafeCout& getInstance() {
		static ThreadSafeCout tsc;
		return tsc;
	}

	template<typename T>
	ThreadSafeCout& operator()(T&& _elem) {
		std::lock_guard<std::recursive_mutex> lockGuard(coutLock);
		std::cout << _elem;
		return *this;
	}

	template<typename T, typename... Args>
	ThreadSafeCout& operator()(T&& _elem, Args&& ... args) {
		std::lock_guard<std::recursive_mutex> lockGuard(coutLock);
		std::cout << _elem;
		return operator()(std::forward<Args>(args)...);
	}

private:
	ThreadSafeCout() = default;

	std::recursive_mutex coutLock;
};
#pragma once
#include <map>
#include <mutex>
#include <shared_mutex>

/*
	Very simple header only implementation of a ConcurrentMap.
	Use "safe" variants of methods when performing concurrent operations.
	Acquire a shared_lock for thread safe iterration.
	Acquire a unique_lock if you want to iterate and delete
*/

template<typename key, typename value>
class ConcurrentMap : public std::map<key, value>
{
public:
	/*Thread safe insert operation. Acquires unique lock.*/
	void safeInsert(std::pair<key, value> element)
	{
		std::unique_lock<std::shared_mutex> lg(lock);
		std::map<key,value>::insert(element);
	}

	/*Thread safe erase operation. Acquires unique lock.*/
	void safeErase(key k)
	{
		std::unique_lock<std::shared_mutex> lg(lock);
		std::map<key, value>::erase(k);
	}

	/*Thread safe find operation. Acquires shared lock.*/
	std::map<key,value>::iterator safeFind(key k)
	{
		std::shared_lock<std::shared_mutex> lg(lock);
		return std::map<key, value>::find(k);
	}

	/*Returns a shared lock for the given map. 
	This lock will provide the executing thread shared read access, and block SafeErrase + SafeInsert in other threads. 
	Acquire this lock before iterating through the map.*/
	std::shared_lock<std::shared_mutex> getSharedLock()
	{
		return std::shared_lock<std::shared_mutex>(lock);
	}

	/*Returns a unique lock for the given map. 
	This lock will provide the executing thread exclusive access to the map until it goes out of scope.*/
	std::shared_lock<std::shared_mutex> getUniqueLock()
	{
		return std::shared_lock<std::shared_mutex>(lock);
	}
private:
	std::shared_mutex lock;
};

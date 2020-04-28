#include <iostream>
#include <thread>

#include "ConcurrentMap.h"

ConcurrentMap<int, int> cmap;

void InsertThread()
{
	cmap.safeInsert(std::make_pair(0, 0));
	std::cout << "safe insert : " << 0 << std::endl;

	for (int i = 1; i <= 100; i++)
	{
		//cmap.safeErase(i - 1);
		//std::cout << "safe erase : " << i << std::endl;
		cmap.safeInsert(std::make_pair(i, i));
		std::cout << "safe insert : " << i << std::endl;
	}
}

void ReadThread()
{
	for (int i = 0; i < 150; i++)
	{
    //acquire a shared_lock (read lock) before iterating.
		std::shared_lock<shared_mutex> lock = cmap.getSharedLock();
		for (auto it : cmap)
		{
			std::cout << "read : " << it.second << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}

int main()
{
	std::thread t1(&InsertThread);
	std::thread t2(&ReadThread);

	t1.join();
	t2.join();
  
  return 0;
}

# ConcurrentMap

A single header implementation of a ConcurrentMap. The implementation is in the form of a wrapper around std::map, extending its functionality by providing "safe" variants of common operations.

In order to guarantee thread safety when not using "safe" variants you must acquire locks on the map. For example, if you want to iterate through the map, you should acquire a shared_lock first. If you want to iterate as well as modify (erase / insert) elements, you should acquire a unique_lock first. The way you release the lock is by either having it go out of scope, or explicitly unlocking it.

To view an example of usage [click here](example.cpp)

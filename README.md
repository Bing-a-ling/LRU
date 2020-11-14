# LRU
a simple LRU container.

## Usage

### include
```c++
#include "LRUcache.hpp"
```

### define
LRU container can store key-value elements.
Value type should be given as template argument.
Container size should be given as constructor argument. 
```c++
LRUCache<Value-type> mycache(size);
```

### api
Only two api: put & get
```c++
void put(int key, UserType value);
UserType get(int key);
```

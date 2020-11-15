#include <iostream>
#include <random>
#include <time.h>
#include "LRUcache.hpp"
using namespace std;
// test LRUcache
int main(){
    std::default_random_engine random;
    random.seed(static_cast<unsigned int>(time(NULL)));
    LRUCache<int64_t> my_cache(100);
    for(int i = 0; i < 10000; i++){
        int key = random() % 1000;
        if(random() % 2){
            cout << "Add: " << key << " " << key << endl;
            my_cache.put(key, 'a' + key);
        }else{
            int64_t res = my_cache.get(key);
            if(res){
                cout << "Hit: " << key << " " << res << endl;
            }else{
                cout << "Miss:" << key << endl;
            }
        }
    }
    return 0;
}

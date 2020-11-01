#include <iostream>
#include <random>
#include <time.h>
#include "LRUcache.hpp"
using namespace std;
// test LRUcache
int main(){
    std::default_random_engine random;
    random.seed(static_cast<unsigned int>(time(NULL)));
    LRUCache<int> my_cache(5);
    for(int i = 0; i < 100; i++){
        int key = random() % 10;
        if(random() % 2){
            cout << "Add: " << key << " " << key << endl;
            my_cache.put(key, 'a' + key);
        }else{
            char res = my_cache.get(key);
            if(res){
                cout << "Hit: " << key << " " << res << endl;
            }else{
                cout << "Miss:" << key << endl;
            }
        }
    }
    return 0;
}

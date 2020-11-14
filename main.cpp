#include <iostream>
#include <random>
#include <string>
#include <time.h>
#include "LRUcache.hpp"
using namespace std;
// test LRUcache
int main(){
    std::default_random_engine random;
    random.seed(static_cast<unsigned int>(time(NULL)));
    LRUCache<string>* my_cache = new LRUCache<string>(10000);
    for(int i = 0; i < 2000000; i++){
        int key = random() % 40000;
        if(random() % 2){
            string value = "r3045804982t0aojgkahglajslfdkgbathoifjaodaglhoaheifjabnlkjflajgaogaegaeobn0945840640568adgjaldgjg";
            cout << "Add: " << key << " " << value << endl;
            my_cache->put(key, value);
        }else{
            string res = my_cache->get(key);
            if(res != ""){
                cout << "Hit: " << key << " " << res << endl;
            }else{
                cout << "Miss:" << key << endl;
            }
        }
    }
    delete my_cache;
    return 0;
}

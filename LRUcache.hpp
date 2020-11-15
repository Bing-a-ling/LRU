//  LRUcache.hpp
//  Author: Bing-a-ling
#ifndef LRUcache_h
#define LRUcache_h
#include <unordered_map>
#include <list>

namespace{
    template <class ElemType>
    class Node{
    public:
        int key;
        ElemType val;
        std::shared_ptr<Node> last;
        std::shared_ptr<Node> next;
        Node(int k)
        :key(k), val(ElemType{}), last(nullptr), next(nullptr){}
        Node(int k, ElemType e)
        :key(k), val(e), last(nullptr), next(nullptr){}
    };
    template <class ElemType>
    class DoubleList{
    public:
        DoubleList(){
            head = std::make_shared<Node<ElemType>>(0);
            tail = std::make_shared<Node<ElemType>>(0);
            head->next = tail;
            tail->last = head;
            size = 0;
        }
        ~DoubleList(){
            while(size > 0){
                remove(head->next);
            }
            head->next = nullptr;
            tail->last = nullptr;
        }
        std::shared_ptr<Node<ElemType>> add(std::shared_ptr<Node<ElemType>> tmp){
            std::shared_ptr<Node<ElemType>> prev = tail->last;
            prev->next = tmp;
            tmp->last = prev;
            tmp->next = tail;
            tail->last = tmp;
            size++;
            return tmp;
        }
        // 需要保证x是list中的结点
        void remove(std::shared_ptr<Node<ElemType>> x){
            x->next->last = x->last;
            x->last->next = x->next;
            x->last = nullptr;
            x->next = nullptr;
            size--;
        }
        std::shared_ptr<Node<ElemType>> removeFront(){
            if(head->next == tail) return nullptr;
            std::shared_ptr<Node<ElemType>> deleted_node = head->next;
            remove(deleted_node);
            return deleted_node;
        }
        int getSize(){
            return size;
        }
    private:
        std::shared_ptr<Node<ElemType>> head;
        std::shared_ptr<Node<ElemType>> tail;
        int size;
    };
}

template <class ElemType>
class LRUCache{
public:
    LRUCache(int c)
    :capacity(c){}
    ~LRUCache(){
        map.clear();
    }
    void put(int key, ElemType value){
        if(map.find(key) != map.end()){
            deleteKey(key);
            addRecently(key, value);
            return;
        }
        if(cache.getSize() == capacity){
            deleteLeastRecently();
        }
        addRecently(key, value);
    }
    ElemType get(int key){
        if(map.find(key) == map.end()) return ElemType{};
        makeRecently(key);
        return map[key]->val;
    }
private:
    void makeRecently(int key){
        std::shared_ptr<Node<ElemType>> node = map[key];
        cache.remove(node);
        cache.add(node);
    }
    void addRecently(int key, ElemType& val){
        auto tmp = std::make_shared<Node<ElemType>>(key, val);
        std::shared_ptr<Node<ElemType>> node = cache.add(tmp);
        map[key] = node;
    }
    void deleteKey(int key){
        if(map.find(key) != map.end()){
            std::shared_ptr<Node<ElemType>> elem = map[key];
            cache.remove(elem);
            map.erase(key);
        }
    }
    void deleteLeastRecently(){
        std::shared_ptr<Node<ElemType>> front = cache.removeFront();
        if(front){
            map.erase(front->key);
        }
    }
private:
    DoubleList<ElemType> cache;
    std::unordered_map<int, std::shared_ptr<Node<ElemType>>> map;
    int capacity;
};

#endif /* LRUcache_h */

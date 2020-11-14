//  LRUcache.hpp
//  Author: Bing-a-ling
#ifndef LRUcache_h
#define LRUcache_h
#include <unordered_map>

namespace{
    template <class ElemType>
    class Node{
    public:
        int key;
        ElemType val;
        Node* last;
        Node* next;
        Node(int k, ElemType elem = ElemType{})
        :key(k), val(elem), last(nullptr), next(nullptr){}
    };
    template <class ElemType>
    class DoubleList{
    public:
        DoubleList(){
            head = new Node<ElemType>(0);
            tail = new Node<ElemType>(0);
            head->next = tail;
            tail->last = head;
            size = 0;
        }
        ~DoubleList(){
            while(size > 0){
                auto p = removeFront();
                delete p;
            }
            delete head;
            delete tail;
        }
        void add(Node<ElemType>* tmp){
            Node<ElemType>* prev = tail->last;
            prev->next = tmp;
            tmp->last = prev;
            tmp->next = tail;
            tail->last = tmp;
            size++;
        }
        // 需要保证x是list中的结点
        void remove(Node<ElemType>* x){
            x->next->last = x->last;
            x->last->next = x->next;
            x->last = nullptr;
            x->next = nullptr;
            size--;
        }
        Node<ElemType>* removeFront(){
            if(head->next == tail) return nullptr;
            Node<ElemType>* deleted_node = head->next;
            remove(deleted_node);
            return deleted_node;
        }
        int getSize(){
            return size;
        }
    private:
        Node<ElemType> * head;
        Node<ElemType> * tail;
        int size;
    };
}

template <class ElemType>
class LRUCache{
public:
    LRUCache(int c)
    :capacity(c){}
    ~LRUCache(){

    }
    void put(int key, ElemType value){
        if(map.find(key) != map.end()){
            deleteKey(key);
        }
        if(cache.getSize() == capacity){
            deleteLeastRecently();
        }
        addRecently(key, value);
    }
    ElemType get(int key){
        if(map.find(key) == map.end()) return ElemType {};
        makeRecently(key);
        return map[key]->val;
    }
private:
    void makeRecently(int key){
        Node<ElemType>* node = map[key];
        cache.remove(node);
        cache.add(node);
    }
    void addRecently(int key, ElemType& val){
        Node<ElemType>* tmp = new Node<ElemType>(key, val);
        cache.add(tmp);
        map[key] = tmp;
    }
    void deleteKey(int key){
        if(map.find(key) != map.end()){
            Node<ElemType>* elem = map[key];
            cache.remove(elem);
            map.erase(key);
            delete(elem);
        }
    }
    void deleteLeastRecently(){
        Node<ElemType>* front = cache.removeFront();
        if(front){
            map.erase(front->key);
            delete front;
        }
    }
private:
    DoubleList<ElemType> cache;
    std::unordered_map<int, Node<ElemType>*> map;
    int capacity;
};

#endif /* LRUcache_h */

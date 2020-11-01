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
        Node* last;
        Node* next;
        Node(int k, ElemType elem)
        :key(k), val(elem), last(nullptr), next(nullptr){}
    };
    template <class ElemType>
    class DoubleList{
    public:
        DoubleList(){
            head = new Node<ElemType>(0, NULL);
            tail = new Node<ElemType>(0, NULL);
            head->next = tail;
            tail->last = head;
            size = 0;
        }
        Node<ElemType>* add(Node<ElemType>* tmp){
            Node<ElemType>* prev = tail->last;
            prev->next = tmp;
            tmp->last = prev;
            tmp->next = tail;
            tail->last = tmp;
            size++;
            return tmp;
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
    ~LRUCache(){}
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
        if(map.find(key) == map.end()) return NULL;
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
        Node<ElemType>* node = cache.add(tmp);
        map[key] = node;
    }
    Node<ElemType>* deleteKey(int key){
        if(map.find(key) != map.end()){
            Node<ElemType>* elem = map[key];
            cache.remove(elem);
            map.erase(key);
            return elem;
        }
        return nullptr;
    }
    Node<ElemType>* deleteLeastRecently(){
        Node<ElemType>* front = cache.removeFront();
        if(front){
            map.erase(front->key);
        }
        return front;
    }
private:
    DoubleList<ElemType> cache;
    std::unordered_map<int, Node<ElemType>*> map;
    int capacity;
};

#endif /* LRUcache_h */

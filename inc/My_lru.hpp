#include<iostream>
#include<map>
#include<atomic>
#include<mutex>
using namespace std;
struct CatchNode
{
    /* data */
    int key;
    int value;
    CatchNode* pre, * next;
    CatchNode(int k, int v):key(k), value(v), pre(nullptr), next(nullptr){}
};
class My_lru
{
private:
    /* data */
    int _size;
    CatchNode* _head, *_tail;
    map<int, CatchNode*> _map;
public:
    explicit My_lru(int size):_size(size), _head(nullptr), _tail(nullptr){};
    My_lru(const My_lru&rhs) = delete;
    My_lru&operator=(const My_lru&rhs) = delete;
    My_lru(My_lru&&rhs) = delete;
    int get(int key){
        auto Cur = _map.find(key);
        if(Cur == _map.end()) return -1;
        remove(Cur->second);
        sethead(Cur->second);
    }
    void set(int key, int value)
    {
        auto Cur = _map.find(key);
        if(Cur!=_map.end()){
            remove(Cur->second);
            Cur->second->value = value;
            _map[key] = Cur->second;
            sethead(Cur->second);
        }
        else{
            CatchNode* in = new CatchNode(key, value);
            if(_size <= _map.size()) {
                auto Cur = _map.find(_tail->key);
                
                remove(Cur->second);
                
            }
            _map[key] = in;
            _map.erase(Cur);
            sethead(in);
        }
    }
    void remove(CatchNode* node){
        if(node->pre) node->pre->next = node->next;
        else _head = node->next;
        if(node->next) node->next->pre = node->pre;
        else _tail = node->pre;
    }
    void sethead(CatchNode* node){
        node->next = _head;
        if(_head) _head->pre = node;
        _head = node;
        if(!_tail) _tail = node;
    }
    ~My_lru();
};



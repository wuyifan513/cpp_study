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
    explicit My_lru(int size):_size(size){};
    
    ~My_lru();
};



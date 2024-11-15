#include<iostream>
#include<memory>
#include<atomic>
#include<thread>
#include<mutex>
#include<queue>
using namespace std;
template<class T>
class Shared
{
private:
    /* data */
    T* _ptr{nullptr};
    int* ref_count{nullptr};
    mutex* mux{nullptr};
    void addref(){
        mux->lock();
        ++(*ref_count);
        mux->unlock();
    }
    void deref(){
        bool flag = false;
        mux->lock();
        if(--(*ref_count) == 0){
            flag = true;
            delete _ptr;
            delete ref_count;
        }
        mux->unlock();
        delete mux;
        _ptr = nullptr;
        ref_count = nullptr;
        mux = nullptr;
    }
public:
    Shared(T* ptr):_ptr(ptr), mux(nullptr), ref_count(nullptr){
        if(ptr){
            ref_count = new int(1);
            mux = new mutex();
        }
    }
    Shared(const Shared& rhs):_ptr(rhs._ptr), mux(rhs.mux), ref_count(rhs.ref_count){
        if(_ptr){
            addref();
        }
    }
    Shared&operator=(const Shared&rhs){
        if(_ptr) deref();
        this->ref_count = rhs.ref_count;
        this->mux = rhs.mux;
        this->_ptr = rhs._ptr;
        return *this;
    }
    Shared(Shared&& rhs){
        if(_ptr) deref();
        this->_ptr = rhs.ptr;
        this->ref_count = rhs.ref_count;
        this->mux = rhs.mux;
    }
(/* args */);
    ~Shared(){
        deref();
    }
();
};



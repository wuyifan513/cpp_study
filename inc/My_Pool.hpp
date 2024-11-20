#include<atomic>
#include<queue>
#include<vector>
#include<condition_variable>
#include<iostream>
#include<mutex>
#include<thread>
using namespace std;
template <class T>
class My_Pool
{
private:
    /* data */
    atomic_bool is_running;
    int num_thread;
    condition_variable cv;
    mutex mux;
    queue<Task> q;
    vector<thread> workers;
    void work(){
        cout<<this_thread::get_id()<< endl;
        while(is_running)
        {
            Task t;
            {

            
                unique_lock<mutex> lk(mux);
                if(!q.empty()){
                    t = q.front();
                    q.pop();
                }
                else if(is_running&&q.empty()) cv.wait(lk);
            }
            if(t) t();
        }
    }
public:
    using Task = function<void()>;
    explicit My_Pool(int num):num_thread(num), is_running(false){};
    void start(){
        {
            unique_lock<mutex> lk(mux);
            is_running = true;
        }
        for(int i = 0; i < num_thread; i ++){
            workers.push_back(thread(&My_Pool::work, &My_Pool));
        }
    }
    void appendtast(const Task& t){
        if(is_running){
            unique_lock<mutex> lk(mux);
            q.push(t);
        }
    }
    void stop(){
        {
            unique_lock<mutex> lk(mux);
            is_running = false;
        }
        for(int i = 0; i < num_thread; i ++){
            if(workers[i].joinable()) workers[i].join();
        }
    }
    ~My_Pool(){};
};


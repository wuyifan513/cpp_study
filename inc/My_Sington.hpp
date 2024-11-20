#include<iostream>
#include<mutex>
using namespace std;
class My_Sington
{
private:
    /* data */
    My_Sington(/* args */){};
    My_Sington(const My_Sington&rhs) = delete;
    My_Sington&operator=(const My_Sington&rhs) = delete;
    My_Sington(My_Sington&&rhs) = delete;
    static My_Sington* instance;
    static mutex mux;
    ~My_Sington();
public:
    static My_Sington* get_instance(){
        if(!instance){
            unique_lock<mutex> lk(mux);
            if(!instance){
                volatile auto tmp = new My_Sington();
                instance = tmp;
            }
            
        }
        return instance;
    }
    static void deleteinstance(){
        unique_lock<mutex> lk(mux);
        if(instance){
            delete instance;
            instance = nullptr;
        }
    }
};
My_Sington* My_Sington::instance = nullptr;
mutex My_Sington::mux;


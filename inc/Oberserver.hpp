#include<iostream>
#include<vector>
#include<unordered_map>
#include<list>
using namespace std;
class AbstractOberserver
{
private:
    /* data */
public:
    AbstractOberserver(/* args */){};
    virtual void Updata(const string& str) = 0;
    virtual ~AbstractOberserver(){};
};
class Abstractproduct
{
private:
    /* data */
public:
    Abstractproduct(/* args */){};
    virtual ~Abstractproduct(){};
    virtual void Attach(AbstractOberserver* ob) = 0;
    virtual void Detach(AbstractOberserver* ob) = 0;
    virtual void Notify() = 0;
};
class Concreteproduct:public Abstractproduct{
public:
    Concreteproduct(const string& mes):messages(mes){};
    Concreteproduct():messages("default"){};
    ~Concreteproduct(){};
    void Attach(AbstractOberserver* ob) override{
        oblist.push_back(ob);
    }
    void Detach(AbstractOberserver* ob) override{
        oblist.remove(ob);
    }
    void Notify() override{
        for(auto&item:oblist){
            item->Updata(messages);
        }
    }
    void RefreshMessage(const string& message){
        messages = message;
        Notify();
    }
private:
    list<AbstractOberserver*> oblist;
    string messages;
};



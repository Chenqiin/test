#include <iostream>
#include <thread>
#include <functional>
#include <mutex>

using namespace std;
once_flag g_flag;
void func()
{
    cout<<endl;
    cout<<"jhHHh"<<endl;
    cout<<endl;
}
void func2(string name ,int age)
{
    cout<<endl;
    cout<<name<<endl;
    cout<<endl;
}
//单例模式---懒汉模式（call_once()实现）
class Base
{
public:
    Base(const Base& obj) = delete;
    Base& operator= (const Base& obj) = delete;
    static Base* getInstance()
    {
        call_once(g_flag , [&](){
            obj  = new Base;
            cout<<"chuangjian"<<endl;
        });
        return obj;
    }

    void set(string name)
    {
        this->name = name;
    }
    string getName()
    {
        return name;
    }
private:
    Base(){};
    static  Base* obj;
    string name;
};

// 在类定义之后
Base* Base::obj = nullptr;


int main1() {
//    //测试多线程
//    thread t2(func);
//
//    thread t3(func2,"my",2);
//
//    t2.join();
//    t3.join();

    Base::getInstance()->set("ddd");
    cout<<Base::getInstance()->getName()<<endl;
//
    Base::getInstance()->set("qq");
    cout<<Base::getInstance()->getName()<<endl;

    Base::getInstance()->set("ccc");
    cout<<Base::getInstance()->getName()<<endl;
    return 0;
}

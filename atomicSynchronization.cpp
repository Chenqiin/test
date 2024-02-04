//
// Created by Administrator on 2024/2/4.
//
/*
 * 使用原子变量实现线程同步
 */
#include <iostream>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;
class Counter
{
public:
    void increment()
    {
        for(int i = 0;i<100;++i)
        {
            number++;
            cout<<"++ increment thread id:"<<this_thread::get_id()
            <<", number:"<<number<<endl;
            this_thread::sleep_for(chrono::milliseconds(25));
        }
    }
    void increment1()
    {
        for(int i = 0;i<100;++i)
        {
            number++;
            cout<<"** increment thread id:"<<this_thread::get_id()
                <<", number:"<<number<<endl;
            this_thread::sleep_for(chrono::milliseconds(30));
        }
    }
private:
//    int number = 0;
    atomic_int number = 0;
};
int main()
{
    Counter c;
    thread t1(&Counter::increment,&c);
    thread t2(&Counter::increment1,&c);
    t1.join();
    t2.join();
    cout<<"ddd";
}
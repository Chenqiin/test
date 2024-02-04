//
// Created by Administrator on 2024/2/4.
//
#include <iostream>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <string>
using namespace std;
/**
 * @brief promise使用方法
 * @param pro
 */
void func(promise<string>& pro)
{
    this_thread::sleep_for(chrono::seconds(3));
    pro.set_value("ddf sadfsdafsd");
}
int main()
{
    promise<string> pro;
    thread t1(func,std::ref(pro));

    string str = pro.get_future().get();
    t1.join();
    cout<<str<<endl;
    return 0;
}
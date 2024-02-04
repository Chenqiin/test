//
// Created by Administrator on 2024/2/3.
//
#include <iostream>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;
//消费者生产者模型
class Task
{
public:
    Task(){
        cout<<"创建无参构造函数"<<endl;
        i = 0;
    }
    Task(const Task  & a){
        cout<<"创建拷贝构造函数"<<endl;
        i = 0;
    }
    Task(Task  && a){
        cout<<"创建移动构造函数"<<endl;
        i = 0;
    }
    ~Task()
    {
        cout<<"销毁"<<endl;
    }
    int i ;
};
//任务队列
template<typename T>
class TaskQueue
{
public:
    //添加数据
    void putTask(T&& t1);
    //取数据
    T&& take()
    {
        while(isEmpty())
        {
            unique_lock<mutex> locker(m_mutex);
            notEmpty.wait(locker);
        }
        T&& t = std::move(taskQueue.front());
        taskQueue.pop();
        notFull.notify_one();
        return std::forward<T>(t);
    }
    bool ifFull()
    {
        lock_guard<mutex>locker(m_mutex);
        if(maxSize == taskQueue.size())
        {
            return true;
        }
        return false;
    }
    bool isEmpty()
    {
        lock_guard<mutex>locker(m_mutex);
        if(taskQueue.size() == 0)
        {
            return true;
        }
        return false;
    }
    int taskSize()
    {
        lock_guard<mutex>locker(m_mutex);
        return taskQueue.size();
    }
private:
    int maxSize = 10;
    queue<T> taskQueue;
    mutex m_mutex;
    condition_variable notFull; //管理生产者线程
    condition_variable notEmpty;    //管理消费者线程
};
template<typename T>
void TaskQueue<T>::putTask(T&& t1)
{
    while(ifFull())
    {
        unique_lock<mutex> locker(m_mutex);
        notFull.wait(locker);
    }
    taskQueue.push(std::forward<T>(t1));
    cout<<"添加任务,线程ID:"<<this_thread::get_id<<endl;
    notEmpty.notify_one();
}
int main() {
    TaskQueue<int> que;
    int i =1;
//    Task a;
//    que.putTask(Task());
//    auto b = que.take();
    thread t1[5];
    for(int i = 0;i<5;++i)
    {
        t1[i] =  thread(&TaskQueue<int>::putTask,&que,i+1);

    }

    for(int i = 0 ;i<5 ;++i)
    {
        auto a = que.take();
        cout<<"a:"<<a<<endl;
    }


    for(int i = 0;i<5;++i)
    {
        t1[i].join();

    }

    cout<<"dd"<<endl;
}



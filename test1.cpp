//
// Created by Administrator on 2024/2/3.
//
#include <iostream>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
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
        T&& t = std::move(taskQueue.front());
        taskQueue.pop();
        return std::forward<T>(t);
    }
    bool ifFull()
    {
        if(maxSize == taskQueue.size())
        {
            return true;
        }
        return false;
    }
    bool isEmpty()
    {
        if(taskQueue.size() == 0)
        {
            return true;
        }
        return false;
    }
private:
    int maxSize;
    queue<T> taskQueue;
};
template<typename T>
void TaskQueue<T>::putTask(T&& t1)
{
    taskQueue.push(std::forward<T>(t1));
    cout<<"添加任务,线程ID:"<<this_thread::get_id<<endl;
}
int main() {
    TaskQueue<Task> que;
    int i =1;
//    Task a;
    que.putTask(Task());

    auto b = que.take();
    cout<<"dd"<<endl;
}



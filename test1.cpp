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
//������������ģ��
class Task
{
public:
    Task(){
        cout<<"�����޲ι��캯��"<<endl;
        i = 0;
    }
    Task(const Task  & a){
        cout<<"�����������캯��"<<endl;
        i = 0;
    }
    Task(Task  && a){
        cout<<"�����ƶ����캯��"<<endl;
        i = 0;
    }
    ~Task()
    {
        cout<<"����"<<endl;
    }
    int i ;
};
//�������
template<typename T>
class TaskQueue
{
public:
    //�������
    void putTask(T&& t1);
    //ȡ����
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
    condition_variable notFull; //�����������߳�
    condition_variable notEmpty;    //�����������߳�
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
    cout<<"�������,�߳�ID:"<<this_thread::get_id<<endl;
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



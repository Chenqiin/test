//
// Created by Administrator on 2024/2/3.
//
#include <iostream>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
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
    cout<<"�������,�߳�ID:"<<this_thread::get_id<<endl;
}
int main() {
    TaskQueue<Task> que;
    int i =1;
//    Task a;
    que.putTask(Task());

    auto b = que.take();
    cout<<"dd"<<endl;
}



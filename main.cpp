#include <iostream>
#include <thread>
using namespace std;
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
int main() {
//    thread t1;

    thread t2(func);

    thread t3(func2,"my",2);
//    std::cout << "Hello, World!" << std::endl;
//    t1.join();
    t2.join();
    t3.join();
    return 0;
}

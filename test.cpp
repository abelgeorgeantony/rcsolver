#include<iostream>
using namespace std;
float test = 5;
float& testt()
{
    float* address;
    address = &test;
    return *address;
}

int main()
{
    float *ptr = &testt();
    cout<<ptr<<"\n";
    cout<<&test<<"\n";
    return(0);
}

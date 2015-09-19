/*************************************************************************
    > File Name: trylistvoid.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Wed 25 Mar 2015 08:50:36 PM CST
 ************************************************************************/

#include<iostream>
#include<list>
#include<malloc.h>
using namespace std;
void tryList(list<void*> listvoid)
{
	int *p = static_cast<int*>(listvoid.front());	
	cout << *p << endl;
	listvoid.pop_front();
	char *str = static_cast<char*>(listvoid.front());
	cout << str << endl;
	listvoid.pop_front();
}

int main()
{
	list<void *> listtry;
	int a = 1;
	int *p = &a;
	listtry.push_back(static_cast<void*>(p));
	char *c; 
	string str = "woshiheike";
	int len = str.length();
	c = (char *)malloc((len+1)*sizeof(char));
	str.copy(c,len,0);
	listtry.push_back(static_cast<void*>(c));
	tryList(listtry);
	return 0;
}

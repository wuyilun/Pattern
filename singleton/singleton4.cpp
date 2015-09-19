/*************************************************************************
    > File Name: singleton4.cpp
    > Author: wuyilun
    > Mail: wuyilun526@163.com 
    > Created Time: Sat Sep 19 19:13:21 2015
 ************************************************************************/

#include<iostream>
using namespace std;

class Singleton{
	public:
		static Singleton * GetInstance(){
			return m_Instance;
		}

		int GetTest(){
			return m_Test;
		}

	private:
		Singleton(){
			m_Test = 10;
		}
		static Singleton * m_Instance;
		int m_Test;

		class GC{
			public:
				~GC(){
					if(m_Instance != NULL){
						cout << "Here is the test." << endl;
						delete m_Instance;
						m_Instance = NULL;
					}
				}
		};
		static GC gc;
};

Singleton * Singleton::m_Instance = new Singleton();
Singleton ::GC Singleton :: gc; 

int main(){
	Singleton * singletonObj = Singleton::GetInstance();
	cout << singletonObj->GetTest() << endl;
	return 0;
}

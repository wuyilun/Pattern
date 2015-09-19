/*************************************************************************
    > File Name: singleton2.cpp
    > Author: wuyilun
    > Mail: wuyilun526@163.com 
    > Created Time: Sat Sep 19 16:47:28 2015
 ************************************************************************/

#include<iostream>
using namespace std;

class Singleton{
	public:
		static Singleton * GetInstance(){
			return const_cast<Singleton *>(m_Instance);
		}

		static void DestroyInstance(){
			if(m_Instance != NULL){
				delete m_Instance;
				m_Instance = NULL;
			}
		}

		int GetTest(){
			return m_Test;
		}
	
	private:
		Singleton(){
			m_Test = 10;
		}
		static const Singleton * m_Instance;
		int m_Test;
};


const Singleton * Singleton::m_Instance = new Singleton();

int main(){
	Singleton * singletonObj = Singleton::GetInstance();
	cout << singletonObj->GetTest() << endl;
	Singleton::DestroyInstance();
}

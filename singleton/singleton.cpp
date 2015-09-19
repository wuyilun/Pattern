/*************************************************************************
    > File Name: singleton.cpp
    > Author: wuyilun
    > Mail: wuyilun526@163.com 
    > Created Time: Sat Sep 19 16:06:44 2015
 ************************************************************************/

#include<iostream>
using namespace std;

class Singleton{
	public:
		static Singleton * createInstance(int number){
			if(m_instance == NULL){
				m_instance = new Singleton(number);
			}
			return m_instance;
		}
		static void * deleteInstance(){
			if(m_instance != NULL){
				delete m_instance;
				m_instance = NULL;
			}
			cout << "successed delete." << endl;
		}
		void print(){
			cout << "number:" << m_number << endl;
		}
	private:
		Singleton(int number);
		int m_number;
		static Singleton * m_instance;
};

Singleton * Singleton::m_instance = NULL;
Singleton::Singleton(int number):m_number(number){

}

int main(){
	//Singleton * trysingleton = new Singleton(10);   //wrong
	Singleton * singleton = Singleton::createInstance(10);
	Singleton * singleton2 = Singleton::createInstance(12);
	singleton->print();		
	singleton2->print();
	singleton->deleteInstance();
	singleton2->deleteInstance();
	return 0;
}

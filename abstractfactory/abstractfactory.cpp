/*************************************************************************
    > File Name: abstractfactory.cpp
    > Author: wuyilun
    > Mail: wuyilun526@163.com 
    > Created Time: Sat Sep 19 21:34:28 2015
 ************************************************************************/

#include<iostream>
using namespace std;

class Product {
	public:
		virtual void Show() = 0;
};

class ProductA1 : public Product {
	public:
		void Show(){
			cout << "ProductA1." << endl;
		}
};

class ProductA2 : public Product {
	public:
		void Show(){
			cout << "ProductA2." << endl;
		}
};

class ProductB1 : public Product {
	public:
		void Show(){
			cout << "ProductB1." << endl;
		}
};

class ProductB2 : public Product {
	public:
		void Show(){
			cout << "ProductB2." << endl;
		}
};

class AbstractFactory {
	public:
		virtual Product * CreateProductA() = 0;
		virtual Product * CreateProductB() = 0;
};

class Factory1 : public AbstractFactory {
	public:
		Product * CreateProductA(){
			return new ProductA1();
		}
		Product * CreateProductB(){
			return new ProductB1();
		}
};

class Factory2 : public AbstractFactory {
	public:
		Product * CreateProductA(){
			return new ProductA2();
		}
		Product * CreateProductB(){
			return new ProductB2();
		}
};

int main(){
	AbstractFactory *factory = new Factory1();
	Product *productA = factory->CreateProductA();
	Product *productB = factory->CreateProductB();
	productA->Show();
	productB->Show();
	
	AbstractFactory *factory2 = new Factory2();
	Product *productA2 = factory2->CreateProductA();
	Product *productB2 = factory2->CreateProductB();
	productA2->Show();
	productB2->Show();

	delete factory;
	factory = NULL;
	delete productA;
	productA = NULL;
	delete productB;
	productB = NULL;

	delete factory2;
	factory2 = NULL;
	delete productA2;
	productA2 = NULL;
	delete productB2;
	productB2 = NULL;

	return 0;
}

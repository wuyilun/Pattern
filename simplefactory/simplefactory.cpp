/*************************************************************************
    > File Name: simplefactory.cpp
    > Author: wuyilun
    > Mail: wuyilun526@163.com 
    > Created Time: Sat Sep 19 20:18:57 2015
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

typedef enum ProductTypeTag{
	TypeA,
	TypeB,
	TypeC
}PRODUCTTYPE;

class Product{
	public:
		virtual void show() = 0;
};

class ProductA : public Product{
	public:
		void show(){
			cout << "ProductA." << endl;
		}
};

class ProductB: public Product{
	public:
		void show(){
			cout << "ProductB." << endl;
		}
};


class ProductC: public Product{
	public:
		void show(){
			cout << "ProductC." << endl;
		}
};

class Factory{
	public:
		Product * CreateProduct(PRODUCTTYPE type){
			switch(type){
				case TypeA:
					return new ProductA();
				case TypeB:
					return new ProductB();
				case TypeC:
					return new ProductC();
				default:
					return NULL;
			}
		}
};

int main(){
	Factory *productFactory = new Factory();
	Product *productA = productFactory->CreateProduct(TypeA);
	if(productA != NULL){
		productA->show();
	}
	Product *productB = productFactory->CreateProduct(TypeB);
	if(productB != NULL){
		productB->show();
	}

	delete productA;
	productA = NULL;

	delete productB;
	productB = NULL;

	return 0;
}

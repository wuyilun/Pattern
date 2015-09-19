/*************************************************************************
    > File Name: factorymethod.cpp
    > Author: wuyilun
    > Mail: wuyilun526@163.com 
    > Created Time: Sat Sep 19 20:51:27 2015
 ************************************************************************/

#include<iostream>
using namespace std;

class Product{
	public:
		virtual void Show() = 0;
};

class ProductA : public Product {
	public:
		void Show(){
			cout << "ProductA." << endl;
		}
};

class ProductB : public Product {
	public:
		void Show(){
			cout << "ProductB." << endl;
		}
};

class Factory{
	public:
		virtual Product * CreateProduct() = 0;
};

class ProductAFactory : public Factory {
	public:
		Product * CreateProduct(){
			return new ProductA();
		}
};

class ProductBFactory : public Factory {
	public:
		Product * CreateProduct(){
			return new ProductB();
		}
};

int main(){
	Factory *factoryA = new ProductAFactory();
	Product *productA = factoryA->CreateProduct();
	if(productA != NULL){
		productA->Show();
	}
	Factory *factoryB = new ProductBFactory();
	Product *productB = factoryB->CreateProduct();
	if(productB != NULL){
		productB->Show();
	}

	delete factoryA;
	factoryA = NULL;
	delete productA;
	productA = NULL;

	delete factoryB;
	factoryB = NULL;
	delete productB;
	productB = NULL;

	return 0;
}

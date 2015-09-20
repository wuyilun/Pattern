#ifndef CASH_CPP
#define CASH_CPP

#include<string>
#include<iostream>
#include<list>
using namespace std;

class Product{
	public:
		Product(int id, double unit_price, double sale_number): product_id_(id), unit_price_(unit_price), sale_number_(sale_number){}
		void set_product_id(int id){
			product_id_ = id;
		}
		int get_product_id(){
			return product_id_;
		}
		void set_unit_price(double price){
			unit_price_ = price;
		}
		double get_unit_price(){
			return unit_price_;
		}
		void set_sale_number(double number){
			sale_number_ = number;
		}
		double get_sale_number(){
			return sale_number_;
		}
	private: 
		int product_id_;
		double unit_price_;
		double sale_number_;
};

class SuperStrategy
{
	public:
		virtual void Handle() = 0;
		virtual double Result() = 0;
};

class Normal: public SuperStrategy
{
	public:
		Normal(list<Product> material): material_(material){}
		void Handle(){
			cash_ = 0.0;
			for(list<Product>::iterator i = material_.begin(); i != material_.end(); i++)
				cash_ += (*i).get_unit_price() * (*i).get_sale_number();
		}
		double Result(){
			Handle();
			return cash_; 
		}
	private:
		list<Product> material_;
		double cash_;
};

class Rate: public SuperStrategy 
{
	public:
		explicit Rate(list<Product> material, double rate):material_(material), rate_(rate){}
		void Handle(){
			cash_ = 0.0;
			for(list<Product>::iterator i = material_.begin(); i != material_.end(); i++)
				cash_ += (*i).get_unit_price() * (*i).get_sale_number();
		}
		double Result(){
			Handle();
			cout << cash_ << endl;
			cash_ = cash_ * rate_;
			return cash_;
		}
	private:
		list<Product> material_;
		double rate_;
		double cash_;
};

class ReturnCash: public SuperStrategy 
{
	public:
		ReturnCash(list<Product>material, double condition, double returncash):material_(material), condition_cash_(condition), return_cash_(returncash){}
		void Handle(){
			cash_ = 0.0;
			for(list<Product>::iterator i = material_.begin(); i != material_.end(); i++)
				cash_ += (*i).get_unit_price() * (*i).get_sale_number();
		}
		double Result(){
			Handle();
			double money = cash_;	
			cout << money << endl;
			if( money > condition_cash_ )
			{
				money -= static_cast<int>(money/condition_cash_) * return_cash_; 
			}
			return money;
		}
	private:
		list<Product> material_;
		double condition_cash_;
		double return_cash_;
		double cash_;
};

class CashContext
{
	public:
			explicit CashContext(list<Product> material, int strategy) {
			switch(strategy)
			{
				case 0:
					superStrategy_ = new Normal(material);
					break;
				case 1:
					superStrategy_ = new Rate(material, 0.8);
					break;
				case 2:
					superStrategy_ = new Rate(material, 0.9);
					break;
				case 3: 
					superStrategy_ = new ReturnCash(material, 300, 100);
					break;
				case 4:
					superStrategy_ = new ReturnCash(material, 500, 200);
				default:
					break;
			}
		}
		double ActuallyNeedToPay(){
			return superStrategy_->Result();
		}
	private:
		SuperStrategy *superStrategy_;
};

class StrategyFactory
{
	public:
		virtual void CreateStrategy() = 0;
};

class NormalFactory: public StrategyFactory
{
	public:
		void CreateStrategy()
		{
			return Normal();
		}
};

class RateFactory: public StrategyFactory
{
	public:
		void CreateStrategy()
		{
			return Rate();
		}
};

class ReturnCashFactory: public StrategyFactory
{
	public:
		void CreateStrategy()
		{
			return ReturnCash();
		}
};
#endif

#ifndef CASH_CPP
#define CASH_CPP

#include<string>
#include<iostream>
#include<list>
#include<set>
#include<algorithm>

using namespace std;

class Product{
	public:
		Product(int id, double unit_price, double sale_number): product_id_(id), unit_price_(unit_price), sale_number_(sale_number){
			unit_price_after_strategy_ = unit_price;	//set default value for unit_price after strategy done.
														//you should change this value when you change the product's price
														//in the strategy's Handle function.
		}
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
		void set_unit_price_after_strategy(double price){
			unit_price_after_strategy_ = price;
		}
		double get_unit_price_after_strategy(){
			return unit_price_after_strategy_;
		}
	private: 
		int product_id_;
		double unit_price_;
		double sale_number_;
		double unit_price_after_strategy_;
};

class SuperStrategy
{
	public:
		virtual void set_material(list<Product> &material) = 0;
		virtual void set_condition(list<void *> condition_list) = 0;
		virtual void Handle() = 0;
		virtual double Result() = 0;
};

class Normal: public SuperStrategy
{
	public:
		Normal(){}
		void set_material(list<Product> &material){
			material_ = &material;
		}
		void set_condition(list<void *> condition_list){
			condition_list_ = condition_list;
		}
		void Handle(){
			cash_ = 0.0;
			for(list<Product>::iterator i = (*material_).begin(); i != (*material_).end(); i++)
				cash_ += (*i).get_unit_price() * (*i).get_sale_number();
		}
		double Result(){
			Handle();
			return cash_; 
		}
	private:
		list<Product> *material_;
		list<void *> condition_list_;
		double cash_;
};

class Rate: public SuperStrategy 
{
	public:
		explicit Rate(){}
		void set_material(list<Product> &material){
			material_ = &material;
		}
		void set_condition(list<void *> condition_list){
			condition_list_ = condition_list;
			rate_ = 1.0;
			if(!condition_list_.empty())
			{
				double *rate = static_cast<double *>(condition_list_.front());
				condition_list_.pop_front();				
				rate_ = *rate;
			}
		}
		void Handle(){
			cash_ = 0.0;
			for(list<Product>::iterator i = (*material_).begin(); i != (*material_).end(); i++)
				cash_ += (*i).get_unit_price() * (*i).get_sale_number();
		}
		double Result(){
			Handle();
			cash_ = cash_ * rate_;
			return cash_;
		}
	private:
		list<Product> *material_;
		list<void *> condition_list_;
		double rate_;
		double cash_;
};

class SecondPieceRate: public SuperStrategy
{
	public:
		explicit SecondPieceRate(){}
		void set_material(list<Product> &material){
			material_ = &material;
		}
		void set_condition(list<void *> condition_list){
			condition_list_ = condition_list;
			rate_ = 1.0;
			if(!condition_list_.empty())
			{
				double *rate = static_cast<double *>(condition_list_.front());
				condition_list_.pop_front();				
				rate_ = *rate;
			}
		}
		void Handle(){
			cash_ = 0.0;
			for(list<Product>::iterator i = (*material_).begin(); i != (*material_).end(); i++)
			{
				int number = (*i).get_sale_number();
				int number_to_rate = number/2;
				int number_not_rate = number - number_to_rate;
				double unit_price = (*i).get_unit_price();
				cash_ += number_not_rate*unit_price + number_to_rate*unit_price*rate_;		//rate_ is the rate of the second piece of product 

				(*i).set_unit_price_after_strategy(cash_/number);
				//(*i).set_unit_price_after_strategy(0);
			}
		}
		double Result(){
			Handle();
			return cash_;
		}
	private:
		list<Product> *material_;
		list<void *> condition_list_;
		double rate_;
		double cash_;
		
};

class ReturnCash: public SuperStrategy 
{
	public:
		ReturnCash(){}
		void set_material(list<Product> &material){
			material_ = &material;
		}
		void set_condition(list<void *> condition_list){
			condition_list_ = condition_list;
			condition_cash_ = 1000000000;
			return_cash_ = 0.0;
			if(!condition_list_.empty())
			{
				double *condition_cash = static_cast<double *>(condition_list_.front());
				condition_list_.pop_front();				
				condition_cash_ = *condition_cash;
			}
			if(!condition_list_.empty())
			{
				double *return_cash = static_cast<double *>(condition_list_.front());
				condition_list_.pop_front();				
				return_cash_ = *return_cash;
			}
		}
		void Handle(){
			cash_ = 0.0;
			for(list<Product>::iterator i = (*material_).begin(); i != (*material_).end(); i++)
				cash_ += (*i).get_unit_price() * (*i).get_sale_number();
		}
		double Result(){
			Handle();
			double money = cash_;	
			if( money > condition_cash_ )
			{
				money -= static_cast<int>(money/condition_cash_) * return_cash_; 
			}
			return money;
		}
	private:
		list<Product> *material_;
		list<void *> condition_list_;
		double condition_cash_;
		double return_cash_;
		double cash_;
};

class Set: public SuperStrategy  //promotion set
{
	public:
		Set(){
		}
		void set_material(list<Product> &material){
			material_ = &material;
			for(list<Product>::iterator i = (*material_).begin(); i != (*material_).end(); i++)
				material_product_id_.insert((*i).get_product_id());
		}
		void set_condition(list<void *> condition_list){
		}
		set<int> findSet()
		{
			set<int> rule_id;
			string sql("select id from set_rule where flag = 1 and day() < enddate and day() > startdate");
			while()
			{
				string sql("select product_id from rule_activity where rule_id = ?");
				set<int> productid;
				while(string("next"))
				{
					productid.insert();	
				}
				bool is_subset = includes(material_product_id_.begin(), material_product_id_.end(), productid.begin(), productid.end());
				if(is_subset == true)
					rule_id.insert();
			}
			return rule_id;
		}
		void Handle(){
			cash_ = 0.0;
			for(list<Product>::iterator i = (*material_).begin(); i != (*material_).end(); i++)
				cash_ += (*i).get_unit_price() * (*i).get_sale_number();
		}
		double Result(){
			Handle();
			double money = cash_;	
			if( money > condition_cash_ )
			{
				money -= static_cast<int>(money/condition_cash_) * return_cash_; 
			}
			return money;
		}
	private:
		set<int> material_product_id_;
		list<Product> *material_;
		list<void *> condition_list_;
		double cash_;
};



class StrategyFactory
{
	public:
		virtual SuperStrategy* CreateStrategy() = 0;
};

class NormalFactory: public StrategyFactory
{
	public:
		SuperStrategy* CreateStrategy()
		{
			return new Normal();
		}
};

class RateFactory: public StrategyFactory
{
	public:
		SuperStrategy* CreateStrategy()
		{
			return new Rate();
		}
};

class SecondPieceRateFactory: public StrategyFactory
{
	public:
		SuperStrategy* CreateStrategy()
		{
			return new SecondPieceRate();
		}
};

class ReturnCashFactory: public StrategyFactory
{
	public:
		SuperStrategy* CreateStrategy()
		{
			return new ReturnCash();
		}
};
#endif

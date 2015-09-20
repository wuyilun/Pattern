/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Sat 21 Mar 2015 11:17:29 AM CST
 ************************************************************************/

#include<iostream>
//#include"cash.hpp"
#include"strategy.hpp"
using namespace std;

int main()
{
	//set material.
	list<Product> material;
	Product p1(1, 20, 40);
	Product p2(2, 30, 10);
	material.push_back(p1);
	material.push_back(p2);
	
	//strategy's name
	string strategy_name = "SecondPieceRate";

	if(strategy_name == "ReturnCash")
	{
		//set condition.
		list<void *> condition_list;
		double condition = 200;
		double returnmoney = 100;
		condition_list.push_back(static_cast<void *> (&condition));
		condition_list.push_back(static_cast<void *> (&returnmoney));

		//use factory pattern.
		StrategyFactory *factory = new ReturnCashFactory();
		SuperStrategy *strategy = factory->CreateStrategy();
		strategy->set_material(material);
		strategy->set_condition(condition_list);
		double cash = strategy->Result();
		cout << cash << endl;
	}
	else if(strategy_name == "Rate")
	{
		//set condition.
		list<void *> condition_list;
		double rate = 0.8;
		condition_list.push_back(static_cast<void *> (&rate));

		//use factory pattern.
		StrategyFactory *factory = new RateFactory();
		SuperStrategy *strategy = factory->CreateStrategy();
		strategy->set_material(material);
		strategy->set_condition(condition_list);
		double cash = strategy->Result();
		cout << cash << endl;
	}
	else if(strategy_name == "SecondPieceRate")
	{
		//set condition.
		list<void *> condition_list;
		double rate = 0.5;
		condition_list.push_back(static_cast<void *> (&rate));

		//use factory pattern.
		StrategyFactory *factory = new SecondPieceRateFactory();
		SuperStrategy *strategy = factory->CreateStrategy();
		strategy->set_material(material);
		strategy->set_condition(condition_list);
		double cash = strategy->Result();
		cout << cash << endl;

		Product s = material.front();
		cout << s.get_unit_price_after_strategy() << endl;
	}
	else if(strategy_name == "Normal")
	{
		//set condition.
		list<void *> condition_list;

		//use factory pattern.
		StrategyFactory *factory = new NormalFactory();
		SuperStrategy *strategy = factory->CreateStrategy();
		strategy->set_material(material);
		strategy->set_condition(condition_list);
		double cash = strategy->Result();
		cout << cash << endl;
	}
}


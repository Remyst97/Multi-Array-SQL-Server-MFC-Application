#include <iostream>
#include <string>

using namespace std;

#include "stdafx.h" 

#pragma once
#include <iostream>
using namespace std;


#ifndef NET_H  
#define NET_H 


class Net : public CObject
{

public:

	Net(CString& lastname, double previousbalance, double payments, double charges);

	~Net();

	void printdata();

	static int getcount();
	bool searchdata();

	void highestdata(CString& ln, double& pb, double& pay, double& charg, double& mebal);

	void printtotals();

	void addcolumns();
	void compute(Net* per, int x, int y);

	void copydatatogroup(Net* per);
	void getdata(CString& ln, double& pb, double& pay, double& charg, double& mebal);

	friend ostream& operator<< (ostream& cout, const Net* per);
	bool operator==(CString thename);

private:

	CString lastname;
	double previousbalance, payments, charges;
	double nbalance, financecharge, mebalance;

	static int row, col;
	static int count;

	CStringList lastnamelist;
	double number[6][4], totalarrays[4];




};
#endif


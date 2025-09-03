#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "Net.h"

int Net::count = 0;
int Net::row = 0;
int Net::col = 0;

Net::Net(CString& elname, double pbalance, double pay, double charg)
{
	lastname = elname;
	previousbalance = pbalance;
	payments = pay;
	charges = charg;

	count = count + 1;

}

ostream& operator<< (ostream& cout, const Net* per)
{

	cout << setw(20)
		<< per->lastname << setw(10)
		<< per->previousbalance << setw(10)
		<< per->payments << setw(10)
		<< per->charges << setw(10)
		<< per->nbalance << setw(10)
		<< per->financecharge << setw(10)
		<< per->mebalance << endl;

	return cout;
}


void Net::copydatatogroup(Net* per)
{
	lastnamelist.AddHead(per->lastname);
	

	col = 0;

	number[row][col] = per->previousbalance;
	number[row][++col] = per->payments;
	number[row][++col] = per->charges;

	row = row + 1;


}
Net::~Net()
{

}

int Net::getcount()
{
	return count;

}

void Net::printdata()
{
	POSITION pos = lastnamelist.GetTailPosition();
	CString lastname = lastnamelist.GetPrev(pos);
	int count = lastnamelist.GetCount();
	for (int i = 0; i < count; i++)
	{
		cout << setw(11) << lastname;
		for (int j = 0; j < 4; j++)
		{
			cout << setw(11) << number[i][j];
		}
		cout << endl;
		if (i < count - 1)
		{
			lastname = lastnamelist.GetPrev(pos);
		}
	}
}


void Net::printtotals()
{
	cout << endl;
	for (int z = 0; z < 4; z++)
	{
		if (z == 0)
			cout << setw(37) << totalarrays[z] << " ";
		else
		{
			cout << setw(11) << totalarrays[z] << " ";
		}
	}
}


void Net::highestdata(CString& ln, double& pb, double& pay, double& charg, double& mebal)
{
	double highest = 0;

	int i = 0;

	POSITION pos = lastnamelist.GetTailPosition();
	CString lastname = lastnamelist.GetPrev(pos);

	for (int j = 0; j < 6; j++)
	{
		for (i = 0; i < 4; i++)
		{
			if (i == 0)
				previousbalance = number[j][i];

			if (i == 1)
				payments = number[j][i];

			if (i == 2)
				charges = number[j][i];

			if (i == 3)
				mebalance = number[j][i];

		}

		if (i == 4)
		{

			if (mebalance > highest)
			{
				highest = mebalance;

				ln = lastname;
				pb = previousbalance;
				pay = payments;
				charg = charges;
				mebal = mebalance;

			}
		}


		if (j < count - 1)
		{
			lastname = lastnamelist.GetPrev(pos);
			
		}


	}

}



bool Net::operator==(CString thename)
{
	if (lastname == thename)
		return true;
	else
		return false;
}


void Net::getdata(CString& ln, double& pb, double& pay, double& charg, double& mebal)
{
	ln = lastname;
	pb = previousbalance;
	pay = payments;
	charg = charges;
	mebal = mebalance;
}



bool Net::searchdata()
{
	CString namesearch;

	char thename[20];

	cout << "\nEnter the  name to search ";
	cin >> thename;

	namesearch = (CString)thename;

	bool found = false;

	POSITION pos2 = lastnamelist.GetTailPosition();
	CString name = lastnamelist.GetPrev(pos2);

	int count = lastnamelist.GetCount();

	for (int i = 0; i < count; i++)
	{
		if (name == namesearch)
			found = true;

		if (i < count - 1)
		{
			name = lastnamelist.GetPrev(pos2);
		}
	}
	return found;
}



void Net::compute(Net* per, int rownum, int colnum)
{

	previousbalance = number[rownum][colnum];
	payments = number[rownum][++colnum];
	charges = number[rownum][++colnum];

	nbalance = previousbalance - payments + charges;
	financecharge = nbalance * .12;
	mebalance = nbalance + financecharge;

	number[rownum][++colnum] = nbalance;
	number[rownum][++colnum] = financecharge;
	number[rownum][++colnum] = mebalance;

	per->nbalance = nbalance;
	per->financecharge = financecharge;
	per->mebalance = mebalance;


}
void Net::addcolumns()
{
	double value = 0;
	double totalvalue = 0;

	for (int x = 0; x < 4; x++)
	{
		totalvalue = 0;

		for (int y = 0; y < 6; y++)
		{
			value = number[y][x];
			totalvalue += value;

		}
		totalarrays[x] = totalvalue;
	}
}

// NewAnnualSalaryOOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;

#include "afxwin.h"
#include <afxdb.h>
#include "Net.h"  

void printheading();
void printreport(Net* person[]);
void printhighest(Net* person[]);
void getsearch(Net* person[]);
void processgroup(Net* person[]);
void computeobjects(Net* person[]);

#pragma unmanaged

int main()
{
	system("cls");
	system("Color 70");

	CString Connection;
	CDatabase database;

	CString username;
	CString password;

	username = "ENLIGHTENER\\REMY\\redju";

	Connection = _T("Driver={SQL Server Native Client 11.0};Server=ENLIGHTENER\\REMY;Database=MonthEndBalanceSQL;Trusted_Connection=Yes;Uid=") + username + _T(";Pwd=") + password + _T(";");

	database.OpenEx(Connection, CDatabase::useCursorLib);

	const int size = 10;

	Net* person[size];

	int i = 0;

	CString query = "SELECT LastName, PreviousBalance, Payments, Charges FROM MonthendTable";

	CRecordset recordset(&database);
	CString temp, record;
	recordset.Open(CRecordset::forwardOnly, query, CRecordset::readOnly);

	CString lastname, spreviousbalance, spayments, scharges;
	CStringList lastnamelist;

	double previousbalance, payments, charges;
	double number[6][4];

	int col = 0, row = 0;

	while (!recordset.IsEOF())
	{
		record = _T("");
		register int len = recordset.GetODBCFieldCount();

		recordset.GetFieldValue("LastName", lastname);
		recordset.GetFieldValue("PreviousBalance", spreviousbalance);
		recordset.GetFieldValue("Payments", spayments);
		recordset.GetFieldValue("Charges", scharges);

		lastnamelist.AddHead(lastname);

		col = 0;

		previousbalance = atof(spreviousbalance);
		number[row][col] = previousbalance;
		payments = atof(spayments);
		number[row][++col] = payments;
		charges = atof(scharges);
		number[row][++col] = charges;

		row = row + 1;

		recordset.MoveNext();

	}


	processgroup(person);

	computeobjects(person);

	printheading();

	printreport(person);

	printhighest(person);

	getsearch(person);

	cout << endl << endl;

	cout << "Program end" << endl;
	cin.get();
	while (cin.get() != '\n');

	return 0;
}

void compute(double number[6][4])
{
	double previousbalance, payments, charges;
	double nbalance, financecharge, mebalance;
	int i = 0;
	for (int j = 0; j < 6; j++)
	{
		for (i = 0; i < 3; i++)
		{
			if (i == 0)
				previousbalance = number[j][i];
			if (i == 1)
				payments = number[j][i];
			if (i == 2)
				charges = number[j][i];
		}
		nbalance = previousbalance - payments + charges;
		financecharge = nbalance * .12;
		mebalance = nbalance + financecharge;
		number[j][i] = nbalance;
		number[j][+i] = financecharge;
		number[j][++i] = mebalance;
	}

}


void processgroup(Net* person[])
{
	int num = Net::getcount();
	Net* temp = person[0];

	for (int x = 0; x < num; x++)
	{
		temp->copydatatogroup(person[x]);
	}
}

void printheading()
{
	cout << endl << endl;
	cout << setw(40) << "Monthend Balance Report " << endl;
	cout << "Last Name" << setw(11) << "Previous Balance" << setw(11) << "Payments" << setw(11) << "Charges" << setw(11) << "New Balance " << setw(8) << "Finance Charge" << setw(11) << "Monthend Balance" << endl;
	cout << "Number  " << setw(11) << "Name     " << setw(11) << "Number" << setw(11) << "Salary" << setw(11) << "Increase" << setw(8) << "     " << setw(11) << "Salary" << endl;
	cout << endl;
}


void computeobjects(Net* person[])
{
	int col = 0;
	int num = Net::getcount();
	Net* object = person[0];

	for (int row = 0; row < num; row++)
	{
		object->compute(person[row], row, col);

	}
	person[0]->addcolumns();
}


void printreport(Net* person[])
{

	Net* object = person[0];

	person[0]->printdata();

	cout << endl << endl;

}


void printhighest(Net* person[])
{
	int num;
	cout << endl << endl;

	cout << "Highest using CStringList and multi-dimenional array" << endl;
	cout << "Highest Monthend Balance " << endl;

	CString lastname;
	double previousbalance, payments, charges;
	double nbalance, financecharge, mebalance;

	Net* object = person[0];

	object->highestdata(lastname, previousbalance, payments, charges, mebalance);

	cout << setw(20)
		<< lastname << setw(10)
		<< previousbalance << setw(10)
		<< payments << setw(10)
		<< charges << setw(10)
		<< mebalance << endl;



}


void getsearch(Net* person[])
{
	int num, index = 0;
	char name[20];

	CString namsearch;

	cout << "\nEnter the  name to search ";
	cin >> name;

	namsearch = (CString)name;
	bool found = false;

	num = Net::getcount();
	int x = 0;

	while ((found != true) && (x <= num))
	{
		if (*person[x] == namsearch)
		{
			cout << person[x];
			found = true;
		}

		x++;
	}

	if (found == false)
		cout << "Object not found " << endl;
}

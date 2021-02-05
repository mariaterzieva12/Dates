#include<iostream>
using namespace std;

class Date
{
public:
	Date()
	{
		setDay(1);
		setMonth(1);
		setYear(2000);
	}

	Date(int _day, int _month, int _year)
	{
		setYear(_year);
		setMonth(_month);
		if (isLeapYear(_year))
		{
			if (_day < 1 || _day > leap[month])
			{
				_day = 1;
				cout << "Invalid day, day set to 1" << endl;
			}
		}
		setDay(_day);
	}

	void setDay(int _day)
	{
		day = _day;
	}

	void setMonth(int _month)
	{
		if (_month < 1 && _month > 12)
		{
			_month = 1;
			cout << "Invalid month, the month has been set to January" << endl;
		}
		month = _month;
	}

	void setYear(int _year)
	{
		if (_year < 0)
		{
			_year = 1;
			cout << "Jesus wasn't born yet, year set to 1" << endl;
		}
		year = _year;
	}

	int getDay() const
	{
		return day;
	}

	int getMonth() const
	{
		return month;
	}

	int getYear() const
	{
		return year;
	}

	bool isLeapYear(int year)
	{
		if (year % 4 != 0)
		{
			return false;
		}
		else if (year % 4 == 0 && year % 100 != 0)
		{
			return true;
		}
		else if (year % 400 != 0)
		{
			return false;
		}
		return true;
	}

	void addDays(int n)
	{
		this->day += n;
		int* thisYear = nullptr;

		if (isLeapYear(year))
		{
			thisYear = leap;
		}
		else thisYear = notLeap;

		if (day > thisYear[month])
		{
			day -= thisYear[month];
			++month;
		}

		if (month > 12)
		{
			month = 1;
			++year;
		}
	}

	void removeDays(int n)
	{
		this->day -= n;
		int* thisYear = nullptr;

		if (isLeapYear(year))
		{
			thisYear = leap;
		}
		else thisYear = notLeap;

		if (day <= thisYear[month])
		{
			day += thisYear[month];
			--month;
		}

		if (month < 1)
		{
			month = 12;
			--year;
		}
	}

	int iWantItToBeXmas()
	{
		int daysToXmas = 0;
		int* thisYear = nullptr;

		if (isLeapYear(year))
		{
			thisYear = leap;
		}
		else thisYear = notLeap;

		for (int i = month; i < 13; ++i)
		{
			if (month == 12)
			{
				daysToXmas += (25 - day);
				break;
			}
			if (i == month)
			{
				daysToXmas += thisYear[month] - day;
			}
			else
				daysToXmas += thisYear[i];
		}

		if (daysToXmas <= 0)
		{
			daysToXmas += 365;
		}
		return daysToXmas;
	}

	void print() const
	{
		cout << day << ':' << month << ':' << year << endl;
	}

	bool isLaterDate(const Date& date) const
	{
		if (date.year > year)   //no else bcs we want the check to continue if both dates have the same year
			return true;
		if (date.year < year)
			return false;

		if (date.month > month)
			return true;
		if (date.month < month)
			return false;

		if (date.day > day)
			return true;

		return false;
	}

private:
	int day;
	int month;
	int year;
	int leap[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //Days in each month in the year
	int notLeap[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
};

Date diff(Date& d1, Date& d2)
{

	Date diff(d1);

	if (d1.isLaterDate(d2))
	{
		diff.removeDays(d1.getDay());
		diff.setMonth(d2.getMonth() - d1.getMonth());
		diff.setYear(d2.getYear() - d1.getYear());
	}

	diff.setDay(d1.getDay() - d2.getDay());
	diff.setMonth(d1.getMonth() - d2.getMonth());
	diff.setYear(d1.getYear() - d2.getYear());

	diff.print();
	return diff;
}

int main()
{
	Date d1(10, 12, 2016);
	d1.addDays(10);
	d1.print();

	cout << d1.iWantItToBeXmas();
	cout << endl;

	diff(d1, d1);


	system("pause");
	return 0;
}
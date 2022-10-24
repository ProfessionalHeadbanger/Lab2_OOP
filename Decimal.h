#ifndef DECIMAL_LAB2_OOP
#define DECIMAL_LAB2_OOP

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

class Decimal
{
private:
	long int *integer;
	unsigned short int *fraction;
	int scale_koef;
	bool minus;
	int Scale(int);
	void Reduce();
	void Merge(Decimal object, long int &left, long int &right, char oper);

public:
	Decimal();
	Decimal(std::string);
	Decimal(const Decimal& object);
	~Decimal();

	std::string toString();

	void Set_integer(long int);
	void Set_fraction(unsigned short int);
	void Set_scale(int);

	long int Get_integer();
	unsigned short int Get_fraction();
	int Get_scale();

	Decimal operator + (Decimal);
	Decimal operator - (Decimal);
	Decimal operator * (Decimal);
	Decimal operator / (Decimal);

	bool operator > (Decimal);
	bool operator < (Decimal);
	bool operator == (Decimal);

	friend std::ostream& operator << (std::ostream&, Decimal&);
	friend std::istream& operator >> (std::istream&, Decimal&);

	Decimal& operator = (const Decimal& object);
};

#endif
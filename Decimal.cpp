#include "Decimal.h"

int Decimal::Scale(int scale_koef)
{
	int scale = 1;
	for (int i = 0; i < scale_koef; i++)
	{
		scale *= 10;
	}
	return scale;
}

void Decimal::Reduce()
{
	while (*fraction % 10 == 0)
	{
		*fraction /= 10;
		scale_koef--;
	}
}

void Decimal::Merge(Decimal object, long int &left, long int &right, char oper)
{
	if (oper == '+' || oper == '-')
	{
		if (scale_koef > object.scale_koef)
		{
			if (minus)
			{
				left = -(abs(*integer * Scale(scale_koef)) + *fraction);
			}
			else
			{
				left = (abs(*integer * Scale(scale_koef)) + *fraction);
			}
			if (object.minus)
			{
				right = -(abs(*object.integer * Scale(scale_koef)) + *object.fraction * Scale(scale_koef - object.scale_koef));
			}
			else
			{
				right = (abs(*object.integer * Scale(scale_koef)) + *object.fraction * Scale(scale_koef - object.scale_koef));
			}
		}

		else if (object.scale_koef > scale_koef)
		{
			if (minus)
			{
				left = -abs((*integer * Scale(object.scale_koef) + *fraction * Scale(object.scale_koef - scale_koef)));
			}
			else
			{
				left = abs((*integer * Scale(object.scale_koef) + *fraction * Scale(object.scale_koef - scale_koef)));
			}
			if (object.minus)
			{
				right = -abs((*object.integer * Scale(object.scale_koef) + *object.fraction));
			}
			else
			{
				right = abs((*object.integer * Scale(object.scale_koef) + *object.fraction));
			}
		}
		else if (scale_koef == object.scale_koef)
		{
			if (minus)
			{
				left = -abs((*integer * Scale(object.scale_koef) + *fraction));
			}
			else
			{
				left = abs((*integer * Scale(object.scale_koef) + *fraction));
			}
			if (object.minus)
			{
				right = -abs((*object.integer * Scale(object.scale_koef) + *object.fraction));
			}
			else
			{
				right = abs((*object.integer * Scale(object.scale_koef) + *object.fraction));
			}
		}
	}
	else if (oper == '*' || oper == '/')
	{
		if (minus)
		{
			left = -(abs(*integer * Scale(scale_koef)) + *fraction);
		}
		else
		{
			left = (abs(*integer * Scale(scale_koef)) + *fraction);
		}
		if (object.minus)
		{
			right = -abs((*object.integer * Scale(object.scale_koef) + *object.fraction));
		}
		else
		{
			right = abs((*object.integer * Scale(object.scale_koef) + *object.fraction));
		}
	}
}

Decimal::Decimal()
{
	integer = new long int;
	*integer = 0; 
	fraction = new unsigned short int;
	*fraction = 0;
	scale_koef = 1;
	minus = false;
}

Decimal::Decimal(std::string decimal)
{
	const char SEP = '.';
	std::istringstream ist(decimal);
	std::string left;
	std::string right;
	std::getline(ist, left, SEP);
	std::getline(ist, right, SEP);

	integer = new long int;
	if (left[0] == '-')
	{
		minus = true;
	}
	*integer = std::stol(left);

	fraction = new unsigned short int;
	*fraction = std::stoul(right);
	scale_koef = right.size();
	Reduce();
}

Decimal::Decimal(const Decimal& object)
{
	this->integer = new long int;
	*this->integer = *object.integer;
	this->fraction = new unsigned short int;
	*this->fraction = *object.fraction;
	this->scale_koef = object.scale_koef;
	this->minus = object.minus;
}

Decimal::~Decimal()
{
	delete integer;
	delete fraction;
}

std::string Decimal::toString()
{
	std::stringstream stream;
	if (minus && *integer == 0)
	{
		stream << '-';
	}
	stream << *integer << '.';
	std::string fr = std::to_string(*fraction);
	int fr_size = fr.size();
	while (scale_koef > fr_size)
	{
		fr = '0' + fr;
		fr_size++;
	}
	stream << fr;
	std::string str;
	stream >> str;
	return str;
}

void Decimal::Set_integer(long int _integer)
{
	*integer = _integer;
}

void Decimal::Set_fraction(unsigned short int _fraction)
{
	*fraction = _fraction;
}

void Decimal::Set_scale(int _scale)
{
	scale_koef = _scale;
}

long int Decimal::Get_integer()
{
	return *integer;
}

unsigned short int Decimal::Get_fraction()
{
	return *fraction;
}

int Decimal::Get_scale()
{
	return scale_koef;
}

Decimal Decimal::operator+(Decimal object)
{
	Decimal temp;
	temp.scale_koef = std::max(scale_koef, object.scale_koef);
	long int left, right;
	Merge(object, left, right, '+');
	*temp.integer = left + right;
	if (*temp.integer < 0)
	{
		temp.minus = true;
	}
	else
	{
		temp.minus = false;
	}
	*temp.fraction = abs(*temp.integer) % Scale(temp.scale_koef);
	temp.Reduce();
	*temp.integer /= Scale(temp.scale_koef);
	return temp;
}

Decimal Decimal::operator-(Decimal object)
{
	Decimal temp;
	temp.scale_koef = std::max(scale_koef, object.scale_koef);
	long int left, right;
	Merge(object, left, right, '-');
	*temp.integer = left - right;
	if (*temp.integer < 0)
	{
		temp.minus = true;
	}
	else
	{
		temp.minus = false;
	}
	*temp.fraction = abs(*temp.integer) % Scale(temp.scale_koef);
	temp.Reduce();
	*temp.integer /= Scale(temp.scale_koef);
	return temp;
}

Decimal Decimal::operator*(Decimal object)
{
	Decimal temp;
	long int left, right;
	Merge(object, left, right, '*');
	*temp.integer = left * right;
	if (*temp.integer < 0)
	{
		temp.minus = true;
	}
	else
	{
		temp.minus = false;
	}
	temp.scale_koef = scale_koef + object.scale_koef;
	long int fraction_buffer = abs(*temp.integer) % Scale(temp.scale_koef);
	int scale_koef_buffer = temp.scale_koef;
	if (temp.scale_koef > 4)
	{
		temp.scale_koef = 4;
	}
	*temp.fraction = fraction_buffer / Scale(scale_koef_buffer - temp.scale_koef);
	*temp.integer /= Scale(scale_koef_buffer);
	temp.Reduce();
	return temp;
}

Decimal Decimal::operator/(Decimal object)
{
	Decimal temp;
	long int left, right;
	Merge(object, left, right, '/');
	*temp.integer = left / right;
	if (*temp.integer < 0)
	{
		temp.minus = true;
	}
	else
	{
		temp.minus = false;
	}
	temp.scale_koef = scale_koef + object.scale_koef;
	long int fraction_buffer = abs(*temp.integer) % Scale(temp.scale_koef);
	int scale_koef_buffer = temp.scale_koef;
	if (temp.scale_koef > 4)
	{
		temp.scale_koef = 4;
	}
	*temp.fraction = fraction_buffer / Scale(scale_koef_buffer - temp.scale_koef);
	*temp.integer /= Scale(scale_koef_buffer);
	temp.Reduce();
	return temp;
}

bool Decimal::operator>(Decimal object)
{
	long int left, right;
	Merge(object, left, right, '+');
	if (left > right)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Decimal::operator<(Decimal object)
{
	long int left, right;
	Merge(object, left, right, '+');
	if (left < right)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Decimal::operator==(Decimal object)
{
	long int left, right;
	Merge(object, left, right, '+');
	if (left == right)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::ostream& operator << (std::ostream& stream, Decimal& object)
{
	stream << object.toString();
	return stream;
}

std::istream& operator>>(std::istream& stream, Decimal& object)
{
	const char SEP = '.';
	std::string input;
	stream >> input;
	std::stringstream ss(input);
	std::string left;
	std::string right;
	std::getline(ss, left, SEP);
	std::getline(ss, right, SEP);

	if (left[0] == '-')
	{
		object.minus = true;
	}
	*object.integer = std::stol(left);

	*object.fraction = std::stoul(right);
	object.scale_koef = right.size();
	object.Reduce();
	return stream;
}

Decimal& Decimal::operator=(const Decimal &object)
{
	if (this == &object)
	{
		return *this;
	}

	*integer = *object.integer;
	*fraction = *object.fraction;
	minus = object.minus;
	scale_koef = object.scale_koef;

	return *this;
}
/*Jason Avina, cs100b, 4/15/2019
Professor Dave Harden, Assignment 11

The Fraction class can be used to represent mathematical fractions, in the
form of a numerator divided by some denominator.



Fraction(int = 0, int = 1);
postcondition: calling object has the value of the parameters passed to it

Fraction();
postcondition: calling object has the value of 0;



friend std::ostream& operator<<(std::ostream& out, const Fraction& right);
	preconditions: calling object is an ostream object and
				parameter is a Fraction object
	postconditions: the parameter fraction object is output to calling object

friend std::istream& operator>>(std::istream& in, Fraction& right);
	preconditions: calling object is an istream object and
					parameter is a Fraction object
	postconditions: the Fraction object is input to the calling object



friend bool operator<(const Fraction& left, const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: returns true if calling object represents a fraction
					that is lesser in value than the parameter object

friend bool operator<=(const Fraction& left, const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: returns true if calling object represents a fraction
					that is less than or equal in value to the parameter object

friend bool operator>(const Fraction& left, const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: returns true if calling object represents a fraction
					that is greater in value than the parameter object

friend bool operator>=(const Fraction& left, const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: returns true if calling object represents a fraction
					that is greater than or equal in value to the parameter object

friend bool operator==(const Fraction& left, const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: returns true if calling object represents a fraction
					that is equal in value to the parameter object

friend bool operator!=(const Fraction& left, const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: returns true if calling object represents a fraction
					that is not equal in value to the parameter object



friend Fraction operator+(const Fraction& left, const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: the sum of the calling object and parameter is returned

friend Fraction operator-(const Fraction& left, const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: the difference of the calling object and parameter is returned

friend Fraction operator*(const Fraction& left, const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: the product of the calling object and parameter is returned

friend Fraction operator/(const Fraction& left, const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: the quotient of the calling object and parameter is returned



Fraction operator+=(const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: the sum of the calling object and parameter is returned

Fraction operator-=(const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: the difference of the calling object and parameter is returned

Fraction operator*=(const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: the product of the calling object and parameter is returned

Fraction operator/=(const Fraction& right);
	preconditions: calling object and parameter are both Fraction objects
	postconditions: the quotient of the calling object and parameter is returned



Fraction operator++();
	preconditions: calling object is a Fraction object
	postconditions: the calling object's fraction value is incremented by one

Fraction operator++(int);
	preconditions: calling object is a Fraction and the parameter is an integer
	postconditions: the calling object's fraction value is incremented by the parameter

Fraction operator--();
	preconditions: calling object is a Fraction object
	postconditions: the calling object's fraction value is decremented by one

Fraction operator--(int);
	preconditions: calling object is a Fraction and the parameter is an integer
	postconditions: the calling object's fraction value is decremented by the parameter

*/

#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

namespace cs_fraction {

	Fraction::Fraction(int num, int den)
	{
		assert(den != 0);
		numerator = num;
		denominator = den;
		simplify();
	}




	/*This function simplifies the a fraction objects value
to the lowest terms of the fraction it represents. E.g. 4/6 becomes 2/3.
It simplifies fractions by setting the GCF(greatest common factor)
to be the lower of the numerator and denominator's absolute value.
If they are equal the object value is set to one. If there is a
lower value then that value is used as a divisor for both the
numerator and denominator in a for loop until the remainder is zero
at which point the loop stops. The quotients of these divisions are
stored as the new, reduced numerator and denominator. It also ensures
the denominator is never negative and that the denominator is never
equal to zero.*/

	void Fraction::simplify()
	{
		int GCF = 0;
		if (abs(numerator) < abs(denominator)) {
			GCF = abs(numerator);
		}
		else if (abs(numerator) > abs(denominator)) {
			GCF = abs(denominator);
		}
		else if (abs(numerator) == abs(denominator)) {
			numerator = 1;
			denominator = 1;
		}
		for (int i = 0; GCF > i; --GCF) {
			if ((numerator % GCF == 0) && (denominator % GCF == 0)) {
				numerator = numerator / GCF;
				denominator = denominator / GCF;
			}
		}
		if (denominator < 0) {
			numerator *= -1;
			denominator *= -1;
		}
		if (numerator == 0) {
			denominator = 1;
		}
	}






/*This function overloads the stream insertion operator so
that it can output an entire fraction object in the proper
mathematical form of a fraction, which is:
"numerator / denominator". If both numerator and denominator
are equal it outputs the value of 1.*/

	ostream& operator<<(ostream& out, const Fraction& right)
	{
		int wholePart;
		Fraction fractionalPart;
		if (abs(right.numerator) < abs(right.denominator)) {
			out << right.numerator;
			if (right.numerator != 0)
				cout << "/" << right.denominator;
		}
		else if (abs(right.numerator) > right.denominator) {
			wholePart = (right.numerator / right.denominator);
			fractionalPart.numerator = (right.numerator % right.denominator);
			fractionalPart.denominator = right.denominator;
			out << wholePart;
			if (fractionalPart.numerator != 0) {
				cout << "+" << abs(fractionalPart.numerator)
					<< "/" << fractionalPart.denominator;
			}
		}
		else if (abs(right.numerator) == abs(right.denominator))
			cout << (right.numerator / right.denominator);
		return out;
	}





/*This function overloads the stream extraction operator. It inputs
the calling object data into the calling object, and stores that data in
fractional form. The function checks for whole numbers mixed numbers	
and fractions. If the number is a whole number the input data is stored
in the parameter's denominator value. If they input data is a fraction
then it is stored in the denominator and numerator. If the input data
is a mixed number then it is turned into an imporper fraction and stored
that way in the parameter. At the end of the function the parameter is
simplified.*/

	istream& operator>>(istream& in, Fraction& right)
	{
		int temp, mixWholeTemp, mixNumerTemp, mixDenomTemp;
		in >> temp;

		if (in.peek() == '+') {
			mixWholeTemp = temp;
			in.ignore();
			in >> mixNumerTemp;
			in.ignore();
			in >> mixDenomTemp;
			right.numerator = abs(mixWholeTemp * mixDenomTemp) + mixNumerTemp;
			if (mixWholeTemp < 0)
				right.numerator *= -1;
			right.denominator = mixDenomTemp;
		}

		else if (in.peek() == '/') {
			right.numerator = temp;
			in.ignore();
			in >> temp;
			right.denominator = temp;
		}

		else {
			right.numerator = temp;
		}

		right.simplify();
		return in;
	}






	bool operator<(const Fraction& left, const Fraction& right)
	{
		int convLeftNumer = 0, convRightNumer = 0;
		convLeftNumer = left.numerator * right.denominator;
		convRightNumer = right.numerator * left.denominator;
		return (convLeftNumer < convRightNumer);
	}






	bool operator<=(const Fraction& left, const Fraction& right)
	{
		int convLeftNumer = 0, convRightNumer = 0;
		convLeftNumer = left.numerator * right.denominator;
		convRightNumer = right.numerator * left.denominator;
		return (convLeftNumer <= convRightNumer);
	}
	bool operator>(const Fraction& left, const Fraction& right)
	{
		int convLeftNumer = 0, convRightNumer = 0;
		convLeftNumer = left.numerator * right.denominator;
		convRightNumer = right.numerator * left.denominator;
		return (convLeftNumer > convRightNumer);
	}






	bool operator>=(const Fraction& left, const Fraction& right)
	{
		int convLeftNumer = 0, convRightNumer = 0;
		convLeftNumer = left.numerator * right.denominator;
		convRightNumer = right.numerator * left.denominator;
		return (convLeftNumer >= convRightNumer);
	}






	bool operator==(const Fraction& left, const Fraction& right)
	{
		int convLeftNumer = 0, convRightNumer = 0;
		convLeftNumer = left.numerator * right.denominator;
		convRightNumer = right.numerator * left.denominator;
		return (convLeftNumer == convRightNumer);
	}






	bool operator!=(const Fraction& left, const Fraction& right)
	{
		int convLeftNumer = 0, convRightNumer = 0;
		convLeftNumer = left.numerator * right.denominator;
		convRightNumer = right.numerator * left.denominator;
		return (convLeftNumer != convRightNumer);
	}






	Fraction operator+(const Fraction& left,
		const Fraction& right)
	{
		Fraction answer;
		answer.numerator = (left.numerator * right.denominator)
			+ (right.numerator * left.denominator);
		answer.denominator = left.denominator * right.denominator;
		answer.simplify();
		return answer;
	}





	Fraction operator-(const Fraction& left,
		const Fraction& right)
	{
		Fraction answer;
		answer.numerator = (left.numerator * right.denominator)
			- (right.numerator * left.denominator);
		answer.denominator = left.denominator * right.denominator;
		answer.simplify();
		return answer;
	}





	Fraction operator*(const Fraction& left,
		const Fraction& right)
	{
		Fraction answer;
		answer.numerator = left.numerator * right.numerator;
		answer.denominator = left.denominator * right.denominator;
		answer.simplify();
		return answer;
	}





	Fraction operator/(const Fraction& left,
		const Fraction& right)
	{
		Fraction answer;
		answer.numerator = left.numerator * right.denominator;
		answer.denominator = left.denominator * right.numerator;
		answer.simplify();
		return answer;
	}





	Fraction Fraction::operator+=(const Fraction& right)
	{
		*this = *this + right;
		simplify();
		return *this;
	}





	Fraction Fraction::operator-=(const Fraction& right)
	{
		*this = *this - right;
		simplify();
		return *this;
	}





	Fraction Fraction::operator*=(const Fraction& right)
	{
		*this = *this * right;
		simplify();
		return *this;
	}





	Fraction Fraction::operator/=(const Fraction& right)
	{
		*this = *this / right;
		simplify();
		return *this;
	}





	Fraction Fraction::operator++()
	{
		*this = *this + 1;
		simplify();
		return *this;
	}





	Fraction Fraction::operator++(int)
	{
		Fraction temp(numerator, denominator);
		*this = *this + 1;
		simplify();
		return temp;
	}





	Fraction Fraction::operator--()
	{
		*this = *this - 1;
		simplify();
		return *this;
	}





	Fraction Fraction::operator--(int)
	{
		Fraction temp(numerator, denominator);
		*this = *this - 1;
		simplify();
		return temp;
	}
}

#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>



namespace cs_fraction {

	class Fraction
	{
	public:
		Fraction(int = 0, int = 1);

		friend std::ostream& operator<<(std::ostream& out,
			const Fraction& right);
		friend std::istream& operator>>(std::istream& in,
			Fraction& right);

		friend bool operator<(const Fraction& left,
			const Fraction& right);
		friend bool operator<=(const Fraction& left,
			const Fraction& right);
		friend bool operator>(const Fraction& left,
			const Fraction& right);
		friend bool operator>=(const Fraction& left,
			const Fraction& right);
		friend bool operator==(const Fraction& left,
			const Fraction& right);
		friend bool operator!=(const Fraction& left,
			const Fraction& right);

		friend Fraction operator+(const Fraction& left,
			const Fraction& right);
		friend Fraction operator-(const Fraction& left,
			const Fraction& right);
		friend Fraction operator*(const Fraction& left,
			const Fraction& right);
		friend Fraction operator/(const Fraction& left,
			const Fraction& right);

		Fraction operator+=(const Fraction& right);
		Fraction operator-=(const Fraction& right);
		Fraction operator*=(const Fraction& right);
		Fraction operator/=(const Fraction& right);

		Fraction operator++();
		Fraction operator++(int);
		Fraction operator--();
		Fraction operator--(int);

	private:
		int numerator;
		int denominator;
		void simplify();
	};
}



#endif // !
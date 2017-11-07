#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <list>
#include <exception>
#include <iostream>
#include <math.h>

using namespace std;

class Complex{
protected:
	double real_;
	double imag_;

public:
	// -----------------ctors--------------------------//
	Complex() {};
	Complex(double real);
	Complex(double real, double imag);

	// ------------operator overloading --------------//
	// a+b
	Complex operator+(const Complex& rhs) const;

	
	// a*b
	Complex operator*(const Complex& rhs) const;



	// other operators
	const Complex& operator=(const Complex& rhs);
	const bool operator==(const Complex& rhs) const;
	const bool operator!=(const Complex& rhs) const;
	const bool operator<(const Complex& rhs) const;

	friend ostream& operator<<(ostream& ro, const Complex& complex);

	// ------------additional functions----------------//
	double get_real() const;
	double get_imag() const;
	double abs() const;

};

Complex abs(Complex& c);



#endif
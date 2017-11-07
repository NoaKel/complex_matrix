#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "complex.h"

using std::cout;
using std::endl;

/* *****************************************************
Function: Complex Ctor only real number
Abstract: Ctor
Parameters: N/A
Return Value: N/A
***************************************************** */
Complex::Complex(double real) : real_(real), imag_(0.0) {}

/* *****************************************************
Function: Complex Ctor real and imag given
Abstract: Ctor
Parameters: N/A
Return Value: N/A
***************************************************** */
Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}


/* *****************************************************
Function: operator+ memebr
Abstract: Add two complex numbers
Parameters: rhs - number to add
Return Value: Addition of two complex numbers
***************************************************** */
Complex Complex::operator+(const Complex& rhs) const
{
	return Complex(real_ + rhs.get_real(), imag_ + rhs.get_imag());
}

/* *****************************************************
Function: operator* member
Abstract: Multiplies two complex numbers
Parameters: rhs - number to multiply
Return Value: Multiplicaation of two complex numbers
***************************************************** */
Complex Complex::operator*(const Complex& rhs) const
{

	double new_real = (real_ * rhs.get_real()) - (imag_ * rhs.get_imag());
	double new_imag = (real_ * rhs.get_imag()) + (imag_ * rhs.get_real());
	return Complex(new_real, new_imag);
}


/* *****************************************************
Function: operator=
Abstract: Sets a complex numbers
Parameters: rhs - number to set
Return Value: Complex number
***************************************************** */
const Complex& Complex::operator=(const Complex& rhs)
{
	real_ = rhs.get_real();
	imag_ = rhs.get_imag();

	return *this;

}

/* *****************************************************
Function: operator==
Abstract: Compares to numbers
Parameters: rhs - number to compare
Return Value: true - if equal false - if not
***************************************************** */
const bool Complex::operator==(const Complex& rhs) const
{
	if ((real_ == rhs.get_real()) && (imag_ == rhs.get_imag()))
		return true;
	else
		return false;
}

/* *****************************************************
Function: operator==
Abstract: Compares to numbers
Parameters: rhs - number to compare
Return Value: true - if not equal false - if equal
***************************************************** */
const bool Complex::operator!=(const Complex& rhs) const
{
	if ((real_ != rhs.get_real()) || (imag_ != rhs.get_imag()))
		return true;
	else
		return false;
}

/* *****************************************************
Function: operator<<
Abstract: Prints complex number
Parameters:
ro - ostream
rhs - number to compare
Return Value: ostream
***************************************************** */
ostream& operator<<(ostream& ro, const Complex& complex)
{
	ro << complex.get_real() << " + " << complex.get_imag() << "i";
	return ro;
}

/* *****************************************************
Function: operator<
Abstract: compares two complex numbers
Parameters: rhs - complex number to compare
Return Value: true/false
***************************************************** */
const bool Complex::operator<(const Complex & rhs) const
{
	if (abs()<rhs.abs())
		return true;
	return false;
}



// -------------------additional functions--------------------------//
/* *****************************************************
Function: get_real()
Abstract: returns real part of complex number
Parameters: N/A
Return Value: real part
***************************************************** */
double Complex::get_real() const
{
	return real_;
}

/* *****************************************************
Function: get_imag()
Abstract: returns imaginary part of complex number
Parameters: N/A
Return Value: imaginary part
***************************************************** */
double Complex::get_imag() const
{
	return imag_;
}

/* *****************************************************
Function: norm_squared()
Abstract: returns sqrt(real^2+imag^2)
Parameters: N/A
Return Value: sqrt(real^2+imag^2)
***************************************************** */
double Complex::abs() const
{
	return (sqrt(real_*real_ + imag_*imag_));
}

/* *****************************************************
Function: norm_squared()
Abstract: returns sqrt(real^2+imag^2)
Parameters: N/A
Return Value: sqrt(real^2+imag^2)
***************************************************** */
Complex abs(Complex& c)
{
	return (sqrt(c.get_real()*c.get_real() + c.get_imag()*c.get_imag()));
}
















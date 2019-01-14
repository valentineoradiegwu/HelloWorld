#include "complex.h"
namespace Val
{
	Complex operator+ (Complex lhs, const Complex& rhs)
	{
		lhs += rhs;
		return lhs;
	}
	Complex operator- (Complex lhs, const Complex& rhs)
	{
		lhs -= rhs;
		return lhs;
	}
	Complex operator+ (Complex rhs)
	{
		return rhs;
	}
	Complex operator- (const Complex& rhs)
	{
		return{ -rhs.real(), -rhs.imag() };
	}
	bool operator== (const Complex& lhs, const Complex& rhs)
	{
		return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
	}
	bool operator!= (const Complex& lhs, const Complex& rhs)
	{
		return !(lhs == rhs);
	}
}
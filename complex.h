#pragma once
/*
1. A default ctor with 2 default params will knock up 3 constructors in one
2. operator+=
3. operator-=
4. Binary operator+ and operator- which have to global type functions
5. Unary operator+ and operator- which have to global type functions
6. equality operators - which should be global to ensure implicit conversion on operands.

*/
namespace Val
{
	class Complex
	{
		double m_re;
		double m_im;
	public:
		Complex(double re = 0.0, double im = 0.0)
			:m_re{ re },
			m_im{ im }
		{}
		double real() const { return m_re; }
		double imag() const { return m_im; }
		Complex& operator+=(const Complex& rhs)
		{
			m_re += rhs.m_re;
			m_im += rhs.m_im;
			return *this;
		}
		Complex& operator-=(const Complex& rhs)
		{
			m_re -= rhs.m_re;
			m_im -= rhs.m_im;
			return *this;
		}
	};
	Complex operator+ (Complex lhs, const Complex& rhs);
	Complex operator- (Complex lhs, const Complex& rhs);
	Complex operator+ (Complex rhs);
	Complex operator- (const Complex& rhs);
	bool operator== (const Complex& lhs, const Complex& rhs);
	bool operator!= (const Complex& lhs, const Complex& rhs);
}
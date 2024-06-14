#include <cmath>

class Complex
{
public:
    double real;      // Real part of the complex number
    double imaginary; // Imaginary part of the complex number

    /*
     * @brief   Constructor for Complex class.
     * @param   Real        Real part of the complex number (default: 0).
     * @param   Imaginary   Imaginary part of the complex number (default: 0).
     */
    Complex(double Real = 0, double Imaginary = 0)
        : real(Real), imaginary(Imaginary) {}

    /*
     * @brief   Overloaded addition operator for complex numbers.
     * @param   a   Complex number to add.
     * @return  Result of addition operation.
     */
    Complex operator+(const Complex &a)
    {
        return Complex(real + a.real, imaginary + a.imaginary);
    }

    /*
     * @brief   Overloaded multiplication operator for complex numbers.
     * @param   a   Complex number to multiply.
     * @return  Result of multiplication operation.
     */
    Complex operator*(const Complex &a)
    {
        return Complex(real * a.real - imaginary * a.imaginary, imaginary * a.real + a.imaginary * real);
    }

    /*
     * @brief   Calculate absolute value (modulus) of the complex number.
     * @return  Absolute value (modulus) of the complex number.
     */
    double abs()
    {
        return sqrt(real * real + imaginary * imaginary);
    }
};
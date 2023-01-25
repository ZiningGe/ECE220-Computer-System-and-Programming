#include "ComplexNumber.h"
#include "helper.h"
//#include <math.h>
// partner ziningg2, mingzex2

ComplexNumber::ComplexNumber()
{
    real_component = 0.0; // set to 0
    imaginary_component = 0.0; //set to 0
    number_type = 2;
    magnitude = 0.0;
    phase = 0.0;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
    number_type = 2;
    magnitude = sqrt(rval_real_component * rval_real_component + rval_imaginary_component * rval_imaginary_component);
    phase = calculate_phase(rval_real_component, rval_imaginary_component);
}

ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
    real_component = other.real_component;
    imaginary_component = other.imaginary_component;
    number_type = 2;
    magnitude = other.magnitude;
    phase = other.phase;
}

void ComplexNumber::set_real_component (double rval)
{
    real_component = rval;
    magnitude = sqrt(real_component * real_component + imaginary_component * imaginary_component);
    phase = calculate_phase(real_component, imaginary_component);
}

double ComplexNumber::get_real_component() const
{
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    imaginary_component = rval;
    magnitude = sqrt(real_component * real_component + imaginary_component * imaginary_component);
    phase = calculate_phase(real_component, imaginary_component);
}

double ComplexNumber::get_imaginary_component() const
{
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    return magnitude;
}

double ComplexNumber::get_phase() const{
    return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber(a + c, b + d);
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber(a - c, b - d);
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber(a * c - b * d, (a + b) * (c + d) - a * c - b * d);
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    double d = arg.get_imaginary_component();
    return ComplexNumber((a * c + b * d) / (c * c + d * d), (b * c - a * d) / (c * c + d * d));
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
	return ComplexNumber(real_component + arg.get_real_component(), imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
	return ComplexNumber(real_component - arg.get_real_component(), imaginary_component);
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
	return ComplexNumber(a * c, b * c);
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_real_component();
    return ComplexNumber(a / c, b / c);
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
	return ComplexNumber(real_component, imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    return ComplexNumber(real_component, imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_imaginary_component();
    return ComplexNumber(-1 * c * b, a * c);
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    double a = real_component;
    double b = imaginary_component;
    double c = arg.get_imaginary_component();
	return ComplexNumber(b / c, -1 * a / c);
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}


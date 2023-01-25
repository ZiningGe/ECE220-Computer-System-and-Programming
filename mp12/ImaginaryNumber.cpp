#include "ImaginaryNumber.h"
#include "helper.h"
// partner: ziningg2, mingzex2
    ImaginaryNumber::ImaginaryNumber()
    {
        number_type = IMAGINARY;
        magnitude = 0;
        phase = calculate_phase(0, 0);
        imaginary_component = 0;
    }
    
    ImaginaryNumber::ImaginaryNumber(double rval)
    {
        number_type = IMAGINARY;
        magnitude = sqrt(pow(rval,2));
        phase = calculate_phase(0, rval);
        imaginary_component = rval;
    }
    
    ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other )
    {
        number_type = other.number_type;
        magnitude = other.magnitude;
        phase = other.phase;
        imaginary_component = other.imaginary_component;
    }
    
    void ImaginaryNumber::set_imaginary_component (double rval)
    {
        imaginary_component = rval;
        magnitude = sqrt(pow(rval,2));
        phase = calculate_phase(0, rval);
    }
    
    double ImaginaryNumber::get_imaginary_component() const
    {
        return imaginary_component;
    }
    
    //Getter function for magnitude
    double ImaginaryNumber::get_magnitude() const{
        return magnitude;
    }
    
    //Getter function for phase
    double ImaginaryNumber::get_phase() const{
        return phase;
    }
    
    //Operator Overload
    ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
    {
        return ImaginaryNumber(imaginary_component + arg.get_imaginary_component());
    }
    
    ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
    {
        return ImaginaryNumber(imaginary_component - arg.get_imaginary_component());
    }
    
    RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
    {
        return RealNumber(-imaginary_component * arg.get_imaginary_component());
    }
    
    RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
    {
        return RealNumber(imaginary_component / arg.get_imaginary_component());
    }
    
    ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
    {
        return ComplexNumber(arg.get_real_component(), imaginary_component);
    }
    
    ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
    {
        return ComplexNumber(-arg.get_real_component(), imaginary_component);
    }
    
    ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
    {
        return ImaginaryNumber(arg.get_real_component() * imaginary_component);
    }
    
    ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
    {
        return ImaginaryNumber(imaginary_component / arg.get_real_component());
    }
    
    ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
    {
        return ComplexNumber(arg.get_real_component(), arg.get_imaginary_component() + imaginary_component);
    }
    
    ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
    {
        return ComplexNumber(-arg.get_real_component(), -arg.get_imaginary_component() + imaginary_component);
    }
    
    ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
    {
        return ComplexNumber(-imaginary_component * arg.get_imaginary_component(), imaginary_component * arg.get_real_component());
    }
    
    ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
    {
        return ComplexNumber((imaginary_component*arg.get_imaginary_component())/(pow(arg.get_real_component(),2)+pow(arg.get_imaginary_component(),2)), (imaginary_component*arg.get_real_component())/(pow(arg.get_real_component(),2)+pow(arg.get_imaginary_component(),2)));
    }
    
    string ImaginaryNumber::to_String(){
        /* Do not modify */
        stringstream my_output;
        my_output << std::setprecision(3) << imaginary_component << 'i';
        return my_output.str();
    }



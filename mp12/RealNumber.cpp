#include "RealNumber.h"
#include "helper.h"
//#include "math.h"
//partner: ziningg2. mingzex2 
    RealNumber::RealNumber()
    {
        // Empty Constructor: Initialize the number to 0
        number_type = REAL;
        magnitude = 0;
        phase = calculate_phase(0, 0);
        real_component = 0;
    }
    
    RealNumber::RealNumber(double rval)
    {
        // Constructor: Initialize the number to rval
        number_type = REAL;
        magnitude = sqrt(pow(rval,2));
        phase = calculate_phase(rval, 0);
        real_component = rval;
    }
    
    RealNumber::RealNumber( const RealNumber& other )
    {
        // Copy constructor: Initialize the number to the real number given at RealNumber
        number_type = other.number_type;
        magnitude = other.magnitude;
        phase = other.phase;
        real_component = other.real_component;
    }
    
    void RealNumber::set_real_component (double rval)
    {
        // Set the real component to rval
        real_component = rval;
        magnitude = sqrt(pow(rval,2));
        phase = calculate_phase(rval, 0);
        
    }
    
    double RealNumber::get_real_component() const
    {
        // Get the real_component of the number
        return real_component;
    }
    
    double RealNumber::get_magnitude() const{
        // Get the magnitude of the number
        return magnitude;
    }
    
    double RealNumber::get_phase() const{
        // Get the phase of the number
        return phase;
    }
    
    RealNumber RealNumber::operator + (const RealNumber& arg)
    {
    double sum = real_component + arg.get_real_component();
        return RealNumber(sum);
    }
    
    RealNumber RealNumber::operator - (const RealNumber& arg)
    {
        double diff = real_component - arg.get_real_component();
        return RealNumber(diff);
    }
    
    RealNumber RealNumber::operator * (const RealNumber& arg)
    {
        double mul = real_component * arg.get_real_component();
        return RealNumber(mul);
    }
    
    RealNumber RealNumber::operator / (const RealNumber& arg)
    {
        double div = real_component / arg.get_real_component();
        return RealNumber(div);
    }
    
    ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
        return ComplexNumber(real_component, arg.get_imaginary_component());
    }
    
    ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
        return ComplexNumber(real_component, arg.get_imaginary_component());
    }
    
    ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    return ImaginaryNumber(real_component*arg.get_imaginary_component());
    }
    
    ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
        return ImaginaryNumber((-real_component*arg.get_imaginary_component())/pow(arg.get_imaginary_component(),2));
    }
    
    ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
        return ComplexNumber(real_component + arg.get_real_component(), arg.get_imaginary_component());
    }
    
    ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
        return ComplexNumber(real_component - arg.get_real_component(), arg.get_imaginary_component());
    }
    
    ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
        return ComplexNumber(real_component * arg.get_real_component(), real_component * arg.get_imaginary_component());
    }
    
    ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
        /* Your code here */
        return ComplexNumber((real_component*arg.get_real_component())/(pow(arg.get_real_component(),2)+pow(arg.get_imaginary_component(),2)),(-real_component*arg.get_imaginary_component())/(pow(arg.get_real_component(),2)+pow(arg.get_imaginary_component(),2)));
    }
    
    string RealNumber::to_String(){
        /* Do not modify */
        stringstream my_output;
        my_output << std::setprecision(3) << real_component;
        return my_output.str();
    }



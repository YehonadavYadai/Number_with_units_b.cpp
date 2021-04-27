//
// Created by yehonadav2 on 18/04/2021.
//
#include <iostream>

#include <string>
using namespace std;

namespace ariel {
    class NumberWithUnits{

    private:
        double value;
        string unit;

    public:
        NumberWithUnits(double value,const string &unit);
      

        static void read_units(ifstream& units_file);
        friend int compare(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend ostream& operator<<(ostream& out, const NumberWithUnits& a);
        friend istream& operator>>(istream& s, NumberWithUnits& n);
        
        friend NumberWithUnits operator+(const NumberWithUnits& n1,const NumberWithUnits& n2);
        friend const NumberWithUnits& operator+(const NumberWithUnits& n1);
        NumberWithUnits& operator+=(const NumberWithUnits& n);
        friend NumberWithUnits operator-(const NumberWithUnits& n1,const NumberWithUnits& n2);
        friend NumberWithUnits operator-(const NumberWithUnits& n);
        NumberWithUnits& operator-=(const NumberWithUnits& n);
        friend NumberWithUnits& operator++(NumberWithUnits& n);
        friend NumberWithUnits operator++(NumberWithUnits& n,int a);
        friend NumberWithUnits& operator--(NumberWithUnits& n);
        friend NumberWithUnits operator--(NumberWithUnits& n,int a);
        friend NumberWithUnits operator*(const NumberWithUnits &n,const long double &num);
        friend NumberWithUnits operator*(const long double &num,const NumberWithUnits &n);
        friend bool operator>(const NumberWithUnits &n1,const NumberWithUnits &n2);
        friend bool operator>=(const NumberWithUnits &n1,const NumberWithUnits &n2);
        friend bool operator<(const NumberWithUnits &n1,const NumberWithUnits &n2);
        friend bool operator<=(const NumberWithUnits &n1,const NumberWithUnits &n2);
        friend bool operator==(const NumberWithUnits &n1,const NumberWithUnits &n2);
        friend bool operator!=(const NumberWithUnits &n1,const NumberWithUnits &n2);
       
    };
}
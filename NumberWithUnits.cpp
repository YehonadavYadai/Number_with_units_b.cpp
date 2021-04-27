

//
// Created by yehonadav2 on 18/04/2021.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include "NumberWithUnits.hpp"
#include <stdexcept>
#include <math.h>

using namespace std;

namespace ariel {
    const double EPS = 0.001;

static map<string, map<string, double>> units;

NumberWithUnits::NumberWithUnits(double value,const string &unit)// Here you DEFINE your constructor
{
   
        if (units.count(unit)==0)
                    {
                        throw std::invalid_argument{"not such unit "};    
                    }
        this->unit=unit;
        this->value=value;
      
}



    
    void print_table(){
    for (auto const &current_unit:units) {
        for (auto const &current_unit_2:units[current_unit.first]){
                cout<<"1 "<<current_unit.first<<" = "<<current_unit_2.second<< " "<<current_unit_2.first<<endl;

        }

    }
    }

void Fill_sibs(string& unit_left,string &unit_right , double u1,double u2){

                    for (auto const &current_unit:units[unit_right]) {
                    //if unit_right have sibling that unit_left does now connect to them/
                    if (units[unit_left].count(current_unit.first)==0)
                    {
                    const auto &key = current_unit.first;
                    const auto &value = current_unit.second;
                    double conv = value * u2;
                   //connect them
                    units[unit_left][key] = conv;
                    units[key][unit_left] = 1 / conv;
                    }
                }
                //same just from right to left.
                for (auto const &current_unit:units[unit_left]) {
                    if (units[unit_right].count(current_unit.first)==0)
                    {
                   
                    const auto &key = current_unit.first;
                    const auto &value = current_unit.second;

                    double conv = value*(1/u2);
                    units[unit_right][key] = conv;
                    units[key][unit_right] = 1 / conv;
                      
                    }
                }

    }
   
    double convert(const string &n1, const string &n2, double value) {

        
        //if its the same unit do nothing.
        if (n1 == n2){
            return value;
            }
            //if n1 type does not connected to n2 type so throw expe.
        if (units[n1].find(n2) == units[n1].end()) {
            string ans="Units do not match - ["+n1+"] cannot be converted to ["+n2+"]";
            throw std::out_of_range{ans};

        }
        //if they are connected return the value*yahas between n2 type to n1 .
        return value * units.at(n2).at(n1);

    }

    
    void NumberWithUnits::read_units(std::ifstream &units_file) {
        //setting for method.
        double u1=0;
        double u2=0;
        string unit_left=" ";
        string unit_right=" ";
        string none=" "; 

        //start read the file line by line.
        while (!units_file.eof()) {
           const int one = 1;
            units_file >> u1 >> unit_left >> none >> u2 >> unit_right;
            //check if the line is legal if the first str is "1"
            if (u1 == one) {
                //if its legal "connect them"
                units[unit_left][unit_right] = u2;
                units[unit_right][unit_left] = u1 / u2;
                units[unit_right][unit_right]=1;
                units[unit_left][unit_left]=1;
                //connect there siblings.
                Fill_sibs( unit_left,unit_right ,  u1, u2);

               
            }
        }
        //option to see all the units.
         //print_table();

    }
    

    ostream &operator<<(ostream &out, const NumberWithUnits &a) {
        out << a.value << "[" << a.unit << ']';
        return out;}


//sourcse : ADI DAHARI      
     istream &operator>>(istream &s, NumberWithUnits &n)
    {
        char c = 0;
        string a;
        double v = 0;
        s >> v >> c >> a >> c;
        if (a[a.length() - 1] == ']')
        {
            a.pop_back();
        }
        if (c == '-')
        {
            s.putback('-');
        }
        try
        {
            units.at(a);
            n.value = v;
            n.unit = a;
            return s;
        }
        catch (const exception &e)
        {
            throw std::invalid_argument(a + " is not a valid unit!");
        }
    }


   NumberWithUnits operator+(const NumberWithUnits& n1,const NumberWithUnits& n2){
        double num2_val=convert(n1.unit,n2.unit,n2.value);
        return NumberWithUnits(n1.value+num2_val,n1.unit);
        } 


    const NumberWithUnits& operator+(const NumberWithUnits &n){
        return n;
    }
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& n){
        double num2_val=convert(this->unit,n.unit,n.value);
        this->value+=num2_val;
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& n){
        double num2_val=convert(this->unit,n.unit,n.value);
        this->value-=num2_val;
        return *this;
    }
    NumberWithUnits operator-(const NumberWithUnits& n1,const NumberWithUnits& n2){
        
        return n1+(-n2);
    }
    NumberWithUnits operator-(const NumberWithUnits& n){
        return NumberWithUnits(-n.value,n.unit);
    }



      int compare(const NumberWithUnits &n1, const NumberWithUnits &n2) {
        
        NumberWithUnits n2_con(convert(n1.unit, n2.unit, n2.value), n1.unit);
        double check= (n1.value - n2_con.value);
        double ab=fabs(check);
        int ans=0;
        if (ab<EPS){
            ans=0;
        }
        else if(check>0) {
            ans= 1;
        }
        else{
            ans=-1;
        }
        
        return ans;
    }
    bool operator>(const NumberWithUnits &n1, const NumberWithUnits &n2) {
        return compare(n1, n2) > 0;
    }

    bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2) {
        return compare(n1, n2) >= 0;
    }

    bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2) {
        return compare(n1, n2) < 0;
    }

    bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2) {
        return compare(n1, n2) <= 0;;
    }

    bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2) {
        return compare(n1, n2) == 0;
    }

    bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2) {
        return !(n1 == n2);
    }

    NumberWithUnits& operator++(NumberWithUnits& n){
        n.value++;
        return n;
    }
    NumberWithUnits operator++(NumberWithUnits &n,int a){
        NumberWithUnits copy=NumberWithUnits(n);
        ++n;
        return copy;
    }
    NumberWithUnits& operator--(NumberWithUnits& n){
        n.value--;
        return n;
    }
    NumberWithUnits operator--(NumberWithUnits &n,int a){
        NumberWithUnits copy=NumberWithUnits(n);
        --n;
        return copy;
    }
    NumberWithUnits operator*(const NumberWithUnits& n,const long double& num){
        NumberWithUnits n2=NumberWithUnits(n);
        n2.value*=(double)num;
        return n2;
    }
    NumberWithUnits operator*(const long double& num,const NumberWithUnits& n){
        return n*num;
    }

}









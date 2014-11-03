#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;
void strtok_char( string s,char c,vector<string> &v );
double log2( double number,double base );
void entropy( vector<string> &testarray, vector<double> &result );

int main( int argc , char *argv[] )
{
    ifstream fin;
    ofstream fout;
    string tmpstr;

    fin.open("open file");
    fout.open("output file");
    int count=0;
    string current_time = "your file first time";
    int current_index = 1;
    int mininute = 0;
    vector<string> dst_port_vector;
    vector<string> dst_ip_vector;
    vector<string> src_port_vector;
    vector<string> src_ip_vector;
    vector<double> dst_port_result;
    vector<double> dst_ip_result;
    vector<double> src_port_result;
    vector<double> src_ip_result;
    while( getline( fin,tmpstr) )
    {
        count++;
        vector< string > tmpvec;
        tmpvec.clear();
        strtok_char( tmpstr, '\t', tmpvec );
        if (tmpvec[0] != current_time)
        {
            mininute ++;
            //cout << "Time: " << current_time << endl;
            entropy(dst_port_vector,dst_port_result);
            entropy(dst_ip_vector,dst_ip_result);
            entropy(src_port_vector,src_port_result);
            entropy(src_ip_vector,src_ip_result);
            fout << current_time << '\t' << count-current_index << '\t';
            fout << dst_port_result[0] << '\t' << dst_port_result[1] << '\t'   << dst_port_result[2] << '\t';
            fout << dst_ip_result[0] << '\t' << dst_ip_result[1] << '\t'   << dst_ip_result[2] << '\t';
            fout << src_port_result[0] << '\t' << src_port_result[1] << '\t'   << src_port_result[2] << '\t';
            fout << src_ip_result[0] << '\t' << src_ip_result[1] << '\t'   << src_ip_result[2] << endl;
            current_time = tmpvec[0];
            current_index = count;
            dst_port_vector.clear();
            dst_ip_vector.clear();
            dst_port_result.clear();
            dst_ip_result.clear();
            src_port_vector.clear();
            src_ip_vector.clear();
            src_port_result.clear();
            src_ip_result.clear();
        }
        dst_port_vector.push_back(tmpvec[8]);
        dst_ip_vector.push_back(tmpvec[7]);
        src_port_vector.push_back(tmpvec[6]);
        src_ip_vector.push_back(tmpvec[5]); 
    }
    fin.close();
    fin.clear();
    fout.close();
    fout.clear();
    return 0;
}

void strtok_char( string s,char c,vector<string> &v )   
{
    while( s.find( c ) != string::npos )
    {
        v.push_back( s.substr(0,s.find_first_of(c)) );
        if( s.find_first_of(c) != s.size()-1 )
            s = s.substr( s.find_first_of(c)+1 );
        else
            s = "";
    }
    if( s != "" )
        v.push_back( s ); 
}
double log_base( double number, double base ) {
   return log( number ) / log( base ) ;
}
 
void entropy( vector<string> &testarray , vector<double> &result ) {
   map<string , int> frequencies ;
   pair<string , int> p ;
   for (vector<string>::iterator it = testarray.begin() ; it != testarray.end(); ++it)
     frequencies[*it] ++ ;
   int numlen = testarray.size( ) ;
   int base = frequencies.size( ) ;
   double infocontent_base2 = 0 ;
   double infocontent_base_freq = 0 ;
   //for (map<string, int>::iterator at=frequencies.begin(); at!=frequencies.end(); ++at)
   //  cout << at->first << " => " << at->second << '\n';
   for (map<string, int>::iterator p = frequencies.begin() ; p != frequencies.end(); ++p) {
      infocontent_base2 -= (double)p->second/numlen*log_base((double)p->second/numlen, (double)2);
      infocontent_base_freq -= (double)p->second/numlen*log_base((double)p->second/numlen, (double)base);
   }
   result.push_back(infocontent_base2);
   result.push_back(infocontent_base_freq);
   result.push_back(base);
}

#include<cstdio>
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<cmath>
#include<map>

using namespace std;

string getPrefix(const string& s,const char& c,int k);
string getSuffix(const string& s,const char& c,int k);
void strtok_char( string s,char c,vector<string> &v );

int main( int argc , char *argv[] )
{
    ifstream fin;
    ofstream fout;
    string tmpstr;

    fin.open("your file location");
    fout.open("your out file location");
    int count=0;
    while( getline( fin,tmpstr) )
    {
        count++;
        vector< string > tmpvec;
        tmpvec.clear();
        strtok_char( tmpstr, ' ', tmpvec );
	if(count%2==1)
	{
            unsigned found0 = tmpvec[1].find_last_of(":");
	    fout << tmpvec[0] <<  " " <<tmpvec[1].substr(0,found0) << '\t' << tmpvec[2]<<'\t';
            
	    unsigned found = tmpvec[3].find_last_of(",");
            fout << tmpvec[3].substr(0,found) << '\t' << tmpvec[4] <<'\t';

            unsigned found1 = tmpvec[5].find_last_of(")");
            fout << tmpvec[5].substr(1,found1-1) << '\t';
	}
	else
        {
            unsigned found2 = tmpvec[0].find_last_of(".");
            fout << tmpvec[0].substr(0,found2) << '\t' << tmpvec[0].substr(found2+1,tmpvec[0].size()-found2) << '\t';

            unsigned found3 = tmpvec[1].find_last_of(".");
	    fout << tmpvec[1].substr(0,found3) << '\t' <<  tmpvec[1].substr(found3+1,tmpvec[1].size()-2-found3) << '\t';

            fout<< tmpvec[2] << endl;
        }	
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
string getPrefix(const string& s,const char& c,int k)
{
    int i;
    if( k <= 0 )
        return s;
    size_t pos;
    string tmp;
    tmp = s;
    for( i = 0; i < k ; i++ )
    {
        pos = tmp.find_last_of(c);
        if( pos == string::npos )
            break;
        tmp = tmp.substr(0,pos);
    }
    return tmp;
}
string getSuffix(const string& s,const char& c,int k)
{
    int i;
    if( k <= 0 )
        return s;
    size_t pos;
    string tmp;
    tmp = s;
    for( i = 0; i < k ; i++ )
    {
        pos = tmp.find_first_of(c);
        if( pos == string::npos )
            break;
        if( tmp.size()-pos-1 == 0 )
            tmp = "";
        else
            tmp = tmp.substr(pos+1,tmp.size()-pos-1);
    }
    return tmp;
}

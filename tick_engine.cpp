#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <bitset>
#include <time.h>
#include <cmath>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <sstream>

using namespace std;

#define MOD 1000000007LL
#define LL long long
#define LD long double
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(x) ((x)<0?-(x):(x))

#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define FORR(i,n) for(int i=(n);i>=0;i--)

const double PI=3.14159265358979323846264338327950288419716939937510582097494459230;

struct tick
{
	int timestamp;
	string symbol;
	vector<string> field_name;
	vector<int> field_value;
	
};

void Tokenize(const string& str,vector<string>& tokens,const string& delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

vector<tick> tickset;

void readData()
{
   	string s;
	vector<string> first_tokens;
	std::getline (std::cin,s);
	Tokenize(s,first_tokens);
    string::size_type sz;
	int ticklines = std::stoi (first_tokens[1],&sz);
	cout<<ticklines<<endl;
	REP(i,ticklines)
	{
		tick dat;
		vector<string> data_tokens;
		getline(std::cin,s);
		Tokenize(s,data_tokens);
		//cout<<data_tokens[0];
		dat.timestamp=stoi(data_tokens[0],&sz);
		dat.symbol = data_tokens[1];

		FOR(j,2,data_tokens.size())
		{
			if(j%2==0)
				dat.field_name.push_back(data_tokens[j]);
			else dat.field_value.push_back(stoi(data_tokens[j],&sz));
		}
		tickset.push_back(dat);
	}
}

void printData()
{
	REP(i,tickset.size())
	{
		cout<<tickset[i].timestamp<<" "<<tickset[i].symbol<<" ";
		REP(j,tickset[i].field_name.size())
		{
			cout<<tickset[i].field_name[j]<<" "<<tickset[i].field_value[j]<<" ";
		}
		cout<<endl;
	}
}
	


int main()
{
	readData();
	printData();
	


	return 0;
}

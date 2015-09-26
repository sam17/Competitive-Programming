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
#include <map>

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
map <int,int> indexMap;
map <string, map<string,int> > symbolField;
map <string, map<string,int> > sum_symbolField;
vector <  map <string, map<string,int> > > time_sum; 

int readData()
{
   	string s;
	vector<string> first_tokens;
	std::getline (std::cin,s);
	Tokenize(s,first_tokens);
    string::size_type sz;
	int ticklines = std::stoi (first_tokens[1],&sz);
//	cout<<ticklines<<endl;
	REP(i,ticklines)
	{
		tick dat;
		vector<string> data_tokens;
		getline(std::cin,s);
		Tokenize(s,data_tokens);
		dat.timestamp=stoi(data_tokens[0],&sz);
		string symbol = data_tokens[1];
		dat.symbol = symbol;
	    for(int j=2;j<data_tokens.size();j=j+2)
		{
			string name;
			int value;
			name = data_tokens[j];
			dat.field_name.push_back(name);
			value = stoi(data_tokens[j+1],&sz);
			dat.field_value.push_back(value);
			symbolField[symbol][name]=value;
			sum_symbolField[symbol][name]+=value;
//			time_sum.push_back(sum_symbolField);
		}
	   
		time_sum.push_back(sum_symbolField);
		
		if(i>0 && tickset[i-1].timestamp==dat.timestamp)
		{
			time_sum[indexMap[dat.timestamp]]=sum_symbolField;
		}
		else indexMap[dat.timestamp]=i;
		
		tickset.push_back(dat);
	}
	//sum_symbolField.clear();
	cout<<"tickfile completed"<<endl;
	return ticklines;
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

int findMax(int start_time,int end_time,string symbol,string field_name,int k)
{
	int max=0;
	

//	cout<<start_time<<" "<<end_time<<" "<<symbol<<" "<<field_name<<" "<<k<<endl;
	return max;
}

int findSum(int start_time,int end_time,string symbol,string field_name)
{
	int index1 = indexMap[start_time];
	int index2 = indexMap[end_time];
	//cout<<index1<<" "<<index2<<" "<<" "<<time_sum[index2][symbol][field_name]<<endl;
	int sum;
	if(index1==0)
		sum = time_sum[index2][symbol][field_name];
	else
		sum = time_sum[index2][symbol][field_name]-time_sum[index1-1][symbol][field_name];

	return sum;
}

void findSOP(int start_time,int end_time,string symbol,string field_name_one,string field_name_two)
{


	
}

void readQuery()
{
	while(!cin.eof())
	{
		string s;
		vector<string> query_tokens;
		getline (std::cin,s);
		Tokenize(s,query_tokens);
		string::size_type sz;
		int start_time=stoi(query_tokens[1],&sz);
		int end_time=stoi(query_tokens[2],&sz);
		string symbol =query_tokens[3];

		int query_id;
		if(query_tokens[0]=="max")
			query_id=0;
		else if(query_tokens[0]=="sum")
			query_id=1;
		else if(query_tokens[1]=="product")
			query_id=2;

		switch(query_id)
		{
		case 0: cout<<findMax(start_time,end_time,symbol,query_tokens[4],stoi(query_tokens[5],&sz));
			break;
		case 1: cout<<findSum(start_time,end_time,symbol,query_tokens[4])<<endl;
			break;
		case 2: //cout<<findSOP(start_time,end_time,symbol,query_tokens[4],query_tokens[5]);
			break;
			
		}
	}	

}

int main()
{
	readData();
	//printData();
	readQuery();
	
	//cout<<time_sum[4]["s2"]["f2"];

	
	return 0;
}

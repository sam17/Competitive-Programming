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
#include <stack>
#define MAXN 100000
#define INF numeric_limits<double>::infinity()

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

std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}


void processProduct()
{

}
map <int, map<string, map <string,int> > > sum_store;
map<string, map <string,int> > store;
int readData()
{
   	string s;
	vector<string> first_tokens;
	safeGetline (std::cin,s);
	Tokenize(s,first_tokens);
    string::size_type sz;
	int ticklines = std::stoi (first_tokens[1],&sz);
//	cout<<ticklines<<endl;
	REP(i,ticklines)
	{
		tick dat;
		vector<string> data_tokens;
		safeGetline(std::cin,s);
		Tokenize(s,data_tokens);
		dat.timestamp=stoi(data_tokens[0],&sz);
		string symbol = data_tokens[1];
		dat.symbol = symbol;
		if(i>0 && tickset[i-1].timestamp==dat.timestamp);
		else indexMap[dat.timestamp]=i;
		
	    for(int j=2;j<data_tokens.size();j=j+2)
		{
			string name;
			int value;
			name = data_tokens[j];
			dat.field_name.push_back(name);
			value = stoi(data_tokens[j+1],&sz);
			dat.field_value.push_back(value);
			store[dat.symbol][name]+=value;
			sum_store[indexMap[dat.timestamp]]+=store;
		}
	   	   
		tickset.push_back(dat);
	}
	//sum_symbolField.clear();
	//processProduct();
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
map<int,int> subtractMaps(map<int,int> a,map<int,int> b)
{
	map<int,int> diff;
	return diff;	
}
void printMax(int start_time,int end_time,string symbol,string field_name,int k)
{
}
//Assuming that every time stamp will have only one value of a field name
/*int findSum(int start_time,int end_time,string symbol,string field_name)
{
	std::map<int,int>::iterator it1 = indexMap.lower_bound(start_time);
	int index1,index2;
	if(indexMap.find(start_time)!=indexMap.end())
		index1 = it1->second;
	else index1=it1->second;
	std::map<int,int>::iterator it2 = indexMap.lower_bound(end_time);
	if(indexMap.find(end_time)!=indexMap.end())
		index2 = it2->second;
	else index2=it2->second-1;
	
	//index2 = it2->second;
	//cout<<index1<<" "<<index2<<" "<<" "<<time_sum[index2][symbol][field_name]<<endl;
	int sum;
	if(index1==0)
		sum = time_sum[index2][symbol][field_name];
	else
		sum = time_sum[index2][symbol][field_name]-time_sum[index1-1][symbol][field_name];
	return sum;
}
*/
int findSum(int start_time,int end_time,string symbol,string field_name)
{
	std::map<int,int>::iterator it1 = indexMap.lower_bound(start_time);
	int index1,index2;
	if(indexMap.find(start_time)!=indexMap.end())
		index1 = it1->second;
	else if(it1 == indexMap.end())
		index1 = -1;
	else index1=it1->second;
	std::map<int,int>::iterator it2 = indexMap.lower_bound(end_time);
	if(indexMap.find(end_time)!=indexMap.end())
		index2 = it2->second;
	else 
	{
		it2--;
		index2 = it2->second;
	}

	int sum=0;
	
	//int sum;
	if(index1==0)
		sum = store[index2][symbol][field_name];
	else
		sum = store[index2][symbol][field_name]-store[index1-1][symbol][field_name];
	return sum;

	//return sum;
}

int findSOP(int start_time,int end_time,string symbol,string field_name_one,string field_name_two)
{
	int sum;
	return sum;
}

/*double printDelta(string symbol,string field_name,int C)
{
}*/
void readQuery()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		//cout<<"here";
		string s;
		vector<string> query_tokens;
		safeGetline (std::cin,s);
		Tokenize(s,query_tokens);
		string::size_type sz;
		int start_time;
		int end_time;
		string symbol =query_tokens[3];

		int query_id=-1;
		if(query_tokens[0]=="max")
		{
			start_time=stoi(query_tokens[1],&sz);
			end_time=stoi(query_tokens[2],&sz);
			symbol =query_tokens[3];
			query_id=0;
		}
		else if(query_tokens[0]=="sum")
		{
			start_time=stoi(query_tokens[1],&sz);
			end_time=stoi(query_tokens[2],&sz);
			symbol =query_tokens[3];
			query_id=1;
		}
		else if(query_tokens[0]=="product")
		{
			start_time=stoi(query_tokens[1],&sz);
			end_time=stoi(query_tokens[2],&sz);
			symbol =query_tokens[3];
			query_id=2;
		}
		else if(query_tokens[0]=="delta")
		{
			symbol =query_tokens[1];
			query_id=3;
		}

		switch(query_id)
		{
		case 0: //printMax(start_time,end_time,symbol,query_tokens[4],stoi(query_tokens[5],&sz));
			break;
		case 1: cout<<findSum(start_time,end_time,symbol,query_tokens[4])<<endl;
			break;
		case 2: //cout<<findSOP(start_time,end_time,symbol,query_tokens[4],query_tokens[5])<<endl;
			break;
		case 3: //cout<<printDelta(symbol,query_tokens[2],stoi(query_tokens[3],&sz))<<endl;
			break;
			}
	}	

}

int main()
{
	readData();
	//printData();
	readQuery();
	//map<int,int> a = time_counter[indexMap[1015]]["s2"]["f3"];
	cout<<store[indexMap[1009]]["s2"]["f3"];
	//map<int,int> b = time_counter[indexMap[1010]]["s2"]["f3"];
	//map<int,int> diff = subtractMaps(a,b);;
	//cout<<a.rbegin()->first;
	//cout<<time_sum[indexMap[1274]]["s2"]["f3"];
    
	return 0;
}

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

struct Point {
	int x, y;
	bool operator < (const Point& that) const {
		return x < that.x;
	}
};

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

map < string,map <string, map<int,int> > > number_counter;
vector< map < string,map <string, map<int,int> > > > time_counter;
map < string, map <string, map <string,int> > > product_list;
vector< map < string, map <string, map <string,int> > > > time_product;

void processProduct()
{
	REP(i,tickset.size())
	{

		REP(j,tickset[i].field_name.size())
		{
			FOR(k,j,tickset[i].field_name.size())
			{
				string str1 = tickset[i].field_name[j];
				string str2 = tickset[i].field_name[k];
				if(str1.compare(str2)>0)
					product_list[tickset[i].symbol][str1][str2]+=(tickset[i].field_value[j]*tickset[i].field_value[k]);
				else product_list[tickset[i].symbol][str2][str1]+=(tickset[i].field_value[k]*tickset[i].field_value[j]);			
			}
		}
		time_product.push_back(product_list);
		if(i>0 && tickset[i-1].timestamp==tickset[i].timestamp)
		{
			time_product[indexMap[tickset[i].timestamp]]=product_list;
		}
	}		
}
map <string, map <string, pair<int,int> > > time_value; 
vector< map <string, map <string, pair<int,int> > > > time_series;

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
	    for(int j=2;j<data_tokens.size();j=j+2)
		{
			string name;
			int value;
			name = data_tokens[j];
			dat.field_name.push_back(name);
			value = stoi(data_tokens[j+1],&sz);
			dat.field_value.push_back(value);
			symbolField[symbol][name]=value;
			number_counter[symbol][name][value]++;
			sum_symbolField[symbol][name]+=value;
			time_value[symbol][name]=make_pair(dat.timestamp,value);
//			time_sum.push_back(sum_symbolField);
		}
	   
		time_sum.push_back(sum_symbolField);
		//time_counter.push_back(number_counter);
		time_series.push_back(time_value);
		
		if(i>0 && tickset[i-1].timestamp==dat.timestamp)
		{
			time_sum[indexMap[dat.timestamp]]=sum_symbolField;
			time_counter[indexMap[dat.timestamp]]=number_counter;
		}
		else indexMap[dat.timestamp]=i;
		
		tickset.push_back(dat);
	}
	//sum_symbolField.clear();
	processProduct();
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
	for(map<int,int>::iterator it=a.begin();it!=a.end();++it)
	{
		if(a.find(it->first)!=a.end() && (a[it->first]-b[it->first])>0)
			diff[it->first]=a[it->first]-b[it->first];
	}
	return diff;	
}
void printMax(int start_time,int end_time,string symbol,string field_name,int k)
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

	map<int,int> ans;
	if(index1==0)
		ans = time_counter[index2][symbol][field_name];
	else
	{
		map <int,int> a = time_counter[index2][symbol][field_name];
		map <int,int> b = time_counter[index1-1][symbol][field_name];
		ans = subtractMaps(a,b);
	}
	int i=0;
	//cout<<k<<endl;
	for(std::map<int,int>::reverse_iterator rit=ans.rbegin();i<k && rit!=ans.rend();i++,rit++)
	{
		REP(j,rit->second)
		{
			cout<<rit->first<<" ";
			if(j>0) i++;
		}
	}
	cout<<endl;
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
	// else index2=it2->second-1;
	
	// //index2 = it2->second;
	// for(map<int,int> :: iterator it = indexMap.begin(); it != indexMap.end(); it++)
	// 	cout<<it->first <<" : "<<it->second<<endl;
	// cout<<index1<<" "<<index2<<" "<<" "<<time_sum[index2][symbol][field_name]<<endl;
	int sum;
	if(index1==0)
		sum = time_sum[index2][symbol][field_name];
	else if(index1 == -1)
		sum = 0;
	else
		sum = time_sum[index2][symbol][field_name]-time_sum[index1-1][symbol][field_name];
	return sum;
}

int findSOP(int start_time,int end_time,string symbol,string field_name_one,string field_name_two)
{
	string str1,str2;
	if(field_name_one.compare(field_name_two)>0)
	{
		str1=field_name_one;
		str2 = field_name_two;
	}
	else
	{
		str1=field_name_two;
		str2=field_name_one;
	}
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
	
	//index2 = it2->second;
	//cout<<index1<<" "<<index2<<" "<<" "<<time_sum[index2][symbol][field_name]<<endl;
	int sum;
	if(index1==0)
		sum = time_product[index2][symbol][str1][str2];
	else
		sum = time_product[index2][symbol][str1][str2]-time_product[index1-1][symbol][str1][str2];
	return sum;
}

double printDelta(string symbol,string field_name,int C)
{
	int N, i, j, k, interval;
	long long x_sum, y_sum, xy_sum, xsqr_sum, num, denom;
	double tmp, mn;
	vector<Point> points;
	FOR(i,1,time_series.size()+1)
	{

		if(time_series[i].find(symbol)!=time_series[i].end()&&time_series[i][symbol].find(field_name)!=time_series[i][symbol].end())
		{
			Point p;
			p.x= time_series[0]["s2"]["f2"].first;
			p.y=time_series[0]["s2"]["f2"].second;
			points.push_back(p);
			cout<<p.x<<" "<<p.y<<endl;
		}
	}
	N = points.size();
		// precompute the error terms
	long long cumulative_x[N + 1], cumulative_y[N + 1], cumulative_xy[N + 1], cumulative_xSqr[N + 1];
	double slope[N + 1][N + 1], intercept[N + 1][N + 1], E[N + 1][N + 1];
	double OPT[N + 1];
	int opt_segment[N + 1];

	cumulative_x[0] = cumulative_y[0] = cumulative_xy[0] = cumulative_xSqr[0] = 0;
	for (j = 1; j <= N; j++)
	{
		cumulative_x[j] = cumulative_x[j-1] + points[j].x;
		cumulative_y[j] = cumulative_y[j-1] + points[j].y;
		cumulative_xy[j] = cumulative_xy[j-1] + points[j].x * points[j].y;
		cumulative_xSqr[j] = cumulative_xSqr[j-1] + points[j].x * points[j].x;
		
		for (i = 1; i <= j; i++)
		{
			interval = j - i + 1;
			x_sum = cumulative_x[j] - cumulative_x[i-1];
			y_sum = cumulative_y[j] - cumulative_y[i-1];
			xy_sum = cumulative_xy[j] - cumulative_xy[i-1];
			xsqr_sum = cumulative_xSqr[j] - cumulative_xSqr[i-1];
			
			num = interval * xy_sum - x_sum * y_sum;
			if (num == 0)
				slope[i][j] = 0.0;
			else
			{
				denom = interval * xsqr_sum - x_sum * x_sum;
				slope[i][j] = (denom == 0) ? INF : (num / double(denom));				
			}
            		intercept[i][j] = (y_sum - slope[i][j] * x_sum) / double(interval);
            
           		for (k = i, E[i][j] = 0.0; k <= j; k++)
				{
            			tmp = points[k].y - slope[i][j] * points[k].x - intercept[i][j];
            			E[i][j] += tmp * tmp;
            		}
		}
	}
	
	// find the cost of the optimal solution
	OPT[0] = opt_segment[0] = 0;
	for (j = 1; j <= N; j++)
	{
		for (i = 1, mn = INF, k = 0; i <= j; i++)
		{
			tmp = E[i][j] + OPT[i-1];
			if (tmp < mn)
			{
				mn = tmp;
				k = i;
			}
		}
		OPT[j] = mn + C;
		opt_segment[j] = k;
	}
	
	//printf("\nCost of the optimal solution : %lf\n", OPT[N]);

	return OPT[N];
}
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
		case 2: cout<<findSOP(start_time,end_time,symbol,query_tokens[4],query_tokens[5])<<endl;
			break;
		case 3: cout<<printDelta(symbol,query_tokens[2],stoi(query_tokens[3],&sz))<<endl;
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
	
	//map<int,int> b = time_counter[indexMap[1010]]["s2"]["f3"];
	//map<int,int> diff = subtractMaps(a,b);;
	//cout<<a.rbegin()->first;
	//cout<<time_sum[indexMap[1274]]["s2"]["f3"];
    
	return 0;
}

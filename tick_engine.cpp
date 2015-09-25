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

// A utility function to get the middle index from corner indexes.
int getMid(int s, int e) {  return s + (e -s)/2;  }
 
/*  A recursive function to get the sum of values in given range of the array.
    The following are parameters for this function.
 
    st    --> Pointer to segment tree
    si    --> Index of current node in the segment tree. Initially 0 is
             passed as root is always at index 0
    ss & se  --> Starting and ending indexes of the segment represented by
                 current node, i.e., st[si]
    qs & qe  --> Starting and ending indexes of query range */
int getSumUtil(int *st, int ss, int se, int qs, int qe, int si)
{
    // If segment of this node is a part of given range, then return the
    // sum of the segment
    if (qs <= ss && qe >= se)
        return st[si];
 
    // If segment of this node is outside the given range
    if (se < qs || ss > qe)
        return 0;
 
    // If a part of this segment overlaps with the given range
    int mid = getMid(ss, se);
    return getSumUtil(st, ss, mid, qs, qe, 2*si+1) +
           getSumUtil(st, mid+1, se, qs, qe, 2*si+2);
}
 
/* A recursive function to update the nodes which have the given index in
   their range. The following are parameters
    st, si, ss and se are same as getSumUtil()
    i    --> index of the element to be updated. This index is in input array.
   diff --> Value to be added to all nodes which have i in range */
void updateValueUtil(int *st, int ss, int se, int i, int diff, int si)
{
    // Base Case: If the input index lies outside the range of this segment
    if (i < ss || i > se)
        return;
 
    // If the input index is in range of this node, then update the value
    // of the node and its children
    st[si] = st[si] + diff;
    if (se != ss)
    {
        int mid = getMid(ss, se);
        updateValueUtil(st, ss, mid, i, diff, 2*si + 1);
        updateValueUtil(st, mid+1, se, i, diff, 2*si + 2);
    }
}
 
// The function to update a value in input array and segment tree.
// It uses updateValueUtil() to update the value in segment tree
void updateValue(int arr[], int *st, int n, int i, int new_val)
{
    // Check for erroneous input index
    if (i < 0 || i > n-1)
    {
        printf("Invalid Input");
        return;
    }
 
    // Get the difference between new value and old value
    int diff = new_val - arr[i];
 
    // Update the value in array
    arr[i] = new_val;
 
    // Update the values of nodes in segment tree
    updateValueUtil(st, 0, n-1, i, diff, 0);
}
 
// Return sum of elements in range from index qs (quey start) to
// qe (query end).  It mainly uses getSumUtil()
int getSum(int *st, int n, int qs, int qe)
{
    // Check for erroneous input values
    if (qs < 0 || qe > n-1 || qs > qe)
    {
        printf("Invalid Input");
        return -1;
    }
 
    return getSumUtil(st, 0, n-1, qs, qe, 0);
}
 
// A recursive function that constructs Segment Tree for array[ss..se].
// si is index of current node in segment tree st
int constructSTUtil(int arr[], int ss, int se, int *st, int si)
{
    // If there is one element in array, store it in current node of
    // segment tree and return
    if (ss == se)
    {
        st[si] = arr[ss];
        return arr[ss];
    }
 
    // If there are more than one elements, then recur for left and
    // right subtrees and store the sum of values in this node
    int mid = getMid(ss, se);
    st[si] =  constructSTUtil(arr, ss, mid, st, si*2+1) +
              constructSTUtil(arr, mid+1, se, st, si*2+2);
    return st[si];
}
 
/* Function to construct segment tree from given array. This function
   allocates memory for segment tree and calls constructSTUtil() to
   fill the allocated memory */
int *constructST(int arr[], int n)
{
    // Allocate memory for segment tree
    int x = (int)(ceil(log2(n))); //Height of segment tree
    int max_size = 2*(int)pow(2, x) - 1; //Maximum size of segment tree
    int *st = new int[max_size];
 
    // Fill the allocated memory st
    constructSTUtil(arr, 0, n-1, st, 0);
 
    // Return the constructed segment tree
    return st;
}
 

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

int findMax(int start_time,int end_time,string symbol,string field_name,int k)
{
	int max=0;
	

//	cout<<start_time<<" "<<end_time<<" "<<symbol<<" "<<field_name<<" "<<k<<endl;
	return max;
}

void findSum(int start_time,int end_time,string symbol,string field_name)
{


	
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
		std::getline (std::cin,s);
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
		case 1: //cout<<findSum(start_time,end_time,symbol,query_tokens[4]);
			break;
		case 2: //cout<<findSOP(start_time,end_time,symbol,query_tokens[4],query_tokens[5]);
			break;
			
		}
	}
	
}
int main()
{
	readData();
	printData();
	readQuery();


	return 0;
}

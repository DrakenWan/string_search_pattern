#include<iostream>
#include<string>
#include<vector>

using namespace std;
 
void input_string(vector<char>& str)
{
    char a;
    while (1)
    {
        a = tolower(getchar());
        if (a == '\n')
          break;
        str.push_back(a);
    }
    return;
}
 
void print_string(vector<char> strn)
{
    for (std::vector<char>::iterator it = strn.begin();it != strn.end(); it++)
        cout<<*it;
    return;
}

int match_string(vector<char>& original, vector<char> match)
{
    vector<char>::iterator p, q, r;
    int i = 0;
 
    p = original.begin();
    while (r <= match.end() && p <= original.end())
    {
        r = match.begin();
        
        //Iterate through the original vector to find the first letter match
        while (*p != *r && p < original.end())
        {
            p++;
            i++;
        }
 
 		//Put value of iterator 'p' into the iterator 'q' to remember the first match
        q = p;
        
        //further run the iterators 'p' in original and 'q' 
		//in match vectors until reach the end of the match
        while (*p == *r && r <= match.end() && p<=original.end())
        {
            p++; i++;
            r++;
        }
 		
        if (r >= match.end())
        {
        	//Erasing the part of vectors that were iterated through
            original.erase(original.begin(), q + 1);
            return (i - match.size() + 1);
        }
 
        if (p >= original.end())
         return 0;
         
        p = ++q;
    }
}
 
 
int main()
{
    std::vector<char> original, match;
    int i, result, k=0, sum=0;
 
    cout<<"Enter String:";
    input_string(original);
    
    cout<<"Enter Search Pattern:";
    input_string(match);
 
    if (match.size() > original.size())
        cout<<"Error: Original string too small.";
 
    do
    {
        result = match_string(original, match);
        sum += result;    //to store previous found position
        if (result > 0)
        {
            k++;
            cout<<"\nMatch found from Position = "<<sum;
        }
     } while (result > 0);   //loop to find all patterns
 
     if (k == 0)
         cout<<"Error: Match Not Found";
     return 0;
}

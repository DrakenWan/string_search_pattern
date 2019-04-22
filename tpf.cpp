#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

//Defined vector of string
vector<string> words;

//Function which converts all the characters in a string to upper case 
string RemoveWhitespace(string a)
 {
  //Defining a new string
  string str = a;
  int track=0;
  
  //looping through size of string
   for(int i=0; i<a.length(); i++)
    {
     //If the character is not a space
     if(a[i] != ' ')
      {
      	str[track]=a[i];
      	track++;
	  }
	}
	str[track]='\0';
   return str.c_str(); //c_str() returns a null-terminated string
 }


string ConvertToUpper(string str) 
{  
 //Loop through the size of the string 
  for(int i=0;i< str.length();i++)     
   {    //If the character is not a space  
      if(str[i] != ' ')    
	   { //Reset the value of the array position to the new upper case letter    
	     str[i] = toupper(str[i]);   
	   }  
	}     
 return str; 
} 
 
//Function which converts all the characters in a string to lower case 
string ConvertToLower(string str) 
 {  //Loop through the size of the string 
    for(int i=0;i< str.length();i++)     
	{   
	    //If the character is not a space    
	    if(str[i] != ' ')
		 { //Reset the value of the array position to the new upper case letter    
		   str[i] = tolower(str[i]); 
		 }    
    }     
 return str; 
 }

//Function that will turn the string into a vector
void turnVect(string str)
 {
 	int i, prevPos=0,sizeCounter=0;
 	for(i=0; i<str.length(); i++)
 	{
     if(str[i] == ' '/*||str[i]=='.'||str[i]=='!'*/)
      {
      	words.push_back(str.substr(prevPos, sizeCounter));
      	prevPos = i+1;
      	sizeCounter=0;
	  }
	  sizeCounter++;
    }
}

int main()
 {
 	turnVect("My quill is fatter than you think. Baby! I love you!");
    cout<<words.size()<<endl;
    for(int i=0; i<words.size();i++)
     cout<<words[i]<<endl;
     
    string str;
    cout<<"Enter the string to match: "; cin>>str;

 	return 0;
 }

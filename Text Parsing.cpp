#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

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

//Function which parses out a string based on the delimiter of choice
/*
  The results are stored address back into a vector which is passed
  in by memory address
*/

void GetTokens(string str,vector<string>& tokenVector, char token) 
{  
 //Skips the delimeters are the beginning of the string
  int lastPosition = str.find_first_not_of(token, 0);
  //Find the first non delimiter 
  int position = str.find_first_of(token, lastPosition);
  
 //While loop which iterates through a string to subtract tokens  
 while (str.length() != position || str.length() != lastPosition)    
 {    
  //Adds found token to the vector
  tokenVector.push_back(str.substr(lastPosition, position - lastPosition)); 
  //Finds the next delimiter
  lastPosition = str.find_first_not_of(token, position); 
  //Finds the next non delimiter
  position = str.find_first_of(token, lastPosition);    
 }
} 

//Search text for a simple match 
vector<string> results; 
void simpleSearch(string str, vector<string>& tokenVector)
{
	//Loop thrught the tokenized vector and check for matches
	for(int i=0; i<tokenVector.size(); i++)
	 {
	 	//Does a boolean operation between two arrays to check for
	 	// a match
	 	if(str==tokenVector[i])
	 	 {
	 	 	//If a match is found, push the result into a different vector
	 	 	results.push_back(tokenVector[i]);
		  }
	 }
}

void partialSearch(string str, vector<string>& tokenVector)
 { 
   //Loop through the tokenized vector and check for matches
   for (int i = 0; i < tokenVector.size(); i++) 
    { 
	 //This uses the strstr() to find if an occurrance of our 
	 // search string has occured in the vector element
	 const char *ptr = strstr(tokenVector[i].c_str(),str.c_str()); 
	 
	 //A match is found if the pointer returned by the strstr() is not NULL
	  if(ptr != NULL)
	   {  
	    //If a match is found, push the result into a different vector
		 results.push_back(tokenVector[i]);
	   }
	} 
  } 

////////////////////////////////////////////////////////////////////////////////////////////

//Complex searching algorithm to handle multi word searches 
void complexSearch(string temp, string originalNotes) 
 { 
  //This uses the strstr function to find if an occurance of our search string has occurred in the original string  
  const char *ptr = strstr(originalNotes.c_str(), temp.c_str()); 
  //A match is found if the pointer returned by the strstr function is not NULL   
  if( ptr != NULL)   
   { 
    //Create a new string by using strdup to duplicate the string starting at the position an occurance was found 
	string str = strdup(ptr);   
	string searchString = temp;   
	int start = 0;   
	string final;   
	bool finished = false; 
	
	//Round up the last word by finding the next whitespace  
	while(start < searchString.size()-1 || finished == false && start<str.size())   
	{    
	 //Make sure we don’t go out of bounds while itterating the string    
	 if(start > searchString.size()-1)    
	 { 
	   //If we find anything, but a space, add the character to our last  word     
	   if(str[start] != ' ')     
	   { 
	    //Add the character to the final word and increase the position      
		final = final + str[start];
		start++;
	   }
	   
	   //If a space was found, it means that the word has been rounded up 
	   else
	   { 
	    //Set a boolean so our loop will break
		finished = true;
	   }    
	 } 
	 
	//This is an edge case for if the word to be rounded is the last word in the original string    
	else 
	 { 
	  //Add the character to the final word and increase the position     
	   final = final + str[start];     
	   start++;
	 }   
	}
	
	//Inilize a vector to store tokenized strings into    
	vector<string> tokens;   
	
	//Call the tokenizing function and separate the words by space   
	GetTokens(final, tokens, ' ');   
	int foundPosition;   
	//Look for the occurance of the first search word in vector of original words   
	for (int j = 0; j < formattedText.size(); j++)   
	{ 
	 const char *ptr = strstr(formattedText[j].c_str(), tokens[0].c_str()); 
	 //Found an occurance   
	  if(ptr != NULL)    
	   {
	    //If we find a match, we need to start at that position and 
		//see if the next words in the search vector match the corresponding order of words 
		//in the original word vector     
		foundPosition = j;
		int count = 0;
		//Loop through the vector of tokens     
		for (int i = 0; i < tokens.size(); i++)
		{ 
		 //If the arrays don’t match, then break from the loop
		 if(tokens[i] != formattedText[foundPosition])
		  { break;}      
		 foundPosition++;
		 count++; 
		} 
		
		//If all occurance of the search string occurred in correct order, then we are done     
		if( count == tokens.size() )
		{
		 searchResults.push_back(final);
		}
	   }
	}
  }
} 

int main()
 {
 	cout<<ConvertToLower("HELLO I am Karry")<<endl;
 	cout<<ConvertToUpper("HELLO I am Karry Kaul and I am here to tell")<<endl;
 	cout<<RemoveWhitespace("HELLO I am Karry Kaul and I am here to tell");
 	return 0;
 }

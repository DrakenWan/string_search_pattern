#include<bits/stdc++.h>
#include<limits.h>
#define d 256
#define title cout<<"\t\t\tTEXT SEARCHING"
#include<conio.h>

using namespace std;

//function to get maximum of two integers
int max (int a, int b) { return (a > b)? a: b; }

//NAIVE SEARCH ALGORITHM FUNCTION
void naive_search(char* pat, char* txt, int pos)
{
    int M = strlen(pat);
    int N = strlen(txt);
 
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) 
	{
        int j;
        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
         if (txt[i + j] != pat[j])
          break;
 
        if (j == M) 
		// if pat[0...M-1] = txt[i, i+1, ...i+M-1]4
		{
         cout<<"Pattern found at index "<<i+pos<<endl;}
    }
}
//END OF NAIVE SEARCH

//KNUTH MORRIS PRATT FUNCTION
void computeLPSArray(char pat[], int M, int lps[]);
 
// Prints occurrences of txt[] in pat[]
void KMPSearch(char pat[], char txt[], int pos)
{
    int M = strlen(pat);
    int N = strlen(txt);
 
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];
 
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
 
    int i = 0;  // index for txt[]
    int j = 0;  // index for pat[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
        
        if (j == M)
        {
            printf("Found pattern at index %d\n", i-j+pos);
            j = lps[j-1];
        }
 
        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
}
 
// Fills lps[] for given patttern pat[0...M-1]
void computeLPSArray(char *pat, int M, int *lps)
{
    // length of the previous longest prefix suffix
    int len = 0;
    
    lps[0] = 0; // lps[0] is always 0
     
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0)
            {
                len = lps[len-1];
 
                //note not to increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
//END OF KNUTH MORRIS PRATT ALGORITHM

//RABIN KARP SEARCH ALGORITHM FUNCTION
void rksearch(char pat[], char txt[], int q, int pos)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
 	
    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M-1; i++)
        h = (h*d)%q;
 
    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }
 
    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {
 
        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters on by one
        if ( p == t )
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }
 
            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M){
                cout<<"Pattern found at index "<<i+pos<<endl;}
        }
 
        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < N-M )
        {
            t = (d*(t - txt[i]*h) + txt[i+M])%q;
 
            // We might get negative value of t, converting it
            // to positive
            if (t < 0)
            t = (t + q);
        }
    }
}
//END OF RABIN KARP ALGORITHM FUNCTION

//BOYER MOORE BAD CHAR HEURISTIC FUNCTION

// The preprocessing function for Boyer Moore's
// bad character heuristic
void badCharHeuristic(char *str, int size, int badchar[d])
{
    int i;
 
    // Initialize all occurrences as -1
    for (i = 0; i < d; i++)
         badchar[i] = -1;
 
    // Fill the actual value of last occurrence 
    // of a character
    for (i = 0; i < size; i++)
         badchar[(int) str[i]] = i;
}
 
/* Bad Character Heuristic of Boyer Moore Algorithm */
void bmsearch1(char *txt,  char *pat, int pos)
{
    int m = strlen(pat);
    int n = strlen(txt);
 
    int badchar[d];
 
    /* Fill the bad character array by calling 
       the preprocessing function badCharHeuristic() 
       for given pattern */
    badCharHeuristic(pat, m, badchar);
 
    int s = 0;  // s is shift of the pattern with 
                // respect to text
    while(s <= (n - m))
    {
        int j = m-1;
 
        /* Keep reducing index j of pattern while 
           characters of pattern and text are 
           matching at this shift s */
        while(j >= 0 && pat[j] == txt[s+j])
            j--;
        
        /* If the pattern is present at current
           shift, then index j will become -1 after
           the above loop */
        if (j < 0)
        {
            cout<<"\nPattern occurs at shift = "<<s+pos;
 			cout<<"\nIndex "<<s+pos<<" to Index "<<s+strlen(pat)-1+pos;
            /* Shift the pattern so that the next 
               character in text aligns with the last 
               occurrence of it in pattern.
               The condition s+m < n is necessary for 
               the case when pattern occurs at the end 
               of text */
            s += (s+m < n)? m-badchar[txt[s+m]] : 1;
 
        }
 
        else
            /* Shift the pattern so that the bad character
               in text aligns with the last occurrence of
               it in pattern. The max function is used to
               make sure that we get a positive shift. 
               We may get a negative shift if the last 
               occurrence  of bad character in pattern
               is on the right side of the current 
               character. */
            s += max(1, j - badchar[txt[s+j]]);
    }
}
//END OF BAD CHAR HEURISTIC BOYER MOORE

//BOYER MOORE GOOD SUFFIX HEURISTIC FUNCTION
// preprocessing for strong good suffix rule
void preprocess_strong_suffix(int *shift, int *bpos,
                                char *pat, int m)
{
    // m is the length of pattern 
    int i=m, j=m+1;
    bpos[i]=j;
 
    while(i>0)
    {
        /*if character at position i-1 is not equivalent to
          character at j-1, then continue searching to right
          of the pattern for border */
        while(j<=m && pat[i-1] != pat[j-1])
        {
            /* the character preceding the occurence of t in 
               pattern P is different than mismatching character in P, 
               we stop skipping the occurences and shift the pattern
               from i to j */
            if (shift[j]==0)
                shift[j] = j-i;
 
            //Update the position of next border 
            j = bpos[j];
        }
        /* p[i-1] matched with p[j-1], border is found.
           store the  beginning position of border */
        i--;j--;
        bpos[i] = j; 
    }
}
 
//Preprocessing for case 2
void preprocess_case2(int *shift, int *bpos,
                      char *pat, int m)
{
    int i, j;
    j = bpos[0];
    for(i=0; i<=m; i++)
    {
        /* set the border postion of first character of pattern
           to all indices in array shift having shift[i] = 0 */
        if(shift[i]==0)
            shift[i] = j;
 
        /* suffix become shorter than bpos[0], use the position of 
           next widest border as value of j */
        if (i==j)
            j = bpos[j];
    }
}
 
/*Search for a pattern in given text using
  Boyer Moore algorithm with Good suffix rule */
void bmsearch2(char *text, char *pat, int pos)
{
    // s is shift of the pattern with respect to text
    int s=0, j;
    int m = strlen(pat);
    int n = strlen(text);
 
    int bpos[m+1], shift[m+1];
 
    //initialize all occurence of shift to 0
    for(int i=0;i<m+1;i++) shift[i]=0;
 
    //do preprocessing
    preprocess_strong_suffix(shift, bpos, pat, m);
    preprocess_case2(shift, bpos, pat, m);
 
    while(s <= n-m)
    {
 
        j = m-1;
 
        /* Keep reducing index j of pattern while characters of
             pattern and text are matching at this shift s*/
        while(j >= 0 && pat[j] == text[s+j])
            j--;
 
        /* If the pattern is present at current shift, then index j
             will become -1 after the above loop */
        if (j<0)
        {
            cout<<"Pattern occurs at shift = "<<s+pos<<endl;
            s += shift[0];
        }
        else
            /*pat[i] != pat[s+j] so shift the pattern
              shift[j+1] times  */
            s += shift[j+1];
    }
}
//END OF GOOD SUFFIX HEURISITC BOYER MOORE

int main()
 {
 	char dna_txt[63], pat[100];
 	char txt[]="ABCBCDBABCBACBABACABCDABCDEBACABADBABCACABACBADBCABCDBCABDCACBDCCCBDCACDBCDCCBBBBCACDCABCDCACBDCBADBCACACACACACBCBDBCAADBACBABAABACDABCDABCDABCDABADCBADCAAAABBBCAAACACABCDACBAABABABACDEABAEDCBADCBDDCBDDDCABDCADCBDADCBACBDCADCBDCACBDCABABCDACCDACBDCABDCABAASECACDB";
 	int i, q, pos=0, choice;
	do
 	 {
 	 	system("cls");
 	 	title;
 	 	cout<<"\n\nPRESS   FOR"<<endl
 	 	    <<"1       DNA Pattern Search"<<endl
 	 	    <<"2       Simple Pattern Search"<<endl
 	 	    <<"3       EXIT\n";
 	 	cin>>choice;
 	 	
 	 	if(choice == 1)
 	 	 {
 	 	 	pos = 0;
 	 	 	system("cls");
 	 	 	title;
 	 	 	cout<<"\n\nDNA PATTERN SEARCH";
 	 	 	cout<<"\nEnter the DNA sequence: ";
 	 	 	cin>>pat;
 	 	 	//Converting pattern to lowercase sequencing
 	 	 	for(i=0; pat[i]; i++) pat[i] = tolower(pat[i]);
 	 	 	ifstream file;
			file.open("C:\\Users\\Draken Wan\\Desktop\\dna.txt", ios::in);
			cout<<"\n\nSEARCH ALGORITHM PREFERENCE:\n";
			cout<<"ENTER  FOR\n"
			    <<"1       Naive Search\n"
			    <<"2       KMP Search\n"
			    <<"3       RabinKarp Search\n"
			    <<"4       Boyer Moore Bad Character Heuristic\n"
			    <<"5       Boyer Moore Good Suffix Heuristic\n";
			cin>>choice;
			
			while(!file.eof())
	 		{
	 		 file>>dna_txt;
        	 switch(choice)
        	  {
        	  	case 1 :
        	  		naive_search(pat, dna_txt,pos);
        	  		break;
        	  	case 2 :
        	  		KMPSearch(pat, dna_txt,pos);
        	  		break;
        	  	case 3 :
        	  		q = 3;
        	  		rksearch(pat, dna_txt, q, pos);
        	  		break;
        	    case 4 :
        	    	bmsearch1(dna_txt, pat, pos);
        	    	break;
        	    case 5 :
        	    	bmsearch2(dna_txt, pat, pos);
        	    	break;
        	    default:
        	    	cout<<"Wrong option!";
			  }
        	 pos+=63;
	 	    }
	 	    getch();
	        file.close();
		  }//CHOICE 1
		else
		 {
		 	if(choice == 2)
		 	 {
		 	 	pos=0;
		 	 	system("cls");
		 	 	title;
		 	 	cout<<"\n\nSimple Pattern Search";
		 	   
			    cout<<"\nEnter pattern to be searched: ";
			    cin>>pat;
			    cout<<"\n\nSEARCH ALGORITHM PREFERENCE:\n";
				cout<<"ENTER  FOR\n"
			    	<<"1       Naive Search\n"
			    	<<"2       KMP Search\n"
			    	<<"3       RabinKarp Search\n"
			    	<<"4       Boyer Moore Bad Character Heuristic\n"
			   	 	<<"5       Boyer Moore Good Suffix Heuristic\n";
				cin>>choice;
        	 	switch(choice)
        	 	 {
        	  		case 1 :
        	  			naive_search(pat,txt,pos);
        	  			break;
	        	  	case 2 :
	        	  		KMPSearch(pat, txt,pos);
        	  			break;
        	  		case 3 :
        	  			q = 3;
        	  			rksearch(pat, txt, q, pos);
        	  			break;
        	   	 	case 4 :
        	    		bmsearch1(txt, pat, pos);
        	    		break;
        	    	case 5 :
        	    		bmsearch2(dna_txt, pat, pos);
        	    		break;
        	    	default:
        	    		cout<<"Wrong option!";
			  	 } 
	 	      getch();
		   }//CHOICE 2
		 else
		   {
		   	cout<<"EXITING. Press Enter.";
		   	cin.get();
		   	exit(0);
		   }
		 }
	 } while(1);
 	return 0;
 }

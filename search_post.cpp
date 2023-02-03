#include "Graph.h"
#include <stdbool.h>


// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(string pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];

                // Also, note that we do not increment
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


// Prints occurrences of txt[] in pat[]
bool KMPSearch(string pat, string txt)
{
    const char* patt = pat.c_str();
    const char* txtt = txt.c_str();

    int M = strlen(patt);
    int N = strlen(txtt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int* lps = new int[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            delete[] lps;
            return true;
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    delete[] lps;
    return false;
}
// function to search for a given word in all the posts 
vector<Post*> Post_Search(string word, vector<Post*> Posts)
{
    int n = Posts.size();   
    vector<Post*> posts_found;  //the vector which will be returned that contains the posts that carry the word we want to search
    for (int i = 0; i < n; i++)  //loop over all the posts
    {
        if (KMPSearch(word, Posts[i]->Body))  //check if the word is in a body of the post 
        {
            posts_found.push_back(Posts[i]);  //add the reference to the post in the returned vector
        }
        else
        {
            for (int j = 0; j < Posts[i]->Topics.size(); j++)    //loop on topics in a given post
            {
                
                if (word == Posts[i]->Topics[j])      //check if the word exists in the topics
                {
                    posts_found.push_back(Posts[i]);  //add the reference to the post in the returned vector
                    break;          
                }
            }
        }

    }
    return posts_found;
}

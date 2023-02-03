#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "xml.h"
using namespace std;


void computeLPSArray(string pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {
     
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else 
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

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


vector<Post*> Post_Search(string word, vector<Post*> Posts)
{
    int n = Posts.size();
    vector<Post*> posts_found;
    for (int i = 0; i < n; i++)
    {
        if (KMPSearch(word, Posts[i]->Body))
        {
            posts_found.push_back(Posts[i]);
        }
        else
        {
            for (int j = 0; j < Posts[i]->Topics.size(); j++)
            {
                
                if (word == Posts[i]->Topics[j])
                {
                    posts_found.push_back(Posts[i]);
                    break;
                }
            }
        }

    }
    return posts_found;
}
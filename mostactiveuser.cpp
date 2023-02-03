#include <iostream>
#include <vector>
using namespace std;

//This function finds the node with the most follows in a social network represented by an adjacency matrix.
int getMostActiveUser(vector<vector<int>> adjacencyMatrix) {
    int nodeWithMostFollows = 0;
    int maxFollows = 0;
    for (int i = 0; i < adjacencyMatrix.size(); i++) { //looping on all columns (i)
        int follows = 0;
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) { // looping through each row j and counts the number of follows by summing up the values in the column.
            follows += adjacencyMatrix[j][i];
        }
        if (follows > maxFollows) {  //if the number of follows for the current node is greater than the current maxFollows, it updates maxFollows and nodeWithMostFollows to the new values
            maxFollows = follows;
            nodeWithMostFollows = i;
        }
    }
    return nodeWithMostFollows;
}

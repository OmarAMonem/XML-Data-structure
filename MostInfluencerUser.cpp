#include "Graph.h"

//This function finds the node with the most followers in a social network represented by an adjacency matrix.
int getMostInfluencerUser(vector<vector<int>> adjacencyMatrix) {
    int nodeWithMostFollowers = 0;
    int maxFollowers = 0;
    for (int i = 0; i < adjacencyMatrix.size(); i++) { //looping on all rows( nodes )
        int followers = 0;
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) { //looping through each column j to count the number of followers of each node by summing up the values in the row.
            followers += adjacencyMatrix[i][j];
        }
        if (followers > maxFollowers) {  //If the number of followers for the current node is greater than the current maxFollowers, it updates maxFollowers and nodeWithMostFollowers to the new values
            maxFollowers = followers;
            nodeWithMostFollowers = i;
        }
    }
    return nodeWithMostFollowers;
}

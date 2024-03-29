#include "Graph.h"

//This is a Function that takes the Id of a certain user and returns a lists of Suggested Users
vector<int> get_suggested_users(int id, vector<vector<int>> adjacencyMatrix) {
    vector<int> suggested_users;                                           //initializing a vector named "Suggested Users" to store all the suggested followers.
    int index = id - 1;                                                    //variable “index” equal to the id -1.
    for (int i = 0; i < adjacencyMatrix.size(); i++) {                    //iterating to find the indices of all the nodes that follows the node whose ID was passed as a parameter.
        if (adjacencyMatrix[index][i] == 1) {                             // if adjacencyMatrix[index][i] is equal to 1, it means that i is following index
            for (int j = 0; j < adjacencyMatrix[i].size(); j++) {       //iterating  to find the followers of the followers and pushing them in the Suggested Users Vector
                if (adjacencyMatrix[i][j] == 1 && index != j && i != j) {
                    suggested_users.push_back(j);
                }
            }
        }
    }
    sort(suggested_users.begin(), suggested_users.end());  //sorting the Vector
    suggested_users.erase(unique(suggested_users.begin(), suggested_users.end()), suggested_users.end()); //removing the Duplicates From the Suggested Users
    
    for (int i = 0; i < suggested_users.size(); i++)  //checking if the suggested users obtained are from the followers and add them to the result
    {
        flag = 0;
        for (int j = 0; j < followers.size(); j++)
        {
            if (suggested_users[i] == followers[j])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            result.push_back(suggested_users[i]);
        }
    }

    return result;
}
}

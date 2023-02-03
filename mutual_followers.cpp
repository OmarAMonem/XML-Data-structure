#include "Graph.h"

// The method takes the first user ID, the second user ID, 
// and the adjacency matrix which represents the graph of the XML file as parameters
vector<int> mutual_followers(int user1Id, int user2Id, vector<vector<int>> adjacencyMatrix)
{
	vector <int> result;
	// We loop over the rows numbers that equal users’ ID parameters – 1.
	for (int i = 0; i < adjacencyMatrix[user1Id].size(); i++)
	{
		// If the two users (rows) have Ones in the same column, 
		// then the user whose ID is equal to the column number + 1 is considered a mutual follower for the two users.
		if (adjacencyMatrix[user1Id - 1][i] == 1 && adjacencyMatrix[user2Id - 1][i] == 1)
		{
			// we push the column number to a vector.
			result.push_back(i);
		}
	}
	// return the vector which contains the number of columns that represent the IDs of mutual followers – 1.
	return result;
}

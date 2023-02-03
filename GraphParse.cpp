#include "Graph.h"

Graph Graph_Parse(string inputString)
{
    Graph graph;
    Post* post = nullptr;
    User_Node* newNode = nullptr;
    string User_tag, data;
    string start_of_tag = "<";
    string end_of_tag = ">";
    int FollowerFlag = 0, user_flag = 0;
    unsigned int start_tag_index = 0, end_tag_index;

    start_tag_index = inputString.find(start_of_tag, start_tag_index); // find the index of the < in the first tag
    end_tag_index = inputString.find(end_of_tag, start_tag_index);     // find the index of the > in the first tag
    

    while (inputString.find(start_of_tag, end_tag_index) != string::npos) // loop all over the xml string till the end
    {
        User_tag = inputString.substr(start_tag_index + 1, end_tag_index - start_tag_index - 1); // extract the tag name from the xml ex: <tagname>
        start_tag_index = inputString.find(start_of_tag, end_tag_index); //find the next "<"
        data = inputString.substr(end_tag_index + 1, start_tag_index - end_tag_index - 1);
           
        if (User_tag[0] != '/') // if starting tage found. ex. <tagname>
        {
            if (start_tag_index != string::npos)
            {
                if (User_tag == "user") //check if user tagname
                {
                    newNode = new User_Node;
                    graph.addUser(newNode);     //insert the newNode in the graph
                }
                else if (User_tag == "id")
                {
                    if (FollowerFlag == 1)      //check if follower
                    {
                        newNode->addFollower(data);     //add the follower of the user
                        FollowerFlag = 0;
                    }
                    else
                    {
                        newNode->setId(data);   //set id of the user
                    }
                }
                else if (User_tag == "name")
                {
                    newNode->setName(data);     //set name of the user
                }
                else if (User_tag == "post")    
                {
                    post = graph.addPost();     //add the post the array of posts in the graph
                }
                else if (User_tag == "body")
                {
                    post->setBody(data);        //set the body of the post
                }
                else if (User_tag == "topic")
                {
                    data.erase(std::remove(data.begin(), data.end(), '\n'), data.end()); //remove "\n" from the data extracted
                    data.erase(std::remove(data.begin(), data.end(), ' '), data.end());  //remove " " from the data extracted
                    post->addTopic(data);       //add the data(topic) in the array of topics of the post
                }
                else if (User_tag == "follower")
                {
                    FollowerFlag = 1;           //raise a flag to indicate that the next id tag is a follower not the user id
                }
            }
        }
        end_tag_index = inputString.find(end_of_tag, start_tag_index); // get index of ">" of the next tag
    }
    graph.addEdges(graph.users);     //Construct the adjacency matrix of the graph
    return graph;
}

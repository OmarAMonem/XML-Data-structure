#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Post
{
public:
    string Body;
    vector<string> Topics;

    Post()
    {
    }

    void setBody(string body)
    {
        this->Body = body;
    }

    void addTopic(string topic)
    {
        Topics.push_back(topic);
    }

    ~Post()
    {
    }
};

class User_Node
{
public:
    string id;
    string name;
    vector<string> followers;


    User_Node()
    {
    }

    void setId(string id)
    {
        this->id = id;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void addFollower(string follower)
    {
        followers.push_back(follower);
    }

    ~User_Node()
    {
    }

};

class Graph
{
public:
    vector<User_Node*> users;
    vector<vector<int>> Adjacency_Matrix;
    vector<Post*> Posts;

    Graph()
    {
    }

    void addUser(User_Node* user)
    {
        users.push_back(user);
    }

    void addEdges(vector<User_Node*> users)
    {
        int n = users.size();
        int row = 0, i = 0;
        int col = 0, j = 0;
        this->Adjacency_Matrix.resize(n, vector<int>(n)); // matrix n*n all zeroes
        while (i < n)
        {
            row = i;
            j = 0;
            while (j < (users[i]->followers.size()))
            {
                col = stoi(users[i]->followers[j]) - 1;
                this->Adjacency_Matrix[row][col] = 1;
                j++;
            }
            i++;
        }
    }

    Post* addPost()
    {
        Post* post = new Post;
        Posts.push_back(post);
        return post;
    }

    ~Graph()
    {
    }
};


#endif
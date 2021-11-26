#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class User
{
public:
	static int numUsers;
	string name;
	string userID;
	unsigned int age;

	//====Creation and Destruction====
	User();
	User(string _name, int _age);
	static string makeID(int num);
};
class Graph
{
	unsigned int numVertices;
	unordered_map<string, User*> lookupID;

	/*
	Graph is implemented using an adjacency list that stores pointers to each user.
	unordered_set used for easy find(), no repeats allowed 
	*/
	unordered_map<User*, unordered_set<User*>> adjList;

public:
	//====Creation and Destruction====
	Graph();
	//====Getters and Setters====
	unsigned int Vertices() { return numVertices; };
	//====Insertion and Deletion====
	bool insertVertex(User& user);
	bool insertEdge(User& user1, User& user2); //could add a friendship factor (0-1) for Dijktras...?

	//====Standard Algorithms====

};

/*USER==================CREATION AND DESTRUCTION=================================*/
User::User()
{
	name = "";
	age = -1;
	userID = makeID(++numUsers);
}
User::User(string _name, int _age)
{
	name = _name;
	age = _age;
	userID = makeID(++numUsers);
}
string User::makeID(int num)
{
	return to_string(num); //Will probably be changed later based on needs
}
int User::numUsers = 0;

/*GRAPH===================CREATION AND DETRUCTION==============================*/
Graph::Graph()
{
	numVertices = 0;
}

/*GRAPH=====================INSERTION AND DELETION==============================*/
bool Graph::insertVertex(User& user)
{
	if (lookupID.find(user.userID) != lookupID.end())
	{
		return false; //user already in graph
	}
	else
	{
		lookupID[user.userID] = &user;
		numVertices++;
		return true;
	}
}
bool Graph::insertEdge(User& user1, User& user2)
{
	if (adjList[&user1].find(&user2) != adjList[&user1].end() && adjList[&user2].find(&user1) != adjList[&user2].end())
	{
		return false; //edge already exists
	}
	else
	{
		insertVertex(user1);
		insertVertex(user2);
		adjList[&user1].insert(&user2);
		adjList[&user2].insert(&user1);
		return true;
	}
		// addd two vertices to graph
		// add edge to adj list
}
int main()
{
	Graph theg;
	User user1("Allen", 20);
	User user2("Logan", 21);
	User user3("Jake", 19);
	theg.insertEdge(user1, user2);
	theg.insertEdge(user2, user3);
	theg.insertEdge(user1, user3);
	return 0;
}

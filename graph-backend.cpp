#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
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
	unordered_map<User*, unordered_map<User*, double>> adjList;

public:
	//====Creation and Destruction====
	Graph();
	//====Getters and Setters====
	unsigned int Vertices() { return numVertices; };
	bool isEdge(User& user1, User& user2);
	vector<User*> getAdjacent(User& user);
	double FriendFactor(User& user1, User& user2);
	//====Insertion and Deletion====
	bool insertVertex(User& user);
	bool insertEdge(User& user1, User& user2, double friendFactor); //could add a friendship factor (0-1) for Dijktras...?

	//====Standard Algorithms====
	//BFS to find if name exists
	//Perhaps a highest friendship factor search to find good names?
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

/*GRAPH=====================GETTERS AND SETTERS=================================*/
bool Graph::isEdge(User& user1, User& user2) //asssumes vertices are valid, could change
{
	if (adjList[&user1].find(&user2) != adjList[&user1].end() && adjList[&user2].find(&user1) != adjList[&user2].end())
	{
		return true; //edge already exists
	}
	else
		return false;
}
double Graph::FriendFactor(User& user1, User& user2)
{
	if (this->isEdge(user1, user2))
	{
		return adjList[&user1].at(&user2);
	}
	else
		return 0;
}
vector<User*> Graph::getAdjacent(User& user)
{
	if (lookupID.find(user.userID) != lookupID.end())
	{
		vector<User*> retVec;
		for (auto it = adjList[&user].begin(); it != adjList[&user].end(); ++it)
		{
			retVec.push_back((*it).first);
		}
		return retVec;
	}
	else
		return vector<User*>();
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
bool Graph::insertEdge(User& user1, User& user2, double friendFactor)
{
	if (this->isEdge(user1, user2))
	{
		return false; //edge already exists
	}
	else
	{
		// add two vertices to graph
		// add edge to adj list
		insertVertex(user1);
		insertVertex(user2);
		adjList[&user1].emplace(&user2, friendFactor);
		adjList[&user2].emplace(&user1, friendFactor);
		return true;
	}
}
// IGNORE BELOW, USED FOR TESTING========================================================================================
int main()
{
	Graph theg;
	User user1("Allen", 20);
	User user2("Logan", 21);
	User user3("Jake", 19);
	theg.insertEdge(user1, user2, 1);
	theg.insertEdge(user2, user3, 2);
	theg.insertEdge(user1, user3, 3);
	auto l = theg.getAdjacent(user1);
	for (unsigned int i = 0; i < l.size(); i++)
		 cout << l.at(i)->name << std::endl;
	return 0;
}

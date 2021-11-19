#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class User
{
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
	unordered_map<User, vector<User>> adjList;


	//====Creation and Destruction====
	Graph();
	~Graph();
	//====Getters and Setters====
	unsigned int numVertices() { return numVertices; };
	//====Insertion and Deletion====

	//====Standard Algorithms====

};

//==================CREATION AND DESTRUCTION=================================
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

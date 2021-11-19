#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class User
{
	string name;
	string userID;
	unsigned int age;

	//====Creation and Destruction====
	User();
	User(string name, string age);
};
class Graph
{
	unsigned int numVertices;
	unordered_map<string, unsigned int> vertLookup; //matches a string ID (obj attribute) to a vertex index
	unordered_map<unsigned int, vector<int>> adjList; //connects vertices to other vertices
	unordered_map<unsigned int, User*> userLookup; //match a vertex to a person object

	/* im thinking like userLookup[adjList[vertLookup["bobert"]].at(0)]
	*  Tracks from name to index to neighbor index to user 
	* */

	//====Creation and Destruction====
	Graph();
	~Graph();
	//====Getters and Setters====

	//====Insertion and Deletion====

	//====Standard Algorithms====

};
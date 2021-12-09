//Misc
#include <iostream>
#include <string>
#include <algorithm>

//STL Data Containers
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <stack>
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
	// possible a "You" User* variable, for whom the program works on primarily

	/*
	Graph is implemented using an adjacency list that stores pointers to each user.
	unordered_map used for easy find(), no repeats allowed 
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
	pair<User*, unsigned int> breadthFirstSearch(string target, User& source, unsigned int maxDepth);
	vector<pair<User*, double>> dijkstra(User& source);
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

/*=======================STANDARD ALGORITHMS====================================*/

/*This algorithm conducts a breadth first search for a target name, starting from source (usually yourself),
* up to maxDepth connections deep. Users further from the source than maxDepth are ignored.
* Returns a pair with the target, and the number of connections from the source */
pair<User*, unsigned int> Graph::breadthFirstSearch(string target, User& source, unsigned int maxDepth)
{
	unordered_set<User*> touched; //tracks vertices that have already been hit by the traversal
	queue<pair<User*, unsigned int>> q; //tracks nodes that need to be analyzed next, second value tracks depth of node
	q.push(make_pair(&source, 0));
	while (!q.empty())
	{
		if (q.front().first->name == target)
			return q.front();
		touched.insert(q.front().first);
		auto adjacent = adjList[q.front().first];
		unsigned int depthOfNode = q.front().second;
		if (depthOfNode < maxDepth) //do not add further vertices if we are already at maxDepth
		{
			for (auto it = adjacent.begin(); it != adjacent.end(); ++it) //for each item in this nodes adjacency list
			{
				if (touched.find((*it).first) == touched.end())
				{
					q.push(make_pair((*it).first, depthOfNode + 1));
					touched.insert((*it).first);
				}
			}
		}
		q.pop();
	}
	return make_pair(nullptr, 0); //no user with name found
}

// used by sort function in dijkstra to sort the distances
bool pairCompareFc(pair<User*, double> i, pair<User*, double> j) { return (i.second < j.second); }

/*This algorithm returns a sorted list of users by shortest path (sum of friendship factors) to the source.*/
vector<pair<User*, double>> Graph::dijkstra(User& source)
{
	// Four main data structures to solve problem
	priority_queue<pair<double, User*>, vector<pair<double, User*>>, greater<pair<double, User*>>> pq; //distance to source
	unordered_map<User*, double> d;
	//vector<double> d(numVertices, INT_MAX);
	unordered_map<User*, User*> p; //predecessor
	//unordered_set<User*> computed;
	//unordered_set<User*> notComputed;
	//add all vertices to notComputed and update map to set all vertices to infinity
	for (auto it = lookupID.begin(); it != lookupID.end(); ++it)
	{
		d.insert(make_pair((*it).second, INFINITY));
	}
	//Process the source
	pq.push(make_pair(0, &source));
	p[&source] = nullptr;
	d[&source] = 0;
	
	//main iterative loop
	while (!pq.empty())
	{
		auto v = pq.top();
		pq.pop();
		//relax all adjacent vertices //check this ->
		for (auto k : adjList.at(v.second))
		{
			if (k.second + d[v.second] < d[k.first])
			{
				d[k.first] = k.second + d[v.second];
				p[k.first] = v.second; //update predecessor
				pq.push(make_pair(k.second + d[v.second], k.first));
			}
		}
		//cout << v << endl;
		//computed.insert(v.second);
		//notComputed.erase(v.second);
		//for (auto it = notComputed.begin(); it != notComputed.end(); ++it)
		//{
		//    cout << *it << " ";
		//}
		//cout << endl;
	}

	// sort and iterate O(n + nlog(n))
	vector<pair<User*, double>> retVec;
	for (auto it = d.begin(); it != d.end(); ++it)
		retVec.push_back(make_pair((*it).first, (*it).second));
	std::sort(retVec.begin(), retVec.end(), pairCompareFc);
	return retVec;
}

int main()
{
	Graph theg;
	//Verts
	User A("A", 1);
	User B("B", 1);
	User C("C", 1);
	User D("D", 1);
	User E("E", 1);
	User F("F", 1);
	User G("G", 1);
	User H("H", 1);
	User I("I", 1);
	//Edges
	theg.insertEdge(A, B, 4);
	theg.insertEdge(A, H, 8);
	theg.insertEdge(B, H, 11);
	theg.insertEdge(B, C, 8);
	theg.insertEdge(C, D, 7);
	theg.insertEdge(C, F, 4);
	theg.insertEdge(C, I, 2);
	theg.insertEdge(D, E, 9);
	theg.insertEdge(D, F, 14);
	theg.insertEdge(E, F, 10);
	theg.insertEdge(F, G, 2);
	theg.insertEdge(G, H, 1);
	theg.insertEdge(G, I, 6);
	theg.insertEdge(H, I, 7);
	//Algo
	//auto x = theg.breadthFirstSearch("I", A, 3);
	//auto y = theg.breadthFirstSearch("E", A, 2);
	//cout << endl;
	auto vec = theg.dijkstra(A);
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		cout << vec.at(i).first->name << ": " << vec.at(i).second << endl;
	}
	return 0;
}

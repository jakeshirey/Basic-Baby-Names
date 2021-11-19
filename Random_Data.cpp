#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

class CSVReader {
    string fileName;
public:
    CSVReader(string filename){
        fileName = filename;
    }
    vector<string> getData();
};
vector<string> CSVReader::getData() {
    ifstream file(fileName);
    vector<string> dataList;
    string line = "";
    while (getline(file, line)){
        dataList.push_back(line);
    }
    file.close();
    return dataList;
}


int main() {
    CSVReader reader("/Users/rachelfenton/Desktop/Names.txt");
    vector<string> names = reader.getData();
    for(string vec : names){
        cout << vec << endl;
    }

    //vector<User> userList;
    for (int i = 0; i < 100000; i++){
        //make a user oject with ID = i, name = names[random # from 1-10,000]

    }
    return 0;
}

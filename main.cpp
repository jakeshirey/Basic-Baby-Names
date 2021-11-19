#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include "LegoList.h"
using namespace std;

int main()
{
	ifstream input;
	bool continueProgram = true;
	cout << std::fixed << setprecision(2);
	while (continueProgram)
	{
		try 
		{
			LegoList* list = new LegoList();
			cout << "Which file(s) to open?\n";
			cout << "1. lego1.csv" << endl;
			cout << "2. lego2.csv" << endl;
			cout << "3. lego3.csv" << endl;
			cout << "4. All 3 files" << endl;
			int option;
			cin >> option;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (option > 4 || option == 0)
			{
				throw out_of_range("Invalid input. Please enter an integer 1-4.");
			}
			if (option == 1)
			{
				input.open("lego1.csv");
				list->UploadFile(input, "lego1.csv");
			}
			else if (option == 2)
			{
				input.open("lego2.csv");
				list->UploadFile(input, "lego2.csv");

			}
			else if (option == 3)
			{
				input.open("lego3.csv");
				list->UploadFile(input, "lego3.csv");

			}
			else if (option == 4)
			{
				input.open("lego1.csv");
				list->UploadFile(input, "lego1.csv");
				input.close();
				input.open("lego2.csv");
				LegoList* list2 = new LegoList();
				list2->UploadFile(input, "lego2.csv");
				input.close();
				list->AddLegoList(list2);
				input.open("lego3.csv");
				LegoList* list3 = new LegoList();
				list3->UploadFile(input, "lego3.csv");
				input.close();
				list->AddLegoList(list3);
			}
			cout << "Total number of sets: " << list->numSets << endl;
			
			cout << "1. Most Expensive set" << endl;
			cout << "2. Largest piece count" << endl;
			cout << "3. Search for set name containing..." << endl;
			cout << "4. Search themes..." << endl;
			cout << "5. Part count information" << endl;
			cout << "6. Price information" << endl;
			cout << "7. Minifigure information" << endl;
			cout << "8. If you bought one of everything..." << endl;
			cout << "0. Exit" << endl;

			int choice;
			cin >> choice;
			cin.get();// Clear newline character for any later input
			if (choice > 8)
			{
				throw out_of_range("Invalid input. Please enter an integer 0-8.");
			}
			if (choice == 0)
			{
				cout << "Exiting program." << endl;
			}
			if (choice == 1)
			{
				LegoList::LegoSet* exp = list->MostExpensive();
				cout << "The most expensive set is: " << endl;
				LegoList::PrintLegoSet(exp);
			}
			if (choice == 2)
			{
				LegoList::LegoSet* most = list->MostPieces();
				cout << "The set with the highest parts count: " << endl;
				LegoList::PrintLegoSet(most);
			}
			if (choice == 3)
			{
				string term;
				getline(cin, term);
				cin.get();
				vector<LegoList::LegoSet*> matches = list->SearchName(term);
				if (matches.size() == 0)
				{
					cout << "No sets found matching that search term" << endl;
				}
				else
				{
					cout << "Sets matching \"" << term << "\":" << endl;
					for (unsigned int i = 0; i < matches.size(); i++)
					{
						LegoList::QuickPrint(matches.at(i));
					}
				}
			}
			if (choice == 4)
			{
				string term;
				getline(cin, term);
				cin.get();
				vector<LegoList::LegoSet*> matches = list->SearchTheme(term);
				if (matches.size() == 0)
				{
					cout << "No sets found matching that search term" << endl;
				}
				else
				{
					cout << "Sets matching \"" << term << "\":" << endl;
					for (unsigned int i = 0; i < matches.size(); i++)
					{
						LegoList::QuickPrint(matches.at(i));
					}
				}
			}
			if (choice == 5)
			{
				cout << "Average part count for " << list->numSets << " sets: " << list->AveragePartCount() << endl << endl;
			}
			if (choice == 6)
			{
				cout << "Average price for " << list->numSets << " sets: $" << list->AveragePrice() << endl << endl;
				LegoList::LegoSet* most = list->MostExpensive();
				LegoList::LegoSet* least = list->LeastExpensive();
				cout << "Least expensive set: " << endl;
				LegoList::PrintLegoSet(least);
				cout << endl;
				cout << "Most expensive set: " << endl;
				LegoList::PrintLegoSet(most);

			}
			if (choice == 7)
			{
				cout << "Average number of minifigures: " << list->AverageMinifigs() << endl << endl;
				LegoList::LegoSet* most = list->MostMinifigs();
				cout << "Set with the most minifigures:" << endl;
				LegoList::PrintLegoSet(most);
			}
			if (choice == 8)
			{
				cout << "If you bought one of everything..." << endl;
				cout << "It would cost: $" << list->TotalPrice << endl;
				cout << "You would have " << list->TotalPartCount() << " pieces in your collection" << endl;
				cout << "You would have an army of " << list->TotalMinifigs() << " minifigures!" << endl;
			}
			/*======= Based on the choice, execute the appropriate task and show the results =======*/
			continueProgram = false; //THIS IS THE LAST LINE OF THE TRY BLOCK NO MATTER WHAT
			// executing a statement below this line means you fucked up
		}
		catch (out_of_range& e)
		{
			cout << e.what() << endl;
		}
		catch (invalid_argument& e)
		{
			cout << e.what() << endl;
		}
	}
	return 0;
}
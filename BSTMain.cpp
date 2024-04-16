#include "BST.hpp"
#include "Book.hpp"
#include "Library.hpp"
#include <iostream>
using namespace std;

int main() {
	// Testing book comparisons
	Book b1("Acorns", "Shmoe, Joe", 1984, "Science Books", 12345, 3.5);
	Book b2("Birch Trees","Shmoe, Joe",2019, "Science Books",34567,4.0);
	Book b3("Dogs Are My Best Friend","David, Alex",2006, "Books for Children",22222,4.0);
	cout << (b1 < b1);
	cout << (b1 < b2);
	cout << (b1 < b3);
	cout << (b1 == b1);
	cout << (b1 == b2);
    cout << (b1 != b3);
	cout << (b1 > b1);
	cout << (b1 > b2);
    cout << (b1 > b3);
	cout << (b1 <= b1);
	cout << (b1 <= b2);
	cout << (b1 <= b3);
	cout << (b1 >= b1);
	cout << (b1 >= b2);
	cout << (b1 >= b3);

	Library library("C:\\Users\\clock\\OneDrive - University of Delaware - o365\\Sophomore Spring 2024\\CISC220\\BTSLibaray-1\\halloween.txt");
	library.menu();


	return 0;
}

//Connor Lockwood and Thomas Boston
#include "Book.hpp"

#include <iostream>
#include <string>
using namespace std;


Book::Book(string t, string auth, int yr, string pub, long long isbn, float rate) {
	title = t;
	author = auth;
	year = yr;
	publisher = pub;
	isbn13 = isbn;
	rating = rate;
	checked_out = false;
}

Book::Book() {
	title = "";
	author = "";
	year = 0;
	publisher = "";
	isbn13 = 0;
	rating = 0;
	checked_out = false;
}

float Book::getRating() {
	return rating;
}


void Book::printBook() {
	cout << "---------------------" << endl;
	cout << title << "\nAuthor: " << author << "\t\tYear: " << year << endl;
	cout << "Publisher: " << publisher << "\tISBN-13: " << isbn13 << "\tRating: " << rating << endl;
	cout << "Currently Available: " << (checked_out ? "No" : "Yes") << endl;
}

bool Book::operator<(Book b2) {
    if(author == b2.author){
        return title < b2.title;
    } else{
        return author < b2.author;
    }
}

bool Book::operator>(Book b2) {
    if(author == b2.author){
        return title > b2.title;
    } else{
        return author > b2.author;
    }
}

bool Book::operator==(Book b2) {
    return(author == b2.author && title == b2.title);
}

bool Book::operator!=(Book b2) {
    return(author != b2.author || title != b2.title);
}

bool Book::operator<=(Book b2) {
    if(author == b2.author){
        return title <= b2.title;
    } else{
        return author <= b2.author;
    }
}

bool Book::operator>=(Book b2) {
    if(author == b2.author){
        return title >= b2.title;
    } else{
        return author >= b2.author;
    }
}

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to create a 4D dynamic array and fill it with random lowercase letters
char**** CreateBookshelf(int *p, int *q, int *r, int *s, int *i, int *j, int *k, int *l) {
    char**** bookshelf = new char***[*p];
    for (*i = 0; *i < *p; (*i)++) {
        bookshelf[*i] = new char**[*q];
        for (*j = 0; *j < *q; (*j)++) {
            bookshelf[*i][*j] = new char*[*r];
            for (*k = 0; *k < *r; (*k)++) {
                bookshelf[*i][*j][*k] = new char[*s];
                for (*l = 0; *l < *s; (*l)++) {
                    bookshelf[*i][*j][*k][*l] = 'a' + rand() % 26; // Fill with random lowercase letters
                }
            }
        }
    }
    return bookshelf;
}

// Function to display the contents of the bookshelf
void Display(char**** bookShelf, int *p, int *q, int *r, int *s, int *i, int *j, int *k, int *l) {
    for (*i = 0; *i < *p; (*i)++) {
        cout << "BOOK " << *i << endl;
        for (*j = 0; *j < *q; (*j)++) {
            cout << "Page " << *j << endl;
            for (*k = 0; *k < *r; (*k)++) {
                for (*l = 0; *l < (*s - 1); (*l)++) {
                    cout << bookShelf[*i][*j][*k][*l] << ", ";
                }
                cout << bookShelf[*i][*j][*k][(*s - 1)] <<  endl;
            }
        }
    }
}

// Function to search for a character in the bookshelf
int* Search(char**** bookShelf, int *p, int *q, int *r, int *s, char *c, int *i, int *j, int *k, int *l) {
    int* count = new int(0);
    for (*i = 0; *i < *p; (*i)++) {
        for (*j = 0; *j < *q; (*j)++) {
            for (*k = 0; *k < *r; (*k)++) {
                for (*l = 0; *l < *s; (*l)++) {
                    if (bookShelf[*i][*j][*k][*l] == *c) {
                        (*count)++;
                    }
                }
            }
        }
    }
    return count;
}

// Function to deallocate memory for the bookshelf
void DeallocateBookshelf(char**** &bookShelf, int *p, int *q, int *r, int *i, int *j, int *k) {
    for (*i = 0; *i < *p; (*i)++) {
        for (*j = 0; *j < *q; (*j)++) {
            for (*k = 0; *k < *r; (*k)++) {
                delete[] bookShelf[*i][*j][*k];
            }
            delete[] bookShelf[*i][*j];
        }
        delete[] bookShelf[*i];
    }
    delete[] bookShelf;
    bookShelf = nullptr;
}

int main() {
    srand(time(0));

    int *p = new int(2); // Number of books
    int *q = new int(3); // Number of pages per book
    int *r = new int(2); // Number of lines per page
    int *s = new int(3); // Number of characters per line

    int *i = new int(0);
    int *j = new int(0);
    int *k = new int(0);
    int *l = new int(0);
    
    char**** bookShelf = CreateBookshelf(p, q, r, s, i, j, k, l);

    Display(bookShelf, p, q, r, s, i, j, k, l);

    char* searchChar = new char('a'); // Character to search for
    int* count = Search(bookShelf, p, q, r, s, searchChar, i, j, k, l);
    cout << "Character '" << *searchChar << "' appears " << *count << " times in the bookshelf." << endl;

    DeallocateBookshelf(bookShelf, p, q, r, i, j, k);

    if(p != nullptr){
        delete p;
        p = nullptr;
    }

    if(q != nullptr){
        delete q;
        q = nullptr;
    }

    if(r != nullptr){
        delete r;
        r = nullptr;
    }

    if(s != nullptr){
        delete s;
        s = nullptr;
    }

    if(searchChar != nullptr){
        delete searchChar;
        searchChar = nullptr;
    }

    if(count != nullptr){
        delete count;
        count = nullptr;
    }

    if(i != nullptr){
        delete i;
        i = nullptr;
    }

    if(j != nullptr){
        delete j;
        j = nullptr;
    }

    if(k != nullptr){
        delete k;
        k = nullptr;
    }

    if(l != nullptr){
        delete l;
        l = nullptr;
    }

    return 0;
}

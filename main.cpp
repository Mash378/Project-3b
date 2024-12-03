#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue> 

using namespace std;

struct Book {
    string title;
    string author;
    string genre;
    double rating;
};

vector<Book> loadBooksFromFile() {
    vector<Book> books;
    ifstream inFile("books.txt", ios::in);  // Open a file for reading
    
    if (!inFile) {  // check if the file was successfully opened
        cerr << "Error opening file for reading." << endl;
        return books;
    }

    Book tempBook;
    while (getline(inFile, tempBook.title) && 
           getline(inFile, tempBook.author) &&
           getline(inFile, tempBook.genre) &&
           inFile >> tempBook.rating) {
        inFile.ignore();  // to ignore the newline after reading the rating
        books.push_back(tempBook);  // Add the book to the list
    }

    inFile.close();  // close the file after reading
    cout << "Books loaded from file successfully." << endl;
    return books;
}

void displayBooks(const vector<Book>& books) {
    for (const auto& book : books) {
        cout << "Title: " << book.title << ", Author: " << book.author
             << ", Genre: " << book.genre << ", Rating: " << book.rating << endl;
    }
}

class Node {
public:
    Book data;
    Node* left;
    Node* right;

    Node(Book b) : data(b), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, Book book) {
        if (node == nullptr) {
            return new Node(book);
        }
        if (book.title < node->data.title) {
            node->left = insert(node->left, book);
        } else {
            node->right = insert(node->right, book);
        }
        return node;
    }

    void inorder(Node* node, std::vector<Book>& books) {
        if (node != nullptr) {
            inorder(node->left, books);
            books.push_back(node->data);
            inorder(node->right, books);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(Book book) {
        root = insert(root, book);
    }

    std::vector<Book> searchSimilarBooks(bool bfs = true) {
        std::vector<Book> books;
        if (bfs) {
            queue<Node*> q;
            if (root) q.push(root);
            while (!q.empty()) {
                Node* current = q.front();
                q.pop();
                books.push_back(current->data);
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
        } else {
            inorder(root, books);
        }
        return books;
    }
};

int main() {
    vector<Book> books = loadBooksFromFile();
    BST bst;

    for (const auto& book : books) {
        bst.insert(book);
    }

    vector<Book> sortedBooks = bst.searchSimilarBooks(false);  // DFS (Inorder)
    displayBooks(sortedBooks);

    vector<Book> bfsBooks = bst.searchSimilarBooks(true);  // BFS
    displayBooks(bfsBooks);

    return 0;
}

/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
class Book {
private:
    std::string title;
    std::string author;
    int year;

public:
    Book(std::string t, std::string a, int y) : title(t), author(a), year(y) {}

    std::string getTitle() const {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }

    int getYear() const {
        return year;
    }

    void displayBook() const {
        std::cout << std::setw(25) << std::left << title
                  << std::setw(25) << std::left << author
                  << std::setw(6) << std::right << year << std::endl;
    }
};

class TreeNode {
public:
    Book book;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Book b) : book(b), left(nullptr), right(nullptr) {}
};

class Library {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* root, Book book) {
        if (root == nullptr) {
            return new TreeNode(book);
        }

        if (book.getTitle() < root->book.getTitle()) {
            root->left = insert(root->left, book);
        } else if (book.getTitle() > root->book.getTitle()) {
            root->right = insert(root->right, book);
        }

        return root;
    }

    TreeNode* search(TreeNode* root, const std::string& title) {
        if (root == nullptr || root->book.getTitle() == title) {
            return root;
        }

        if (title < root->book.getTitle()) {
            return search(root->left, title);
        } else {
            return search(root->right, title);
        }
    }

    void inorderTraversal(TreeNode* root) {
        if (root != nullptr) {
            inorderTraversal(root->left);
            root->book.displayBook();
            inorderTraversal(root->right);
        }
    }

    void deleteTree(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }

    void saveTreeToFile(std::ofstream& outFile, TreeNode* root) {
        if (root != nullptr) {
            outFile << root->book.getTitle() << ","
                    << root->book.getAuthor() << ","
                    << root->book.getYear() << std::endl;

            saveTreeToFile(outFile, root->left);
            saveTreeToFile(outFile, root->right);
        }
    }

public:
    Library() : root(nullptr) {}

    ~Library() {
        deleteTree(root);
    }

    void addBook(Book book) {
        root = insert(root, book);
    }

    void searchBook(const std::string& title) {
        TreeNode* result = search(root, title);
        if (result != nullptr) {
            std::cout << "Book Found - ";
            result->book.displayBook();
        } else {
            std::cout << "Book Not Found" << std::endl;
        }
    }

    void displayBooks() {
        std::cout << std::setw(25) << std::left << "Title"
                  << std::setw(25) << std::left << "Author"
                  << std::setw(6) << std::right << "Year" << std::endl;

        std::cout << "-----------------------------------------------------------\n";
        inorderTraversal(root);
    }

    void deleteBook(const std::string& title) {
        TreeNode* parent = nullptr;
        TreeNode* current = root;

        while (current != nullptr && current->book.getTitle() != title) {
            parent = current;
            if (title < current->book.getTitle()) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (current == nullptr) {
            std::cout << "Book Not Found" << std::endl;
            return;
        }

        if (current->left == nullptr && current->right == nullptr) {
            if (parent != nullptr) {
                if (parent->left == current) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            } else {
                root = nullptr;
            }

            delete current;
        } else if (current->left == nullptr || current->right == nullptr) {
            TreeNode* temp = (current->left != nullptr) ? current->left : current->right;
            if (parent != nullptr) {
                if (parent->left == current) {
                    parent->left = temp;
                } else {
                    parent->right = temp;
                }
            } else {
                root = temp;
            }

            delete current;
        } else {
            TreeNode* successor = current->right;
            TreeNode* successorParent = current;

            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }

            current->book = successor->book;

            if (successorParent->left == successor) {
                successorParent->left = successor->right;
            } else {
                successorParent->right = successor->right;
            }

            delete successor;
        }

        std::cout << "Book Deleted Successfully" << std::endl;
    }

    void saveLibraryToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            saveTreeToFile(outFile, root);
            outFile.close();
            std::cout << "Library data saved to " << filename << std::endl;
        } else {
            std::cout << "Error: Unable to save library data to file" << std::endl;
        }
    }

    void loadLibraryFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            std::string line;
            while (std::getline(inFile, line)) {
                std::istringstream ss(line);
                std::string title, author, year_str;
                std::getline(ss, title, ',');
                std::getline(ss, author, ',');
                std::getline(ss, year_str);

                int year = std::stoi(year_str);
                addBook(Book(title, author, year));
            }

            inFile.close();
            std::cout << "Library data loaded from " << filename << std::endl;
        } else {
            std::cout << "Error: Unable to load library data from file" << std::endl;
        }
    }
};

int main() {
    Library library;

    std::string filename = "library_data.txt";

    library.loadLibraryFromFile(filename);

    int choice;
    do {
        std::cout << "\nChoose an option:" << std::endl;
        std::cout << "1. Add a book" << std::endl;
        std::cout << "2. Search for a book" << std::endl;
        std::cout << "3. Display all books" << std::endl;
        std::cout << "4. Delete a book" << std::endl;
        std::cout << "5. Save library data" << std::endl;
        std::cout << "6. Exit" << std::endl;

        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string title, author;
                int year;

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter title: ";
                std::getline(std::cin, title);

                std::cout << "Enter author: ";
                std::getline(std::cin, author);

                std::cout << "Enter publication year: ";
                std::cin >> year;

                library.addBook(Book(title, author, year));
                break;
            }

            case 2: {
                std::string searchTitle;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter the title of the book to search: ";
                std::getline(std::cin, searchTitle);

                library.searchBook(searchTitle);
                break;
            }

            case 3:
                std::cout << "\nLibrary Contents:" << std::endl;
                library.displayBooks();
                break;

            case 4: {
                std::string deleteTitle;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter the title of the book to delete: ";
                std::getline(std::cin, deleteTitle);

                library.deleteBook(deleteTitle);
                break;
            }

            case 5:
                library.saveLibraryToFile(filename);
                break;

            case 6:
                std::cout << "Exiting..." << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Try again." << std::endl;
                break;
        }
    } while (choice != 6);

    return 0;
}


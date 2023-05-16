#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <thread>
#include <cctype>
#include <algorithm>
#include <limits>
#include <ctime>

using namespace std;

struct Book
{
	string bookID;
	string title;
	string author;
	string genre;
	string publisher;
	string field;
	string keyword;
	int quantity;
	Book *next;
};

struct BanDoc
{
	string keyword;
	string field;
	string IDSV;
	string name;
	string gender;
	string birthdate;
	string cls;
	string number;
	BanDoc *next;
};

struct User
{
	string user;
	string password;
	User *next;
};

BanDoc *headDoc = nullptr;
Book *head = nullptr;
User *headU = nullptr;

string removeSpaces(string str)
{
	str.erase(0, str.find_first_not_of(' '));
	str.erase(str.find_last_not_of(' ') + 1);
	return str;
}

void returnToPreviousFunction()
{
	int input;
	do
	{
		std::cout << "  Enter 0 to return to the previous function: ";
		std::cin >> input;
	} while (input != 0);
	std::cout << "  Exiting.....";
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	system("cls");
	cin.ignore();
}

// book----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void addBook(string bookID, string title, string author, string genre, string publisher, int quantity)
{
	Book *newBook = new Book;
	newBook->bookID = bookID;
	newBook->title = title;
	newBook->author = author;
	newBook->genre = genre;
	newBook->publisher = publisher;
	newBook->quantity = quantity;
	newBook->next = nullptr;
	if (head == nullptr)
	{
		head = newBook;
	}
	else
	{
		Book *temp = head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = newBook;
	}
}

void readFromFile(string filename)
{
	ifstream inFile(filename);
	if (!inFile)
	{
		cout << "  Can't open file" << endl;
		return;
	}

	string line;
	while (getline(inFile, line))
	{
		vector<string> fields;
		stringstream ss(line);
		string field;
		while (getline(ss, field, ';'))
		{
			fields.push_back(field);
		}

		if (fields.size() != 6)
		{
			cout << "  Invalid data format" << endl;
			continue;
		}

		string bookID = fields[0];
		string title = fields[1];
		string author = fields[2];
		string genre = fields[3];
		string publisher = fields[4];
		int quantity = stoi(fields[5]);

		addBook(bookID, title, author, genre, publisher, quantity);
	}

	inFile.close();
}

void displayBook()
{
	Book *temp = head;
	cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
	cout << "| BookID |                       Title                           |               Author               |            Genre           |                    Publisher                  |    Quantity   |" << endl;
	cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
	while (temp != nullptr)
	{
		cout << "| " << setw(6) << left << removeSpaces(temp->bookID) << " | " << setw(53) << left << removeSpaces(temp->title) << " | " << setw(34) << left << removeSpaces(temp->author) << " | "
		 << setw(26) << left << removeSpaces(temp->genre) << " | " << setw(45) << left << removeSpaces(temp->publisher) << " | " << setw(13) << left << temp->quantity << " |" << endl;
		cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
		temp = temp->next;
	}
}

void displaynewBook(string bookID, string title, string author, string genre, string publisher, int quantity)
{
	cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
	cout << "| BookID |                       Title                           |               Author               |            Genre           |                    Publisher                  |    Quantity   |" << endl;
	cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
	cout << "| " << setw(6) << left << bookID << " | " << setw(53) << left << title << " | " << setw(34) << left << author << " | " << setw(26) << left
		 << genre << " | " << setw(45) << left << publisher << " | " << setw(13) << left << quantity << " |" << endl;
	cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
}

void displaynewadjustBook(string newID, string newname_book, string newtacgia, string newtheloai, string newnxb, int newquantity)
{
	cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
	cout << "| BookID |                       Title                           |               Author               |            Genre           |                    Publisher                  |    Quantity   |" << endl;
	cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
	cout << "| " << setw(6) << left << newID << " | " << setw(53) << left << newname_book << " | " << setw(34) << left << newtacgia << " | " << setw(26) << left
		 << newtheloai << " | " << setw(45) << left << newnxb << " | " << setw(13) << left << newquantity << " |" << endl;
	cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
}

vector<Book *> searchBook(string keyword, string field)
{
	vector<Book *> result;
	Book *temp = head;
	while (temp != nullptr)
	{
		if (field == "bookID")
		{
			temp->bookID.erase(0, temp->bookID.find_first_not_of(' '));
			temp->bookID.erase(temp->bookID.find_last_not_of(' ') + 1);
			if (temp->bookID == removeSpaces(keyword))
			{
				result.push_back(temp);
			}
		}
		else if (field == "title")
		{
			temp->title.erase(0, temp->title.find_first_not_of(' '));
			temp->title.erase(temp->title.find_last_not_of(' ') + 1);
			if (temp->title == removeSpaces(keyword))
			{
				result.push_back(temp);
			}
		}
		else if (field == "author")
		{
			temp->author.erase(0, temp->author.find_first_not_of(' '));
			temp->author.erase(temp->author.find_last_not_of(' ') + 1);
			if (temp->author == removeSpaces(keyword))
			{
				result.push_back(temp);
			}
		}
		else if (field == "genre")
		{
			temp->genre.erase(0, temp->genre.find_first_not_of(' '));
			temp->genre.erase(temp->genre.find_last_not_of(' ') + 1);
			if (temp->genre == keyword)
			{
				result.push_back(temp);
			}
		}
		else if (field == "publisher")
		{
			temp->publisher.erase(0, temp->publisher.find_first_not_of(' '));
			temp->publisher.erase(temp->publisher.find_last_not_of(' ') + 1);
			if (temp->publisher == keyword)
			{
				result.push_back(temp);
			}
		}
		temp = temp->next;
	}
	return result;
}

void findBook(string keyword, string field)
{
	vector<Book *> booksToFind = searchBook(keyword, field);
	if (booksToFind.empty())
	{
		cout << "  No book found in the library." << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("cls");
		return;
	}
	else
	{
		cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
		cout << "| BookID |                       Title                           |               Author               |            Genre           |                    Publisher                  |    Quantity   |" << endl;
		cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
		for (Book *book : booksToFind)
		{
			cout << "| " << setw(6) << left << removeSpaces(book->bookID) << " | " << setw(53) << left << removeSpaces(book->title) << " | " << setw(34) << left << removeSpaces(book->author)
				 << " | " << setw(26) << left << removeSpaces(book->genre) << " | " << setw(45) << left << removeSpaces(book->publisher) << " | " << setw(13) << left << book->quantity << " |" << endl;
			cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
		}
	}
}

void adjustBook(string keyword, string field, string newID, string newname_book, string newtacgia, string newtheloai, string newnxb, int newquantity)
{
	vector<Book *> booksToAdjust = searchBook(keyword, field);
	if (booksToAdjust.empty())
	{
		cout << "  No books found to adjust." << endl;
		return;
	}
	for (Book *book : booksToAdjust)
	{
		book->bookID = newID;
		book->title = newname_book;
		book->author = newtacgia;
		book->genre = newtheloai;
		book->publisher = newnxb;
		book->quantity = newquantity;
	}
	cout << "  Book information updated successfully." << endl;
}

void deleteBook(string bookID)
{
	if (head == nullptr)
	{
		cout << "  The library is empty." << endl;
		return;
	}
	Book *temp = head;
	Book *prev = nullptr;
	while (temp != nullptr && temp->bookID != bookID)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == nullptr)
	{
		cout << "  Book not found in the library." << endl;
		return;
	}
	if (prev == nullptr)
	{
		head = head->next;
	}
	else
	{
		prev->next = temp->next;
	}
	delete temp;
	cout << "  Book deleted successfully." << endl;
}

void displaySortedBooks(string sortBy)
{
    if (head == nullptr)
    {
        cout << "The library is empty." << endl;
        return;
    }

    // Copy the linked list to an array
    int listSize = 0;
    Book *temp = head;
    while (temp != nullptr)
    {
        listSize++;
        temp = temp->next;
    }
    Book *bookArray = new Book[listSize];
    temp = head;
    for (int i = 0; i < listSize; i++)
    {
        bookArray[i] = *temp;
        temp = temp->next;
    }

    // Sort the array using insertSort
    for (int i = 1; i < listSize; i++)
    {
        Book key = bookArray[i];
        int j = i - 1;
        while (j >= 0 && (
            (sortBy == "bookID" && bookArray[j].bookID > key.bookID) ||
            (sortBy == "title" && bookArray[j].title > key.title) ||
            (sortBy == "author" && bookArray[j].author > key.author)))
        {
            bookArray[j + 1] = bookArray[j];
            j--;
        }
        bookArray[j + 1] = key;
    }

    // Display the sorted array
    cout << "-----------------------------------" << endl;
	cout << "  List of book sorted by " << sortBy << ":" << endl;
	cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
	cout << "| BookID |                       Title                           |               Author               |            Genre           |                    Publisher                  |    Quantity   |" << endl;
	cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
	for (int i = 1; i < listSize; i++)
	{
		cout << "| " << setw(6) << left << removeSpaces(bookArray[i].bookID) << " | " << setw(53) << left << removeSpaces(bookArray[i].title) << " | " << setw(34) << left << removeSpaces(bookArray[i].author)
			 << " | " << setw(26) << left << removeSpaces(bookArray[i].genre) << " | " << setw(45) << left << removeSpaces(bookArray[i].publisher) << " | " << setw(13) << left << bookArray[i].quantity << " |" << endl;
		cout << "+--------+-------------------------------------------------------+------------------------------------+----------------------------+-----------------------------------------------+---------------+" << endl;
	}
    // Delete the temporary array
    delete[] bookArray;
}

void exportData(string filename)
{
	ofstream outputFile(filename);
	Book *temp = head;

	while (temp != nullptr)
	{
		outputFile << temp->bookID << ";" << temp->title << ";" << temp->author << ";" << temp->genre << ";" << temp->publisher << ";" << temp->quantity << endl;
		temp = temp->next;
		outputFile.flush();
	}

	outputFile.close();
}
// end book------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// reader--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void addBanDoc(string IDSV, string name, string birthdate, string gender, string number, string cls)
{
	BanDoc *newBanDoc = new BanDoc;
	newBanDoc->IDSV = IDSV;
	newBanDoc->name = name;
	newBanDoc->birthdate = birthdate;
	newBanDoc->gender = gender;
	newBanDoc->number = number;
	newBanDoc->cls = cls;
	newBanDoc->next = nullptr;

	if (headDoc == nullptr)
	{
		headDoc = newBanDoc;
	}
	else
	{
		BanDoc *temp = headDoc;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = newBanDoc;
	}
}

void readFromFilehuman(string filename)
{
	ifstream inFile(filename);
	if (!inFile)
	{
		cout << "  Can't open file" << endl;
		return;
	}
	string line;
	while (getline(inFile, line))
	{
		vector<string> fields;
		stringstream ss(line);
		string field;
		while (getline(ss, field, ';'))
		{
			fields.push_back(field);
		}

		if (fields.size() != 6)
		{
			cout << "  Invalid data format" << endl;
			continue;
		}

		string IDSV = fields[0];
		string name = fields[1];
		string birthdate = fields[2];
		string gender = fields[3];
		string number = fields[4];
		string cls = fields[5];

		addBanDoc(IDSV, name, birthdate, gender, number, cls);
	}

	inFile.close();
}

void DisplayBanDoc()
{
	BanDoc *temp = headDoc;
	cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
	cout << "| Student ID |                        Name                           |          Gender        |       Date of birth     |                Phone Number              |     Class   |" << endl;
	cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
	while (temp != nullptr)
	{
		cout << "| " << setw(10) << left << removeSpaces(temp->IDSV) << " | " << setw(53) << left << removeSpaces(temp->name) << " | " << setw(22) << left << removeSpaces(temp->gender) << " | "
		 << setw(23) << left << removeSpaces(temp->birthdate) << " | " << setw(40) << left << removeSpaces(temp->number) << " | " << setw(11) << left << removeSpaces(temp->cls) << " |" << endl;
		cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
		temp = temp->next;
	}
}

void displaynewReader(string IDSV, string name, string birthdate, string gender, string number, string cls)
{
	cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
	cout << "| Student ID |                        Name                           |          Gender        |       Date of birth     |                Phone Number              |     Class   |" << endl;
	cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
	cout << "| " << setw(10) << left << IDSV << " | " << setw(53) << left << name << " | " << setw(22) << left << gender << " | " << setw(23) << left << birthdate << " | "
	 << setw(40) << left << number << " | " << setw(11) << left << cls << " |" << endl;
	cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
}

void displaynewadjustReader(string newIDSV, string newname, string newbirthdate, string newgender, string newnumber, string newcls)
{
	cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
	cout << "| Student ID |                        Name                           |          Gender        |       Date of birth     |                Phone Number              |     Class   |" << endl;
	cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
	cout << "| " << setw(10) << left << newIDSV << " | " << setw(53) << left << newname << " | " << setw(22) << left << newgender << " | " << setw(23) << left << newbirthdate << " | "
	 << setw(40) << left << newnumber << " | " << setw(11) << left << newcls << " |" << endl;
	cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
}

vector<BanDoc *> searchHuman(string keyword, string field)
{
	vector<BanDoc *> show;
	BanDoc *temp = headDoc;
	while (temp != nullptr)
	{
		if (field == "IDSV")
		{
			temp->IDSV.erase(0, temp->IDSV.find_first_not_of(' '));
			temp->IDSV.erase(temp->IDSV.find_last_not_of(' ') + 1);
			if (temp->IDSV == removeSpaces(keyword))
			{
				show.push_back(temp);
			}
		}
		else if (field == "name")
		{
			temp->name.erase(0, temp->name.find_first_not_of(' '));
			temp->name.erase(temp->name.find_last_not_of(' ') + 1);
			if (temp->name == removeSpaces(keyword))
			{
				show.push_back(temp);
			}
		}
		else if (field == "gender")
		{
			temp->gender.erase(0, temp->gender.find_first_not_of(' '));
			temp->gender.erase(temp->gender.find_last_not_of(' ') + 1);
			if (temp->gender == removeSpaces(keyword))
			{
				show.push_back(temp);
			}
		}
		else if (field == "birthdate")
		{
			temp->birthdate.erase(0, temp->birthdate.find_first_not_of(' '));
			temp->birthdate.erase(temp->birthdate.find_last_not_of(' ') + 1);
			if (temp->birthdate == removeSpaces(keyword))
			{
				show.push_back(temp);
			}
		}
		else if (field == "number")
		{
			temp->number.erase(0, temp->number.find_first_not_of(' '));
			temp->number.erase(temp->number.find_last_not_of(' ') + 1);
			if (temp->number == removeSpaces(keyword))
			{
				show.push_back(temp);
			}
		}
		else if (field == "cls")
		{
			temp->cls.erase(0, temp->cls.find_first_not_of(' '));
			temp->cls.erase(temp->cls.find_last_not_of(' ') + 1);
			if (temp->cls == removeSpaces(keyword))
			{
				show.push_back(temp);
			}
		}
		temp = temp->next;
	}
	return show;
}

void findHuman(string keyword, string field)
{
	vector<BanDoc *> humanToFind = searchHuman(keyword, field);
	if (humanToFind.empty())
	{
		cout << "  Not found in the system." << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("cls");
		return;
	}
	else
	{
		cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
		cout << "| Student ID |                        Name                           |          Gender        |       Date of birth     |                Phone Number              |     Class   |" << endl;
		cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
		for (BanDoc *bandoc : humanToFind)
		{
			cout << "| " << setw(10) << left << removeSpaces(bandoc->IDSV) << " | " << setw(53) << left << removeSpaces(bandoc->name) << " | " << setw(22) << left
				 << removeSpaces(bandoc->gender) << " | " << setw(23) << left << removeSpaces(bandoc->birthdate) << " | " << setw(40) << left << removeSpaces(bandoc->number) << " | " 
				 << setw(11) << left << removeSpaces(bandoc->cls) << " |" << endl;
			cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
		}
	}
}

void adjustHuman(string keyword, string field, string newIDSV, string newname, string newbirthdate, string newgender, string newnumber, string newcls)
{
	vector<BanDoc *> humansToAdjust = searchHuman(keyword, field);
	if (humansToAdjust.empty())
	{
		cout << "  Not found in the system." << endl;
		return;
	}
	for (BanDoc *humanToAdjust : humansToAdjust)
	{
		humanToAdjust->IDSV = newIDSV;
		humanToAdjust->name = newname;
		humanToAdjust->birthdate = newbirthdate;
		humanToAdjust->gender = newgender;
		humanToAdjust->number = newnumber;
		humanToAdjust->cls = newcls;
	}
	cout << "  Human information updated successfully." << endl;
}

void DeleteBanDoc(string IDSV)
{
	if (headDoc == nullptr)
	{
		return;
	}

	if (headDoc->IDSV == IDSV)
	{
		BanDoc *temp = headDoc;
		headDoc = headDoc->next;
		delete temp;
		return;
	}

	BanDoc *prev = headDoc;
	BanDoc *temp = headDoc->next;

	while (temp != nullptr)
	{
		if (temp->IDSV == IDSV)
		{
			prev->next = temp->next;
			delete temp;
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}

void displaySortedHuman(string sortBy)
{
	if (headDoc == nullptr)
	{
		cout << "  The information system is empty." << endl;
		return;
	}
	// Copy the linked list to an array
	int listSize = 0;
	BanDoc *temp = headDoc;
	while (temp != nullptr)
	{
		listSize++;
		temp = temp->next;
	}
	BanDoc *humanArray = new BanDoc[listSize];
	temp = headDoc;
	for (int i = 0; i < listSize; i++)
	{
		humanArray[i] = *temp;
		temp = temp->next;
	}
	// Sort the array using insertSort
	for (int i = 1; i < listSize; i++)
	{
		BanDoc key = humanArray[i];
		int j = i - 1;
		while (j >= 0 && ((sortBy == "IDSV" && humanArray[j].IDSV > key.IDSV) ||
						  (sortBy == "name" && humanArray[j].name > key.name) ||
						  (sortBy == "cls" && humanArray[j].cls > key.cls)))
		{
			humanArray[j + 1] = humanArray[j];
			j--;
		}
		humanArray[j + 1] = key;
	}
	// Display the sorted array
	cout << "-----------------------------------" << endl;
	cout << "  List of human sorted by " << sortBy << ":" << endl;
	cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
	cout << "| Student ID |                        Name                           |          Gender        |       Date of birth     |                Phone Number              |     Class   |" << endl;
	cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
	for (int i = 0; i < listSize; i++)
	{
		cout << "| " << setw(10) << left << removeSpaces(humanArray[i].IDSV) << " | " << setw(53) << left << removeSpaces(humanArray[i].name) << " | " << setw(22) << left << removeSpaces(humanArray[i].gender) << " | " 
		<< setw(23) << left << removeSpaces(humanArray[i].birthdate) << " | " << setw(40) << left << removeSpaces(humanArray[i].number) << " | " << setw(11) << left << removeSpaces(humanArray[i].cls) << " |" << endl;
		cout << "+------------+-------------------------------------------------------+------------------------+-------------------------+------------------------------------------+-------------+" << endl;
	}
	// Delete the temporary array
	delete[] humanArray;
}

void exportDatahuman(string filename)
{
	ofstream outputFile(filename);
	BanDoc *temp = headDoc;
	while (temp != nullptr)
	{
		outputFile << temp->IDSV << ";" << temp->name << ";" << temp->birthdate << ";" << temp->gender << ";" << temp->number << ";" << temp->cls << endl;
		temp = temp->next;
	}
	outputFile.close();
}
// end reader-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// create username------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void create()
{
	string user, password, passworda;
	cout << "  -> Enter username: \n";
	cout << "          ";
	getline(cin, user);
	while (true)
	{
		cout << "  -> Enter password: \n";
		cout << "          ";
		getline(cin, password);
		cout << "  -> Enter password again: \n";
		cout << "          ";
		getline(cin, passworda);
		if (password != passworda)
		{
			cout << "  Password does not match: ";
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			system("cls");
			cout << " -> Enter username: \n";
			cout << "         " << user << endl;
			continue;
		}
		break;
	}
	User *newUser = new User;
	newUser->user = user;
	newUser->password = password;
	ofstream outputFile("user.txt", ios::app);
	outputFile << newUser->user << "; " << newUser->password << endl;
	outputFile.close();
	cout << "  Create succesfully! \n";
}
// End create username------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// logic--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool trueuser(string username, string pass)
{
	ifstream file("user.txt");
	string line;
	while (getline(file, line))
	{
		istringstream iss(line);
		string user, password;
		getline(iss, user, ';');
		getline(iss, password, ';');
		if ((removeSpaces(user) == username) && (removeSpaces(password) == pass))
		{
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}

// end login----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// edit---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void editname(string &name)
{
	int i;
	while (!all_of(name.begin(), name.end(), [](unsigned char c)
				   { return isalpha(c) || isspace(c) || c == ',' || c == '-' || c == '.' || c == '&'; }))
	{
		cout << "  Wrong enter! Name contains only characters, spaces, ',', '-', '.', '&': ";
		getline(cin, name);
	}
	name[0] = toupper(name[0]);
	for (i = 1; i < name.length(); i++){
		name[i] = tolower(name[i]);
		if (isspace(name[i - 1]))
		{
			name[i] = toupper(name[i]);
		}
	}
}

void editbook(string &book)
{
	int i;
	while (!all_of(book.begin(), book.end(), [](unsigned char c)
				   { return isalnum(c) || isspace(c) || c == ',' || c == '-' || c == '.' || c == '&';; }))
	{
		cout << "  Wrong enter! Book contains only numbers, characters, spaces, ',', '-', '.', '&': ";
		getline(cin, book);
	}
	book[0] = toupper(book[0]);
	for (i = 1; i < book.length(); i++){
		book[i] = tolower(book[i]);
		if (isspace(book[i - 1]))
		{
			book[i] = toupper(book[i]);
		}
	}
}

void editnewbook(string &book)
{
	int i;
	while (!all_of(book.begin(), book.end(), [](unsigned char c)
				   { return isalnum(c) || isspace(c) || c == ',' || c == '-' || c == '.' || c == '&';; }))
	{
		cout << "  Wrong enter! Book contains only numbers, characters, spaces, ',', '-', '.', '&': ";
		getline(cin, book);
	}
	book[0] = toupper(book[0]);
	for (i = 1; i < book.length(); i++){
		book[i] = tolower(book[i]);
		if (isspace(book[i - 1]))
		{
			book[i] = toupper(book[i]);
		}
	}
	vector<Book *> booktitle = searchBook(book, "title");
	if (booktitle.empty())
	{
		return;
	}
	else
	{
		cout << "  Wrong enter! This book have already exist: ";
		getline(cin, book);
		editbook(book);
	}
}

bool isInteger(string &str)
{
	if (str.empty())
		return false;
	for (int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]) && str[i] != '-')
			return false;
	}
	return true;
}

bool isIDExist(string ID)
{
	ifstream file("Sach.txt");
	string line;
	while (getline(file, line))
	{
		istringstream iss(line);
		string bookID;
		getline(iss, bookID, ';');
		if (bookID == ID)
		{
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}

void editID(string &ID)
{
	while (true)
	{
		getline(cin, ID);
		if (!isInteger(ID))
		{
			cout << "  Wrong enter! ID contains numbers only: ";
			continue;
		}
		if (isIDExist(ID))
		{
			cout << "  Wrong enter! ID have already exist: ";
			continue;
		}
		break;
	}
}

void editnumber(string &number)
{
	string input;
	bool isNum;
	do
	{
		getline(cin, input);
		isNum = true;
		for (char const &c : input)
		{
			if (isdigit(c) == false)
			{
				isNum = false;
				break;
			}
		}
		if (isNum == false)
		{
			cout << "  Wrong enter! Contains numbers only : ";
		}
	} while (isNum == false);
	stringstream num(input);
	num >> number;
}

void editnumberint(int &number)
{
	string input;
	bool isNum;
	do
	{
		getline(cin, input);
		isNum = true;
		for (char const &c : input)
		{
			if (isdigit(c) == false)
			{
				isNum = false;
				break;
			}
		}
		if (isNum == false)
		{
			cout << "  Wrong enter! Contains numbers only : ";
		}
	} while (isNum == false);
	stringstream num(input);
	num >> number;
}

bool isIDSVExist(string SID)
{
	ifstream file("human.txt");
	string line;
	while (getline(file, line))
	{
		istringstream iss(line);
		string IDSV;
		getline(iss, IDSV, ';');
		if (IDSV == SID)
		{
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}

void editIDSV(string &SID)
{
	while (true)
	{
		getline(cin, SID);
		bool isNumeric = true;
		for (char c : SID)
		{
			if (!isdigit(c))
			{
				isNumeric = false;
				break;
			}
		}
		if (!isNumeric)
		{
			cout << "  Wrong enter! Student's ID contains numbers only: ";
			continue;
		}
		if (SID.length() != 8)
		{
			cout << "  Wrong enter! Student's ID must have exactly 8 digits: ";
			continue;
		}
		int ID = stoi(SID);
		if (ID < 0 || ID > 23000000)
		{
			cout << "  Wrong enter! Student's ID must be in range from 0 to 23000000: ";
			continue;
		}
		if (isIDSVExist(SID))
		{
			cout << "  Wrong enter! Student's ID have already exist: ";
			continue;
		}
		break;
	}
}

void editAdjustIDSV(string &SID)
{
	while (true)
	{
		getline(cin, SID);
		bool isNumeric = true;
		for (char c : SID)
		{
			if (!isdigit(c))
			{
				isNumeric = false;
				break;
			}
		}
		if (!isNumeric)
		{
			cout << "  Wrong enter! Student's ID contains numbers only: ";
			continue;
		}
		if (SID.length() != 8)
		{
			cout << "  Wrong enter! Student's ID must have exactly 8 digits: ";
			continue;
		}
		int ID = stoi(SID);
		if (ID < 0 || ID > 23000000)
		{
			cout << "  Wrong enter! Student's ID must be in range from 0 to 23000000: ";
			continue;
		}
		break;
	}
}

bool editbirthday(string birthdate)
{
	time_t t = time(NULL);
	tm *timePtr = localtime(&t);
	int currentYear = 1900 + timePtr->tm_year;
	int day, month, year;
	sscanf(birthdate.c_str(), "%d/%d/%d", &day, &month, &year);
	if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > currentYear)
	{
		cout << "  Invalid date of birth! ";
		return false;
	}
	bool is_valid_date = true;
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
		{
			is_valid_date = false;
		}
	}
	else if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			if (day > 29)
			{
				is_valid_date = false;
			}
		}
		else
		{
			if (day > 28)
			{
				is_valid_date = false;
			}
		}
	}
	if (!is_valid_date)
	{
		cout << "  Invalid date of birth! ";
		return false;
	}
	if (currentYear - year < 18)
	{
		cout << "  This student is not old enough! ";
		return false;
	}
	return true;
}

void editchoice(int &choice)
{
	string enter;
	bool validChoice = false;
	while (!validChoice)
	{
		getline(cin, enter);
		if (isInteger(enter) && enter.length() == 1)
		{
			choice = stoi(enter);
			validChoice = true;
		}
		else
		{
			cout << "  Invalid input! Please enter a single integer: ";
		}
	}
}

void editPhoneNumber(string &number)
{
	while (true)
	{
		getline(cin, number);

		bool isNumeric = true;
		for (char c : number)
		{
			if (!isdigit(c))
			{
				isNumeric = false;
				break;
			}
		}
		if (!isNumeric)
		{
			cout << "  Wrong enter! Phone number contains numbers only: ";
			continue;
		}

		if (number.length() != 10)
		{
			cout << "  Wrong enter! Phone number must have exactly 10 digits: ";
			continue;
		}

		if (number[0] != '0')
		{
			cout << "  Wrong enter! Invalid phone number: ";
			continue;
		}

		break;
	}
}

void editclass(string &cls)
{
	int i;
	while (!all_of(cls.begin(), cls.end(), [](unsigned char c)
				   { return isalnum(c); }))
	{
		cout << "  Wrong enter! Class contains only numbers and characters: ";
		getline(cin, cls);
	}
	for (i = 0; i < cls.length(); i++)
	{
		cls[i] = toupper(cls[i]);
	}
}
// edit----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// borrow & return-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void borrowBook()
{
	string bookID = "bookID";
	string readerID = "IDSV";
	string BookID;
	string ID;
	int choice;
	cout << "  Enter the reader ID: ";
	getline(cin, ID);
	vector<BanDoc *> HumanBorrow = searchHuman(ID, readerID);
	if (HumanBorrow.empty())
	{
		cout << "  Reader not found in the system." << endl;
		do
		{
			cout << "  You want to add new once? \n";
			cout << "+------------+-------------+ \n";
			cout << "| 1. For yes | 0. For exit | \n";
			cout << "+------------+-------------+ \n";
			editchoice(choice);
			switch (choice)
			{
			case 1:
			{
				system("cls");
				string IDSV;
				string name;
				string birthdate;
				string gender;
				string number;
				string cls;
				cout << "  Enter student's ID: ";
				editIDSV(IDSV);
				cout << "  Enter student's name: ";
				getline(cin, name);
				editname(name);
				bool valid_birthday = false;
				cout << "  Enter student's birthday: ";
				do
				{
					cin >> birthdate;
					valid_birthday = editbirthday(birthdate);
				} while (!valid_birthday);
				cin.ignore();
				do
				{
					cout << "+-------------+---------------+--------------+ \n";
					cout << "| 1. For male | 2. For female | 3. For other | \n";
					cout << "+-------------+---------------+--------------+ \n";
					cout << "  Enter student's gender: ";
					editchoice(choice);
					switch (choice)
					{
					case 1:
					{
						gender = "Male";
						break;
					}
					case 2:
					{
						gender = "Female";
						break;
					}
					case 3:
					{
						gender = "Other";
						break;
					}
					default:
					{
						cout << "  Wrong input! Please try again." << endl;
						break;
					}
					}
				} while (gender.empty());
				cout << "  Enter student's phone number: ";
				editPhoneNumber(number);
				cout << "  Enter student's class: ";
				getline(cin, cls);
				editclass(cls);
				cout << "  Please check your enter again \n";
				displaynewReader(IDSV, name, birthdate, gender, number, cls);
				cout << "  If it true, enter 1; false, enter 0: ";
				editchoice(choice);
				switch (choice)
				{
				case 0:
				{
					std::cout << "  Exiting.....";
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}
				case 1:
				{
					addBanDoc(IDSV, name, birthdate, gender, number, cls);
					cout << "  Add success!" << endl;
					exportDatahuman("human.txt");
					break;
				}
				}
				break;
			}

			default:
			{
				cout << "  Wrong enter! Please enter again: " << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				system("cls");
				break;
			}

			case 0:
			{
				std::cout << "  Exiting.....";
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				system("cls");
				break;
			}
			}
		} while (choice != 0);
		return;
	}
	else
	{
		cout << "+------------+-------------------------------------------------------+" << endl;
		cout << "| Student ID |                        Name                           |" << endl;
		cout << "+------------+-------------------------------------------------------+" << endl;
		cout << "| " << setw(10) << left << ID << " | " << setw(53) << left << removeSpaces(HumanBorrow[0]->name) << " | " << endl;
		cout << "+------------+-------------------------------------------------------+" << endl;
		int timeBorrowed;
		cout << "  Enter time borrowed (weeks) : ";
		cin >> timeBorrowed;
		int numBooks;
		cout << "  Enter the number of books to borrow: ";
		cin >> numBooks;
		while (numBooks > 5)
		{
			cout << "  Input number must be less than 5. Enter again: ";
			cin >> numBooks;
		};
		vector<Book *> booksToBorrow;
		for (int i = 0; i < numBooks; i++)
		{
			string BookID;
			cout << "  Enter book ID " << i + 1 << ": ";
			cin >> BookID;
			vector<Book *> foundBooks = searchBook(BookID, bookID);
			if (foundBooks.empty())
			{
				cout << "  Book with ID " << BookID << " not found in the library." << endl;
				i--;
				continue;
			}
			if (foundBooks[0]->quantity == 0)
			{
				cout << "  All copies of book " << foundBooks[0]->title << " by " << foundBooks[0]->author << " are currently borrowed." << endl;
				i--;
				continue;
			}
			booksToBorrow.push_back(foundBooks[0]);
			foundBooks[0]->quantity--;
			exportData("Sach.txt");
			cout << "  Data saved to file Sach.txt" << endl;
		}
		if (booksToBorrow.empty())
		{
			cout << "  No books were borrowed." << endl;
			return;
		}
		time_t now = time(0);
		tm *ltm = localtime(&now);
		char date[20];
		strftime(date, sizeof(date), "%d/%m/%Y %H:%M:%S", ltm);
		tm dueDateTm = *ltm;
		dueDateTm.tm_mday += timeBorrowed * 7;
		mktime(&dueDateTm);
		char dueDate[20];
		strftime(dueDate, sizeof(dueDate), "%d/%m/%Y %H:%M:%S", &dueDateTm);
		ofstream fout("borrow.txt", ios::app);
		cout << "+------------+-------------------------------------------------------+" << endl;
		cout << "| Student ID |                        Name                           |" << endl;
		cout << "+------------+-------------------------------------------------------+" << endl;
		cout << "| " << setw(10) << left << ID << " | " << setw(53) << left << removeSpaces(HumanBorrow[0]->name) << " | " << endl;
		cout << "+------------+-------------------------------------------------------+" << endl;
		cout << "+--------+-------------------------------------------------------+------------------------------------+-----------------------------+" << endl;
		cout << "| BookID |                       Title                           |               Author               |            Status           |" << endl;
		cout << "+--------+-------------------------------------------------------+------------------------------------+-----------------------------+" << endl;
		for (Book *book : booksToBorrow)
		{
			fout << ID << " " << book->bookID << " / Day: " << date << " / Borrowing time: " << timeBorrowed << " week" << " / Due date: " << dueDate << endl;
			cout << "| " << setw(6) << left << removeSpaces(book->bookID) << " | " << setw(53) << left << removeSpaces(book->title) << " | "
			 << setw(34) << left << removeSpaces(book->author) << " | " << setw(27) << left << "Successfully"
				 << " | " << endl;
			cout << "+--------+-------------------------------------------------------+------------------------------------+-----------------------------+" << endl;
		}
		fout.close();
	}
}
void displayBorrowedBooks() {
    string line;
    ifstream myfile ("borrow.txt");
    if (myfile.is_open()) {
        cout << "+------------+----------------------+------------------------------+----------------------------+------------------------------+------------------------------+----------------------------+" << endl;
        cout << "|  Reader ID |      Book ID         |  Date borrowed               |      Time                  |   Borrowing Time             |           Due Day            |        Due Time            |" << endl;
        cout << "+------------+----------------------+------------------------------+----------------------------+------------------------------+------------------------------+----------------------------+" << endl;
        while (getline(myfile,line)) {
            istringstream ss(line);
            string currentID, currentBookID, day, time, timeBorrowed, dayreturn, timereturn;
            ss >> currentID >> currentBookID;
			getline(ss, day, ':');
			getline(ss, day, ' ');
			ss >> day;
			ss >> time;
			getline(ss, timeBorrowed, ':');
			ss >> timeBorrowed;
			getline(ss, dayreturn, ':');
			getline(ss, dayreturn, ' ');
			ss >> dayreturn;
			ss >> timereturn;
            cout << "| " << setw(10) << left << currentID << " | " << setw(20) << left << currentBookID << " | " << setw(28) << left << day << " | " << setw(26) << left 
			<< time << " | "  << setw(28) << left << timeBorrowed << " | " << setw(28) << left << dayreturn << " | " << setw(26) << left 
			<< timereturn << " |"  << endl;
        }
        cout << "+------------+----------------------+------------------------------+----------------------------+------------------------------+------------------------------+----------------------------+" << endl;
        myfile.close();
    }
    else cout << "Unable to open file.";
}

void returnBook()
{
	string bookID = "bookID";
	string IDSV = "IDSV";
	string ID;
	cout << "  Enter the reader ID: ";
	getline(cin, ID);
	vector<BanDoc *> HumanReturn = searchHuman(ID, IDSV);
	if (HumanReturn.empty())
	{
		cout << "  Reader not found in the system." << endl;
		return;
	}
	cout << "+------------+-------------------------------------------------------+" << endl;
	cout << "| Student ID |                        Name                           |" << endl;
	cout << "+------------+-------------------------------------------------------+" << endl;
	cout << "| " << setw(10) << left << ID << " | " << setw(53) << left << removeSpaces(HumanReturn[0]->name) << " | " << endl;
	cout << "+------------+-------------------------------------------------------+" << endl;
	bool bookReturned = false;
	while (!bookReturned)
	{
		string BookID;
		cout << "  Enter the book ID (or type 'done' to finish returning): ";
		getline(cin, BookID);
		if (BookID == "done")
		{
			bookReturned = true;
		}
		else
		{
			vector<Book *> BookToReturn = searchBook(BookID, bookID);
			if (BookToReturn.empty())
			{
				cout << "  Book not found in the library." << endl;
			}
			else
			{
				time_t now = time(0);
				tm *ltm = localtime(&now);
				char returnDate[20];
				strftime(returnDate, sizeof(returnDate), "%d/%m/%Y %H:%M:%S", ltm);
				ofstream fout("return.txt", ios::app);
				ifstream fin("borrow.txt");
				ofstream foutTmp("borrow_tmp.txt");
				bool found = false;
				string line;
				while (getline(fin, line))
				{
					istringstream iss(line);
					string currentID, currentBookID, day, time, timeBorrowed, daydue, timedue;
					iss >> currentID >> currentBookID;
					getline(iss, day, ':');
					getline(iss, day, ' ');
					iss >> day;
					iss >> time;
					getline(iss, timeBorrowed, ':');
					iss >> timeBorrowed;
					getline(iss, daydue, ':');
					getline(iss, daydue, ' ');
					iss >> daydue;
					iss >> timedue;

					if (currentID == ID && currentBookID == BookID)
					{
						Book *book = BookToReturn[0];
						book->quantity++;
						exportData("Sach.txt");
						cout << "  Data saved to file Sach.txt" << endl;
						int weeksBorrowed = stoi(timeBorrowed);
						fout << currentID << " " << currentBookID << " / Day: " << day << " / Borrowing time: " << timeBorrowed << " week / Due date: " << daydue << "/" << timedue << " / Return time: " << returnDate << endl;
						cout << "  Book returned successfully!" << endl;
						found = true;
					}
					else
					{
						foutTmp << line << endl;
					}
				}
				fin.close();
				fout.close();
				foutTmp.close();
				if (!found)
				{
					cout << "  This reader has not borrowed this book." << endl;
					remove("borrow.txt");
					rename("borrow_tmp.txt", "borrow.txt");
				}
				else
				{
					cout << "+--------+-------------------------------------------------------+------------------------------------+-----------------------------+" << endl;
					cout << "| BookID |                       Title                           |               Author               |            Status           |" << endl;
					cout << "+--------+-------------------------------------------------------+------------------------------------+-----------------------------+" << endl;
					cout << "| " << setw(6) << left << removeSpaces(BookToReturn[0]->bookID) << " | " << setw(53) << left << removeSpaces(BookToReturn[0]->title) << " | "
						 << setw(34) << left << removeSpaces(BookToReturn[0]->author) << " | " << setw(27) << left << "Successfully"
						 << " | " << endl;
					cout << "+--------+-------------------------------------------------------+------------------------------------+-----------------------------+" << endl;
					remove("borrow.txt");
					rename("borrow_tmp.txt", "borrow.txt");
				}
			}
		}
	}
}

void displayReturnData() {
    ifstream fin("return.txt");
    string line;
    cout << "+------------+----------------------+------------------------------+----------------------------+------------------------------+----------------------------+------------------------------+" << endl;
    cout << "|  Reader ID |      Book ID         |  Date borrowed               |      Borrowing Time        |   Due Day                    |        Return Day          |        Return Time           |" << endl;
    cout << "+------------+----------------------+------------------------------+----------------------------+------------------------------+----------------------------+------------------------------+" << endl;
    if (fin.is_open()) {
        while (getline(fin,line)) {
            istringstream ss(line);
            string currentID, currentBookID, day, timeBorrowed, daydue, timedue, dayreturn, timereturn;
            ss >> currentID >> currentBookID;
			getline(ss, day, ':');
			getline(ss, day, ' ');
			ss >> day;
			getline(ss, timeBorrowed, ':');
			ss >> timeBorrowed;
			getline(ss, daydue, ':');
			getline(ss, timedue, ' ');
			ss >> daydue;
			ss >> timedue;
			getline(ss, dayreturn, ':');
			getline(ss, dayreturn, ' ');
			ss >> dayreturn;
			ss >> timereturn;
            cout << "| " << setw(10) << left << currentID << " | " << setw(20) << left << currentBookID << " | " << setw(28) << left << day << " | " << setw(26) << left 
			<< timeBorrowed << " | "  << setw(28) << left << daydue << " | " << setw(26) << left 
			<< dayreturn << " | " << setw(28) << left << timereturn << " |" << endl;
        }
        cout << "+------------+----------------------+------------------------------+----------------------------+------------------------------+----------------------------+------------------------------+" << endl;
        fin.close();
    } else cout << "Unable to open file.";
}

// end borrow & return-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// interface Book------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void InterfaceBook()
{
	int choice, adjust, find, arrange;
	system("cls");
	while (true)
	{
		cout << "               +=================================================+ \n";
		cout << "               |NHOM 3_____CHIEU THU 4______ALDS335764_22_2_02CLC| \n";
		cout << "               |-------------------------------------------------| \n";
		cout << "               |  1. NGUYEN VAN HAO                20119223      | \n";
		cout << "               |  2. DAO NGOC MINH HUY             20119045      | \n";
		cout << "               |  3. PHAN NHAT MINH                20119033      | \n";
		cout << "               +=================================================+ \n";
		cout << "                                                                   \n";
		cout << "               +=================================================+ \n";
		cout << "               | STT  |              BOOK MANAGEMENT             | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  1.  |  Show book list                          | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  2.  |  Add new book                            | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  3.  |  Adjust book list                        | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  4.  |  Delete book                             | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  5.  |  Finding book                            | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  6.  |  Arrange book                            | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  0.  |  Exit the program                        | \n";
		cout << "               +=================================================+ \n";
		cout << "              	       Select fuction: ";
		editchoice(choice);
		switch (choice)
		{
		case 1:
		{
			system("cls");
			displayBook();
			returnToPreviousFunction();
			break;
		}

		case 2:
		{
			string bookID, title, author, genre, publisher;
			int quantity;
			cout << "  Enter book ID: ";
			editID(bookID);
			cout << "  Enter book title: ";
			getline(cin, title);
			editnewbook(title);
			cout << "  Enter book author: ";
			getline(cin, author);
			editname(author);
			cout << "  Enter book category: ";
			getline(cin, genre);
			editname(genre);
			cout << "  Enter publishing company: ";
			getline(cin, publisher);
			editname(publisher);
			cout << "  Enter quantity: ";
			editnumberint(quantity);
			cout << "  Please check your enter again \n";
			displaynewBook(bookID, title, author, genre, publisher, quantity);
			cout << "+-------------+--------------+ \n";
			cout << "| 1. For true | 0. For false | \n";
			cout << "+-------------+--------------+ \n";
			cout << "  Select your answer: ";
			editchoice(choice);
			switch (choice)
			{
			case 0:
			{
				std::cout << "  Exiting.....";
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				system("cls");
				break;
			}
			case 1:
			{
				addBook(bookID, title, author, genre, publisher, quantity);
				exportData("Sach.txt");
				cout << "  Add success!" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				system("cls");
				break;
			}
			}
			break;
		}

		case 3:
		{
			system("cls");
			string newID;
			string newname_book;
			string newtacgia;
			string newtheloai;
			string newnxb;
			int newquantity;
			do
			{
				cout << "               +=================================================+ \n";
				cout << "               |NHOM 3_____CHIEU THU 4______ALDS335764_22_2_02CLC| \n";
				cout << "               |-------------------------------------------------| \n";
				cout << "               |  1. NGUYEN VAN HAO                20119223      | \n";
				cout << "               |  2. DAO NGOC MINH HUY             20119045      | \n";
				cout << "               |  3. PHAN NHAT MINH                20119033      | \n";
				cout << "               +=================================================+ \n";
				cout << "                                                                   \n";
				cout << "               +=================================================+ \n";
				cout << "               | STT  |       SELECT ADJUST FUNCTION             | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  1.  |  Adjust by ID                            | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  2.  |  Adjust by book title                    | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  0.  |  Exit                                    | \n";
				cout << "               +=================================================+ \n";
				cout << "               		  Select function: ";
				editchoice(adjust);
				switch (adjust)
				{
				case 1:
				{
					string ID;
					string bookID = "bookID";
					cout << "  Find by ID: ";
					editnumber(ID);
					findBook(ID, bookID);
					vector<Book *> booksToFind = searchBook(ID, bookID);
					if (booksToFind.empty())
					{
						break;
					}
					cout << "  Enter new ID: ";
					editnumber(newID);
					cout << "  Enter new book title: ";
					getline(cin, newname_book);
					editbook(newname_book);
					cout << "  Enter new author: ";
					getline(cin, newtacgia);
					editname(newtacgia);
					cout << "  Enter new category: ";
					getline(cin, newtheloai);
					editname(newtheloai);
					cout << "  Enter new publishing company: ";
					getline(cin, newnxb);
					editname(newnxb);
					cout << "  Enter new quantity: ";
					editnumberint(newquantity);
					cout << "  Please check your enter again \n";
					displaynewadjustBook(newID, newname_book, newtacgia, newtheloai, newnxb, newquantity);
					cout << "+-------------+--------------+ \n";
					cout << "| 1. For true | 0. For false | \n";
					cout << "+-------------+--------------+ \n";
					cout << "  Select your answer: ";
					editchoice(choice);
					switch (choice)
					{
					case 0:
					{
						std::cout << "  Exiting.....";
						std::this_thread::sleep_for(std::chrono::milliseconds(200));
						system("cls");
						break;
					}
					case 1:
					{
						adjustBook(ID, bookID, newID, newname_book, newtacgia, newtheloai, newnxb, newquantity);
						exportData("Sach.txt");
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						system("cls");
						break;
					}
					}
					break;
				}

				case 2:
				{
					string name;
					string title = "title";
					cout << "  Find by title: ";
					getline(cin, name);
					editbook(name);
					findBook(name, title);
					vector<Book *> booksToFind = searchBook(name, title);
					if (booksToFind.empty())
					{
						break;
					}
					cout << "  Enter new ID: ";
					editnumber(newID);
					cout << "  Enter new book title: ";
					getline(cin, newname_book);
					editbook(newname_book);
					cout << "  Enter new author: ";
					getline(cin, newtacgia);
					editname(newtacgia);
					cout << "  Enter new category: ";
					getline(cin, newtheloai);
					editname(newtheloai);
					cout << "  Enter new publishing company: ";
					getline(cin, newnxb);
					editname(newnxb);
					cout << "  Enter new quantity: ";
					editnumberint(newquantity);
					cout << "  Please check your enter again \n";
					displaynewadjustBook(newID, newname_book, newtacgia, newtheloai, newnxb, newquantity);
					cout << "+-------------+--------------+ \n";
					cout << "| 1. For true | 0. For false | \n";
					cout << "+-------------+--------------+ \n";
					cout << "  Select your answer: ";
					editchoice(choice);
					switch (choice)
					{
					case 0:
					{
						std::cout << "  Exiting.....";
						std::this_thread::sleep_for(std::chrono::milliseconds(200));
						system("cls");
						break;
					}
					case 1:
					{
						adjustBook(name, title, newID, newname_book, newtacgia, newtheloai, newnxb, newquantity);
						exportData("Sach.txt");
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						system("cls");
						break;
					}
					}
					break;
				}

				default:
				{
					cout << "  Wrong enter! Please enter again: " << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}

				case 0:
				{
					std::cout << "  Exiting.....";
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}
				}
			} while (adjust != 0);
			break;
		}

		case 4:
		{
			string bookID;
			string ID = "bookID";
			cout << "  Enter the book ID to be deleted: ";
			editnumber(bookID);
			findBook(bookID, ID);
			vector<Book *> booksToFind = searchBook(bookID, ID);
			if (booksToFind.empty())
			{
				break;
			}
			cout << "  You want to delete this book? \n";
			cout << "+------------+-----------+ \n";
			cout << "| 1. For yes | 0. For no | \n";
			cout << "+------------+-----------+ \n";
			cout << "  Select your answer: ";
			editchoice(choice);
			switch (choice)
			{
				case 0:
				{
					std::cout << "  Exiting.....";
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}
				case 1:
				{
					deleteBook(bookID);
					exportData("Sach.txt");
					std::cout << "  Delete successfully.....";
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					system("cls");
					break;
				}
			}
			break;
		}

		case 5:
		{
			system("cls");
			do
			{
				cout << "               +=================================================+ \n";
				cout << "               |NHOM 3_____CHIEU THU 4______ALDS335764_22_2_02CLC| \n";
				cout << "               |-------------------------------------------------| \n";
				cout << "               |  1. NGUYEN VAN HAO                20119223      | \n";
				cout << "               |  2. DAO NGOC MINH HUY             20119045      | \n";
				cout << "               |  3. PHAN NHAT MINH                20119033      | \n";
				cout << "               +=================================================+ \n";
				cout << "                                                                   \n";
				cout << "               +=================================================+ \n";
				cout << "               | STT  |          SELECT SEARCH FUNCTION          | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  1.  |  Find by ID                              | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  2.  |  Find by title                           | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  3.  |  Find by author                          | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  4.  |  Find by genre                           | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  5.  |  Find by publisher                       | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  0.  |  Exit                                    | \n";
				cout << "               +=================================================+ \n";
				cout << "                		  Select function: ";
				editchoice(find);
				switch (find)
				{
				case 1:
				{
					system("cls");
					string ID;
					string bookID = "bookID";
					cout << "  Find by ID: ";
					editnumber(ID);
					findBook(ID, bookID);
					returnToPreviousFunction();
					break;
				}

				case 2:
				{
					system("cls");
					string name;
					string title = "title";
					cout << "  Find by title: ";
					getline(cin, name);
					editbook(name);
					findBook(name, title);
					returnToPreviousFunction();
					break;
				}

				case 3:
				{
					system("cls");
					string authors;
					string author = "author";
					cout << "  Find by author: ";
					getline(cin, authors);
					editname(authors);
					findBook(authors, author);
					returnToPreviousFunction();
					break;
				}

				case 4:
				{
					system("cls");
					string genres;
					string genre = "genre";
					cout << "  Find by genre: ";
					getline(cin, genres);
					editname(genres);
					findBook(genres, genre);
					returnToPreviousFunction();
					break;
				}

				case 5:
				{
					system("cls");
					string publishers;
					string publisher = "publisher";
					cout << "  Find by publisher: ";
					getline(cin, publishers);
					editname(publishers);
					findBook(publishers, publisher);
					returnToPreviousFunction();
					break;
				}

				default:
				{
					cout << "  Wrong enter! Please enter again: " << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}

				case 0:
				{
					std::cout << "  Exiting.....";
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}
				}
			} while (find != 0);
			break;
		}

		case 6:
		{
			system("cls");
			do
			{
				cout << "               +=================================================+ \n";
				cout << "               |NHOM 3_____CHIEU THU 4______ALDS335764_22_2_02CLC| \n";
				cout << "               |-------------------------------------------------| \n";
				cout << "               |  1. NGUYEN VAN HAO                20119223      | \n";
				cout << "               |  2. DAO NGOC MINH HUY             20119045      | \n";
				cout << "               |  3. PHAN NHAT MINH                20119033      | \n";
				cout << "               +=================================================+ \n";
				cout << "                                                                   \n";
				cout << "               +=================================================+ \n";
				cout << "               | STT  |         SELECT ARRANGE FUNCTION          | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  1.  |  Arrange by title                        | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  2.  |  Arrange by ID                           | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  3.  |  Arrange by author                       | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  0.  |  Exit                                    | \n";
				cout << "               +=================================================+ \n";
				cout << "                		  Select function: ";
				editchoice(arrange);
				switch (arrange)
				{
				case 1:
				{
					system("cls");
					cout << "  Arrange by title:\n";
					displaySortedBooks("title");
					exportData("Sach.txt");
					returnToPreviousFunction();
					break;
				}

				case 2:
				{
					system("cls");
					cout << "  Arrange by ID:\n";
					displaySortedBooks("bookID");
					exportData("Sach.txt");
					returnToPreviousFunction();
					break;
				}

				case 3:
				{
					system("cls");
					cout << "  Arrange by author:\n";
					displaySortedBooks("author");
					exportData("Sach.txt");
					returnToPreviousFunction();
					break;
				}

				default:
				{
					cout << "  Wrong enter! Please enter again: " << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}

				case 0:
				{
					std::cout << "  Exiting.....";
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}
				}
			} while (arrange != 0);
			break;
		}

		default:
		{
			cout << "  Wrong enter! Please enter again: " << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			system("cls");
			break;
		}
		case 0:
			cout << "  Exiting...." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			system("cls");
			return;
		}
		cout << endl;
		system("cls");
	}
	return;
}
// End interface Book---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// interface Reader----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void InterfaceReader()
{
	int choice, adjust, find, arrange;
	system("cls");
	while (true)
	{
		cout << "               +=================================================+ \n";
		cout << "               |NHOM 3_____CHIEU THU 4______ALDS335764_22_2_02CLC| \n";
		cout << "               |-------------------------------------------------| \n";
		cout << "               |  1. NGUYEN VAN HAO                20119223      | \n";
		cout << "               |  2. DAO NGOC MINH HUY             20119045      | \n";
		cout << "               |  3. PHAN NHAT MINH                20119033      | \n";
		cout << "               +=================================================+ \n";
		cout << "                                                                   \n";
		cout << "               +=================================================+ \n";
		cout << "               | STT  |             HUMAN MANAGEMENT             | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  1.  |  Show reader information                 | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  2.  |  Add new reader                          | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  3.  |  Adjust information                      | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  4.  |  Delete reader                           | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  5.  |  Finding reader                          | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  6.  |  Arrange reader                          | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  0.  |  Exit the program                        | \n";
		cout << "               +=================================================+ \n";
		cout << "              	       Select fuction: ";
		editchoice(choice);
		switch (choice)
		{
		case 1:
		{
			system("cls");
			DisplayBanDoc();
			returnToPreviousFunction();
			break;
		}

		case 2:
		{
			string IDSV;
			string name;
			string birthdate;
			string gender;
			string number;
			string cls;
			cout << "  Enter student's ID: ";
			editIDSV(IDSV);
			cout << "  Enter student's name: ";
			getline(cin, name);
			editname(name);
			do
			{
				cout << "+-------------+---------------+--------------+ \n";
				cout << "| 1. For male | 2. For female | 3. For other | \n";
				cout << "+-------------+---------------+--------------+ \n";
				cout << "  Enter student's gender: ";
				editchoice(choice);
				switch (choice)
				{
				case 1:
				{
					gender = "Male";
					break;
				}
				case 2:
				{
					gender = "Female";
					break;
				}
				case 3:
				{
					gender = "Other";
					break;
				}
				default:
				{
					cout << "  Wrong input! Please try again." << endl;
					break;
				}
				}
			} while (gender.empty());
			bool valid_birthday = false;
			cout << "  Enter student's birthday: ";
			do
			{
				cin >> birthdate;
				valid_birthday = editbirthday(birthdate);
			} while (!valid_birthday);
			cout << "  Enter student's phone number: ";
			cin.ignore();
			editPhoneNumber(number);
			cout << "  Enter student's class: ";
			getline(cin, cls);
			editclass(cls);
			cout << "  Please check your enter again \n";
			displaynewReader(IDSV, name, birthdate, gender, number, cls);
			cout << "+-------------+--------------+ \n";
			cout << "| 1. For true | 0. For false | \n";
			cout << "+-------------+--------------+ \n";
			cout << "  Select your answer: ";
			editchoice(choice);
			switch (choice)
			{
			case 0:
			{
				std::cout << "  Exiting.....";
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				system("cls");
				break;
			}
			case 1:
			{
				addBanDoc(IDSV, name, birthdate, gender, number, cls);
				exportDatahuman("human.txt");
				cout << "  Add success!" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				system("cls");
				break;
			}
			}
			break;
		}

		case 3:
		{
			system("cls");
			string newIDSV;
			string newname;
			string newbirthdate;
			string newgender;
			string newnumber;
			string newcls;
			do
			{
				cout << "               +=================================================+ \n";
				cout << "               |NHOM 3_____CHIEU THU 4______ALDS335764_22_2_02CLC| \n";
				cout << "               |-------------------------------------------------| \n";
				cout << "               |  1. NGUYEN VAN HAO                20119223      | \n";
				cout << "               |  2. DAO NGOC MINH HUY             20119045      | \n";
				cout << "               |  3. PHAN NHAT MINH                20119033      | \n";
				cout << "               +=================================================+ \n";
				cout << "                                                                   \n";
				cout << "               +=================================================+ \n";
				cout << "               | STT  |       SELECT ADJUST FUNCTION             | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  1.  |  Adjust by IDSV                          | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  2.  |  Adjust by reader name                   | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  0.  |  Exit                                    | \n";
				cout << "               +=================================================+ \n";
				cout << "               		  Select function: ";
				editchoice(adjust);
				switch (adjust)
				{
				case 1:
				{
					string ID;
					string IDSV = "IDSV";
					cout << "  Find by IDSV: ";
					editnumber(ID);
					findHuman(ID, IDSV);
					vector<BanDoc *> humanToFind = searchHuman(ID, IDSV);
					if (humanToFind.empty())
					{
						break;
					}
					cout << "  Enter new IDSV: ";
					editAdjustIDSV(newIDSV);
					cout << "  Enter new name: ";
					getline(cin, newname);
					editname(newname);
					do
					{
						cout << "+-------------+---------------+--------------+ \n";
						cout << "| 1. For male | 2. For female | 3. For other | \n";
						cout << "+-------------+---------------+--------------+ \n";
						cout << "  Enter new gender: ";
						editchoice(choice);
						switch (choice)
						{
						case 1:
						{
							newgender = "Male";
							break;
						}
						case 2:
						{
							newgender = "Female";
							break;
						}
						case 3:
						{
							newgender = "Other";
							break;
						}
						default:
						{
							cout << "  Wrong input! Please try again." << endl;
							break;
						}
						}
					} while (newgender.empty());
					bool valid_birthday = false;
					cout << "  Enter new birthday: ";
					do
					{
						cin >> newbirthdate;
						valid_birthday = editbirthday(newbirthdate);
					} while (!valid_birthday);
					cout << "  Enter new number: ";
					cin.ignore();
					editPhoneNumber(newnumber);
					cout << "  Enter new class: ";
					getline(cin, newcls);
					editclass(newcls);
					cout << "  Please check your enter again \n";
					displaynewadjustReader(newIDSV, newname, newbirthdate, newgender, newnumber, newcls);
					cout << "+-------------+--------------+ \n";
					cout << "| 1. For true | 0. For false | \n";
					cout << "+-------------+--------------+ \n";
					cout << "  Select your answer: ";
					editchoice(choice);
					switch (choice)
					{
					case 0:
					{
						std::cout << "  Exiting.....";
						std::this_thread::sleep_for(std::chrono::milliseconds(200));
						system("cls");
						break;
					}
					case 1:
					{
						adjustHuman(ID, IDSV, newIDSV, newname, newbirthdate, newgender, newnumber, newcls);
						exportDatahuman("human.txt");
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						system("cls");
						break;
					}
					}
					break;
				}

				case 2:
				{
					string nameSV;
					string name = "name";
					cout << "  Find by name: ";
					getline(cin, nameSV);
					editname(nameSV);
					findHuman(nameSV, name);
					vector<BanDoc *> humanToFind = searchHuman(nameSV, name);
					if (humanToFind.empty())
					{
						break;
					}
					cout << "  Enter new IDSV: ";
					editAdjustIDSV(newIDSV);
					cout << "  Enter new name: ";
					getline(cin, newname);
					editname(newname);
					do
					{
						cout << "+-------------+---------------+--------------+ \n";
						cout << "| 1. For male | 2. For female | 3. For other | \n";
						cout << "+-------------+---------------+--------------+ \n";
						cout << "  Enter new gender: ";
						editchoice(choice);
						switch (choice)
						{
						case 1:
						{
							newgender = "Male";
							break;
						}
						case 2:
						{
							newgender = "Female";
							break;
						}
						case 3:
						{
							newgender = "Other";
							break;
						}
						default:
						{
							cout << "  Wrong input! Please try again." << endl;
							break;
						}
						}
					} while (newgender.empty());
					bool valid_birthday = false;
					cout << "  Enter new birthday: ";
					do
					{
						cin >> newbirthdate;
						valid_birthday = editbirthday(newbirthdate);
					} while (!valid_birthday);
					cout << "  Enter new number: ";
					cin.ignore();
					editPhoneNumber(newnumber);
					cout << "  Enter new class: ";
					getline(cin, newcls);
					editclass(newcls);
					cout << "  Please check your enter again \n";
					displaynewadjustReader(newIDSV, newname, newbirthdate, newgender, newnumber, newcls);
					cout << "+-------------+--------------+ \n";
					cout << "| 1. For true | 0. For false | \n";
					cout << "+-------------+--------------+ \n";
					cout << "  Select your answer: ";
					editchoice(choice);
					switch (choice)
					{
					case 0:
					{
						std::cout << "  Exiting.....";
						std::this_thread::sleep_for(std::chrono::milliseconds(200));
						system("cls");
						break;
					}
					case 1:
					{
						adjustHuman(nameSV, name, newIDSV, newname, newbirthdate, newgender, newnumber, newcls);
						exportDatahuman("human.txt");
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						system("cls");
						break;
					}
					}
					break;
				}

				default:
				{
					cout << "  Wrong enter! Please enter again: " << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}

				case 0:
				{
					std::cout << "  Exiting.....";
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}
				}
			} while (adjust != 0);
			break;
		}

		case 4:
		{
			string IDSV;
			string ID = "IDSV";
			cout << "  Enter ID to delete: ";
			editAdjustIDSV(IDSV);
			findHuman(IDSV, ID);
			vector<BanDoc *> humanToFind = searchHuman(IDSV, ID);
			if (humanToFind.empty())
			{
				break;
			}
			cout << "  You want to delete this person? \n";
			cout << "+------------+-----------+ \n";
			cout << "| 1. For yes | 0. For no | \n";
			cout << "+------------+-----------+ \n";
			cout << "  Select your answer: ";
			editchoice(choice);
			switch (choice)
			{
				case 0:
				{
					std::cout << "  Exiting.....";
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}
				case 1:
				{
					DeleteBanDoc(IDSV);
					exportDatahuman("human.txt");
					std::cout << "  Delete successfully.....";
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					system("cls");
					break;
				}
			}
			break;
		}

		case 5:
		{
			system("cls");
			do
			{
				cout << "               +=================================================+ \n";
				cout << "               |NHOM 3_____CHIEU THU 4______ALDS335764_22_2_02CLC| \n";
				cout << "               |-------------------------------------------------| \n";
				cout << "               |  1. NGUYEN VAN HAO                20119223      | \n";
				cout << "               |  2. DAO NGOC MINH HUY             20119045      | \n";
				cout << "               |  3. PHAN NHAT MINH                20119033      | \n";
				cout << "               +=================================================+ \n";
				cout << "                                                                   \n";
				cout << "               +=================================================+ \n";
				cout << "               | STT  |          SELECT SEARCH FUNCTION          | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  1.  |  Find by IDSV                            | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  2.  |  Find by name                            | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  3.  |  Find by birthdate                       | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  4.  |  Find by gender                          | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  5.  |  Find by phone number                    | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  6.  |  Find by class                           | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  0.  |  Exit                                    | \n";
				cout << "               +=================================================+ \n";
				cout << "                         Select function: ";
				editchoice(find);
				switch (find)
				{
				case 1:
				{
					system("cls");
					string ID;
					string IDSV = "IDSV";
					cout << "  Find by IDSV: ";
					editAdjustIDSV(ID);
					findHuman(ID, IDSV);
					returnToPreviousFunction();
					break;
				}

				case 2:
				{
					system("cls");
					string nameSV;
					string name = "name";
					cout << "  Find by name: ";
					getline(cin, nameSV);
					editname(nameSV);
					findHuman(nameSV, name);
					returnToPreviousFunction();
					break;
				}

				case 3:
				{
					system("cls");
					string birthday;
					string birthdate = "birthdate";
					bool valid_birthday = false;
					cout << "  Enter student's birthday: ";
					do
					{
						cin >> birthday;
						valid_birthday = editbirthday(birthday);
					} while (!valid_birthday);
					findHuman(birthday, birthdate);
					returnToPreviousFunction();
					break;
				}

				case 4:
				{
					system("cls");
					string gender;
					string gioitinh = "gender";
					do
					{
						cout << "+-------------+---------------+--------------+ \n";
						cout << "| 1. For male | 2. For female | 3. For other | \n";
						cout << "+-------------+---------------+--------------+ \n";
						cout << "  Enter finding gender: ";
						editchoice(choice);
						switch (choice)
						{
						case 1:
						{
							gender = "Male";
							break;
						}
						case 2:
						{
							gender = "Female";
							break;
						}
						case 3:
						{
							gender = "Other";
							break;
						}
						default:
						{
							cout << "  Wrong input! Please try again." << endl;
							break;
						}
						}
					} while (gender.empty());
					findHuman(gender, gioitinh);
					returnToPreviousFunction();
					break;
				}

				case 5:
				{
					system("cls");
					string numberSV;
					string number = "number";
					cout << "  Find by phone number: ";
					editPhoneNumber(numberSV);
					findHuman(numberSV, number);
					returnToPreviousFunction();
					break;
				}

				case 6:
				{
					system("cls");
					string Class;
					string cls = "cls";
					cout << "  Find by class: ";
					getline(cin, Class);
					editclass(Class);
					findHuman(Class, cls);
					returnToPreviousFunction();
					break;
				}

				default:
				{
					cout << "  Wrong enter! Please enter again: " << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}

				case 0:
				{
					std::cout << "  Exiting.....";
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}
				}
			} while (find != 0);
			break;
		}

		case 6:
		{
			system("cls");
			do
			{
				cout << "               +=================================================+ \n";
				cout << "               |NHOM 3_____CHIEU THU 4______ALDS335764_22_2_02CLC| \n";
				cout << "               |-------------------------------------------------| \n";
				cout << "               |  1. NGUYEN VAN HAO                20119223      | \n";
				cout << "               |  2. DAO NGOC MINH HUY             20119045      | \n";
				cout << "               |  3. PHAN NHAT MINH                20119033      | \n";
				cout << "               +=================================================+ \n";
				cout << "                                                                   \n";
				cout << "               +=================================================+ \n";
				cout << "               | STT  |         SELECT ARRANGE FUNCTION          | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  1.  |  Arrange by name                         | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  2.  |  Arrange by IDSV                         | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  3.  |  Arrange by class                        | \n";
				cout << "               |------|------------------------------------------| \n";
				cout << "               |  0.  |  Exit                                    | \n";
				cout << "               +=================================================+ \n";
				cout << "                		  Select function: ";
				editchoice(arrange);
				switch (arrange)
				{
				case 1:
				{
					system("cls");
					cout << "Arrange by name:\n";
					string sortBy = "name";
					displaySortedHuman(sortBy);
					exportDatahuman("human.txt");
					returnToPreviousFunction();
					break;
				}

				case 2:
				{
					system("cls");
					cout << "Arrange by IDSV:\n";
					string sortBy = "IDSV";
					displaySortedHuman(sortBy);
					exportDatahuman("human.txt");
					returnToPreviousFunction();
					break;
				}

				case 3:
				{
					system("cls");
					cout << "Arrange by class:\n";
					string sortBy = "cls";
					displaySortedHuman(sortBy);
					exportDatahuman("human.txt");
					returnToPreviousFunction();
					break;
				}

				default:
				{
					cout << "  Wrong enter! Please enter again: " << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}

				case 0:
				{
					std::cout << "  Exiting.....";
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					system("cls");
					break;
				}
				}
			} while (arrange != 0);
			break;

		default:
		{
			cout << "  Wrong enter! Please enter again: " << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			system("cls");
			break;
		}
		case 0:
			cout << "  Exiting...." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			system("cls");
			return;
		}
			cout << endl;
			system("cls");
		}
	}
	return;
}
// End interface Reader-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Interface------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Interface_main()
{
	readFromFilehuman("human.txt");
	readFromFile("Sach.txt");
	int choice;
	while (true)
	{
		cout << "               +=================================================+ \n";
		cout << "               |NHOM 3_____CHIEU THU 4______ALDS335764_22_2_02CLC| \n";
		cout << "               |-------------------------------------------------| \n";
		cout << "               |  1. NGUYEN VAN HAO                20119223      | \n";
		cout << "               |  2. DAO NGOC MINH HUY             20119045      | \n";
		cout << "               |  3. PHAN NHAT MINH                20119033      | \n";
		cout << "               +=================================================+ \n";
		cout << "                                                                   \n";
		cout << "               +=================================================+ \n";
		cout << "               | STT  |       LIBRARY MANAGEMENT SORFWARE        | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  1.  |  BOOK MANAGEMENT                         | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  2.  |  HUMAN MANAGEMENT                        | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  3.  |  BORROW BOOK                             | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  4.  |  RETURN BOOK                             | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  5.  |  Borrower Statistics                     | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  6.  |  Returner Statistics                     | \n";
		cout << "               |------|------------------------------------------| \n";
		cout << "               |  0.  |  Exit                                    | \n";
		cout << "               +=================================================+ \n";
		cout << "                		  Select function: ";
		editchoice(choice);
		switch (choice)
		{
		case 1:
		{
			system("cls");
			InterfaceBook();
			break;
		}

		case 2:
		{
			system("cls");
			InterfaceReader();
			break;
		}

		case 3:
		{
			cout << "  ->BORROW BOOK!" << endl;
			borrowBook();
			returnToPreviousFunction();
			break;
		}

		case 4:
		{
			cout << "  ->RETURN BOOK!" << endl;
			returnBook();
			returnToPreviousFunction();
			break;
		}
		
		case 5:
		{
			displayBorrowedBooks();
			returnToPreviousFunction();
			break;
		}
		
		case 6: 
		{
			displayReturnData();
			returnToPreviousFunction();
			break;
		}

		default:
		{
			cout << "  Wrong enter! Please enter again: " << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			system("cls");
			break;
		}

		case 0:
			cout << "  Good bye, have a nice day!" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			system("cls");
			return;
		}
		cout << endl;
		system("cls");
	}
}
// End Interface------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// login -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void login()
{
	string username, pass;
	int choice;
	while (true)
	{
		cout << "                                  +=================================================+ \n";
		cout << "                                  |NHOM 3_____CHIEU THU 4______ALDS335764_22_2_02CLC| \n";
		cout << "                                  |-------------------------------------------------| \n";
		cout << "                                  |  1. NGUYEN VAN HAO                20119223      | \n";
		cout << "                                  |  2. DAO NGOC MINH HUY             20119045      | \n";
		cout << "                                  |  3. PHAN NHAT MINH                20119033      | \n";
		cout << "                                  +=================================================+ \n";
		cout << "                                                                                      \n";
		cout << "                                  +=================================================+ \n";
		cout << "                                  |                       LOGIN                     | \n";
		cout << "                                  |-------------------------------------------------| \n";
		cout << "                                  |   +----------+                  +-----------+   | \n";
		cout << "                                  |   | 1. Login |                  | 2. Create |   | \n";
		cout << "                                  |   +----------+                  +-----------+   | \n";
		cout << "                                  +=================================================+ \n";
		cout << "                                                         Select: ";
		editchoice(choice);
		switch (choice)
		{
		case 1:
		{
			while (true)
			{
				cout << "  -> Enter username: \n";
				cout << "          ";
				getline(cin, username);
				cout << "  -> Enter password: \n";
				cout << "          ";
				getline(cin, pass);
				if (!trueuser(username, pass))
				{
					cout << "  Wrong username or password! Please check again! \n";
					continue;
				}
				break;
			}
			system("cls");
			Interface_main();
			break;
		}

		case 2:
		{
			create();
			returnToPreviousFunction();
			break;
		}

		default:
		{
			cout << "  Wrong enter! Please enter again: " << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			system("cls");
			break;
		}
		}
	}
	return;
}

int main()
{
	system("cls");
	login();
}

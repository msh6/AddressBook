/*	Creating an Address Book program that allows users to add, edit, and delete contacts.
	Individual contact will have the details such as name, address, phone number, and email address.
*/

#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<string>
#include<vector>

/*	Creating the Contact struct*/
struct Contact {
	std::string m_name;
	std::string m_num;
	std::string m_email;
};

// Displaying the Menu
void showMenu() {
	std::cout << "1. Add new contact" << "\n";
	std::cout << "2. View all contacts" << "\n";
	std::cout << "3. Edit a contact" << "\n";
	std::cout << "4. Delete a contact" << "\n";
	std::cout << "5. Quit" << "\n\n";
}

void viewContacts(const std::vector<Contact>& contacts){
	if (contacts.empty()) {
		std::cout << "No contacts found" << "\n";
		return;
	}
	for (const auto& contact : contacts) {
		std::cout << "Name : " << contact.m_name << "\n";
		std::cout << "Phone Number : " << contact.m_num << "\n";
		std::cout << "Email : " << contact.m_email << "\n\n";
	}	
}

void addContact(std::vector<Contact>& contacts) {
	std::cout << "Creating a new contact...\nProvide the asked details...\n\n";
	Contact newContact;
	std::cout << "Enter contact name :";
	std::getline(std::cin, newContact.m_name);
	std::cout << "Enter contact phone number :";
	std::getline(std::cin, newContact.m_num);
	std::cout << "Enter contact e-mail : ";
	std::getline(std::cin, newContact.m_email);
	contacts.push_back(newContact);
}

void editContact(std::vector<Contact>& contacts) {
	if (contacts.empty()) {
		std::cout << "No contacts found" << "\n";
		return;
	}
	std::string name;

	std::cout << "Enter the name of the contact to edit: ";
	std::getline(std::cin, name);
	auto it = find_if(contacts.begin(), contacts.end(), [&
	](const Contact& c) {return  c.m_name == name; });
	if (it == contacts.end()) {
		std::cout << "Contact not found" << "\n";
		return;
	}
	std::cout << "Enter new phone number: ";
	std::getline(std::cin, it->m_num);
	std::cout << "Enter new email address: ";
	std::getline(std::cin, it->m_email);
	std::cout << "Contact updated" << "\n";
}

void deleteContact(std::vector<Contact>& contacts) {
	if (contacts.empty()) {
		std::cout << "No contacts found" << "\n";
		return;
	}
	std::string name;
	std::cout << "Enter the name of the contact to delete: ";
	std::getline(std::cin, name);
	auto it = find_if(contacts.begin(), contacts.end(), [&](const Contact& c) {return c.m_name == name;});
	if (it == contacts.end()) {
		std::cout << "Contact not found" << "\n";
		return;
	}
	contacts.erase(it);
	std::cout << "Contact deleted" << "\n";
}

void saveContactsToFile(const std::vector<Contact>& contacts) {
	std::ofstream outfile("contacts.txt");
	if (!outfile) {
		std::cerr << "Error opening file" << "\n";
		return;
	}
	for (const auto& contact : contacts) {
		outfile << contact.m_name << "\n";
		outfile << contact.m_num << "\n";
		outfile << contact.m_email << "\n";
	}
}

void loadContactsFromFile(std::vector<Contact>& contacts) {
	std::ifstream infile("contacts.txt");
	if (!infile) {
		std::cerr << "Error opening file" << "\n";
		return;
	}
	Contact contact;
	while (std::getline(infile, contact.m_name) && std::getline(infile, contact.m_num) && std::getline(infile, contact.m_email)) {
		contacts.push_back(contact);
	}
}

int main() {
	
	std::vector<Contact> contacts;
	loadContactsFromFile(contacts);
	while (true) {
		showMenu();
		int choice;
		std::cout << "Please select an option: ";
		std::cin >> choice;
		if (choice == 1) {
			addContact(contacts);
			//saveContactsToFile(contacts);
		}
		else if (choice == 2) {
			viewContacts(contacts);
		}
		else if (choice == 3) {
			editContact(contacts);
		}
		else if (choice == 4) {
			deleteContact(contacts);
		}
		else if (choice == 5)
			return false;
	}

	system("pause>0");
}
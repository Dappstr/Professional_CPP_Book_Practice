#include <iostream>
#include <format>
#include <string>
#include <exception>
#include <stdexcept>

import employee;
import database;

void unitTest();
int displayMenu();
void doHire(Records::Database& db);
void doFire(Records::Database& db);
void doPromote(Records::Database& db);

int main()
{
	using namespace Records;

	unitTest();

	Database employeeDB;
	bool done{ false };
	
	while (!done)
	{
		int selection{ displayMenu() };
		switch (selection)
		{
			case 0:
				done = true;
				break;
			case 1:
				doHire(employeeDB);
				break;
			case 2:
				doFire(employeeDB);
				break;
			case 3:
				doPromote(employeeDB);
				break;
			case 4:
				employeeDB.displayAll();
				break;
			case 5:
				employeeDB.displayCurrent();
				break;
			case 6:
				employeeDB.displayFormer();
				break;
			[[unlikely]] default:
				std::cerr << "Unknown Command\n";
				break;
		}
	}

	return EXIT_SUCCESS;
}

void unitTest()
{
	using namespace Records;

	Employee dappster{ "Lane", "Dappster" };
	dappster.setFirstName("Dappster");
	dappster.setLastName("Lane");
	dappster.setEmployeeNumber(1337);
	dappster.setSalary(120000);
	dappster.promote();
	//dappster.demote();
	dappster.hire();

	Employee dappster2{ "Lane2", "Dappster2" };
	dappster2.setFirstName("Dappster2");
	dappster2.setLastName("Lane2");
	dappster2.setEmployeeNumber(31337);
	dappster2.setSalary(124000);
	dappster2.promote();
	dappster2.demote();
	dappster2.hire();

	Database databaseOne;
	databaseOne.addEmployee(dappster);
	databaseOne.addEmployee(dappster2);
	databaseOne.displayAll();
}

int displayMenu()
{
	int selection{};

	std::cout << "\nEmployee Database\n";
	std::cout << "------------------------------\n";
	std::cout << "1) Hire a new employee\n";
	std::cout << "2) Fire a new employee\n";
	std::cout << "3) Promote an employee\n";
	std::cout << "4) Display all employees\n";
	std::cout << "5) Display current employees\n";
	std::cout << "6) Display former employees\n\n";
	std::cout << "----> ";
	std::cin >> selection;

	return selection;
}

void doHire(Records::Database& db)
{
	std::string firstName{}, lastName{};
	
	std::cout << "First name: ";
	std::cin >> firstName;

	std::cout << "Last name: ";
	std::cin >> lastName;

	auto& employee{ db.addEmployee(firstName, lastName) };
	std::cout << std::format("Hired employee {} {} with employee number {}.", firstName, lastName, employee.getEmployeeNumber()) << '\n';
}

void doFire(Records::Database& db)
{
	int employeeNumber{};
	
	std::cout << "Employee number: ";
	std::cin >> employeeNumber;

	try
	{
		auto& employee{ db.getEmployee(employeeNumber) };
		employee.fire();
		std::cout << std::format("Employee {} terminated\n", employeeNumber);
	}
	catch (const std::logic_error& err)
	{
		std::cerr << "Unable to terminate employee!\n" << err.what();
	}
}

void doPromote(Records::Database& db)
{
	int employeeNumber{};
	
	std::cout << "Employee number: ";
	std::cin >> employeeNumber;

	int raiseAmount{};
	std::cout << "Raise amount: ";
	std::cin >> raiseAmount;

	try
	{
		auto& employee{ db.getEmployee(employeeNumber) };
		employee.promote(raiseAmount);
		std::cout << std::format("Employee {} promoted\n", employeeNumber);
	}
	catch (const std::logic_error& err)
	{
		std::cerr << "Unable to promote employee!\n" << err.what();
	}
}

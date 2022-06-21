module employee;
import <iostream>;
import <format>;

namespace Records
{
	Employee::Employee(const std::string& firstName, const std::string& lastName)
		:m_firstName{ firstName }, m_lastName{ lastName }
	{}

	void Employee::promote(int raiseAmount) { setSalary(getSalary() + raiseAmount); }
	void Employee::demote(int demeritAmount) { setSalary(getSalary() - demeritAmount); }
	
	void Employee::hire() { m_hired = true; }
	void Employee::fire() { m_hired = false; }
	
	void Employee::display() const
	{
		using std::cout, std::format;

		cout << format("Employee: {}, {}", getFirstName(), getLastName()) << '\n';
		cout << "------------------------------\n";
		cout << (isHired() ? "Current employee" : "Currently not an employee") << '\n';
		cout << format("Employee Number: {}", getEmployeeNumber()) << '\n';
		cout << format("Salary: ${}", getSalary()) << '\n';
	}

	void Employee::setFirstName(const std::string& firstName) { m_firstName = firstName; }
	void Employee::setFirstName(std::string&& firstName) && { m_firstName = std::move(firstName) ;}

	[[nodiscard]] const std::string& Employee::getFirstName() const { return m_firstName; }

	void Employee::setLastName(const std::string& lastName) { m_lastName = lastName; }
	void Employee::setLastName(std::string&& lastName) && { m_lastName = std::move(lastName); }

	[[nodiscard]] const std::string& Employee::getLastName() const { return m_lastName; }

	void Employee::setEmployeeNumber(const size_t id)
	{
		if (id < 0) { std::cerr << "Invalid ID number.\n"; }
		else m_employeeNumber = id;
	}
	size_t Employee::getEmployeeNumber() const { return m_employeeNumber; }

	void Employee::setSalary(int newSalary)
	{ 
		if (newSalary < 0) { std::cerr << "New salary value is too low.\n"; }
		else m_salary = newSalary;
	}
	[[nodiscard]] int Employee::getSalary() const noexcept(noexcept(m_salary >= 0)) { return m_salary; }

	bool Employee::isHired() const { return m_hired; }

	Employee::Employee(const Employee&) = default;
	Employee::Employee(Employee&&) = default;

	Employee& Employee::operator=(const Employee&) = default;
	Employee& Employee::operator=(Employee&&) = default;

	Employee::~Employee() = default;
}
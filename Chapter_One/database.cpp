module database;
import <stdexcept>;
import employee;

namespace Records
{
	Employee& Database::addEmployee(const std::string& firstName, const std::string& lastName)
	{
		Employee theEmployee{ firstName, lastName };
		theEmployee.setEmployeeNumber(m_nextEmployeeNumber++);
		theEmployee.hire();
		m_employees.push_back(theEmployee);
		return m_employees.back();
	}

	Employee& Database::getEmployee(int employeeNumber)
	{
		for (auto& employee : m_employees)
		{
			if (employee.getEmployeeNumber() == employeeNumber)
				return employee;
		}
		throw std::logic_error{ "No employee found.\n" };
	}

	Employee& Database::getEmployee(const std::string& firstName, const std::string& lastName)
	{
		for (auto& employee : m_employees)
		{
			if (employee.getFirstName() == firstName && employee.getLastName() == lastName)
				return employee;
		}
		throw std::logic_error{ "No employee found.\n" };
	}

	void Database::displayAll()
	{
		for (auto& employee : m_employees) { employee.display(); }
	}

	void Database::displayCurrent()
	{
		for (const auto& employee : m_employees)
		{
			if (employee.isHired())
				employee.display();
		}
	}

	void Database::displayFormer()
	{
		for (const auto& employee : m_employees)
		{
			if (not(employee.isHired()))
				employee.display();
		}
	}
}
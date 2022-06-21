export module database;

import <string>;
import <vector>;
import employee;

namespace Records
{
	constexpr int firstEmployeeNumber{ 1'000 };

	export class Database
	{
	private:
		std::vector<Employee> m_employees{};
		int m_nextEmployeeNumber{ firstEmployeeNumber };
	
	public:
		Employee& addEmployee(const std::string& firstName, const std::string& lastName);
		Employee& getEmployee(int employeeNumber);
		Employee& getEmployee(const std::string& firstName, const std::string& lastName);

		void displayAll();
		void displayCurrent();
		void displayFormer();
	};
}
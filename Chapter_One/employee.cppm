export module employee;
import <string>;

namespace Records
{
	const int defaultStartingSalary{ 30'000 };
	export extern const int defaultRaiseAndDemeritAmount{1'000}; //Visual Studio 2022 Preview has an issue with exporting const variables due to linkage. So I declared it extern just to remove the annoying red squigle.

	export class Employee
	{
	private:
		std::string m_firstName{};
		std::string m_lastName{};
		size_t m_employeeNumber{0};
		int m_salary{defaultStartingSalary};
		bool m_hired{ false };

	public:
		Employee(const std::string& firstName, const std::string& lastName);

		void promote(int raiseAmount = defaultRaiseAndDemeritAmount);
		void demote(int demeritAmount = defaultRaiseAndDemeritAmount);
		void hire();
		void fire();
		void display() const;

		void setFirstName(const std::string& firstName);
		void setFirstName(std::string&& firstName) &&;

		[[nodiscard]] const std::string& getFirstName() const;

		void setLastName(const std::string& lastName);
		void setLastName(std::string&& lastName) &&;

		void setEmployeeNumber(const size_t id);
		size_t getEmployeeNumber() const;

		[[nodiscard]] const std::string& getLastName() const;

		void setSalary(int newSalary);
		[[nodiscard]] int getSalary() const noexcept(noexcept(m_salary >= 0));

		bool isHired() const;

		Employee(const Employee&);
		Employee(Employee&&);

		Employee& operator=(const Employee&);
		Employee& operator=(Employee&&);

		~Employee();
	};
}
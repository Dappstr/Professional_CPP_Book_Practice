#include <iostream>
import employee;

int main()
{
	using namespace Records;

	Employee dappster{"Lane", "Dappster"};
	
	dappster.setFirstName("Dappster");
	dappster.setLastName("Lane");
	dappster.setEmployeeNumber(1337);
	dappster.setSalary(120000);
	dappster.promote();
	dappster.demote();
	dappster.hire();
	dappster.display();
}

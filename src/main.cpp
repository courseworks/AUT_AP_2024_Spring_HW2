#include <gtest/gtest.h>

#include <iostream>

#include "Account.h"
#include "Bank.h"
#include "Person.h"

int main(int argc, char **argv) {
	if (true)  // make false to run unit-tests
	{
		// debug section
	} else {
		::testing::InitGoogleTest(&argc, argv);
		std::cout << "RUNNING TESTS ..." << std::endl;
		int ret{RUN_ALL_TESTS()};
		if (!ret)
			std::cout << "<<<SUCCESS>>>" << std::endl;
		else
			std::cerr << "FAILED" << std::endl;
	}
	return 0;
}

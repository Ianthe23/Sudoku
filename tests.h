#ifndef TESTS_H_
#define TESTS_H_

#include "domain.h"
#include "repo.h"
#include <assert.h>
#include <iostream>

class Tests {
	void testDomain();
	void testRepo();
public:
	Tests() noexcept {};
	void testAll();
	~Tests() {

	};
};

#endif /* TESTS_H_ */
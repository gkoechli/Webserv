#include "method.hpp"
#include <criterion.h>
/*
Should start by external interface before internal implementation.
-> constructor/getter/setter first?
->then simple operation from mock variables
->then real operations, real implementation
->then refactor
Need to write a test list in text

to define objectives of the current module
-initialisation state

*/
Test(method, construct)
{
	Method method("../../testfiles/empty");
	cr_assert_eq(method.get_status_code(), 200);
	cr_assert_eq(method.get_path(), "../../testfiles/empty");
}

Test(method, check_empty)
{
	Method method("../../testfiles/empty");
	cr_assert_eq(method.get_status_code(), 200);
	std::ifstream File("../../testfiles/empty");
	cr_expect_eq(method.check_error(), true);
	cr_assert_eq(method.get_status_code(), 204);
}
#define BOOST_TEST_MODULE empty node
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "matheval.hpp"

BOOST_AUTO_TEST_CASE(empty_node)
{
    matheval::ast::expression ast;
    matheval::ast::eval solver({});
    BOOST_CHECK_EQUAL(solver(ast),0);
}

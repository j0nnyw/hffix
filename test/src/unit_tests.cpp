#define BOOST_TEST_MODULE hffix Unit Tests
#include <boost/test/included/unit_test.hpp>

#include <hffix.hpp>
#include <hffix_fields.hpp>

using namespace hffix;

BOOST_AUTO_TEST_CASE(basic)
{
    char b[1024];
    message_writer w(b, b + sizeof(b));
    w.push_back_header("FIX.4.2");
    w.push_back_string(tag::MsgType, "A");
    w.push_back_trailer();
    message_reader r(b, b + sizeof(b));

    // A reader constructed from a writer should have the same size.
    BOOST_CHECK(w.message_size() == r.message_size());

    // Construct an invalid iterator.
    message_reader::const_iterator j;

    // Field value comparisons.
    message_reader::const_iterator i = r.begin();
    BOOST_CHECK(r.find_with_hint(tag::MsgType, i));
    BOOST_CHECK(i->value() == "A");
    BOOST_CHECK(i->value() == (const char*)"A");
    BOOST_CHECK(i->value() != "B");
    BOOST_CHECK(i->value() == std::string("A"));
    BOOST_CHECK(i->value() != std::string("B"));
}


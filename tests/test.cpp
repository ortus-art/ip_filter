#include <ip_filter.h>

#include <gtest/gtest.h>
#include <openssl/md5.h>

#include <string>
#include <sstream>
#include <fstream>

using namespace testing;

TEST(main_case, split_on_tab)
{
    std::string test("test\ttest");
    auto result = ip_filter::split_line(test);
    ASSERT_EQ(std::get<0>(result), "test");
    ASSERT_EQ(std::get<1>(result), "test");

}

TEST(main_case, trim_space)
{
    std::string test(" test \ttest");
    auto result = ip_filter::split_line(test);
    ASSERT_EQ(std::get<0>(result), "test");
}

TEST(main_case, trim_new_line)
{
    std::string test("\n test \ttest");
    auto result = ip_filter::split_line(test);
    ASSERT_EQ(std::get<0>(result), "test");
}

TEST(main_case, trim_first_octet)
{
    std::string test("1.11.24.101\ttest");
    auto result = ip_filter::split_line(test);
    result = ip_filter::split_line(std::get<0>(result), '.');
    ASSERT_EQ(std::get<0>(result), "1");
    ASSERT_EQ(std::get<1>(result), "11.24.101");
}


TEST(main_case, parse_ip)
{
    std::string test("1.11.24.101");
    auto result {ip_filter::parse_ip(test)};
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 11);
    ASSERT_EQ(result[2], 24);
    ASSERT_EQ(result[3], 101);

}


TEST(main_case, exception_number_out_range)
{
    std::string test("1111.11.24.101");
    try {
        ip_filter::parse_ip(test);
        FAIL() << "Expected ip_filter::parser_error";
    } catch (ip_filter::parser_error & e) {
         EXPECT_EQ(e.what(),std::string("Octet out of range"));
    } catch (std::exception & e) {
        FAIL() << "Expected ip_filter::parser_error" << e.what();
    } catch (...) {
        FAIL() << "Expected ip_filter::parser_error";
    }
}

TEST(main_case, exception_bad_format)
{
    std::string test("a");
    try {
        ip_filter::parse_ip(test);
        FAIL() << "Expected ip_filter::parser_error";
    } catch (ip_filter::parser_error & e) {
         EXPECT_EQ(e.what(),std::string("Cannot parse to int"));
    } catch (std::exception & e) {
        FAIL() << "Expected ip_filter::parser_error" << e.what();
    } catch (...) {
        FAIL() << "Expected ip_filter::parser_error";
    }
}


TEST(main_case, exception_data_too_long)
{
    std::string test("1.11.24.101.a");
    try {
        ip_filter::parse_ip(test);
        FAIL() << "Expected ip_filter::parser_error";
    } catch (ip_filter::parser_error & e) {
         EXPECT_EQ(e.what(),std::string("Failed to parse IP address"));
    } catch (std::exception & e) {
        FAIL() << "Expected ip_filter::parser_error" << e.what();
    } catch (...) {
        FAIL() << "Expected ip_filter::parser_error";
    }
}

TEST(main_case, input_parse)
{
    std::istringstream is(
    "113.162.145.15\t111\t0\n"
    "157.39.22.224\t5\t6\n"
    "79.180.73.190\t2\t1\n"
    "179.210.145.4\t22\t0\n");

    std::ostringstream log;

    auto result = ip_filter::parse(is, log);
    ASSERT_EQ(result.size(), 4);
    ip_filter::ip_octets oct ={113, 162, 145, 15};
    ASSERT_EQ(result[0], oct);
    oct ={157, 39, 22, 224};
    ASSERT_EQ(result[1], oct);

}

TEST(main_case, input_remove_duplicates)
{
    std::istringstream is(
    "113.162.145.15\t111\t0\n"
    "157.39.22.224\t5\t6\n"
    "79.180.73.190\t2\t1\n"
    "79.180.73.190\t2\t1\n"
    "79.180.73.190\t2\t1\n"
    "179.210.145.4\t22\t0\n"
    "113.162.145.15\t111\t0\n");

    std::ostringstream os;

    ip_filter::parse_and_print(is, os, os);
    ASSERT_EQ(os.str(),
               "179.210.145.4\n"
               "157.39.22.224\n"
               "113.162.145.15\n"
               "79.180.73.190\n"
              );

}

TEST(main_case, input_bad)
{
     std::istringstream is(
    "113.162.145.15\t111\t0\n"
    "157.39.22.224\t5\t6\n"
    "79.180.73.190aaaa\t2\t1\n"
    "179.210.145.4\t22\t0\n");

    std::ostringstream log;

    auto result = ip_filter::parse(is, log);
    ASSERT_EQ(result.size(), 3);
    ip_filter::ip_octets oct ={113, 162, 145, 15};
    ASSERT_EQ(result[0], oct);
    oct ={157, 39, 22, 224};
    ASSERT_EQ(result[1], oct);
    ASSERT_EQ(log.str(), "Error parsing line: 79.180.73.190aaaa:Cannot parse to int\n");

}

TEST(main_case, parse_and_print)
{
    std::istringstream is(
    "113.162.145.15\t111\t0\n"
    "157.39.22.224\t5\t6\n"
    "79.180.73.190\t2\t1\n"
    "179.210.145.4\t22\t0\n");

    std::ostringstream os;

    ip_filter::parse_and_print(is, os, os);
    ASSERT_EQ(os.str(),
               "179.210.145.4\n"
               "157.39.22.224\n"
               "113.162.145.15\n"
               "79.180.73.190\n"
              );
}

#ifdef PROJECT_SOURCE_DIR
TEST(main_case, input_test_file)
{
    std::ifstream file{PROJECT_SOURCE_DIR "/data/data.tsv"};
    std::ostringstream os, os_result;
    ip_filter::parse_and_print(file, os, os);

    unsigned char result[MD5_DIGEST_LENGTH];
    auto out =  os.str();
    MD5((const unsigned char*)out.c_str(), out.size(), result);

    os_result<<std::hex<<std::setfill('0');
    for(long long c: result)
    {
        os_result<<std::setw(2)<<(long long)c;
    }

    ASSERT_EQ(os_result.str(),
               "37a9ee52ffb12c9ffcc961fae39d12b3"
              );
}
#endif




int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

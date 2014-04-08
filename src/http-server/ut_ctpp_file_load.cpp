#ifndef BOOST_STATIC_LINK
#   define BOOST_TEST_DYN_LINK
#endif // BOOST_STATIC_LINK

#define BOOST_TEST_MODULE CtppHtml
#define BOOST_AUTO_TEST_MAIN

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/format.hpp>
#include <boost/utility.hpp> 

#include "Log.hpp"
#include "HtmlMaker.hpp"


const char TEST_TMPL[] = 
    "<html>" 
        "<head>" 
            "<title>News List</title>" 
            "<style type=\"text/css\">" 
                "a {" 
                    "font-family: Verdana, Arial, Helvetica, sans-serif;" 
                    "color: black; font-size: 8pt; font-weight: bold;" 
                "}" 
                "span {" 
                    "font-family: Verdana, Arial, Helvetica, sans-serif;" 
                    "color: black; font-size: 10pt; font-weight: normal;" 
                "}" 
                "span.date {" 
                    "font-family: Verdana, Arial, Helvetica, sans-serif;" 
                    "color: #D00000; font-size: 10pt; font-weight: normal;" 
                "}" 
            "</style>" 
        "</head>" 
        "<body>" 
            "<TMPL_var TEXT_FILE_LOAD(test_file_name)>" 
        "</body>" 
    "</html>";


const char TEST_JSON[] = 
    "{\n"
    "   \"test_file_name\" : \"ut_ctpp_file_load.cpp\""
    "}\n";


const char RESULT[] = "";


struct TestGenerate {
    TestGenerate(const base::bfs::path &cur_path) {
        tmplt::FileSaver file_tmpl(TEST_TMPL, sizeof(TEST_TMPL) - 1, (cur_path / "test.tmpl").string());
        tmplt::FileSaver file_json(TEST_JSON, sizeof(TEST_JSON) - 1, (cur_path / "test.json").string());
        http_server::HtmlMaker make((cur_path / "test.html").string());
        std::string file_make = make;
        tmplt::FileContent fcont(file_make);
        BOOST_CHECK_EQUAL(std::string(fcont), std::string(RESULT));
    }
};


BOOST_AUTO_TEST_CASE(TestCtppTextFileLoad) {
    LOG_TO_STDOUT;
    base::bfs::path cur_path = base::bfs::absolute(base::bfs::current_path());
   
    if (base::bfs::exists(cur_path / "test.html")) {
        LOG(DEBUG) << "Remove `" << (cur_path / "test.html") << "`";
        base::bfs::remove(cur_path / "test.html");
    }
    TestGenerate tgen(cur_path);
}

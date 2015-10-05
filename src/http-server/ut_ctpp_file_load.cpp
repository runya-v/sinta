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


const char TEST_JSON[] = 
	"{\n"   
	"	\"test_file_name\" : \"test.txt\"\n"
	"}\n";


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
            "<title>FastSort.cpp</title>" 
            "<TMPL_var TEXT_FILE_LOAD(test_file_name)>" 
        "</body>" 
    "</html>";


const char TEST_TEXT_FILE[] = 
	"int n, a[n]; //n - количество элементов\n"
	"void qs(int* s_arr, int first, int last) {\n"
	"	int i = first, j = last, x = s_arr[(first + last) / 2];\n"
	"\n" 
	"	do {\n"
	"		while (s_arr[i] < x) i++;\n"
	"		while (s_arr[j] > x) j--;\n"
	"\n"
	"		if(i <= j) {\n"
	"			if (i < j) swap(s_arr[i], s_arr[j]);\n"
	"			i++;\n"
	"			j--;\n"
	"		}\n"
	"	}\n" 
	"	while (i <= j);\n"
	"\n"
	"	if (i < last) {\n"
	"		qs(s_arr, i, last);\n"
	"	}\n"
	"\n"    
	"	if (first < j) {\n"
	"		qs(s_arr, first,j);\n"
	"	}\n"
	"}\n";


const char RESULT[] = 
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
			"<title>FastSort.cpp</title>"
				"int n, a[n]; //n - количество элементов\n"
				"void qs(int* s_arr, int first, int last) {\n"
				"	int i = first, j = last, x = s_arr[(first + last) / 2];\n"
				"\n"
				"	do {\n"
				"		while (s_arr[i] < x) i++;\n"
				"		while (s_arr[j] > x) j--;\n"
				"\n"
				"		if(i <= j) {\n"
				"			if (i < j) swap(s_arr[i], s_arr[j]);\n"
				"			i++;\n"
				"			j--;\n"
				"		}\n"
				"	}\n"
				"	while (i <= j);\n"
				"\n"
				"	if (i < last) {\n"
				"		qs(s_arr, i, last);\n"
				"	}\n"
				"\n"
				"	if (first < j) {\n"
				"		qs(s_arr, first,j);\n"
				"	}\n"
				"}\n"
		"</body>"
	"</html>";


struct TestGenerate {
    TestGenerate(const base::bfs::path &cur_path) {
        tmplt::FileSaver file_tmpl(TEST_TMPL, sizeof(TEST_TMPL) - 1,           (cur_path / "test.tmpl").string());
        tmplt::FileSaver file_json(TEST_JSON, sizeof(TEST_JSON) - 1,           (cur_path / "test.json").string());
        tmplt::FileSaver file_text(TEST_TEXT_FILE, sizeof(TEST_TEXT_FILE) - 1, (cur_path / "test.txt").string());
        http_server::HtmlMaker make((cur_path / "test.html").string());
        std::string file_make = make.string();
        tmplt::FileContent fcont(file_make);
        BOOST_CHECK_EQUAL(std::string(fcont), std::string(RESULT));
    }
};


BOOST_AUTO_TEST_CASE(TestCtppTextFileLoader) {
    LOG_TO_STDOUT;
    base::bfs::path cur_path = base::bfs::absolute(base::bfs::current_path());
   
    if (base::bfs::exists(cur_path / "test.html")) {
        LOG(DEBUG) << "Remove `" << (cur_path / "test.html") << "`";
        base::bfs::remove(cur_path / "test.html");
    }
    TestGenerate tgen(cur_path);
}

#include <algorithm> 
#include <iterator>
#include <fstream>
#include <sstream>

#include "base.hpp"
#include "Log.hpp"
#include "TextFileLoad.hpp"

using namespace tmplt;


TextFileLoad::~TextFileLoad() throw() 
{}


INT_32 TextFileLoad::Handler(CTPP::CDT *arguments, const UINT_32 &arg_num, CTPP::CDT &ret_val) {
	if (1 not_eq arg_num) { 
        LOG(ERROR) << "Invalid number of arguments of template function.";
    }
    else {
        std::string file_name = arguments[1].GetString();
        base::bfs::path file_path(file_name);

        if (not base::bfs::exists(file_path)) {
            LOG(ERROR) << "File `" << file_name << "` is not exists.";
        }
        else {
            uint32_t file_size = base::bfs::file_size(file_name.c_str());
            
            if (not file_size) {
                LOG(ERROR) << "File `" << file_name << "` is empty.";
            }
            else {
                std::ifstream ifs("input.txt");
                
                if (not ifs.is_open()) {
                    LOG(ERROR) << "Can`t open file `" << file_name << "`.";
                }
                else {
                    ret_val = std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
                    return 0;
                }
            }
        }
    }
    return -1;
}


CCHAR_P TextFileLoad::GetName() { 
    return "TEXT_FILE_LOAD"; 
}

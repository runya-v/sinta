#include "HtmlMaker.hpp"
#include "Log.hpp"
#include "Compiler.hpp"

using namespace http_server;


struct CheckExistsComponent {
    bool _is_exists;
    base::bfs::path _path;
    std::time_t _file_time;
    
    CheckExistsComponent(const base::bfs::path &path) {
        if (not base::bfs::exists(path)) {
            _is_exists = false;
            LOG(WARNING) << "Can`t find component `" << path.string() << "`.";
        }
        else {
            _path = path;
            _is_exists = true;
            _file_time = base::bfs::last_write_time(path);
        }
    }
    
    bool exists() {
        return _is_exists;
    }

    std::string string() {
        return _path.string();
    }

    std::time_t fileTime() {
        return _file_time;
    }
};


HtmlMaker::HtmlMaker(const std::string &need_html_file, bool remove) 
    : _html_file(need_html_file)
{
    try {
        base::bfs::path need_path(need_html_file);
        std::string path_stem = (need_path.parent_path() / need_path.stem()).string();
        CheckExistsComponent check_tmpl(base::bfs::path(path_stem + ".tmpl"));
        CheckExistsComponent check_json(base::bfs::path(path_stem + ".json"));
        
        if (check_tmpl.exists() and check_json.exists()) {
            CheckExistsComponent check_html(need_path);
            
            bool is_regen = not check_html.exists() or (
                check_html.exists() and (
                    check_html.fileTime() < check_tmpl.fileTime() or 
                    check_html.fileTime() < check_json.fileTime()
                )
            );
            
            if (is_regen) { 
                tmplt::Compiler cmplr(check_tmpl.string());
                _html_gen.reset(new tmplt::Generator(cmplr.string(), check_json.string(), need_path, remove));
                LOG(INFO) << "Generate `" << std::string(*_html_gen) << "`";
            }
        }
    }
    catch (const std::exception &e) {
        LOG(ERROR) << "`" << e.what() << "`";
    }
}


const std::string& HtmlMaker::string() {
    if (_html_gen) {
        return *_html_gen;
    }
    else {
        return _html_file;
    }
}

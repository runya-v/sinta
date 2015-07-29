#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

#include "Log.hpp"
#include "Chart.hpp"


Chart::Diagram::Diagram(const std::string &name, const std::string &title, const std::string &unit)
    : _name(name)
    , _title(title)
    , _unit(unit)
{
    LOG(INFO);
}


Chart::Chart(const std::string &file_name)
    : _file_name(file_name)
{
    if (std::string::npos == _file_name.rfind(".html")) {
        _file_name += ".html";
    }
    LOG(INFO) << "file: `" << _file_name << "`";
}


void Chart::newDiagram(
    const std::string &name,
    const std::string &title,
    const std::string &unit)
{
    _current_diagram = std::make_shared<Diagram>(name, title, unit);
    _all_diagram.push_back(_current_diagram);
    LOG(INFO) << "Start name: `" << name << "`; title: `" << title << "`; unit: `" << unit << "`";
}


void Chart::newResult(const std::string &serie, const std::string &group, std::size_t value) {
    _current_diagram->_results.push_back({serie, group, value});
    std::cout << serie << ":" << group << ":" << value << std::endl;
    LOG(INFO) << "serie: `" << serie << "`; group: `" << group << "`; value: `" << value << "`";
}


void Chart::output() {
    std::ofstream ofs(_file_name);

    ofs << "<html>\n";
    ofs << "<head>\n";
    ofs << "<script "
                "type=\"text/javascript\" "
                "src=\"https://www.google.com/jsapi\">"
           "</script>\n";
    ofs << "<script type=\"text/javascript\">"
                "google.load('visualization', '1.0', {'packages':['corechart']});"
           "</script>\n";
    ofs << "</head>\n";
    ofs << "<body>\n";
    ofs << "<script type=\"text/javascript\">\n";

    for (auto &diagram : _all_diagram) {
        ofs << "function draw_" << diagram->_name << "(){\n";
        ofs << "var data = google.visualization.arrayToDataTable([\n";

        //['x', 'Cats', 'Blanket 1', 'Blanket 2'],
        typedef std::unordered_map<std::string, std::unordered_map<std::string, std::size_t>> ValuesMap;
        ValuesMap results;
        for (auto &res : diagram->_results) {
            results[res._group][res._serie] = res._value;
        }

        ofs << "['x'";
        auto first = results.begin()->second;
        for(auto& pair : first){
            ofs << ", '" << pair.first << "'";
        }
        ofs << "],\n";

        std::vector<std::string> groups;
        for (auto &group : results) {
            groups.push_back(group.first);
        }

        auto cmp = [](const std::string &lhs, const std::string &rhs)->bool {
            return atoi((lhs).c_str()) < atoi((rhs).c_str());
        };
        std::sort(groups.begin(), groups.end(), cmp);

        std::size_t max = 0;
        for (auto &group_title : groups) {
            ofs << "['" << group_title << "'";
            for (auto &serie : results[group_title]){
                ofs << ", " << serie.second;
                max = std::max(max, serie.second);
            }
            ofs << "],\n";
        }
        ofs << "]);\n";

        ofs << "var diagram = new google.visualization.LineChart(document.getElementById('diagram_" << diagram->_name <<"'));\n"
            << "var options = {curveType: \"function\","
            << "title: \"" << diagram->_title << "\","
            << "animation: {duration:1200, easing:\"in\"},"
            << "width: 600, height: 400,"
            << "hAxis: {title:\"Number of elements\", slantedText:true},"
            << "vAxis: {viewWindow: {min:0}, title:\"" << diagram->_unit << "\"}};\n"
            << "diagram.draw(data, options);\n";

        ofs << "var button = document.getElementById('diagram_button_" << diagram->_name << "');\n"
            << "button.onclick = function(){\n"
            << "if(options.vAxis.logScale){\n"
            << "button.value=\"Logarithmic Scale\";\n"
            << "} else {\n"
            << "button.value=\"Normal scale\";\n"
            << "}\n"
            << "options.vAxis.logScale=!options.vAxis.logScale;\n"
            << "diagram.draw(data, options);\n"
            << "};\n";
        ofs << "}\n";
    }

    //One function to find them
    ofs << "function draw_all(){\n";
    for (auto& diagram : _all_diagram){
        ofs << "draw_" << diagram->_name << "();\n";
    }
    ofs << "}\n";

    //One callback to bring them all
    ofs << "google.setOnLoadCallback(draw_all);\n";
    ofs << "</script>\n\n";

    //And in the web page bind them
    for (auto &diagram : _all_diagram){
        ofs << "<div id=\"diagram_" << diagram->_name << "\" style=\"width: 600px; height: 400px;\"></div>\n";
        ofs << "<input id=\"diagram_button_" << diagram->_name << "\" type=\"button\" value=\"Logarithmic scale\">\n";
    }
    ofs << "</body>\n";
    ofs << "</html>\n";
}

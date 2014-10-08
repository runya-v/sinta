#pragma once

#include <memory>
#include <string>
#include <vector>


class Chart {
    struct Result {
        std::string _serie;
        std::string _group;
        std::size_t _value;
    };

    struct Diagram {
        std::string _name;
        std::string _title;
        std::string _unit;
        std::vector<Result> _results;

        explicit Diagram(const std::string &name, const std::string &title, const std::string &unit);
    };

    std::shared_ptr<Diagram> _current_diagram;
    std::vector<std::shared_ptr<Diagram>> _all_diagram;
    std::string _file_name;

public:
    explicit Chart(const std::string &file_name);

    void newDiagram(
        const std::string &graph_name,
        const std::string &graph_title,
        const std::string &unit);
    void newResult(const std::string &serie, const std::string &group, std::size_t value);
    void output();
};

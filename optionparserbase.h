//
// Created by zvi on 29/04/2020.
//

#pragma once
#include <CLI/CLI.hpp>
#include <spdlog/fmt/fmt.h>

class OptionParserBase : public CLI::App
{
    using super = CLI::App;

public:
    bool verbose = false;
    bool quiet = false;

    explicit OptionParserBase(std::string app_description = "", std::string app_name = "");
    ~OptionParserBase() override = default;

    void parse_args(int argc, const char* const* argv, bool cmdline = true);

    template<typename T>
    void add_option_display(const std::string& label, const T& value)
    {
        m_optionsDisplay.push_back(OptionDisplay{label + ":", fmt::format("{}", value)});
    }

    void log_header();

protected:
    struct OptionDisplay {
        std::string label;
        std::string value;
    };

    virtual void post_parse();

    std::vector<OptionDisplay> m_optionsDisplay;
};

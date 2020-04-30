//
// Created by zvi on 29/04/2020.
//

#include "optionparserbase.h"
#include <filesystem>
#include <spdlog/spdlog.h>

namespace fs = std::filesystem;

OptionParserBase::OptionParserBase(std::string app_description, std::string app_name)
    : super(std::move(app_description), std::move(app_name))
{
    this->add_flag("-v,--verbose", this->verbose, "Write debug messages to the log");
    this->add_flag("-q,--quiet", this->quiet, "Write only warnings or worse to the log")->excludes("--verbose");
    spdlog::set_pattern("%Y-%m-%d %T.%e %^%-7l%$ %v");
    spdlog::set_level(spdlog::level::info);
}

void OptionParserBase::parse_args(int argc, const char* const* argv, bool cmdline)
{
    if (this->get_name().empty())
    {
        this->name(fs::path(argv[0]).stem().string());
    }
    try
    {
        this->parse(argc, argv);
    }
    catch (const CLI::ParseError& e)
    {
        ::exit(this->exit(e));
    }
    if (cmdline && argc > 1)
    {
        std::string space{" "}, cmd{argv[1]};
        for (int i = 2; i < argc; ++i)
        {
            cmd += space + argv[i];
        }
        this->add_option_display("Command", cmd);
    }
    this->post_parse();
}

void OptionParserBase::log_header()
{
    spdlog::info("{} - {}", this->get_name(), this->get_description());
    if (!m_optionsDisplay.empty())
    {
        auto label_width = std::max_element(m_optionsDisplay.begin(), m_optionsDisplay.end(),
                                            [](const OptionDisplay& a, const OptionDisplay& b) {
                                                return a.label.size() < b.label.size();
                                            })
                                   ->label.size();
        for (OptionDisplay& item : m_optionsDisplay)
        {
            spdlog::info("  {:{}} {}", item.label, label_width, item.value);
        }
    }
}

void OptionParserBase::post_parse()
{
    if (this->verbose)
        spdlog::set_level(spdlog::level::debug);
    else if (this->quiet)
        spdlog::set_level(spdlog::level::warn);
}

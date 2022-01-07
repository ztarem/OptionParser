//
// Created by zvi on 29/04/2020.
//

#include "optionparserbase.h"
#include <spdlog/spdlog.h>

class OptionParser : public OptionParserBase
{
    using super = OptionParserBase;

public:
    int first = 1;

    OptionParser() : super("Sample derived OptionParser")
    {
        this->add_option("-f,--first", this->first, "First argument");
    }
    ~OptionParser() override = default;

protected:
    void post_parse() override
    {
        super::post_parse();
        this->add_option_display("First", this->first);
    }
};

int main(int argc, const char* const* argv)
{
    OptionParser parser;
    parser.parse_args(argc, argv);
    parser.log_header();
    spdlog::debug("This is a debug message");
    spdlog::info("This is a message");
    spdlog::warn("This is a warning message");
}

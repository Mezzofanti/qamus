#ifndef OPTIONS_H
#define OPTIONS_H

#include "common.h"

class Options
{
public:
    Options(const int argc, char* const argv[]);
    bool getVerbose() const;
    long getVersion() const;
    bool getVersion(char const*& version) const;
    bool getICUVersion(char const*& version) const;
    bool getTREVersion(char const*& version) const;

private:
    void printUsage(FILE* stream, int exit_code);
    void printVersion();
    void parseOptions(const int argc, char* const argv[]);
    std::string _browser;
    std::string _lexicon;
    std::string _rules;
    bool _verbose;
#ifdef ENABLE_ICU
    char _icuVersion[MAX_VERSION_STRING_LENGTH];
#endif
    char _qamusVersion[MAX_VERSION_STRING_LENGTH];
};

#endif // OPTIONS_H

#ifndef OPTIONS_H
#define OPTIONS_H

#include "common.h"

#ifdef _WIN32
typedef void* Options;
#else
class Options
{
public:
    Options(const int argc, char* const argv[]);
    long getVersion() const;
    bool getVersion(char const*& version) const;
    bool getICUVersion(char const*& version) const;
    bool getTREVersion(char const*& version) const;
    bool getLogToFile() const;
    bool getLogToConsole() const;
    int  getLogLevel() const;
    char* getLogFilename() const;

private:
    void printUsage(FILE* stream, int exit_code);
    void printVersion();
    void parseOptions(const int argc, char* const argv[]);
    std::string _browser;
    std::string _lexicon;
    std::string _rules;
    bool  _logToFile;
    bool  _logToConsole;
    int   _loglevel;
    char* _logfile;
#ifdef ENABLE_ICU
    char _icuVersion[MAX_VERSION_STRING_LENGTH];
#endif
    char _qamusVersion[MAX_VERSION_STRING_LENGTH];
};
#endif

#endif // OPTIONS_H

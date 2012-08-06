#include <iostream>

#include "common.h"
#include "getopt.h"
#include "options.h"

#ifdef ENABLE_ICU
    #include <unicode/utypes.h>
#endif
#ifdef ENABLE_TRE
    #include <tre/tre.h>
#endif


Options::Options(const int argc, char* const argv[])
{
    int ret = sprintf(_qamusVersion, "%d.%d.%d %s", MAJOR, MINOR, REVSN, RELEASE_NAME);
    if (ret > MAX_VERSION_STRING_LENGTH || ret < 0)
    {
        std::cerr << "Error creating version string";
        exit(1);
    }

#ifdef ENABLE_ICU
    Q_ASSERT(MAX_VERSION_STRING_LENGTH >= U_MAX_VERSION_STRING_LENGTH);
    UVersionInfo versionArray;
    u_getVersion(versionArray);

    u_versionToString(versionArray, _icuVersion);
#endif

    _verbose = false;
    _browser.assign(getenv("BROWSER"));
    parseOptions(argc, argv);
}

bool Options::getVerbose() const
{
    return _verbose;
}

long Options::getVersion() const
{
    return (MAJOR << 16) +
           (MINOR <<  8) +
           (REVSN <<  0);
}

bool Options::getVersion(char const*& version) const
{
    version = _qamusVersion;
    return true;
}

bool Options::getICUVersion(char const*& version) const
{
#ifdef ENABLE_ICU
    version = _icuVersion;
    return true;
#else
    version = nullptr;
    return false;
#endif
}

bool Options::getTREVersion(char const*& version) const
{
#ifdef ENABLE_TRE
    version = tre_version();
    return true;
#else
    version = nullptr;
    return false;
#endif
}

void Options::printUsage(FILE* stream, int exit_code)
{
    fprintf(stream, "Usage:  %s options\n", "Qamus");
    fprintf(stream,
            "  -h  --help             Display this usage information.\n"
            "  -l  --lexicon filename Read lexicon from file.\n"
            "  -r  --rules   filename Read rules from file.\n"
            "  -v  --verbose          Print verbose messages.\n"
            "  -V  --version          Print version.\n");
    exit(exit_code);
}


void Options::printVersion()
{
    char tab[] = " ";
    char const *version;

    getVersion(version);
    std::cout << PROJECT_NAME << " " << version << std::endl;

    std::cout << tab << "ICU ";
    if (getICUVersion(version))
    {
        std::cout << version;
    }
    else
    {
        std::cout << " not available";
    }
    std::cout << std::endl;

    std::cout << tab;
    if (getTREVersion(version))
    {
        std::cout << version;
    }
    else
    {
        std::cout << "TRE not available";
    }
    std::cout << std::endl;
}

void Options::parseOptions(const int argc, char* const argv[])
{
    static struct option long_options[] =
    {
        { "help",          no_argument, 0, 'h' },
        { "lexicon", required_argument, 0, 'l' },
        { "rules",   required_argument, 0, 't' },
        { "verbose",       no_argument, 0, 'v' },
        { "version",       no_argument, 0, 'V' },
        {0, 0, 0, 0}
    };

    while (true)
    {
        int option_index = 0;
        char c = getopt_long(argc, argv, "l:r:hvV", long_options, &option_index);

        if (c == -1)
        {
            break;
        }

        switch (c)
        {
        case 0:
            break;
        case 'h':
            printUsage(stdout, 0);
            break;
        case 'l':
            _lexicon.assign(optarg);
            break;
        case 'r':
            _rules.assign(optarg);
            break;
        case 'v':
            _verbose = true;
            break;
        case 'V':
            printVersion();
            exit(0);
            break;
        case '?':
            printUsage(stderr, 1);
            break;
        default:
            break;
        }
    }
}
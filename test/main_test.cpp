#define CATCH_CONFIG_RUNNER
#include <test_helper.h>

int main(int argc, char ** argv)
{
    // If the last argument is "-p", then pause after the tests are run.
    // This allows us to run "leaks" on Mac OS X to check for memory leaks.
    bool pause_after_test = false;
    if (argc && std::string(argv[argc - 1]) == "-p")
    {
        pause_after_test = true;
        argc--;
    }

    int result = Catch::Session().run(argc, argv);

    if (pause_after_test)
    {
        printf("Press enter to continue.");
        std::string s;
        std::cin >> s;
    }

    return result;
}

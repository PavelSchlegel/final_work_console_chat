#ifndef START_ARG
#define START_ARG
#include <array>
#include <string>
#include <assert.h>

class MainArg
{
private:
    std::array<std::string, 2> arg;
public:
    explicit MainArg(int argc, char** argv) noexcept
    {
        switch (argc) {
            case 3 : {
                arg[0] = argv[1];
                arg[1] = argv[2];
                break;
            }
            default: {
                arg[0] = "127.0.0.1";
                arg[1] = "2020";
            }
        }
    }

    std::string& operator[] (const int index)
    {
        assert(index < arg.size() && index >= 0 && "CLASS:MAIN_ARG: OPERATOR[]->ERROR_INDEX");
        return arg[index];
    }
};
#endif //START_ARG
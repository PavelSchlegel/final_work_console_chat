#ifndef OPTIONAL_FUNCTOR  // temporary name
#define OPTIONAL_FUNCTOR  // vorübergehende Name
#include <string>

class Optional_card
{
private:
    bool upper_case {false};
    bool lower_case {false};
    bool special_character {false};
    bool space {false};
    bool number {false};
public:
    Optional_card() {};
    void operator() (char& symbol);
    bool get_up() { return upper_case;}
    bool get_low() {return lower_case;}
    bool get_special() {return special_character;}
    bool get_space() {return space;}
    bool get_num() {return number;}
};
#endif // OPTIONAL_FUNCTOR
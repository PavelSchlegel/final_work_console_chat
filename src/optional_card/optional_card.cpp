#include "optional_card.hpp"

void Optional_card::operator()(char& symbol)
{
    if (std::isalpha(symbol)) {
        if ( ! lower_case ) {
            lower_case = symbol >= 'A' && symbol <= 'Z';
        }

        if ( ! upper_case ) {
            upper_case = symbol >= 'a' && symbol <= 'z';
        }
    }

    if ( ! special_character ) {
        switch (symbol) {
            case '!' :
            case '@' :
            case '#' :
            case '%' :
            case '$' :
            case '&' :
                special_character = true;
                break;
        }
    }

    if ( ! space ) {
        space = symbol == ' ';
    }

    if ( ! number ) {
        number = std::isdigit(symbol);
    }
}
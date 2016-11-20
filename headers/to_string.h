#ifndef TO_STRING_H
#define TO_STRING_H

#include <string>
#include <sstream>

template < typename T > std::string to_string( const T& n ) {
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

#endif
#ifndef DEBUG_PRINT_HPP
#define DEBUG_PRINT_HPP

#include <iostream> 

template<typename T>
inline void debug_print(const T& value)
{
#ifdef DEBUG               
    // only prints with -DDEBUG
    std::cout << value << std::endl;
#endif
}

#endif // DEBUG_PRINT_HPP
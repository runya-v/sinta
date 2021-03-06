/*!
 * \brief  Кокпилятор шаблона.
 * \author Rostislav Velichko. e: rostislav.vel@gmail.com
 * \date   05.11.2013
 */

#pragma once

#include <string>
#include <vector>

#include <boost/utility.hpp>

#include "utility.hpp"


namespace tmplt {
    class Compiler 
        : public boost::noncopyable
    {
        FileSaverPtr _result;
        
    public:
        explicit Compiler(const std::string &&fswr);
        
        const std::string& string() const;
    };
} // tmplt

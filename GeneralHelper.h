/* 
 * File:   GeneralHelper.h
 * Author: Nicholas Hadjiminas
 *
 * Created on August 8, 2013, 11:01 AM
 */

#ifndef GENERALHELPER_H
#define	GENERALHELPER_H

#include <cstddef>
#include <vector>
#include <string>     
#include <iostream> 

using namespace std;

template <typename T> string tostr(const T& t) {
    ostringstream os;
    os << t;
    return os.str();
}

template <typename T> T fromstr(const std::string& s) {
    std::istringstream stream(s);
    T t;
    stream >> t;
    return t;
}

template <typename Container> Container& split(Container& result,const typename Container::value_type& s,const typename Container::value_type& delimiters) {
    result.clear();
    size_t current;
    size_t next = -1;
    do {
        {
            next = s.find_first_not_of(delimiters, next + 1);
            if (next == Container::value_type::npos) break;
            next -= 1;
        }
        current = next + 1;
        next = s.find_first_of(delimiters, current);
        result.push_back(s.substr(current, next - current));
    } while (next != Container::value_type::npos);
    return result;
}

#endif	/* GENERALHELPER_H */


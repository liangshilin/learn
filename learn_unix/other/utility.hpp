#pragma once
#ifndef UTILILTY_HPP_
#define UTILILTY_HPP_
// boost uuid libary
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
// libuuid libary
#include <uuid/uuid.h>

#include <cctype>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class OUtililty
{
public:
    /*
        UUID����(boostʵ��)
    */
    static string&& uuid_boost()
    {
        static auto generate_ = boost::uuids::random_generator();
        boost::uuids::uuid uuid_ = generate_();
        string uuid_str = boost::uuids::to_string(uuid_);
        transform(uuid_str.begin(), uuid_str.end(), uuid_str.begin(), ::toupper);

        return move(uuid_str);
    }

    /*
        UUID����(libuuidʵ��)
    */
    static string&& uuid_libuuid()
    {
        unsigned char uuid_[16] = { 0 };
        uuid_generate(uuid_);
        char tmp[128] = { 0 };
        uuid_unparse_upper(uuid_, tmp);

        return move(string(tmp));
    }

};

namespace utility
{
    void run()
    {
        cout << OUtililty::uuid_boost() << endl;
        cout << OUtililty::uuid_libuuid() << endl;
    }
}


#endif // !UTILILTY_HPP_

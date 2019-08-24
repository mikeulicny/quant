#pragma once

#include <iostream>
#include <rapidjson/document.h>
#include <string>


namespace api
{
    class Order
    {
        public:
            Order();
            ~Order();

            std::string to_json();
            void from_json(std::string &json_string);

            
        

    };  // class Order
} // namespace api
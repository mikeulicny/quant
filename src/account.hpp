#pragma once

#include <iostream>
#include <rapidjson/document.h>
#include <string>

namespace api
{
    class Account {
        public:
            Account();
            ~Account();

            void display();
            std::string get_id() {return account_id; }

        private:
            std::string type;
            std::string account_id;
            bool is_day_trader;
            double availible_funds;
            double buying_power;
            double stock_buying_power;
    };  // accountA
}   // namespace api
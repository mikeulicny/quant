#pragma once

#include "quote.hpp"

api::Quote::Quote(const std::string &buffer_input)
{
    int mutual_fund_iter = 0;
    int future_iter = 0;
    int future_opt_iter = 0;
    int index_iter = 0;
    int option_iter = 0;
    int forex_iter = 0;
    int etf_iter = 0;
    int equity_iter = 0;

    quote_doc.Parse(buffer_input.c_str());
    
    for (rapidjson::Value::ConstMemberIterator symbol_itr = quote_doc.MemberBegin();
        symbol_itr != quote_doc.MemberEnd(); ++symbol_itr)
        {
            const rapidjson::Value &symbol = quote_doc[symbol_itr->name.GetString()];
            rapidjson::Value::ConstMemberIterator &data_itr = symbol.FindMember("description");
            std::string quote_type = data_itr->value.GetString();
            

            if (quote_type == "mutualFund")
            {
                // TODO: Change to single iteration over values based on data received
                mutual_fund_quotes.push_back(Mutual_Fund());
                data_itr = symbol.FindMember("symbol");
                mutual_fund_quotes[mutual_fund_iter].symbol = data_itr->value.GetString();
                data_itr = symbol.FindMember("closePrice");
                mutual_fund_quotes[mutual_fund_iter].close_price = data_itr->value.GetDouble();
                data_itr = symbol.FindMember("netChange");
                mutual_fund_quotes[mutual_fund_iter].net_change = data_itr->value.GetDouble();
                data_itr = symbol.FindMember("totalVolume");
                mutual_fund_quotes[mutual_fund_iter].total_volume = data_itr->value.GetInt();
                // ...
                mutual_fund_iter++;
            }
            if (quote_type == "future")
            {
                future_quotes.push_back(Future());
                future_iter++;
            }
            // TODO:
        }
    
}   // constructor

api::Quote::~Quote()
{
    // destructor
}

void api::Quote::display()
{
    // TODO: display quote depending on type
}

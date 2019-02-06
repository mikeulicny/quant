#pragma once

#include "quote.hpp"

api::Quote::Quote(const std::string &buffer_input)
{
    quote_doc.Parse(buffer_input.c_str());

    for (rapidjson::Value::ConstMemberIterator symbol_itr = quote_doc.MemberBegin();
        symbol_itr != quote_doc.MemberEnd(); ++symbol_itr)
        {
            const rapidjson::Value &symbol = quote_doc[symbol_itr->name.GetString()];
            rapidjson::Value::ConstMemberIterator &data_itr = symbol.FindMember("description");
            std::string quote_type = data_itr->name.GetString();
            
            if (quote_type == "mutualFund")
            {
                // TODO:
            }
            if (quote_type == "future")
            {
                // TODO:
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

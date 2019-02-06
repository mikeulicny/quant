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
            quote_type = data_itr->name.GetString();
            
        }
    
}   // constructor

api::Quote::~Quote()
{
    // destructor
}

void api::Quote::display()
{
    // TODO: display quote depending on type
    // TODO: if multiple of different types exist, display seperately
}

// -- Private functions --
void api::Quote::set_variables()
{
    
}
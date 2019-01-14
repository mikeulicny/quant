#pragma once

#include "quote.hpp"

api::Quote::Quote(const std::string &buffer_input)
{
    rapidjson::Document quote_doc;
    quote_doc.Parse(buffer_input.c_str());

    for (rapidjson::Value::ConstMemberIterator symbol_itr = quote_doc.MemberBegin();
        symbol_itr != quote_doc.MemberEnd(); ++symbol_itr)
        {
            // TODO:
        }
    
}   // constructor

api::Quote::~Quote()
{
    // destructor
}



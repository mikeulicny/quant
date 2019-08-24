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
    
    for (rapidjson::Value::ConstMemberIterator symbol_iter = quote_doc.MemberBegin();
        symbol_iter != quote_doc.MemberEnd(); ++symbol_iter)
        {
            const rapidjson::Value &symbol = quote_doc[symbol_iter->name.GetString()];
            // asset type is returned to identify which type of asset is quoted
            rapidjson::Value::ConstMemberIterator data_iter = symbol.FindMember("assetType");
            std::string asset_type = data_iter->value.GetString();

            if (asset_type == "MUTUAL_FUND")
            {   // populate all mutual fund struct variables
                mutual_fund_quotes.push_back(Mutual_Fund());
                data_iter = symbol.FindMember("symbol");
                mutual_fund_quotes[mutual_fund_iter].symbol = data_iter->value.GetString();
                data_iter = symbol.FindMember("closePrice");
                mutual_fund_quotes[mutual_fund_iter].close_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("netChange");
                mutual_fund_quotes[mutual_fund_iter].net_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("totalVolume");
                mutual_fund_quotes[mutual_fund_iter].total_volume = data_iter->value.GetInt();
                data_iter = symbol.FindMember("tradeTimeInLong");
                mutual_fund_quotes[mutual_fund_iter].trade_time = data_iter->value.GetInt();
                data_iter = symbol.FindMember("exchange");
                mutual_fund_quotes[mutual_fund_iter].exchange = data_iter->value.GetString();
                data_iter = symbol.FindMember("exchangeName");
                mutual_fund_quotes[mutual_fund_iter].exchange_name = data_iter->value.GetString();
                data_iter = symbol.FindMember("digits");
                mutual_fund_quotes[mutual_fund_iter].digits = data_iter->value.GetInt();
                data_iter = symbol.FindMember("52WkHigh");
                mutual_fund_quotes[mutual_fund_iter].year_high = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("52WkLow");
                mutual_fund_quotes[mutual_fund_iter].year_low = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("nAV");
                mutual_fund_quotes[mutual_fund_iter].net_asset_value = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("peRatio");
                mutual_fund_quotes[mutual_fund_iter].pe_ratio = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("divAmount");
                mutual_fund_quotes[mutual_fund_iter].div_amount = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("divYield");
                mutual_fund_quotes[mutual_fund_iter].div_yield = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("divDate");
                mutual_fund_quotes[mutual_fund_iter].div_date = data_iter->value.GetString();
                data_iter = symbol.FindMember("securityStatus");
                mutual_fund_iter++;
            }
            else if (asset_type == "FUTURE")
            {
                future_quotes.push_back(Future());
                data_iter = symbol.FindMember("symbol");
                future_quotes[future_iter].symbol = data_iter->value.GetString();
                data_iter = symbol.FindMember("bidPriceInDouble");
                future_quotes[future_iter].bid_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("askPriceInDouble");
                future_quotes[future_iter].ask_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("lastPriceInDouble");
                future_quotes[future_iter].last_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("bidId");
                future_quotes[future_iter].bid_id = data_iter->value.GetString();
                data_iter = symbol.FindMember("askId");
                future_quotes[future_iter].ask_id = data_iter->value.GetString();
                data_iter = symbol.FindMember("highPriceInDouble");
                future_quotes[future_iter].high_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("lowPriceInDouble");
                future_quotes[future_iter].low_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("closePriceInDouble");
                future_quotes[future_iter].close_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("exchange");
                future_quotes[future_iter].exchange = data_iter->value.GetString();
                data_iter = symbol.FindMember("lastId");
                future_quotes[future_iter].last_id = data_iter->value.GetString();
                data_iter = symbol.FindMember("openPriceInDouble");
                future_quotes[future_iter].open_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("changeInDouble");
                future_quotes[future_iter].net_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("futurePercentChange");
                future_quotes[future_iter].percent_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("exchangeName");
                future_quotes[future_iter].exchange_name = data_iter->value.GetString();
                data_iter = symbol.FindMember("securityStatus");
                future_quotes[future_iter].security_status = data_iter->value.GetString();
                data_iter = symbol.FindMember("openInterest");
                future_quotes[future_iter].open_interest = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("mark");
                future_quotes[future_iter].mark = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("tick");
                future_quotes[future_iter].tick = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("tickAmount");
                future_quotes[future_iter].tick_amount = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("product");
                future_quotes[future_iter].product = data_iter->value.GetString();
                data_iter = symbol.FindMember("futurePriceFormat");
                future_quotes[future_iter].future_price_format = data_iter->value.GetString();
                data_iter = symbol.FindMember("futureTradingHours");
                future_quotes[future_iter].future_trading_hrs = data_iter->value.GetString();
                data_iter = symbol.FindMember("futureIsTradable");
                future_quotes[future_iter].future_is_tradable = data_iter->value.GetBool();
                data_iter = symbol.FindMember("futureMultiplier");
                future_quotes[future_iter].multiplier = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("futureIsActive");
                future_quotes[future_iter].is_active = data_iter->value.GetBool();
                data_iter = symbol.FindMember("futureSettlementPrice");
                future_quotes[future_iter].settlement_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("futureActiveSymbol");
                future_quotes[future_iter].active_symbol = data_iter->value.GetString();
                data_iter = symbol.FindMember("futureExpirationDate");
                future_quotes[future_iter].expiration_date = data_iter->value.GetString();
                future_iter++;
            }
            else if (asset_type == "FUTURE_OPTIONS")
            {
                future_option_quotes.push_back(Future_Option());
                // TODO: get correct symbol format for tdameritrade developer website
                future_opt_iter++;
            }
            else if (asset_type == "INDEX")
            {
                index_quotes.push_back(Index());
                data_iter = symbol.FindMember("symbol");
                index_quotes[index_iter].symbol = data_iter->value.GetString();
                data_iter = symbol.FindMember("description");
                index_quotes[index_iter].description = data_iter->value.GetString();
                data_iter = symbol.FindMember("lastPrice");
                index_quotes[index_iter].last_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("openPrice");
                index_quotes[index_iter].open_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("highPrice");
                index_quotes[index_iter].high_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("lowPrice");
                index_quotes[index_iter].low_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("closePrice");
                index_quotes[index_iter].close_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("netChange");
                index_quotes[index_iter].net_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("totalVolume");
                index_quotes[index_iter].total_volume = data_iter->value.GetInt();
                data_iter = symbol.FindMember("tradeTimeInLong");
                index_quotes[index_iter].trade_time = data_iter->value.GetInt();
                data_iter = symbol.FindMember("exchange");
                index_quotes[index_iter].exchange = data_iter->value.GetString();
                data_iter = symbol.FindMember("exchangeName");
                index_quotes[index_iter].exchange_name = data_iter->value.GetString();
                data_iter = symbol.FindMember("digits");
                index_quotes[index_iter].digits = data_iter->value.GetInt();
                data_iter = symbol.FindMember("52WkHigh");
                index_quotes[index_iter].year_high = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("52WkLow");
                index_quotes[index_iter].year_low = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("securityStatus");
                index_quotes[index_iter].security_status = data_iter->value.GetString();
                index_iter++;
            }
            else if (asset_type == "OPTION")
            {
                option_quotes.push_back(Option());
                // TODO: get correct symbol format for tdameritrade developer website
                option_iter++;
            }
            else if (asset_type == "FOREX")
            {
                forex_quotes.push_back(Forex());
                data_iter = symbol.FindMember("symbol");
                forex_quotes[forex_iter].symbol = data_iter->value.GetString();
                data_iter = symbol.FindMember("bidPriceInDouble");
                forex_quotes[forex_iter].bid_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("askPriceInDouble");
                forex_quotes[forex_iter].ask_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("lastPriceInDouble");
                forex_quotes[forex_iter].last_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("highPriceInDouble");
                forex_quotes[forex_iter].high_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("lowPriceInDouble");
                forex_quotes[forex_iter].low_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("closePriceInDouble");
                forex_quotes[forex_iter].close_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("exchange");
                forex_quotes[forex_iter].exchange = data_iter->value.GetString();
                data_iter = symbol.FindMember("description");
                forex_quotes[forex_iter].description = data_iter->value.GetString();
                data_iter = symbol.FindMember("openPriceInDouble");
                forex_quotes[forex_iter].open_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("changeInDouble");
                forex_quotes[forex_iter].net_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("percentChange");
                forex_quotes[forex_iter].percent_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("exchangeName");
                forex_quotes[forex_iter].exchange_name = data_iter->value.GetString();
                data_iter = symbol.FindMember("digits");
                forex_quotes[forex_iter].digits = data_iter->value.GetInt();
                data_iter = symbol.FindMember("securityStatus");
                forex_quotes[forex_iter].security_status = data_iter->value.GetString();
                data_iter = symbol.FindMember("tick");
                forex_quotes[forex_iter].tick = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("tickAmount");
                forex_quotes[forex_iter].tick_amount = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("product");
                forex_quotes[forex_iter].product = data_iter->value.GetString();
                data_iter = symbol.FindMember("tradingHours");
                forex_quotes[forex_iter].trading_hours = data_iter->value.GetString();
                data_iter = symbol.FindMember("isTradable");
                forex_quotes[forex_iter].is_tradable = data_iter->value.GetBool();
                data_iter = symbol.FindMember("marketMaker");
                forex_quotes[forex_iter].market_maker = data_iter->value.GetString();
                data_iter = symbol.FindMember("52WkHighInDouble");
                forex_quotes[forex_iter].year_high = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("52WkLowInDouble");
                forex_quotes[forex_iter].year_low = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("mark");
                forex_quotes[forex_iter].mark = data_iter->value.GetDouble();
                forex_iter++;
            }
            else if (asset_type == "ETF")
            {
                etf_quotes.push_back(ETF());
                data_iter = symbol.FindMember("symbol");
                etf_quotes[etf_iter].symbol = data_iter->value.GetString();
                data_iter = symbol.FindMember("description");
                etf_quotes[etf_iter].description = data_iter->value.GetString();
                data_iter = symbol.FindMember("bidPrice");
                etf_quotes[etf_iter].bid_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("bidSize");
                etf_quotes[etf_iter].bid_size = data_iter->value.GetInt();
                data_iter = symbol.FindMember("bidId");
                etf_quotes[etf_iter].bid_id = data_iter->value.GetString();
                data_iter = symbol.FindMember("askPrice");
                etf_quotes[etf_iter].ask_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("askSize");
                etf_quotes[etf_iter].ask_size = data_iter->value.GetInt();
                data_iter = symbol.FindMember("askId");
                etf_quotes[etf_iter].ask_id = data_iter->value.GetString();
                data_iter = symbol.FindMember("lastPrice");
                etf_quotes[etf_iter].last_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("lastSize");
                etf_quotes[etf_iter].last_size = data_iter->value.GetInt();
                data_iter = symbol.FindMember("lastId");
                etf_quotes[etf_iter].last_id = data_iter->value.GetString();
                data_iter = symbol.FindMember("openPrice");
                etf_quotes[etf_iter].open_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("highPrice");
                etf_quotes[etf_iter].high_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("lowPrice");
                etf_quotes[etf_iter].low_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("closePrice");
                etf_quotes[etf_iter].close_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("netChange");
                etf_quotes[etf_iter].net_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("totalVolume");
                etf_quotes[etf_iter].total_volume = data_iter->value.GetInt();
                data_iter = symbol.FindMember("quoteTimeInLong");
                etf_quotes[etf_iter].quote_time = data_iter->value.GetInt();
                data_iter = symbol.FindMember("tradeTimeInLong");
                etf_quotes[etf_iter].trade_time = data_iter->value.GetInt();
                data_iter = symbol.FindMember("mark");
                etf_quotes[etf_iter].mark = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("exchange");
                etf_quotes[etf_iter].exchange = data_iter->value.GetString();
                data_iter = symbol.FindMember("exchangeName");
                etf_quotes[etf_iter].exchange_name = data_iter->value.GetString();
                data_iter = symbol.FindMember("marginable");
                etf_quotes[etf_iter].marginable = data_iter->value.GetBool();
                data_iter = symbol.FindMember("shortable");
                etf_quotes[etf_iter].shortable = data_iter->value.GetBool();
                data_iter = symbol.FindMember("volatility");
                etf_quotes[etf_iter].volatility = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("digits");
                etf_quotes[etf_iter].digits = data_iter->value.GetInt();
                data_iter = symbol.FindMember("52WkHigh");
                etf_quotes[etf_iter].year_high = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("52WkLow");
                etf_quotes[etf_iter].year_low = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("peRatio");
                etf_quotes[etf_iter].pe_ratio = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("divAmount");
                etf_quotes[etf_iter].div_amount = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("divYield");
                etf_quotes[etf_iter].div_yield = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("divDate");
                etf_quotes[etf_iter].div_date = data_iter->value.GetString();
                data_iter = symbol.FindMember("securityStatus");
                etf_quotes[etf_iter].security_status = data_iter->value.GetString();
                data_iter = symbol.FindMember("regularMarketLastPrice");
                etf_quotes[etf_iter].reg_market_last_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("regularMarketLastSize");
                etf_quotes[etf_iter].reg_market_last_size = data_iter->value.GetInt();
                data_iter = symbol.FindMember("regularMarketNetChange");
                etf_quotes[etf_iter].reg_market_net_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("regularMarketTradeTimeInLong");
                etf_quotes[etf_iter].reg_market_trade_time = data_iter->value.GetInt();
                etf_iter++;
            }
            else if (asset_type == "EQUITY")
            {
                equity_quotes.push_back(Equity());
                data_iter = symbol.FindMember("symbol");
                equity_quotes[equity_iter].symbol = data_iter->value.GetString();
                data_iter = symbol.FindMember("description");
                equity_quotes[equity_iter].description = data_iter->value.GetString();
                data_iter = symbol.FindMember("bidPrice");
                equity_quotes[equity_iter].bid_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("bidSize");
                equity_quotes[equity_iter].bid_size = data_iter->value.GetInt();
                data_iter = symbol.FindMember("bidId");
                equity_quotes[equity_iter].bid_id = data_iter->value.GetString();
                data_iter = symbol.FindMember("askPrice");
                equity_quotes[equity_iter].ask_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("askSize");
                equity_quotes[equity_iter].ask_size = data_iter->value.GetInt();
                data_iter = symbol.FindMember("askId");
                equity_quotes[equity_iter].ask_id = data_iter->value.GetString();
                data_iter = symbol.FindMember("lastPrice");
                equity_quotes[equity_iter].last_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("lastSize");
                equity_quotes[equity_iter].last_size = data_iter->value.GetInt();
                data_iter = symbol.FindMember("lastId");
                equity_quotes[equity_iter].last_id = data_iter->value.GetString();
                data_iter = symbol.FindMember("openPrice");
                equity_quotes[equity_iter].open_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("highPrice");
                equity_quotes[equity_iter].high_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("lowPrice");
                equity_quotes[equity_iter].low_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("closePrice");
                equity_quotes[equity_iter].close_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("netChange");
                equity_quotes[equity_iter].net_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("totalVolume");
                equity_quotes[equity_iter].total_volume = data_iter->value.GetInt();
                data_iter = symbol.FindMember("quoteTimeInLong");
                equity_quotes[equity_iter].quote_time = data_iter->value.GetInt();
                data_iter = symbol.FindMember("tradeTimeInLong");
                equity_quotes[equity_iter].trade_time = data_iter->value.GetInt();
                data_iter = symbol.FindMember("mark");
                equity_quotes[equity_iter].mark = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("exchange");
                equity_quotes[equity_iter].exchange = data_iter->value.GetString();
                data_iter = symbol.FindMember("exchangeName");
                equity_quotes[equity_iter].exchange_name = data_iter->value.GetString();
                data_iter = symbol.FindMember("marginable");
                equity_quotes[equity_iter].marginable = data_iter->value.GetBool();
                data_iter = symbol.FindMember("shortable");
                equity_quotes[equity_iter].shortable = data_iter->value.GetBool();
                data_iter = symbol.FindMember("volatility");
                equity_quotes[equity_iter].volatility = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("digits");
                equity_quotes[equity_iter].digits = data_iter->value.GetInt();
                data_iter = symbol.FindMember("52WkHigh");
                equity_quotes[equity_iter].year_high = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("52WkLow");
                equity_quotes[equity_iter].year_low = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("peRatio");
                equity_quotes[equity_iter].pe_ratio = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("divAmount");
                equity_quotes[equity_iter].div_amount = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("divYield");
                equity_quotes[equity_iter].div_yield = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("divDate");
                equity_quotes[equity_iter].div_date = data_iter->value.GetString();
                data_iter = symbol.FindMember("securityStatus");
                equity_quotes[equity_iter].security_status = data_iter->value.GetString();
                data_iter = symbol.FindMember("regularMarketLastPrice");
                equity_quotes[equity_iter].reg_market_last_price = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("regularMarketLastSize");
                equity_quotes[equity_iter].reg_market_last_size = data_iter->value.GetInt();
                data_iter = symbol.FindMember("regularMarketNetChange");
                equity_quotes[equity_iter].reg_market_net_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("regularMarketTradeTimeInLong");
                equity_quotes[equity_iter].reg_market_trade_time = data_iter->value.GetInt();
                data_iter = symbol.FindMember("netPercentChangeInDouble");
                equity_quotes[equity_iter].net_percent_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("markChangeInDouble");
                equity_quotes[equity_iter].mark_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("markPercentChangeInDouble");
                equity_quotes[equity_iter].mark_percent_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("regularMarketPercentChangeInDouble");
                equity_quotes[equity_iter].reg_market_percent_change = data_iter->value.GetDouble();
                data_iter = symbol.FindMember("delayed");
                equity_quotes[equity_iter].delayed = data_iter->value.GetBool();
                equity_iter++;
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

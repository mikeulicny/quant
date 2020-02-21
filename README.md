# quant trading system written in c++
___

### goals of this program
Provide an API that integrates with TD Ameritrade's API and a database in order to backtest custom
quantitative analysis and implement it to automate trading on a TD Ameritrade account.

___

### Future Implementations
#### TD Ameritrade API
- Handling orders and saved orders
- Instruments
- Market hours
- Movers
- Option chains
- Transaction history
- User info and preferences
- Watchlist

#### Quantitative analysis
- Volume Profile
- VWAP

#### Big Data analysis
- Implement connections to database to store stock data
- Small API to pull price data from database instead of from TD Ameritrade

#### Automation
- Automate gathering data into database
    1. script to pull stock data for one symbol
    2. pull stock data from entire watchlist, integrating with TD Ameritrade API watchlists
    3. auto-pull stock data
    4. auto-pull max amount of stock data

- Automate trading
    1. script generating quantitative analysis
    2. constantly run scripts, sending buy/sell signals
    3. fully automate buy/sell

___

### Resources
#### cURL Library
A fast REST client for sending and receiving data
<https://curl.haxx.se>

#### nlohmann JSON Library
A json library with a clean API.
<https://github.com/nlohmann/json>

#### Eigen Library
A powerful c++ matrix and mathematics library
<http://eigen.tuxfamily.org/>

#### PostgreSQL
SQL database that provides many powerful tools
<https://www.postgresql.org>

#### TD Ameritrade Developer website
<https://developer.tdameritrade.com>

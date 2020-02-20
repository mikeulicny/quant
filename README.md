# quant system written in c++

### The libraries used are as follows:
- [cURL](https://curl.haxx.se): a rest request library used to make url data transfers
- [nlohmann/json](https://github.com/nlohmann/json): json library for handling the json data returned from the cURL requests
- [Eigen](eigen.tuxfamily.org/dox): a powerful matrix computation library for C++
    
### The following libraries will be implemented later in the future
- [postgreSQL](https://www.postgresql.org): API for connecting and sending querys to a postgre database

___

### Currently in production
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


### TD Ameritrade Developer website
<https://developer.tdameritrade.com>

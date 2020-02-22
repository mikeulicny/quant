# quant trading system written in c++
___

### goals of this program
Provide a low level API that integrates with TD Ameritrade's API and a database in order to backtest custom
quantitative analysis and implement it to automate trading on a TD Ameritrade account.

___

### API for TDAmeritrade
The user must have an app created through the TD Ameritrade developer website
<https://developer.tdameritrade.com/guides>
and followed the steps to obtain a refresh token. Then create a json file containing the
client ID and url encoded refresh token as shown

```json
{
    "client_id": 1234567890,
    "refresh_token": "url_encoded_refresh_token"
}
```

All C++ api is namespaced by tdma

Instantiate an auth object, passing the json file name of where the credentials were previously
stored. Then call auth.post() to request a new access token. Calling auth.post(true) will request
a new refresh and access token.
auth.check() should be used in programs as it checks whether the current timepoint is past the
access token expiry timepoint, and only requests a new auth token if the previous one is expired.
 

```C++`
int main()
{
    tdma::auth user_auth("credentials/default.json");

    // request new access token
    user_auth.post();

    // request new refesh token and access token
    user_auth.post(true);

    // use in programs before executing API calls to TD Ameritrade
    user_auth.check();

    return 0;
}
```

Note: access tokens expires every 30 minutes and refresh tokens expires every 90 days.
If a refresh token expires it must be re-obtained manually through the TD Ameritrade developer website.

The auth object keeps the access and refersh tokens in memory and does not write them to a file
unless the '''write_to_file("filename.json")''' member function is called or the object exits the scope.

All API objects need to be instantiated by passing an auth object and the required parameters

```C++
int main()
{
    // create an auth object
    tdma::auth user_auth("credentials/default.json");

    // create an account object
    tdma::account linked_account(user_auth, "accountID", 0, 0);
   
    nlohmann::json response;
    response = linked_account.get();    // get calls an API request and returns a json object

    std::cout << std::setw(4) << response << std::endl; // pretty print the json object to terminal

    return 0;
}
```

This is the general API design style and is subject to change as progress is made.

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

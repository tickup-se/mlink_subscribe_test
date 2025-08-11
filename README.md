# MLink stream test

Based on SpiderRocks example code the live_prints program streams a set of tickers and counts the number of open and close cross trades.

The program historic_prints is reading trough a historic file and outputs the number of open prints.

## build all

### MacOS:

[![macos](https://github.com/tickup-se/mlink_subscribe_test/actions/workflows/macos.yml/badge.svg)](https://github.com/tickup-se/mlink_subscribe_test/actions/workflows/macos.yml)

```
brew install boost openssl protobuf
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

### Ubuntu 24.04:
[![ubuntu-22.04](https://github.com/tickup-se/mlink_subscribe_test/actions/workflows/ubuntu_24_04.yml/badge.svg)](https://github.com/tickup-se/mlink_subscribe_test/actions/workflows/ubuntu_24_04.yml)

```
sudo apt-get update
sudo apt-get install -y libboost-all-dev libssl-dev build-essential protobuf-compiler libprotobuf-dev libprotoc-dev
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --parallel $(nproc)
```

### usage:

**Live data**

./live_prints <API_KEY> 

Will every 10 seconds output debug information formated like this:

```
(time: 15:02:04 [CEST]) open cross trades: 0 close cross trades: 0 unique open: 0 unique close: 0 no. print messages: 0
```


1. The local time and the local timezone where the code runs
2. number of open cross trades seen from the subscribed universe
3. number of close cross trades seen from the subscribed universe
4. unique open is the number of unique open cross trades mening if AAPL would receive two open cross unique open would count that as one (open cross trades should be the same as this parameter)
5. unique close is the number of unique close cross trades mening if AAPL would receive two close cross unique close would count that as one (close cross trades should be the same as this parameter)
6. no. print messages the number of all StockPrint messages without any filter decoded

**Historic data**

./historic_prints <FILE_NAME> 

First outputs the column names and their respective column number.
Outputs heart beat every 100.000 rows
When a open print is found the name of the ticker is detailed.
At the end the number of open prints are displayed.

*Filtered section, prefix (filtered)*

Number is the number of occasions open/close crosses within the ticker universe filter.

Unique per ticker name, should be the same as the above counters. If for example AAPL occurs twice or more, then the counter count one.

*Non filtered section, prefix (no filtered)*

Number is the number of occasions open/close crosses messages.

Unique per ticker name, should be the same as the above counters. If for example AAPL occurs twice or more, then the counter count one.



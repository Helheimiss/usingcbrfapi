# UsingCBRFAPI
C++ HTTP server for currency conversion using Central Bank of Russia (CBR) API.


## Features
- Convert any currency to Russian Rubles
- Convert between any two currencies
- Simple REST API
- Uses official CBR exchange rates


## Requirements
- C++20 compatible compiler
- CMake 4.10+
- Internet connection (for CBR API access)


## Dependencies
- cpp-httplib (header-only)
- tinyxml2 (included as submodule)


## API Usage
```bash
curl http://localhost:8080/100/USD # Convert to RUB
```

Convert Between Currencies
```bash
curl http://localhost:8080/50/RUB/USD # Converts 50 RUB to USD
curl http://localhost:8080/50/EUR/USD # Converts 50 EUR to USD
```


## Build
```bash
git clone --recursive https://github.com/Helheimiss/usingcbrfapi
cd usingcbrfapi
mkdir build && cd build
cmake ..
make
```
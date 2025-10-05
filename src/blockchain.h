#pragma once
#include <string>
#include "wallet.h"

class Blockchain {
public:
    Blockchain(const std::string& rpc_url);
    double get_native_balance(const std::string& address);
    // Functions for swap, get WETH balance, etc. will go here
    void swap_eth_to_weth(Wallet& wallet, double amount);

private:
    std::string rpc_url;
};

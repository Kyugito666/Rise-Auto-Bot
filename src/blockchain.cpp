#include "blockchain.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include "utils.h"

using json = nlohmann::json;

Blockchain::Blockchain(const std::string& rpc) : rpc_url(rpc) {}

double Blockchain::get_native_balance(const std::string& address) {
    json payload = {
        {"jsonrpc", "2.0"},
        {"method", "eth_getBalance"},
        {"params", {address, "latest"}},
        {"id", 1}
    };

    cpr::Response r = cpr::Post(cpr::Url{rpc_url},
                                cpr::Body{payload.dump()},
                                cpr::Header{{"Content-Type", "application/json"}});

    if (r.status_code == 200) {
        json response = json::parse(r.text);
        std::string hex_balance = response["result"];
        unsigned long long balance_wei = std::stoull(hex_balance, nullptr, 16);
        return static_cast<double>(balance_wei) / 1e18;
    }
    return 0.0;
}

// Dummy implementation for swapping
void Blockchain::swap_eth_to_weth(Wallet& wallet, double amount) {
    // This is a complex function. For a real implementation, you would need a C++ library
    // that can sign and send transactions, like cpp-ethereum or by manually constructing
    // the raw transaction and sending it via eth_sendRawTransaction.
    // For this example, we will just simulate it.
    std::cout << "Simulating swap of " << amount << " ETH for wallet " << wallet.get_address() << std::endl;
}

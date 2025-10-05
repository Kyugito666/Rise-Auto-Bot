#pragma once
#include <string>
#include <vector>

class Wallet {
public:
    Wallet(const std::string& private_key);
    std::string get_address() const;
    std::string get_private_key() const;
    void refresh_balance(const std::string& rpc_url);
    double get_native_balance() const;

private:
    std::string private_key;
    std::string address;
    double native_balance;
    // Add WETH balance here
};

std::vector<Wallet> load_wallets_from_file(const std::string& path);

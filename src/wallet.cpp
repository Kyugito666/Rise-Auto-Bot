#include "wallet.h"
#include "blockchain.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
// You would need a library like Keccak/secp256k1 to derive address from private key
// For simplicity, we'll use a placeholder.
#include "utils.h"

Wallet::Wallet(const std::string& pk) : private_key(pk), native_balance(0.0) {
    // In a real app, derive the address from the private key.
    // This is a complex cryptographic operation. We'll use a placeholder.
    this->address = "0x" + pk.substr(0, 10) + "...";
}

std::string Wallet::get_address() const { return address; }
std::string Wallet::get_private_key() const { return private_key; }
double Wallet::get_native_balance() const { return native_balance; }

void Wallet::refresh_balance(const std::string& rpc_url) {
    Blockchain bc(rpc_url);
    this->native_balance = bc.get_native_balance(this->address);
}

std::vector<Wallet> load_wallets_from_file(const std::string& path) {
    std::vector<Wallet> wallets;
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open private_keys.txt");
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            wallets.push_back(Wallet(line));
        }
    }
    return wallets;
}

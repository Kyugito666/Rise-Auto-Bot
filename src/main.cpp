#include <iostream>
#include <vector>
#include "wallet.h"
#include "ui.h"
#include "utils.h"
#include <cstdlib> // For getenv

std::string get_env_variable(const std::string& key) {
    char* val = getenv(key.c_str());
    return val == NULL ? std::string("") : std::string(val);
}

std::string get_short_address(const std::string& address) {
    if (address.length() < 10) return address;
    return address.substr(0, 6) + "..." + address.substr(address.length() - 4);
}


int main() {
    try {
        std::vector<Wallet> wallets = load_wallets_from_file("private_keys.txt");
        if (wallets.empty()) {
            std::cerr << "No private keys found in private_keys.txt" << std::endl;
            return 1;
        }
        UI ui(wallets);
        ui.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

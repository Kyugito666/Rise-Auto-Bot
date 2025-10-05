#pragma once
#include <vector>
#include "wallet.h"

class UI {
public:
    UI(std::vector<Wallet>& wallets);
    void run();

private:
    void draw_main_window();
    void update_wallet_info();
    void handle_input();
    std::vector<Wallet>& wallets;
    int selected_wallet_index;
};

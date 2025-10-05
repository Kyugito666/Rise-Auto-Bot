#include "ui.h"
#include <curses.h>
#include <fmt/core.h>
#include "utils.h"

UI::UI(std::vector<Wallet>& w) : wallets(w), selected_wallet_index(0) {}

void UI::run() {
    initscr();
    cbreak();
    noecho();
    keypad(stddscr, TRUE);
    curs_set(0);

    // Initial balance fetch
    std::string rpc_url = get_env_variable("RPC_RISE");
    for (auto& wallet : wallets) {
        wallet.refresh_balance(rpc_url);
    }

    while (true) {
        draw_main_window();
        handle_input();
    }

    endwin();
}

void UI::draw_main_window() {
    clear();
    int height, width;
    getmaxyx(stdscr, height, width);

    // Header
    mvprintw(1, (width - 12) / 2, "RISEAUTOBOT C++");

    // Wallet Info
    mvprintw(4, 2, "ACCOUNTS:");
    for (size_t i = 0; i < wallets.size(); ++i) {
        if (i == selected_wallet_index) {
            attron(A_REVERSE);
        }
        std::string text = fmt::format("{}: {} - ETH: {:.4f}", i + 1, get_short_address(wallets[i].get_address()), wallets[i].get_native_balance());
        mvprintw(5 + i, 2, text.c_str());
        if (i == selected_wallet_index) {
            attroff(A_REVERSE);
        }
    }
    
    // Menu
    mvprintw(height - 5, 2, "UP/DOWN to select | S to Swap | R to Refresh | Q to Quit");
    refresh();
}

void UI::handle_input() {
    int ch = getch();
    switch (ch) {
        case KEY_UP:
            if (selected_wallet_index > 0) selected_wallet_index--;
            break;
        case KEY_DOWN:
            if (selected_wallet_index < wallets.size() - 1) selected_wallet_index++;
            break;
        case 's':
        case 'S':
            // Call swap function
            break;
        case 'r':
        case 'R':
        {
            std::string rpc_url = get_env_variable("RPC_RISE");
            wallets[selected_wallet_index].refresh_balance(rpc_url);
            break;
        }
        case 'q':
        case 'Q':
            endwin();
            exit(0);
    }
}

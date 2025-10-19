#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

struct orders {
    int id;
    string type;   // "BUY" or "SELL"
    double price;
    int quantity;
};

// Generate random orders for single stock
orders generateRandomorders(int id) {
    string type = (rand() % 2 == 0) ? "BUY" : "SELL";
    double price = 950 + rand() % 200 + (rand() % 100) / 100.0; // Price between 950-1150
    int quantity = 1 + rand() % 50; // Quantity between 1-50
    return { id, type, price, quantity };
}

// Match orderss for single stock
void matchorderss(vector<orders>& buy_orderss, vector<orders>& sell_orderss) {
    sort(buy_orderss.begin(), buy_orderss.end(), [](const orders& a, const orders& b) { return a.price > b.price; });
    sort(sell_orderss.begin(), sell_orderss.end(), [](const orders& a, const orders& b) { return a.price < b.price; });

    while (!buy_orderss.empty() && !sell_orderss.empty() && buy_orderss[0].price >= sell_orderss[0].price) {
        int trade_qty = min(buy_orderss[0].quantity, sell_orderss[0].quantity);
        double trade_price = (buy_orderss[0].price + sell_orderss[0].price) / 2;

        cout << "Trade Executed: " << trade_qty << " shares @ Rs " << trade_price << endl;

        buy_orderss[0].quantity -= trade_qty;
        sell_orderss[0].quantity -= trade_qty;

        if (buy_orderss[0].quantity == 0) buy_orderss.erase(buy_orderss.begin());
        if (sell_orderss[0].quantity == 0) sell_orderss.erase(sell_orderss.begin());
    }
}

int dynamic_ask_bid() {
    srand(time(0));

    vector<orders> buy_orderss;
    vector<orders> sell_orderss;

    // Initial orderss for single stock
    buy_orderss.push_back({ 1, "BUY", 1050.50, 10 });
    buy_orderss.push_back({ 2, "BUY", 1025.75, 15 });
    sell_orderss.push_back({ 1, "SELL", 1075.25, 8 });
    sell_orderss.push_back({ 2, "SELL", 1100.50, 12 });

    int orders_id = 3;

    for (int i = 0; i < 10; i++) {
        orders new_orders = generateRandomorders(orders_id++);
        cout << "\nNew orders: " << new_orders.type << " " << new_orders.quantity
            << " shares @ Rs " << new_orders.price << endl;

        if (new_orders.type == "BUY")
            buy_orderss.push_back(new_orders);
        else
            sell_orderss.push_back(new_orders);

        matchorderss(buy_orderss, sell_orderss);

        // Print Top-of-Book (Market Depth)
        cout << "--- TOP OF BOOK ---\n";
        if (!buy_orderss.empty()) cout << "Best Bid: Rs " << buy_orderss[0].price << endl;
        if (!sell_orderss.empty()) cout << "Best Ask: Rs " << sell_orderss[0].price << endl;
        cout << "-----------------------\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}

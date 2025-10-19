#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>   // For rand()
#include <ctime>     // For seeding random
#include <thread>    // For sleep_for
#include <chrono>    // For chrono literals


using namespace std;

struct order {
    int id;
    string type;
    double price;
    int quantity;
    string symbol;
};

int stocks_basics() {
    vector<order> buy_orders;
    vector<order> sell_orders;

    buy_orders.push_back({ 1, "BUY", 2005.36, 10, "Mahindra & Mahindra" });
    buy_orders.push_back({ 2, "BUY", 1500.50, 15, "Tata Motors" });
    buy_orders.push_back({ 3, "BUY", 950.25, 20, "Infosys" });
    sell_orders.push_back({ 1, "SELL", 1200.75, 8, "HDFC Bank" });
    sell_orders.push_back({ 2, "SELL", 650.40, 12, "Reliance Industries" });
    sell_orders.push_back({ 2, "SELL", 780.99, 5, "Marico" });

    cout << "--- ORDER BOOK ---\n";
    cout << "BUY ORDERS:\n";
    for (auto& o : buy_orders)
        cout << "ID " << o.id << " | " << o.symbol << " | "
        << o.quantity << " @ Rs " << o.price << endl;

    cout << "\nSELL ORDERS:\n";
    for (auto& o : sell_orders)
        cout << "ID " << o.id << " | " << o.symbol << " | "
        << o.quantity << " @ Rs " << o.price << endl;

    // Concept :

    //Buy Orders → Descending by price(highest first)
    //    Sell Orders → Ascending by price(lowest first)
    //    C++ me iske liye std::sort + lambda function use karte hain.

   // ---  Sort Orders ---
    sort(buy_orders.begin(), buy_orders.end(), [](const order& a, const order& b) {
        return a.price > b.price;
        });
    sort(sell_orders.begin(), sell_orders.end(), [](const order& a, const order& b) {
        return a.price < b.price;
        });

    //Syntax Breakdown :

    //[] → Capture list.Lambda ke andar hum variables outer scope se use kar sakte hain.
    //    Humne koi variable capture nahi kiya, isliye empty[].
    //    (const order & a, const order & b) → Parameters.
    //    Comparator function ko 2 elements diye jaate hain(a aur b)
    //    Hum compare karenge in dono ka price
    //{ return a.price > b.price; } → Function body
    //    Agar true return hota hai → a ko b se pehle rakha jayega
    //    Agar false → b pehle aayega
    //    BUY orders : a.price > b.price → matlab highest price first
    //    SELL orders : a.price < b.price → matlab lowest price first
    // 
    //Buy Orders vector me : [100, 150, 120]
    //    Lambda compare karti hai : return a.price > b.price
    //    Sorting : [150, 120, 100] → Highest first
    //    Sell Orders vector me : [100, 150, 120]
    //    Lambda compare karti hai : return a.price < b.price
    //    Sorting : [100, 120, 150] → Lowest first

    // --- Top of Book ---
    cout << "\n--- TOP OF BOOK ---\n";
    if (!buy_orders.empty())
        cout << "Best Bid: Rs " << buy_orders[0].price << " (" << buy_orders[0].symbol << ")\n";
    if (!sell_orders.empty())
        cout << "Best Ask: Rs " << sell_orders[0].price << " (" << sell_orders[0].symbol << ")\n";

    return 0;
}
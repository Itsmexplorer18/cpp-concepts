//EXAMPLE WHERE TRY_LOCK CAN BE USED WHEN WE HAVE MULTIPLE RESOURCES AND MULTIPLE THREAD THE THREAD CAN GO TRY FOR ONE IF NOT GO TRY FOR ANOTHER
#include <iostream>
#include <thread>
#include <mutex>
#include <array>
#include <chrono>
#include <cstdlib>
#include <ctime>

constexpr int NUM_STOVES  = 4;
constexpr int NUM_CHEFS   = 10;

std::array<std::mutex, NUM_STOVES> stove_mutex;
std::array<int, NUM_STOVES>        stove_fuel = {100, 100, 100, 100};

void cook() {
    const int fuel_needed = std::rand() % 30;

    while (true) {
        for (int i = 0; i < NUM_STOVES; ++i) {

            std::unique_lock<std::mutex> lk(stove_mutex[i], std::try_to_lock);

            if (lk.owns_lock()) {
                // --- critical section ---
                if (stove_fuel[i] - fuel_needed < 0) {
                    std::cout << "Stove " << i << " — no more fuel, going home\n";
                } else {
                    stove_fuel[i] -= fuel_needed;
                    std::cout << "Stove " << i
                              << " — fuel left: " << stove_fuel[i] << "\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
                // --- end critical section (lk auto-unlocks here) ---
                return;
            }

            // All stoves busy on last iteration — back off and retry
            if (i == NUM_STOVES - 1) {
                std::cout << "No stove available yet — waiting...\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                i = -1;  // reset loop (++i makes it 0)
            }
        }
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::array<std::thread, NUM_CHEFS> chefs;
    for (auto& chef : chefs) chef = std::thread(cook);
    for (auto& chef : chefs) chef.join();

    return 0;
}

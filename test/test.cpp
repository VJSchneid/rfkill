#include <rfkill.h>
#include <iostream>

int main() {
    std::vector<rfkill::Event> events = rfkill::list();

    std::cout << "events:" << std::endl;
    for (auto &event: events) {
        std::cout << event.name << std::endl;
    }

    std::cout << std::endl << "rfkill all!" << std::endl;
    rfkill::block(rfkill::ALL, true);
}

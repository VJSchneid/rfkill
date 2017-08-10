#include "../rfkill.h"

int main() {
    std::vector<rfkill::Event> events = rfkill::list();
}
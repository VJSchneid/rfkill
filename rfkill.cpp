#include "rfkill.h"

#include <unistd.h>
#include <fstream>
#include <fcntl.h>
#include <sstream>
#include <cstring>

#include <iostream>

namespace rfkill {

    Event::Event() {}

    Event::Event(RawEvent &rawEvent_) {
        index = rawEvent_.index;
        type = static_cast<Type>(rawEvent_.type);
        soft = static_cast<bool>(rawEvent_.soft);
        hard = static_cast<bool>(rawEvent_.hard);

        name = getName(index);
    }

    std::string getName(uint32_t index) {
        std::string name;
        std::stringstream path;
        path << "/sys/class/rfkill/rfkill" << index << "/name";

        std::ifstream file(path.str());
        if (file.is_open()) {
            std::getline(file, name);
        }

        return std::move(name);
    }

    std::vector<Event> list() {
        std::vector<Event> events;
        RawEvent event;
        ssize_t len;
        int fd;

        fd = open("/dev/rfkill", O_RDONLY);
        if (fd < 0) {
            return events;
        }

        if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0) {
            close(fd);
            return events;
        }

        while ((len = read(fd, &event, sizeof(event)))) {
            if (len < 0) {
                break;
            }

            if (len != sizeof(event)) {
                continue;
            }

            if (event.operation != Operation::ADD) {
                continue;
            }

            events.emplace_back(event);
        }

        close(fd);
        return std::move(events);
    }

    bool send(RawEvent event) {
        ssize_t len;
        int fd;

        fd = open("/dev/rfkill", O_RDWR);
        if (fd < 0) {
            return false;
        }

        len = write(fd, &event, sizeof(event));

        close(fd);
        return len == sizeof(event);
    }

    bool block(uint32_t index, bool value) {
        RawEvent event;

        std::memset(&event, 0, sizeof(event));
        event.operation = Operation::CHANGE;
        event.index = index;
        event.soft = static_cast<uint8_t>(value);

        return send(std::move(event));
    }

    bool block(Type type, bool value) {
        RawEvent event;

        std::memset(&event, 0, sizeof(event));
        event.operation = Operation::CHANGE_ALL;
        event.type = static_cast<uint8_t>(type);
        event.soft = static_cast<uint8_t>(value);

        return send(std::move(event));
    }

}

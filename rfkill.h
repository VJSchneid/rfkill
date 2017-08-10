#ifndef RFKILL_H
#define RFKILL_H

#include <stdint.h>
#include <string>
#include <vector>

namespace rfkill {

    enum Type {
        ALL = 0,
        WLAN,
        BLUETOOTH,
        UWB,
        WIMAX,
        WWAN,
        GPS,
        FM,
        NFC,
        NUM_RFKILL_TYPES,
    };

    enum Operation {
        ADD = 0,
        DEL,
        CHANGE,
        CHANGE_ALL,
    };

    struct RawEvent {
        u_int32_t   index;
        u_int8_t    type;
        u_int8_t    operation;
        u_int8_t    soft, hard;
    } __attribute__((packed));

    struct Event {
        std::string name;
        uint32_t index;
        Type type;
        bool soft;
        bool hard;

        Event();
        Event(RawEvent &rawEvent_);
    };

    std::string getName(uint32_t index);

    std::vector<Event> list();

    bool send(RawEvent event);

    bool block(uint32_t index, bool value);

    bool block(Type type, bool value);

}

#endif
#ifndef MESSAGE_H
#define MESSAGE_H

// Make a struct with no padding
struct __attribute__((__packed__)) Header {
    uint16_t lenName;
    uint32_t lenMessage;
    uint8_t magicNum;
};

#endif
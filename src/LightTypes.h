#ifndef LIGHTTYPES_H
#define LIGHTTYPES_H
#include <stdbool.h>

enum Light
{
    RED,
    YELLOW,
    GREEN
};

struct TrafficLights
{
    enum Light northSouth;
    enum Light eastWest;
    bool carPresentNS;
    bool carPresentEW;
};

enum LightState
{
    NS_GREEN,
    NS_YELLOW,
    ALL_RED_PREV_NS,
    EW_GREEN,
    EW_YELLOW,
    ALL_RED_PREV_EW
};

#endif
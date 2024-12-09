#include "lights.h"


#include <stdio.h>
#include <unistd.h>
#include "LightTypes.h"

#define DEBUG 0

void initLights(struct TrafficLights *lights)
{
    lights->northSouth = GREEN;
    lights->eastWest = RED;
    lights->carPresentNS = false;
    lights->carPresentEW = false;
}

void updateCars(bool carNs, bool carEw, struct TrafficLights *lights)
{
    lights->carPresentNS = carNs;
    lights->carPresentEW = carEw;
}

void updateLights(enum LightState state, struct TrafficLights *lights)
{
    switch (state)
    {
    case NS_GREEN:
        lights->northSouth = GREEN;
        lights->eastWest = RED;
        break;

    case NS_YELLOW:
        lights->northSouth = YELLOW;
        lights->eastWest = RED;
        break;

    case ALL_RED_PREV_NS: // keep both red for a second for safety
        lights->northSouth = RED;
        lights->eastWest = RED;
        break;

    case EW_GREEN:
        lights->northSouth = RED;
        lights->eastWest = GREEN;
        break;
        
    case EW_YELLOW:
        lights->northSouth = RED;
        lights->eastWest = YELLOW;
        break;

    case ALL_RED_PREV_EW: // keep both red for a second for safety
        lights->northSouth = RED;
        lights->eastWest = RED;
        break;

    default: // error, return to default state
        printf("Unknown LightState detected!\n");
        lights->northSouth = GREEN;
        lights->eastWest = RED;
        break;
    }
}

void printLights(struct TrafficLights lights)
{
    printf("\n========================\n");
    printf("North-South lights:\n");
    printf("%s", printLight(lights.northSouth));
    printf("East-West lights:\n");
    printf("%s", printLight(lights.eastWest));
}

char* printLight(enum Light light)
{
    switch (light)
    {
    case RED:
        return "Light is red\n";
        break;
    case YELLOW:
        return "Light is yellow\n";
        break;
    case GREEN:
        return "Light is green\n";
        break;
    default:
        return "Unknown state! :(\n";
        break;
    }
}

enum LightState nextState(enum LightState state, struct TrafficLights *lights)
{
    enum LightState newState = NS_GREEN;

    switch (state)
    {
    case NS_GREEN:
        if(lights->carPresentNS)
        {
            sleep(10);
            if(!lights->carPresentEW)
            {
                sleep(30);
            }
        }
        sleep(5);
        newState = NS_YELLOW;
        break;

    case NS_YELLOW:
        sleep(2);
        newState = ALL_RED_PREV_NS;
        break;

    case ALL_RED_PREV_NS: // keep both red for a second for safety
        sleep(1);
        newState = EW_GREEN;
        break;

    case EW_GREEN:
        if(lights->carPresentEW)
        {
            sleep(10);
            if(!lights->carPresentNS)
            {
                sleep(30);
            }
        }
        sleep(5);
        newState = EW_YELLOW;
        break;
        
    case EW_YELLOW:
        sleep(2);
        newState = ALL_RED_PREV_EW;
        break;

    case ALL_RED_PREV_EW: // keep both red for a second for safety
        sleep(1);
        newState = NS_GREEN;
        break;

    default: // error, return to default state
        printf("Unknown LightState detected!\n");
        break;
    }

    return newState;
}


// void sleepWrapper(int time)
// {
// #if DEBUG
//     sleep(time)
// #else
//     printf("Sleeping for %d s", &time);
// #endif
// }






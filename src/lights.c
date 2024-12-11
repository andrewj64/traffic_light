#include "lights.h"


#include <stdio.h>
#include <unistd.h>
#include "LightTypes.h"

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
    printf("North-South lights: ");
    printf("%s\n", getLightString(lights.northSouth));
    printf("East-West lights: ");
    printf("%s\n", getLightString(lights.eastWest));
}

char* getLightString(enum Light light)
{
    switch (light)
    {
    case RED:
        return "RED";
        break;
    case YELLOW:
        return "YELLOW";
        break;
    case GREEN:
        return "GREEN";
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
        }
        if(lights->carPresentEW)
        {
            sleep(10);
            newState = NS_YELLOW;
        }
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
                sleep(10);
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







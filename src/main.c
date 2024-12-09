#include <stdio.h>
#include "lights.h"
#include "LightTypes.h"

int main()
{
    enum LightState state = NS_GREEN;
    struct TrafficLights lights;
    

    printf("Hello, World!\n");
    while(1)
    {
        updateLights(state, &lights);
        // print state
        printLights(lights);
        printf("%d\n", state);
        // update variables
        // prompt for cars
        // next state
        state = nextState(state, &lights);

    }
    return 0;
}


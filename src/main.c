#include <stdio.h>
#include <unistd.h>
#include "lights.h"
#include "LightTypes.h"

bool promptUserBool()
{
    bool yes = false;
    char r;
    r = getchar();
    if (r == '\n') r = getchar();
    while(r != 'n' && r != 'N' && r != 'y' && r != 'Y')
    {
        printf("invalid input, enter the choice(y/Y/n/N) again : ");
        r = getchar();
        if (r == '\n') r = getchar();
    }
    if(r == 'y' || r == 'Y')
    {
        yes = true;
    }
    return yes;
}

int main()
{
    enum LightState state = NS_GREEN;
    struct TrafficLights lights;
    bool carsNs, carsEw;
    
    while(1)
    {
        // update lights variables
        updateLights(state, &lights);

        // print state
        printLights(lights);

        // prompt for cars
        printf("Are there cars travelling North/South? y/n ");
        carsNs = promptUserBool();
        printf("Are there cars travelling East/West? y/n ");
        carsEw = promptUserBool();
        updateCars(carsNs, carsEw, &lights);


        // get next state
        state = nextState(state, &lights);
    }
    return 0;
}


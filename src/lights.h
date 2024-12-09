#ifndef LIGHTS_H
#define LIGHTS_H

#include "LightTypes.h"

void updateLights(enum LightState state, struct TrafficLights *lights);
void updateCars(bool carNs, bool carEw, struct TrafficLights *lights);
void printLights(struct TrafficLights lights);
char* getLightString(enum Light light);
enum LightState nextState(enum LightState state, struct TrafficLights *lights);

#endif // LIGHTS_H
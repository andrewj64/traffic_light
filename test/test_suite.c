#include "acutest.h"
#include <unistd.h>
// #include <stdio.h>

#include "lights.h"


void test_example()
{
    TEST_CHECK(1==1);
}

void test_updateLights_NS_GREEN()
{
    enum LightState mockState = NS_GREEN;
    struct TrafficLights tl_uut;

    updateLights(mockState, &tl_uut);
    TEST_CHECK(tl_uut.northSouth == GREEN);
    TEST_CHECK(tl_uut.eastWest == RED);
}

void test_updateLights_NS_YELLOW()
{
    enum LightState mockState = NS_YELLOW;
    struct TrafficLights tl_uut;

    updateLights(mockState, &tl_uut);
    TEST_CHECK(tl_uut.northSouth == YELLOW);
    TEST_CHECK(tl_uut.eastWest == RED);
}

void test_updateLights_ALL_RED_PREV_NS()
{
    enum LightState mockState = ALL_RED_PREV_NS;
    struct TrafficLights tl_uut;

    updateLights(mockState, &tl_uut);
    TEST_CHECK(tl_uut.northSouth == RED);
    TEST_CHECK(tl_uut.eastWest == RED);
}

void test_updateLights_EW_GREEN()
{
    enum LightState mockState = EW_GREEN;
    struct TrafficLights tl_uut;

    updateLights(mockState, &tl_uut);
    TEST_CHECK(tl_uut.northSouth == RED);
    TEST_CHECK(tl_uut.eastWest == GREEN);
}

void test_updateLights_EW_YELLOW()
{
    enum LightState mockState = EW_YELLOW;
    struct TrafficLights tl_uut;

    updateLights(mockState, &tl_uut);
    TEST_CHECK(tl_uut.northSouth == RED);
    TEST_CHECK(tl_uut.eastWest == YELLOW);
}

void test_updateLights_ALL_RED_PREV_EW()
{
    enum LightState mockState = ALL_RED_PREV_EW;
    struct TrafficLights tl_uut;

    updateLights(mockState, &tl_uut);
    TEST_CHECK(tl_uut.northSouth == RED);
    TEST_CHECK(tl_uut.eastWest == RED);
}

void test_updateCars()
{
    struct TrafficLights tl_uut;
    int testInputNS, testInputEW;
    for(int i=0; i<=0b11; i++) // loop over all possible test cases from 0b00 to 0b11
    {
        testInputNS = i & 0b01;
        testInputEW = i & (0b10 >> 1);
        updateCars(testInputNS, testInputEW, &tl_uut);
        TEST_CHECK(tl_uut.carPresentNS==testInputNS);
        TEST_CHECK(tl_uut.carPresentEW==testInputEW);
    }
}

void test_getLightString_RED()
{
    enum Light testLight = RED;
    TEST_CHECK(strcmp(getLightString(testLight), "RED")==0);
}

void test_getLightString_YELLOW()
{
    enum Light testLight = YELLOW;
    TEST_CHECK(strcmp(getLightString(testLight), "YELLOW")==0);
}

void test_getLightString_GREEN()
{
    enum Light testLight = GREEN;
    TEST_CHECK(strcmp(getLightString(testLight), "GREEN")==0);
}

void test_nextState_NS_GREEN()
{
    //TEST_SKIP("skipping");
    enum LightState mockState = NS_GREEN;
    struct TrafficLights mockLights;

    mockLights.carPresentEW = true;
    TEST_CHECK(nextState(mockState, &mockLights) == NS_YELLOW);
    mockLights.carPresentEW = false;
    TEST_CHECK(nextState(mockState, &mockLights) == NS_GREEN);
}

void test_nextState_NS_YELLOW()
{
    //TEST_SKIP("skipping");
    enum LightState mockState = NS_YELLOW;
    struct TrafficLights mockLights;

    TEST_CHECK(nextState(mockState, &mockLights) == ALL_RED_PREV_NS);
}

void test_nextState_ALL_RED_PREV_NS()
{
    //TEST_SKIP("skipping");
    enum LightState mockState = ALL_RED_PREV_NS;
    struct TrafficLights mockLights;

    TEST_CHECK(nextState(mockState, &mockLights) == EW_GREEN);
}

void test_nextState_EW_GREEN()
{
    //TEST_SKIP("skipping");
    enum LightState mockState = EW_GREEN;
    struct TrafficLights mockLights;

    TEST_CHECK(nextState(mockState, &mockLights) == EW_YELLOW);
}

void test_nextState_EW_YELLOW()
{
    //TEST_SKIP("skipping");
    enum LightState mockState = EW_YELLOW;
    struct TrafficLights mockLights;

    TEST_CHECK(nextState(mockState, &mockLights) == ALL_RED_PREV_EW);
}

void test_nextState_ALL_RED_PREV_EW()
{
    //TEST_SKIP("skipping");
    enum LightState mockState = ALL_RED_PREV_EW;
    struct TrafficLights mockLights;

    TEST_CHECK(nextState(mockState, &mockLights) == NS_GREEN);
}


TEST_LIST = {
//    { "updateLights", test_updateLights },
   { "example", test_example },
   { "updateLights_NS_GREEN", test_updateLights_NS_GREEN },
   { "updateLights_NS_YELLOW", test_updateLights_NS_YELLOW },
   { "updateLights_ALL_RED_PREV_NS", test_updateLights_ALL_RED_PREV_NS },
   { "updateLights_EW_GREEN", test_updateLights_EW_GREEN },
   { "updateLights_EW_YELLOW", test_updateLights_EW_YELLOW },
   { "updateLights_ALL_RED_PREV_EW", test_updateLights_ALL_RED_PREV_EW },
   { "updateCars", test_updateCars },
   { "getLightString_RED", test_getLightString_RED },
   { "getLightString_YELLOW", test_getLightString_YELLOW },
   { "getLightString_GREEN", test_getLightString_GREEN },
   { "nextState_NS_GREEN", test_nextState_NS_GREEN },
   { "nextState_NS_YELLOW", test_nextState_NS_YELLOW },
   { "nextState_ALL_RED_PREV_NS", test_nextState_ALL_RED_PREV_NS },
   { "nextState_EW_GREEN", test_nextState_EW_GREEN },
   { "nextState_EW_YELLOW", test_nextState_EW_YELLOW },
   { "nextState_ALL_RED_PREV_EW", test_nextState_ALL_RED_PREV_EW },
   { NULL, NULL }     /* zeroed record marking the end of the list */
};
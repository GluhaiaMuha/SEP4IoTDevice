#include <gtest/gtest.h>
#include "fff/fff.h"

extern "C"
{
    #include <sensorHandler.h>
}

class SensorHandler_test : public ::testing::Test
{
protected:
  void SetUp() override
  {
  }
  void TearDown() override
  {
  }
};

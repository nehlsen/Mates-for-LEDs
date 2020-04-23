# Matrix IDF Component

_Overengineered Matrix library for ESP32 IDF using FastLed_

## Credit
Parts copied from or at least inspired by Marcmerlin FastLed NeoMatrix and Adafruit GFX Library.  
Credit goes to
- https://github.com/marcmerlin/FastLED_NeoMatrix.git
- https://github.com/adafruit/Adafruit-GFX-Library

## What's inside:
* `LedMatrix` and `GfxPrimitives` compose the IDF Component
* `test` contains IDF compatible ESP32 Test-cases
* `testapp` contains a standalone test application to be run on the ESP32 (to run the tests from `test`)
* `demoapp` contains a demo application for the library

## Usage

* Component \
Put it into the components directory of your IDF Project (or point to using the `EXTRA_COMPONENT_DIRS` variable in CMakeLists) and use it.
* demoapp
```
# make sure IDF_PATH etc is properly set up
cd demoapp
mkdir build && cd build
cmake ..
make flash
```
* testapp
```
# make sure IDF_PATH etc is properly set up
cd testapp
mkdir build && cd build
cmake ..
make flash monitor
```

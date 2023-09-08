#include "Emulator.h"
#include <algorithm>
using namespace std;


Emulator::Emulator() {
  chip8 = new Chip8();
  keyboard = new Keyboard();
  display = new Display();
  speaker = new Speaker();
}

Emulator::~Emulator() {
  keyboard->shutDown();
  delete keyboard;
  keyboard = NULL;

  display->shutDown();
  delete display;
  display = NULL;

  speaker->shutDown();
  delete speaker;
  speaker = NULL;

  delete chip8;
  chip8 = NULL;
}

/**
 * Runs a single cycle of emulator. Since there are
 * 9 CPU cycles (540Hz) for every 1 refresh cycle (60Hz),
 * this is implemented using a time variable.
*/
void Emulator::runCycle() {
  chip8->execute_instruction();

  if (time == 0) {
    // input
    keyboard->setKeys(chip8->virtualKeys);

    // output
    if (chip8->drawFlag) {
      display->drawDisplay(chip8->virtualDisplay);
      chip8->drawFlag = false;
    }

    // update counters
    if (chip8->dt > 0) {
      chip8->dt = max(chip8->dt, (uint8_t) 0);
    }
    if (chip8->st > 0) {
      chip8->st = max(chip8->st, (uint8_t) 0);
      speaker->playSound();
    }
  }
  time = (time + 1) % 9;
}
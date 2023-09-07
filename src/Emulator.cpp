#include "Emulator.h"
#include <algorithm>
using namespace std;

void Emulator::runCycle() {
  chip8->execute_instruction();

  if (chip8->drawFlag) {
    display->drawDisplay(chip8->virtualDisplay);
    chip8->drawFlag = false;
  }

  if (chip8->dt > 0) {
    chip8->dt = max(chip8->dt, 0);
  }
  if (chip8->st > 0) {
    chip8->st = max(chip8->st, 0);
    speaker->playSound();
  }

  keyboard->setKeys(chip8->virtualKeys);
}
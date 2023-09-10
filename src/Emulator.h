#include "Chip8.h"
#include "InputOutput/Keyboard.h"
#include "InputOutput/Display.h"
#include "InputOutput/Speaker.h"

class Emulator {
  public:
    int time;
    Emulator();
    ~Emulator();
    void runCycle();
    Keyboard *keyboard;

  private:
    Chip8 *chip8;
    Display *display;
    Speaker *speaker;
};
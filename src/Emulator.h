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
    Chip8 *chip8;

  private:
    Display *display;
    Speaker *speaker;
};
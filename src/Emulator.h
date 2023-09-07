#include "Chip8.h"
#include "Keyboard.h"
#include "Display.h"
#include "Speaker.h"

class Emulator {
  public:
    Emulator();
    void runCycle();

  private:
    Chip8 *chip8;
    Keyboard *keyboard;
    Display *display;
    Speaker *speaker;
};
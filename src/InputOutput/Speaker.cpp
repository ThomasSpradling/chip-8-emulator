#include <emscripten.h>
#include "Speaker.h"

/**
 * Forwards TypeScript function to play a sound.
*/
void Speaker::playSound() {
  EM_ASM(
    playSound();
  );
}
void Speaker::shutDown() {}
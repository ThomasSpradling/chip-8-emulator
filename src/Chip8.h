#include <vector>
#include <array>
using namespace std;

class Chip8 {
private:
  uint16_t current_instruction; // two byte opcode

  array<uint8_t, 16> registers; // 16 registers
  uint16_t I;
  array<uint8_t, 4096> memory;  // 4 KB memory

  uint8_t sp; // stack pointer
  array<uint16_t, 16> stack; // array of at most 16 addresses

  int16_t pc; // program counter

public:
  int drawFlag;

  uint8_t dt; // delay timer
  uint8_t st; // sound timer

  array<array<bool, 64>, 32> virtualDisplay; // 32x64 virtual display
  array<bool, 16> virtualKeys; // 16 keys

  /**
   * Resets the memory, registers, stack, input, and output. This includes
   * copying the font set to memory.
  */
  void init();

  /**
   * Makes a call to `init` and loads `buf` into memory starting at 0x200.
  */
  int load(const vector<char> &buf);

  /**
   * Fetches the current instruction and puts it into `current_instruction`
  */
  void fetch_instruction();

  /**
   * Executes instructions based on opcode.
  */
  void execute_instruction();
};
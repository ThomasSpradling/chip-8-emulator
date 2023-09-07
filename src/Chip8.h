#include <vector>
#include <array>
using namespace std;

class Chip8 {
public:
  int drawFlag;
  array<uint8_t, 4096> memory;
  array<array<bool, 64>, 32> virtualDisplay; // 32x64 virtual display
  array<bool, 16> virtualKeys; // 16 keys

  // timers
  int dt;
  int st;

  /**
   * Resets the memory, regiesteers, stack, input, and output. This includes
   * copying the font set to memory.
  */
  void init();

  /**
   * Makes a call to `init` and loads `buf` into memory starting at 0x200.
  */
  int load(const vector<char> &buf);

  /**
   * Executes instructions based on opcode.
  */
  void execute_instruction();
};
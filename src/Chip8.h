#include <vector>
#include <array>
#include <string>
using namespace std;

class Chip8 {
private:
  uint16_t current_instruction; // two byte opcode

  array<uint8_t, 16> registers; // 16 registers
  uint16_t I;
  array<uint8_t, 4096> memory;  // 4 KB memory

  uint8_t sp; // stack pointer
  array<uint16_t, 16> stack; // array of at most 16 addresses

  uint16_t pc; // program counter

  // array<string, 2> indexToRomName = {"example.txt", "example2.txt"};
  array<string, 2> indexToRomName;

public:
  bool drawFlag = false;

  uint8_t dt; // delay timer
  uint8_t st; // sound timer

  array<array<bool, 64>, 32> virtualDisplay; // 32x64 virtual display
  array<bool, 16> virtualKeys; // 16 keys

  Chip8();
  void init();
  void loadROM(const string &filename);
  void fetch_instruction();
  void execute_instruction();
  void incrementPC(uint16_t amount);
  void decrementPC(uint16_t amount);
};
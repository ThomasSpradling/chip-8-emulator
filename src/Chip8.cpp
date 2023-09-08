#include "Chip8.h"
#include <cstdlib>

void Chip8::init() {
  registers.fill(0);
  dt = st = I = sp = pc = 0;

  stack.fill(0);
  memory.fill(0);
}

void Chip8::fetch_instruction() {
  current_instruction = (memory[pc * 2 + 0x200] << 8) | memory[pc * 2 + 0x200 + 1];
}

void Chip8::execute_instruction() {
  fetch_instruction();

  uint16_t nnn = current_instruction & 0x0FFF;
  uint8_t x = (current_instruction >> 8) & 0xF;
  uint8_t y = (current_instruction >> 4) & 0xF;
  uint8_t kk = current_instruction & 0x00FF;
  uint8_t n = current_instruction & 0x000F;

  bool is_valid = true;

  // grab uppermost letter
  switch (current_instruction >> 12) {
    case 0x0:
      // 0x00E0 - CLS: Clear the display.
      if ((current_instruction & 0x0FFF) == 0x0E0) {
        for (auto &row : virtualDisplay)
          row.fill(false);
        break;
      }
      // 0x00EE - RET: Return from subroutine.
      else if ((current_instruction & 0x0FFF) == 0x0EE) {
        pc = stack[sp--];
        break;
      }
      // 0x0nnn - SYS addr: Jump to machine code routine at address nnn.
      else break; // SYS addr is ignored in modern interpreters
    case 0x1:
      // 0x1nnn - JP addr: Jump to address nnn.
      pc = nnn;
      break;
    case 0x2:
      // 0x2nnn - CALL addr: Call subroutine at address nnn.
      stack[++sp] = (pc = nnn);
      break;
    case 0x3:
      // 0x3xkk - SE x, kk: Skip next instruction if Vx = kk.
      if (registers[x] == kk)
        pc += 2;
      break;
    case 0x4:
      // 0x4xkk - SNE Vx, byte: Skip next instruction if Vx != kk.
      if (registers[x] != kk)
        pc += 2;
      break;
    case 0x5:
      // 0x5xy0 - SE Vx, Vy: Skip next instruction if Vx = Vy.
      if ((current_instruction & 0xF) == 0x0) {
        if (registers[x] == registers[y])
          pc += 2;
        break;
      }
    case 0x6:
      // 0x6xkk - LD Vx, byte: Set Vx = kk.
      registers[x] = kk;
      break;
    case 0x7:
      // 0x7xkk - ADD Vx, byte: Set Vx = Vx + kk.
      registers[x] += kk;
      break;
    case 0x8:
      is_valid = true;
      switch (current_instruction & 0xF) {
        case 0x0:
          // 0x8xy0 - LD Vx, Vy: Set Vx = Vy.
          registers[x] = registers[y];
          break;
      
        case 0x1:
          // 0x8xy1 - OR Vx, Vy: Set Vx = Vx OR Vy.
          registers[x] |= registers[y];
          break;

        case 0x2:
          // 0x8xy2 - AND Vx, Vy: Set Vx = Vx AND Vy.
          registers[x] &= registers[y];
          break;

        case 0x3:
          // 0x8xy3 - XOR Vx, Vy: Set Vx = Vx XOR Vy.
          registers[x] ^= registers[y];
          break;

        case 0x4:
          // 0x8xy4 - ADD Vx, Vy: Set Vx = Vx + Vy, set VF = carry.
          // overflow case automatically handled
          registers[x] += registers[y];
          registers[0xF] = (uint8_t) (UINT8_MAX - registers[x] < registers[y]);
          break;

        case 0x5:
          // 0x8xy5 - SUB Vx, Vy: Set Vx = Vx - Vy, set VF = NOT borrow.
          registers[0xF] = (uint8_t) registers[x] > registers[y];
          registers[x] -= registers[y];
          break;

        case 0x6:
          // 0x8xy6 - SHR Vx: Set Vx = Vx SHR 1.
          registers[0xF] = registers[x] & 1;
          registers[x] >>= 1;
          break;

        case 0x7:
          // 0x8xy7 - SUBN Vx, Vy: Set Vx = Vy - Vx, set VF = NOT borrow.
          registers[0xF] = (uint8_t) registers[y] > registers[x];
          registers[x] = registers[y] - registers[x];
          break;

        case 0xE:
          // 0x8xyE - SHL Vx: Set Vx = Vx SHL 1.
          registers[0xF] = registers[x] & 1;
          registers[x] <<= 1;
          break;
        
        default:
          is_valid = false;
          break;
      }
      if (is_valid) {
        break;
      }
    
    case 0x9:
      // 0x9xy0 - SNE Vx, Vy: Skip next instruction if Vx != Vy.
      if ((current_instruction & 0xF) == 0x0) {
        if (registers[x] != registers[y])
          pc += 2;
        break;
      }
    case 0xA:
      // 0xAnnn - LD I, addr: Set I = nnn.
      I = nnn;
      break;
    case 0xB:
      // 0xBnnn - JP V0, addr: Jump to nnn + V0.
      pc = nnn + registers[0x0];
      break;
    case 0xC:
      // 0xCxkk - AND Vx, byte: Set Vx = random byte AND kk.
      registers[x] = (rand() & 0xFF) & kk;
      break;
    case 0xD: {
      // 0xDxyn - DRW Vx, Vy, nibble: Display n-byte sprite at (Vx, Vy).

      bool isCollision = 0;
      // That is, places bytes I, ..., I + n - 1 into display
      for (int j = 0; j < n; j++) {
        // for each byte, memory[I + j]
        for (int i = 1; i <= 8; i++) {
          // modding out to allow wrapping around display
          int x0 = (registers[x] + i - 1) % 64;
          int y0 = (registers[y] + j) % 32;

          // XOR out screen location (x, y) with i-th bit of j-th byte
          int temp = virtualDisplay[x0][y0];
          virtualDisplay[x0][y0] ^= ((memory[I + j] >> (8 - i)) & 1);

          // if any bit went from set to unset
          if (temp == 1 && virtualDisplay[x0][y0] == 0)
            isCollision = 1;
        }
      }

      // tells main loop to draw when ready
      drawFlag = true;
      break;
    }
    case 0xE:
      // 0xEx9E - SKP x: Skip next instruction if key with value x is pressed.
      if ((current_instruction & 0xFF) == 0x9E) {
        if (virtualKeys[x])
          pc += 2;
        break;
      }
      // 0xExA1 - SKNP x: Skip next instruction if key with value x is not pressed.
      else if ((current_instruction & 0xFF) == 0xA1) {
        if (!virtualKeys[x])
          pc += 2;
        break;
      }
    case 0xF:
      is_valid = true;
      switch (current_instruction & 0xFF) {
        case 0x07:
          // 0xFx07 - LD Vx, DT: Set Vx = delay timer value.
          registers[x] = dt;
          break;
        
        case 0x0A:
          // 0xFx0A - LD Vx, K: Stall until key is pressed. Set Vx = key.
          for (int i = 0; i < virtualKeys.size(); i++) {
            if (virtualKeys[i]) {
              registers[x] = (uint8_t) i;
              break;
            }
          }
          // if no key is pressed, then skip this instruction cycle and try again
          pc--;
          break;

        case 0x15:
          // 0xFx15 - LD DT, Vx: Set delay timer = Vx.
          dt = registers[x];
          break;

        case 0x18:
          // 0xFx18 - LD ST, Vx: Set sound timer = Vx.
          st = registers[x];
          break;

        case 0x1E:
          // 0xFx1E - ADD I, Vx: Set I = I + Vx.
          I += registers[x];
          break;

        case 0x29:
          // 0xFx29 - LD F, Vx: Set I = location of sprite for digit Vx.
// TODO
          break;

        case 0x33:
          // 0xFx33 - LD B, Vx: Store BCD representation of Vx starting at I.

          // Stores each digit of Vx into I, I+1, I+2.
          memory[I] = floor(registers[x] / 100);
          memory[I + 1] = int(floor(registers[x] / 10)) % 10;
          memory[I + 2] = registers[x] % 10;
          break;

        case 0x55:
          // 0xFx55 - LD [I], Vx: Store registers V0 - Vx in memory starting at I.
          for (int i = 0; i <= x; i++)
            memory[I + i] = registers[i];
          break;

        case 0x65:
          // 0xFx65 - LD Vx, [I]: Read registers V0 - Vx from memory starting at I.
          for (int i = 0; i <= x; i++)
            registers[i] = memory[I + i];
          break;

        default:
          is_valid = false;
          break;
      }
      if (is_valid) {
        break;
      }
    default:
      break;
  }

  // go to next instruction
  pc++;
}
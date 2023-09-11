#include "Keyboard.h"
#include <iostream>

using namespace std;

void Keyboard::copyKeys(array<bool, 16> &keys) {
  copy(begin(currentKeys), end(currentKeys), begin(keys));
}

void Keyboard::setKey(int key, bool value) {
  cout << key << value << endl;
  // currentKeys[key] = value;
}

void Keyboard::shutDown() {}
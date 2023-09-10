#include <array>
using namespace std;

class Keyboard {
public:
  /**
   * Copies the current keys into the value `keys`.
  */
  void copyKeys(array<bool, 16> &keys);

  void shutDown();

  void setKey(int key, bool value);
private:
  array<bool, 16> currentKeys;

  /**
   * Sets the key `key` to be value `value`
  */
};
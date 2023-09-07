class Keyboard {
public:
  /**
   * Changes the value of keys (by reference) to the currently pressed keys. Here, `true`
   * indicates that a key is currently being pressed and `false` that it isn't.
  */
  void setKeys(array<bool, 16> &keys);
};
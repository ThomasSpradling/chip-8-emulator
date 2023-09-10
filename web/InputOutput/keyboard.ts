const keypad = {
  1: 0x1, 2: 0x2, 3: 0x3, 4: 0xC,
  q: 0x4, w: 0x5, e: 0x6, r: 0xD,
  a: 0x7, s: 0x8, d: 0x9, f: 0xE,
  z: 0xA, x: 0x0, c: 0xB, v: 0xF,
};

const performKeyAction = (e: KeyboardEvent, forwardValue: boolean) => {
  if (e.key in keypad)
    Module.setKey(e.key, forwardValue);
}

var Module = {
  /**
   * On key press, calls a C++ function to update keyboard.
   */
  setKey: (a: string, value: boolean) => {},
  onRuntimeInitialized: function() {
    window.addEventListener('keydown', (e: KeyboardEvent) => performKeyAction(e, true));
    window.addEventListener('keyup', (e: KeyboardEvent) => performKeyAction(e, false));
  },
};
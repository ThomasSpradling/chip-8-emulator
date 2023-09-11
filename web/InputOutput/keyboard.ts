const keypad = {
  1: 0x1, 2: 0x2, 3: 0x3, 4: 0xC,
  q: 0x4, w: 0x5, e: 0x6, r: 0xD,
  a: 0x7, s: 0x8, d: 0x9, f: 0xE,
  z: 0xA, x: 0x0, c: 0xB, v: 0xF,
};

const keys = document.getElementsByClassName('key-button');
for (let i = 0; i < keys.length; i++) {
  const id = keys[i].id.substring(7);
  keys[i].addEventListener('mousedown', () => performKeyAction(id, true));
  keys[i].addEventListener('mouseup', () => performKeyAction(id, false));
}

const performKeyAction = (key: string, forwardValue: boolean) => {
  if (key in keypad) {
    (window as any).Module.setKey(keypad[key as keyof typeof keypad], forwardValue);
    const button = document.getElementById(`button-${key}`);
    if (forwardValue) {
      button?.classList.add('active');
    } else {
      button?.classList.remove('active');
    }
  }
}

const initKeyboard = () => {
  window.addEventListener('keydown', (e: KeyboardEvent) => performKeyAction(e.key, true));
  window.addEventListener('keyup', (e: KeyboardEvent) => performKeyAction(e.key, false));
};
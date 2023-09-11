const ROMS = {
  game1: 0,
  game2: 1,
  game3: 2,
  game4: 3
};

const initROMLoader = () => {
  let currentRom = null;
  const romSelector = document.getElementById("romSelector");

  romSelector.addEventListener('change', (e) => {
    currentRom = ROMS[(e.target as HTMLSelectElement).value as keyof typeof ROMS];
    (window as any).Module.loadROM('example0.txt');
  });
};
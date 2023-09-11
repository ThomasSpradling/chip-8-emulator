const themes = {
  'Classic Mono': {
    primary: 'white',
    secondary: 'black'
  },
  'Retro Green': {
    primary: '#32CD32',
    secondary: '#006400'
  },
  'Cyberpunk Blue': {
    primary: '#7DF9FF',
    secondary: '#4B0082'
  },
  'High Contrast': {
    primary: '#FFFF00',
    secondary: '#00008B'
  },
  'Fire and Ice': {
    primary: '#FF0000',
    secondary: '#00FFFF'
  }
};

let currentTheme = themes['Classic Mono'];
const themeSelector = document.getElementById('themeSelector');
themeSelector.blur();
themeSelector.addEventListener('change', (e) => {
  currentTheme = themes[(e.target as HTMLSelectElement).value as keyof typeof themes];
});


const WIDTH = 64;
const HEIGHT = 32;

const canvas = document.getElementById('canvas') as HTMLCanvasElement;
const context = canvas.getContext('2d');
/**
 * Draws a single pixel at coordinates (x,y) in the HTML canvas. The color corresponds to either
 * the primary color (for `true`) or the secondary color (for `false`)
 */
const renderPixel = (x: number, y: number, color: boolean): void => {
  const [pixelSizeX, pixelSizeY] = [canvas.clientWidth / WIDTH, canvas.clientHeight / HEIGHT];
  context.fillStyle = color ? currentTheme.primary : currentTheme.secondary;
  context.fillRect(x * pixelSizeX, y * pixelSizeY, pixelSizeX, pixelSizeY);
};

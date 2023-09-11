/**
 * Draws a single pixel at coordinates (x,y) in the HTML canvas. The color corresponds to either
 * the primary color (for `true`) or the secondary color (for `false`)
 */
const renderPixel = (x: number, y: number, color: boolean): void => {
  console.log("Pixel drawn!", x, y, color);
};

const themes = {
  basic: {
    primary: 'white',
    secondary: 'black'
  },
  red: {
    primary: 'r',
    secondary: 'g'
  },
};

let currentTheme = themes['basic'];
const themeSelector = document.getElementById('themeSelector');
themeSelector.addEventListener('change', (e) => {
  currentTheme = themes[(e.target as HTMLSelectElement).value as keyof typeof themes];
  console.log(currentTheme);
});

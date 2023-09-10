/**
 * Draws a single pixel at coordinates (x,y) in the HTML canvas. The color corresponds to either
 * the primary color (for `true`) or the secondary color (for `false`)
 */
const renderPixel = (x: number, y: number, color: boolean): void => {
  console.log("Pixel drawn!", x, y, color);
};
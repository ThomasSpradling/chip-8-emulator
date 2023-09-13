const ROMS: {
  [key: string]: {
    src: string,
    title: string,
    author: string,
    description: string,
  }
} = {
  brick: {
    src: 'Brick (Brix hack, 1990).ch8',
    title: 'Brick',
    author: '(Brix hack, 1990)',
    description: 'A modified version of BRIX, a CHIP-8 game. Original BRIX by Andreas Gustafsson. This one is a solid wall; no air between bricks! 4, 6 - left/right',
  },
  brix: {
    src: 'Brix [Andreas Gustafsson, 1990].ch8',
    title: 'Brix',
    author: '(Andres Gustafsson), 1990',
    description: 'Arkanoid clone. 4, 6 - left/right'
  },
  dangerous: {
    src: 'Most Dangerous Game [Peter Maruhnic].ch8',
    title: 'Most Dangerous Game',
    author: '(Peter Maruhnic)',
    description: `
      VIP Most Dangerous Game pits a hunter against a hunted in a maze.  The hunter must
      shoot the hunted before either time runs out or the hunted escapes the maze.
      However, neither the hunted nor the hunter can see a wall in the maze until he runs
      into it.  There is always at least one path through the maze.

      How To Play VIP Most Dangerous Game

      1. Load the CHIP-8 interpretor at 0000-01FF
        and the game starting at 0200.

      2. Turn RUN switch on.

      3. Hunted's turn:
        When the arrow appears in the lower left, it is the hunted's turn.  Keys 2-4-6-8
        control direction (up-left-right-down, respectively).  The hunted continues to
        move until a) he makes 5 moves, b) he hits a wall or c) key 0 is pressed.

      4. Hunter's turn
        When the arrow appears in the lower right, it is the hunter's turn.  The hunter's
        turn consists of two modes, the move and the shoot.  Keys 2-4-6-8 and 0 control both
        modes.  Like the hunted, the hunter continues to move until a) he makes 3 moves,
        b) he hits a wall or c) key 0 is pressed.  If he hits the wall, case b), he cannot
        fire a bullet.  The hunter may fire one of his bullets using the direction keys
        2-4-6-8.  The bullet will travel four squares in the corresponding direction, unless
        a wall is encountered.  If the hunter prefers not to use a bullet, he must press key 0.

      5. Repeat steps 3 and 4 until:
        a) The number of turns (upper left on the display) expire.  The hunted wins.
        b) The hunter lands on or shoots the hunted.  The hunter wins.
        c) The hunted lands on hunter, thereby giving up.  The hunter wins.
        d) The hunted reaches the lower right corner of the maze with at least 1 move
            remaining in his turn.  The hunted wins, by escaping the maze.

      6. Variations of VIP Most Dangerous Game may be played by changing certain bytes in
        the program.
    `
  },
  maze: {
    src: 'Maze [David Winter, 199x].ch8',
    title: 'Maze',
    author: '(David Winter, 199x)',
    description: `Drawing a random maze like this one consists in drawing random diagonal
      lines. There are two possibilities: right-to-left line, and left-to-right
      line. Each line is composed of a 4*4 bitmap. As the lines must form non-
      circular angles, the two bitmaps won't be '/' and '\'. The first one
      (right line) will be a little bit modified. See at the end of this source.

      The maze is composed of 16 lines (as the bitmaps are 4 pixels high), each
      line consists of 32 bitmaps.
      Bitmaps are drawn in random mode. We choose a random value (0 or 1).
      If it is 1, we draw a left line bitmap. If it is 0, we draw a right one.`
  },
  pong: {
    src: 'Pong [Paul Vervalin, 1990].ch8',
    title: 'pong',
    author: '(Paul Vervalin, 1990)',
    description: `
      OK. here is PONG version 1.1.  The ball is a little faster in this
      version making play a little more realistic.  I know PONG 1.0 was
      just posted yesterday, but I think this version is significantly
      better, so here it is.

      Use keys 1 and 4 move left player and C and D move right player.

      Enjoy!!
    `
  },
  puzzle15: {
    src: '15 Puzzle [Roger Ivie].ch8',
    title: '15 Puzzle',
    author: '(Roger Ivie)',
    description: 'Rearrange the tiles into the sequence 0-F. Moves tile by it associated key.'
  },
  sierpinski: {
    src: 'Sierpinski [Sergey Naydenov, 2010].ch8',
    title: 'Sierpinski Carpet Demo',
    author: '(Sergey Naydenov, 2010)',
    description: ''
  },
  spaceinvaders: {
    src: 'Space Invaders [David Winter].ch8',
    title: 'Space Invaders',
    author: '(David Winter',
    description: `The well known game. Destroy the invaders with your ship. Shoot
      with 5, move with 4 and 6. Press 5 to begin a game.`
  },
  tictactoe: {
    src: 'Tic-Tac-Toe [David Winter].ch8',
    title: 'Tic-Tac-Toe',
    author: '(David Winter)',
    description: '2-play noughts and crosses board.',
  },
  trip8: {
    src: 'Trip8 Demo (2008) [Revival Studios].ch8',
    title: 'Trip8 Demo',
    author: '(Revival Studios, 2008)',
    description: `The Trip8/SuperTrip8 demo are demo's for the Chip-8 and SuperChip8 systems. The demo consists of an intro, 3D vectorballs, and 4 randomized dot-effects.  

      Writing a demo for the original Chip-8 interpreter was a real pain, since your framerate basically drops in half for every sprite you need to draw. So even clearing and redrawing a few dots will cause the framerate to drop to near zero :) Originally the demo was going to be bigger and there were much more graphical effects programmed/prototyped, but a lot of these effects turned out to be too much for the original unoptimized Chip-8 interpreters to handle.`
  },
  zero: {
    src: 'Zero Demo [zeroZshadow, 2007].ch8',
    title: 'Zero',
    author: '(zeroZshadow, 2007)',
    description: `
      This is my first program for the CHIP-8, a simple demo with 4 bouncing sprites.
      
      Enjoy!`
  },
};


const initROMLoader = () => {
  let currentRom = null;
  const romSelector = document.getElementById('romSelector');

  romSelector.addEventListener('change', (e) => {
    romSelector.blur();
    currentRom = ROMS[(e.target as HTMLSelectElement).value as keyof typeof ROMS];
    if (currentRom) {
      const description = document.getElementById('game-description');
      description.innerHTML = currentRom.description;

      const title = document.getElementById('game-title');
      title.innerHTML = currentRom.title;

      const author = document.getElementById('game-author');
      author.innerHTML = currentRom.author;

      (window as any).Module.loadROM(currentRom.src);
    }
  });
};
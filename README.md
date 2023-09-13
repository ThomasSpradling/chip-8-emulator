# Chip 8 Emulator

## About
[CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) is an interpreted assembly-like programming designed in the mid-1970s for some early microprocessors. It was primarily used for hobbyists to create simple video games, demonstrations, and even to be used to implement graph calculators. CHIP-8 programs had a simple instruction set whose focus was specifically around input, graphics, and audio.

A CHIP-8 emulator is a software that mimics the behavior of the original virtual machine on modern platforms. This small project is my exercise towards that attempt. Currently, all features from the original CHIP-8 instruction set are implemented as well as input-detection and a display written over the HTML [Canvas API](https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API). I decided not to implement the monotone audio feature associated with CHIP-8 not to distract web users, who typically wouldn't prefer sound playing from websites.

I also included a few preloaded ROMs that users can access to play some of the original CHIP-8 games and demonstrations. This project overally served primarily to practice my programming skills with C++ and how it interfaces with the web via the [Emscripten](https://emscripten.org/) compiler toolchain.

## Install
If you want to use it on your local machine, start by cloning this repo:
```bash
git clone https://github.com/ThomasSpradling/chip-8-emulator.git
cd chip-8-emulator
```
If you don't already have [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) installed, do so now. Ensure the Emscripten either ends up as a PATH variable or at the root directory:
```
~/emscripten/emsdk/emsdk_env.sh
```

I added a Makefile to make C compilation easier. Now run it using:
```
make build
```

To compile the web resources, I used npm:
```
npm run build
```

To start the web server, simply use:
```
npm start
```
and go to [localhost:3000](http://localhost:3000/) to preview.

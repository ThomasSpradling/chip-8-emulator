build: clean source-emscripten make-dist build-emscripten

install:
	mkdir ~/emscripten; cd ~/emscripten; git clone https://github.com/emscripten-core/emsdk.git; cd emsdk; git pull; ./emsdk install latest; ./emsdk activate latest

clean:
	rm -rf web/dist

source-emscripten:
	export EMSDK_QUIET=1; source ~/emscripten/emsdk/emsdk_env.sh

make-dist:
	[ -d "web/dist" ] || mkdir "web/dist"

build-emscripten: src/main.cpp src/Emulator.cpp src/Chip8.cpp src/InputOutput/Keyboard.cpp src/InputOutput/Display.cpp src/InputOutput/Speaker.cpp roms
	em++ -O3 -s WASM=1 src/main.cpp src/Emulator.cpp src/Chip8.cpp src/InputOutput/Keyboard.cpp src/InputOutput/Display.cpp src/InputOutput/Speaker.cpp -o web/dist/emulator.out.js --bind --embed-file roms

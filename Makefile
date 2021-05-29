all: build

.PHONY: build
build:
	.\build.bat

run: build
	./build/debug/game.exe

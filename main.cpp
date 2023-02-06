#include <chrono>
#include <iostream>
#include "Chip8.hpp"
#include "Platform.hpp"

// Calls Cycle() function, handles user input and renders using SDL
// Three command line args:
    // Scale: need a scale factor to play on bigger monitor (video buffer is only 64x32 normally)
    // Delay: Use a delay to assess the ms time b/w cycles. can control to fit certain games
    // ROM: rom file
// Each iteration of while loop: parse input, run cycle if long enough time b/w cycles, update screen
int main(int argc, char** argv) {
    int VIDEO_HEIGHT = 16;
    int VIDEO_WIDTH = 32;

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
		std::exit(EXIT_FAILURE);
    }

    int videoScale = std::stoi(argv[1]);
	int cycleDelay = std::stoi(argv[2]);
	char const* romFilename = argv[3];    

    Platform platform("CHIP-8 Emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

    Chip8 chip8;
    chip8.LoadROM(romFilename);

    int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;
	auto lastCycleTime = std::chrono::high_resolution_clock::now();

	bool quit = false;
    while (!quit) {
		quit = platform.ProcessInput(chip8.keypad);

		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

		if (dt > cycleDelay)
		{
			lastCycleTime = currentTime;

			chip8.Cycle();

			platform.Update(chip8.video, videoPitch);
		}
	}

    return 0;
}
/*
*   NyanCat in C++
*/
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
namespace timerUtility {
	// Class that provides the all timer exception
	class timerException : exception {
	public:
		// Constructors
		timerException() : exception(), exception_msg("") {

		}
		timerException(const char* Exception_msg) : exception_msg(Exception_msg) {

		}
		// Overloading virutal functions
		const char* what() const noexcept {
			return exception_msg;
		}
	private:
		const char* exception_msg;
	};
	class timer {
	public:
		// Constructor of timer
		timer() : enabled(false), startCpuClock(-1), endCpuClock(-1) {
		}
		// Start timer.
		void start() {
			enabled = true;
			startCpuClock = clock();
		}
		// Stop timer.
		void stop() {
			endCpuClock = clock();
			enabled = false;
		}
		// Get duration
		float getDuration() const {
			if (enabled) {
				throw timerException("At <" "timer::getDuration" "> : This timer is running. Please ensure this timer was stop.");
			}
			else if (startCpuClock == -1) {
				throw timerException("At <" "timer::getDuration" "> : This timer is not start yet.");
			}
			float duration = (float)(endCpuClock - startCpuClock) / CLOCKS_PER_SEC;
			return duration * 1000;
		}
	private:
		clock_t startCpuClock;
		clock_t endCpuClock;
		bool enabled;
	};
}
class nyanCatDrawer {
public:
	nyanCatDrawer() {
		reset();
	}
	void updateFrame() {
		printf("\033[A\033[s");
		for (int i = 0; i < 64; i++) {
			for (int j = 0; j < 72; j++) {
				drawPixel(buffer[posMapping(j, i)]);
			}
			fputc('\n', stdout);
		}
		printf("\033[u");
	}
	void drawRect(int x, int y, int w, int h, char c) {
		for(int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				int pos = posMapping(j + x, i + y);
				if (pos >= 0) buffer[pos] = c;
			}
	}
	void drawSinglePixel(int x, int y, int c) {
		drawRect(x, y, 1, 1, c);
	}
	void drawStar(int x, int y, int ani) {
		if (ani == 0) {
			drawSinglePixel(x, y, 1);
		}
		else if (ani == 1) {
			drawSinglePixel(x, y - 1, 1);
			drawSinglePixel(x - 1, y, 1);
			drawSinglePixel(x + 1, y, 1);
			drawSinglePixel(x, y + 1, 1);
		}
		else if (ani == 2) {
			drawRect(x, y - 2, 1, 2, 1);
			drawRect(x - 2, y, 2, 1, 1);
			drawRect(x + 1, y, 2, 1, 1);
			drawRect(x, y + 1, 1, 2, 1);
		}
		else if (ani == 3) {
			drawRect(x , y - 3, 1, 2, 1);

			drawRect(x - 3, y, 2, 1, 1);
			drawRect(x    , y, 1, 1, 1);
			drawRect(x + 2, y, 2, 1, 1);

			drawRect(x    , y + 2, 1, 2, 1);
		}
		else if (ani == 4) {
			drawSinglePixel(x, y - 3, 1);

			drawSinglePixel(x - 2, y - 2, 1);
			drawSinglePixel(x + 2, y - 2, 1);

			drawSinglePixel(x - 3, y, 1);
			drawSinglePixel(x + 3, y, 1);

			drawSinglePixel(x - 2, y + 2, 1);
			drawSinglePixel(x + 2, y + 2, 1);

			drawSinglePixel(x , y + 3, 1);
		}
		else if (ani == 5) {
			drawSinglePixel(x, y - 2, 1);
			drawSinglePixel(x - 3, y, 1);
			drawSinglePixel(x + 3, y, 1);
			drawSinglePixel(x , y + 2, 1);
		}
	}
	void drawRainbow(int x, int y, int ani) {
		const char colours[] = {4, 9, 10, 11, 12, 13};
		for (int i = 0; i < 4; i++) {
			int dx = x + -6 + i * 9;
			for (int j = 0; j < 6; j++) {
				int off = (i & 1) ^ ani;
				int dy = y + off + j * 3;
				drawRect(dx, dy, 9, 3, colours[j]);
			}
		}
		
	}
	void drawCatHead(int x, int y) {
		for (int i = 0; i < 3; i++) {
			drawRect(x + 2, y + 1 + i, 2 + i, 1, 2);
			drawRect(x + 12 - i, y + 1 + i, 2 + i, 1, 2);
			drawSinglePixel(x + 4 + i, y + 1 + i, 3);
			drawSinglePixel(x + 11 - i, y + 1 + i, 3);
		}
		drawRect(x + 1, y + 4, 14, 7, 2);
		drawRect(x + 2, y + 0, 2, 1, 3);
		drawRect(x + 12, y + 0, 2, 1, 3);
		drawRect(x + 1, y + 1, 1, 4, 3);
		drawRect(x + 14, y + 1, 1, 4, 3);
		drawRect(x + 7, y + 3 , 2, 1, 3);
		drawSinglePixel(x + 1, y + 10, 3);
		drawSinglePixel(x + 14, y + 10, 3);
		drawSinglePixel(x + 2, y + 11, 3);
		drawSinglePixel(x + 13, y + 11, 3);
		drawRect(x, y + 5, 1, 5, 3);
		drawRect(x + 15, y + 5, 1, 5, 3);
		drawRect(x + 3, y + 11, 10, 1, 2);
		// Draw Eyes
		drawRect(x + 4, y + 6, 2, 2, 3);
		drawRect(x + 4, y + 6, 1, 1, 1);
		drawRect(x + 11, y + 6, 2, 2, 3);
		drawRect(x + 11, y + 6, 1, 1, 1);
		// Draw Noise
		drawRect(x + 9, y + 7, 1, 1, 3);
		// Draw Mouth
		drawRect(x + 5, y + 9, 1, 1, 3);
		drawRect(x + 8, y + 9, 1, 1, 3);
		drawRect(x + 11, y + 9, 1, 1, 3);
		drawRect(x + 5, y + 10, 7, 1, 3);
		// Draw Blushes
		drawRect(x + 2, y + 8, 2, 2, 7);
		drawRect(x + 13, y + 8, 2, 2, 7);

		drawRect(x + 3, y + 12, 10, 1, 3);
	}
	void drawCatBody(int x, int y) {
		drawRect(x + 2, y, 17, 1, 3);
		drawRect(x + 1, y + 1, 19, 16, 6);
		drawRect(x + 1, y + 1, 1, 1, 3);
		drawRect(x + 19, y + 1, 1, 1, 3);
		drawRect(x, y + 2, 1, 14, 3);
		drawRect(x + 20, y + 2, 1, 14, 3);

		drawRect(x + 1, y + 16, 1, 1, 3);
		drawRect(x + 19, y + 16, 1, 1, 3);
		drawRect(x + 2, y + 17, 17, 1, 3);

		for (int i = 0; i < 2; i++) {
			drawRect(x + 4 - i, y + 2 + i, 13+(i<<1), 1, 5);
			drawRect(x + 4 - i, y + 15 - i, 13 + (i << 1), 1, 5);
		}
		drawRect(x + 2, y + 4, 17, 10, 5);

		// Draw Square Points
		drawSinglePixel(x + 9, y + 3, 8);
		drawSinglePixel(x + 12, y + 3, 8);
		drawSinglePixel(x + 4, y + 4, 8);
		drawSinglePixel(x + 16, y + 5, 8);
		drawSinglePixel(x + 7, y + 7, 8);
		drawSinglePixel(x + 5, y + 9, 8);
		drawSinglePixel(x + 9, y + 10, 8);
		drawSinglePixel(x + 3, y + 11, 8);
		drawSinglePixel(x + 7, y + 13, 8);
		drawSinglePixel(x + 4, y + 14, 8);


	}
	void drawCatTail(int x, int y, int ani) {
		if (ani == 0) {
			// Draw Borders
			drawRect(x - 5, y - 6, 4, 1, 3);
			drawRect(x - 5, y - 5, 5, 1, 3);
			drawRect(x - 5, y - 4, 6, 1, 3);
			drawRect(x - 4, y - 3, 5, 1, 3);
			drawRect(x - 3, y - 2, 4, 1, 3);
			drawRect(x - 2, y - 1, 3, 1, 3);
			drawRect(x, y, 1, 1, 3);
			// Draw Fills
			drawRect(x - 4, y - 5, 2, 1, 2);
			drawRect(x - 3, y - 4, 2, 1, 2);
			drawRect(x - 2, y - 3, 2, 1, 2);
			drawRect(x - 1, y - 2, 2, 1, 2);
		}
		else if (ani == 1 || ani == 5) {
			// Draw Borders
			drawRect(x - 4, y - 5, 2, 1, 3);
			drawRect(x - 5, y - 4, 4, 1, 3);
			drawRect(x - 5, y - 3, 6, 1, 3);
			drawRect(x - 4, y - 2, 5, 1, 3);
			drawRect(x - 3, y - 1, 4, 1, 3);
			drawRect(x - 1, y, 2, 1, 3);
			// Draw Fills
			drawRect(x - 4, y - 4, 2, 1, 2);
			drawRect(x - 4, y - 3, 2, 1, 2);
			drawRect(x - 3, y - 2, 4, 1, 2);
			drawRect(x - 1, y - 1, 2, 1, 2);
		}
		else if (ani == 2) {
			// Draw Borders
			drawRect(x, y - 3, 1, 1, 3);
			drawRect(x - 3, y - 2, 4, 1, 3);
			drawRect(x - 5, y - 1, 6, 1, 3);
			drawRect(x - 5, y, 6, 1, 3);
			drawRect(x - 4, y + 1, 4, 1, 3);
			// Draw Fills
			drawRect(x - 3, y - 1, 4, 1, 2);
			drawRect(x - 4, y, 3, 1, 2);
		}
		else if (ani == 3) {
			// Draw Borders
			drawRect(x - 1, y - 3, 2, 1, 3);
			drawRect(x - 3, y - 2, 4, 1, 3);
			drawRect(x - 4, y - 1, 5, 1, 3);
			drawRect(x - 5, y, 6, 1, 3);
			drawRect(x - 5, y + 1, 4, 1, 3);
			drawRect(x - 4, y + 2, 2, 1, 3);
			// Draw Fills
			drawRect(x - 1, y - 2, 2, 1, 2);
			drawRect(x - 3, y - 1, 4, 1, 2);
			drawRect(x - 4, y, 2, 1, 2);
			drawRect(x - 4, y + 1, 2, 1, 2);
		}
		else if (ani == 4) {
			// Draw Borders
			drawRect(x - 5, y - 5, 4, 1, 3);
			drawRect(x - 6, y - 4, 7, 1, 3);
			drawRect(x - 6, y - 3, 7, 1, 3);
			drawRect(x - 4, y - 2, 5, 1, 3);
			drawRect(x - 1, y - 1, 2, 1, 3);
			// Draw Fills
			drawRect(x - 5, y - 4, 3, 1, 2);
			drawRect(x - 4, y - 3, 4, 1, 2);
			drawRect(x , y - 2, 1, 1, 2);
		}
	}
	void drawCatFoot1(int x, int y, int ani) {
		if (ani == 0) {
			// Draw Borders
			drawRect(x - 2, y - 1, 3, 1, 3);
			drawRect(x - 3, y, 5, 1, 3);
			drawRect(x - 3, y + 1, 5, 1, 3);
			drawRect(x - 3, y + 2, 4, 1, 3);
			// Draw Fills
			drawRect(x - 2, y, 3, 1, 2);
			drawRect(x - 2, y + 1, 2, 1, 2);
		}
		else if (ani == 1 || ani == 3) {
			// Draw Borders
			drawRect(x - 1, y - 1, 2, 1, 3);
			drawRect(x - 2, y, 4, 1, 3);
			drawRect(x - 2, y + 1, 4, 1, 3);
			drawRect(x - 2, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x - 1, y, 2, 2, 2);
		}
		else if (ani == 2) {
			// Draw Borders
			drawRect(x - 1, y - 1, 2, 1, 3);
			drawRect(x - 1, y, 3, 1, 3);
			drawRect(x - 1, y + 1, 4, 1, 3);
			drawRect(x - 1, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x, y, 1, 1, 2);
			drawRect(x, y + 1, 2, 1, 2);
		}
		else if (ani == 4) {
			// Draw Borders
			drawRect(x - 2, y - 2, 2, 1, 3);
			drawRect(x - 3, y - 1, 4, 1, 3);
			drawRect(x - 4, y, 5, 1, 3);
			drawRect(x - 4, y + 1, 4, 1, 3);
			drawRect(x - 4, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x - 3, y, 3, 1, 2);
			drawRect(x - 3, y + 1, 2, 1, 2);
		}
		else if (ani == 5) {
			// Draw Borders
			drawRect(x - 2, y - 2, 2, 1, 3);
			drawRect(x - 3, y - 1, 4, 1, 3);
			drawRect(x - 4, y, 5, 1, 3);
			drawRect(x - 4, y + 1, 4, 1, 3);
			drawRect(x - 4, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x - 2, y - 1, 1, 1, 2);
			drawRect(x - 3, y, 3, 1, 2);
			drawRect(x - 3, y + 1, 2, 1, 2);
		}
	}
	void drawCatFoot2(int x, int y, int ani) {
		if (ani == 0) {
			// Draw Borders
			drawRect(x, y + 1, 4, 1, 3);
			drawRect(x, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x + 1, y + 1, 2, 1, 2);
		}
		else if (ani == 1 || ani == 3) {
			// Draw Borders
			drawRect(x, y + 1, 4, 1, 3);
			drawRect(x + 1, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x + 1, y + 1, 2, 1, 2);
		}
		else if (ani == 2) {
			// Draw Borders
			drawRect(x + 1, y + 1, 4, 1, 3);
			drawRect(x + 2, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x + 2, y + 1, 2, 1, 2);
		}
		else if (ani == 4) {
			// Draw Borders
			drawRect(x - 2, y + 1, 4, 1, 3);
			drawRect(x - 1, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x - 1, y + 1, 2, 1, 2);
		}
		else if (ani == 5) {
			// Draw Borders
			drawRect(x - 2, y + 1, 4, 1, 3);
			drawRect(x - 2, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x - 1, y + 1, 2, 1, 2);
		}
	}
	void drawCatFoot3(int x, int y, int ani) {
		if (ani == 0 || ani == 4) {
			// Draw Borders
			drawRect(x, y + 1, 4, 1, 3);
			drawRect(x + 1, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x + 1, y + 1, 2, 1, 2);
		}
		else if (ani == 1 || ani == 3) {
			// Draw Borders
			drawRect(x + 1, y + 1, 4, 1, 3);
			drawRect(x + 2, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x + 2, y + 1, 2, 1, 2);
		}
		else if (ani == 2) {
			// Draw Borders
			drawRect(x + 2, y + 1, 4, 1, 3);
			drawRect(x + 3, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x + 3, y + 1, 2, 1, 2);
		}
		else if (ani == 5) {
			// Draw Borders
			drawRect(x, y + 1, 4, 1, 3);
			drawRect(x, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x + 1, y + 1, 2, 1, 2);
		}
	}
	void drawCatFoot4(int x, int y, int ani) {
		if (ani == 0) {
			// Draw Borders
			drawRect(x, y, 4, 1, 3);
			drawRect(x, y + 1, 4, 1, 3);
			drawRect(x + 1, y + 2, 2, 1, 3);
			// Draw Fills
			drawRect(x + 2, y , 1, 1, 2);
			drawRect(x + 1, y + 1, 2, 1, 2);
		}
		else if (ani == 1 || ani == 3) {
			// Draw Borders
			drawRect(x + 1, y, 4, 1, 3);
			drawRect(x + 1, y + 1, 4, 1, 3);
			drawRect(x + 2, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x + 3, y, 1, 1, 2);
			drawRect(x + 2, y + 1, 2, 1, 2);
		}
		else if (ani == 2) {
			// Draw Borders
			drawRect(x + 2, y, 4, 1, 3);
			drawRect(x + 2, y + 1, 4, 1, 3);
			drawRect(x + 3, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x + 4, y, 1, 1, 2);
			drawRect(x + 3, y + 1, 2, 1, 2);
		}
		else if (ani == 4 || ani == 5) {
			// Draw Borders
			drawRect(x, y, 4, 1, 3);
			drawRect(x, y + 1, 4, 1, 3);
			drawRect(x + 1, y + 2, 3, 1, 3);
			// Draw Fills
			drawRect(x + 2, y, 1, 1, 2);
			drawRect(x + 1, y + 1, 2, 1, 2);
		}
	}
	void drawCat(int x, int y, int ani) {
		int headOffx = 0, headOffy = 0;
		int allOffy = 0;
		if (ani == 1) {
			headOffx = 1;
		}
		else if (ani == 2 || ani == 3) {
			headOffx = 1;
			allOffy = 1;
		}
		else if (ani == 4) {
			allOffy = 1;
		}
		else if (ani == 5) {
			headOffy = -1;
			allOffy = 1;
		}
		drawCatFoot1(x + 2, allOffy + y + 17, ani);
		drawCatFoot2(x + 5, allOffy + y + 17, ani);
		drawCatFoot3(x + 14, allOffy + y + 17, ani);
		drawCatFoot4(x + 19, allOffy + y + 17, ani);
		drawCatBody(x + 1, allOffy + y);
		drawCatHead(headOffx + x + 11, headOffy + allOffy + y + 5);
		drawCatTail(x, allOffy + y + 13, ani);
	}
	void drawNyanCat(int ani) {
		const int star1Poses[] = { 43, 37, 29, 20, 10, 4, 0, 78, 70, 62, 54, 47 };
		reset();
		drawRainbow(0, 24, ((ani >> 1) & 1)^1);
		drawStar(star1Poses[ani % 12], 1, (ani + 1) % 6); // 43 37 29 20 10 4 0 78 | 70 62 54 47
		drawStar(star1Poses[(ani + 8) % 12], 9, (ani + 9) % 6);
		drawStar(star1Poses[(ani + 6) % 12], 20, (ani + 7) % 6);
		drawStar(star1Poses[(ani + 4) % 12], 40, (ani + 5) % 6);
		drawStar(star1Poses[(ani + 8) % 12], 51, (11 - ani) % 6);
		drawStar(star1Poses[(ani + 1) % 12], 60, (ani + 2) % 6);
		drawCat(28, 23, ani % 6);
	}
	void reset() {
		for (int i = 0; i < 4608; i++)
			buffer[i] = 0;
	}
private:
	char buffer[4608];

	int posMapping(int x, int y) {
		if (x < 0 || x >= 72 || y < 0 || y >= 64) return -1;
		else return y * 72 + x;
	}
	void drawPixel(char c) {
		char flTx[] = "  ";
		switch (c) {
			case  0: printf("\033[48;2;16;64;128m%s\033[0m", flTx); break;

			case  1: printf("\033[48;2;255;255;255m%s\033[0m", flTx); break;
			case  2: printf("\033[48;2;170;170;170m%s\033[0m", flTx); break;
			case  3: printf("\033[48;2;0;0;0m%s\033[0m", flTx); break;

			case  4: printf("\033[48;2;255;16;16m%s\033[0m", flTx); break;

			case  5: printf("\033[48;2;255;164;255m%s\033[0m", flTx); break;
			case  6: printf("\033[48;2;255;211;161m%s\033[0m", flTx); break;
			case  7: printf("\033[48;2;255;170;170m%s\033[0m", flTx); break;
			case  8: printf("\033[48;2;255;64;170m%s\033[0m", flTx); break;

			case  9: printf("\033[48;2;255;170;16m%s\033[0m", flTx); break;

			case 10: printf("\033[48;2;255;255;8m%s\033[0m", flTx); break;

			case 11: printf("\033[48;2;64;255;16m%s\033[0m", flTx); break;

			case 12: printf("\033[48;2;16;170;255m%s\033[0m", flTx); break;

			case 13: printf("\033[48;2;120;70;255m%s\033[0m", flTx); break;
		}
	}
};
int main() {
	using namespace std::this_thread;
	using namespace std::chrono;
	using namespace timerUtility;
	printf("\033[1;1H\033[1K");
	printf("\033[2J\033[3J");
	for (int i = 0; i < 64; i++)
		printf("|-------------------------------------------------------------Animation Playing Area-------------------------------------------------------------|\n");
	printf("Press enter to play.");
	// set buffer of stdout to improve the performance.
	char stdoutBuf[3000];
	setvbuf(stdout, stdoutBuf, _IOFBF, sizeof(stdoutBuf));
	fgetc(stdin);
	printf("\033[1;1H\033[1K");
	printf("\033[2J\033[3J");
	nyanCatDrawer drawer;
	timer frameTimer;
	for (int i = 0; ; i++) {
		frameTimer.start();
		drawer.reset();
		drawer.drawNyanCat(i);
		drawer.updateFrame();
		//fgetc(stdin);
		fflush(stdout);
		frameTimer.stop();
		double waitingTime = (66.666 - frameTimer.getDuration()) * 1000;
		sleep_for(microseconds((int)waitingTime));
	}
	setvbuf(stdout, NULL, _IONBF, 0);
}
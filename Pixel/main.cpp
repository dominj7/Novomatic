#include <iostream>
#include <chrono>
#include <cmath>
#include <array>
#if _WIN32
#include <windows.h>
#endif


using namespace std;


class Screen
{
public:
    Screen()
    {
#ifdef _WIN32
        _hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
#endif
        hideCursor();
        saveCursorPosition();
    }


    void clear()
    {
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                _screen[i][j]='x';
            }
        }
    }


    void draw(char value, float x, float y)
    {
        int xPos = lround(x);
        int yPos = lround(y);
        if(xPos < width && yPos < height)
        {
            _screen[yPos][xPos]=value;
        }
    }


    void flush()
    {
        restoreCursorPosition();


        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                if(_screen[i][j]!='x')
                {
                    setRedFont();
                }
                else
                {
                    setWhiteFont();
                }
                cout << _screen[i][j];
            }
            cout << "\n";
        }
    }


private:
    void hideCursor()
    {
#ifdef _WIN32
        CONSOLE_CURSOR_INFO cursorInfo; 
                GetConsoleCursorInfo(_hConsole, &cursorInfo);
                cursorInfo.dwSize = 1;
                cursorInfo.bVisible = FALSE;
                SetConsoleCursorInfo(_hConsole, &cursorInfo);
#else
        cout << "\33[?25l";//disable cursor
#endif


    }


    void saveCursorPosition()
    {
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO coninfo;
                GetConsoleScreenBufferInfo(_hConsole, &coninfo);
                _prevPos = coninfo.dwCursorPosition;
#else
        cout << "\33[s";
#endif

    }


    void restoreCursorPosition()
    {
#ifdef _WIN32
        SetConsoleCursorPosition(_hConsole, _prevPos);
#else
        cout << "\338";
#endif
    }


    void setRedFont()
    {
#ifdef _WIN32
        WORD attributes = FOREGROUND_RED;
                SetConsoleTextAttribute(_hConsole, attributes);
#else
        cout << "\33[31m";//red color
#endif
    }


    void setWhiteFont()
    {
#ifdef _WIN32
        WORD attributes = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;
                SetConsoleTextAttribute(_hConsole, attributes);
#else
        cout << "\33[37m";//white color
#endif
    }


    static constexpr int width{60};
    static constexpr int height{20};
    char _screen[height][width];
#ifdef _WIN32
    HANDLE _hConsole;
        COORD _prevPos;
#endif
};


struct Position
{
    float x;
    float y;

	bool operator==(Position p) {
		float epsilon{0.001f};

		return fabs(x - p.x) < epsilon and fabs(y - p.y) < epsilon;
	}
};


using Pixel = char;


class Path {
private:
	const float xDisplacement, yDisplacement;
    Position endPoint;
    Position *pixel;

public:
	Path(Position startP, Position endP, float _milliseconds, Position *pixel) :
		xDisplacement((endP.x - startP.x) / _milliseconds), yDisplacement((endP.y - startP.y) / _milliseconds),
		endPoint(endP) {

		this->pixel = pixel;
	}


	void movePixel(float deltaTime) {
		pixel->x += xDisplacement * deltaTime;
		pixel->y += yDisplacement * deltaTime;
	}


	bool arrived() {
		bool equal{endPoint == *pixel};
		if (equal) {
			pixel->x = endPoint.x;
			pixel->y = endPoint.y;
		}

		return equal;
	}


	bool tooFar() {
		float epsilon{0.001f};

		bool xTooFar{false}, yTooFar{false};

		if (xDisplacement > 0)
			xTooFar = pixel->x - endPoint.x > epsilon;
		else if (xDisplacement < 0)
			xTooFar = pixel->x - endPoint.x < epsilon;

		if (yDisplacement > 0)
			yTooFar = pixel->y - endPoint.y > epsilon;
		else if (yDisplacement < 0)
			yTooFar = pixel->y - endPoint.y < epsilon;


		return xTooFar or yTooFar;
	}

};


class Engine {
	size_t counter;
	array<Path, 3> *paths;
    array<Path, 3>::iterator itr;

public:
	Engine() {
		counter = 0;

		Position A{0.0f, 0.0f}, B{40.0f, 0.0f}, C{40.0f, 10.0f};
        Path AB{A, B, 2000.0f, &position}, BC{B, C, 3000.0f, &position},
            CA{C, A, 1000.0f, &position};
        paths = new array<Path, 3>({AB, BC, CA});

        itr = paths->begin();
	}

    void update(chrono::milliseconds deltaTime) {
		if (counter == 5) {
			delete paths;
			exit(EXIT_SUCCESS);
		}

		itr->movePixel(static_cast<float>(deltaTime.count()));
		if (itr->arrived())
			itr++;

		if (itr == paths->end()) {
			counter++;
			itr = paths->begin();
		}

		if (itr->tooFar()) {
			delete paths;
			exit(EXIT_FAILURE);
		}
    }


    void render(Screen& screen)
    {
        screen.draw(pixel, position.x, position.y);
    }
private:
    Pixel pixel{42};
    Position position{0.0f, 0.0f};
};


int main()
{
    Engine engine;
    Screen screen;


    auto startTime = chrono::high_resolution_clock::now();
    while(1)
    {
        auto now = chrono::high_resolution_clock::now();
        auto deltaTime = chrono::duration_cast<chrono::milliseconds>(now - startTime);
        if( deltaTime >=20ms)
        {
            screen.clear();
            engine.update(deltaTime);
            engine.render(screen);
            screen.flush();
            startTime = now;
        }
    }


    return 0;
}
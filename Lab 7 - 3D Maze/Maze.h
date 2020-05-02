#ifndef MAZE_H
#define MAZE_H

#include "MazeInterface.h" 
#include <string>
#include <sstream>
using namespace std;

enum { OPEN, BLOCKED, PATH, EXIT, TEMPORARY };

class Maze : public MazeInterface {
private:
	int mazeHeight;
	int mazeWidth;
	int mazeLayer;
	int*** maze;
public:
	Maze(void) {}
	Maze(int height, int width, int layer) : mazeHeight(height), mazeWidth(width), mazeLayer(layer) {
		maze = new int** [mazeHeight];					// dynamically allocate 3D array
		for (int i = 0; i < mazeHeight; i++) {
			maze[i] = new int* [mazeWidth];

			for (int j = 0; j < mazeWidth; j++) {
				maze[i][j] = new int[mazeLayer];
			}
		}
	}
	~Maze(void) {
		for (int i = 0; i < mazeHeight; ++i) {			// deallocate memory
			for (int j = 0; j < mazeWidth; ++j) {
				delete[] maze[i][j];
			}
			delete[] maze[i];
		}
		delete[] maze;
	}

	void setValue(int height, int width, int layer, int value) { maze[height][width][layer] = value; }

	bool find_maze_path() { return find_maze_path(0, 0, 0); }

	bool find_maze_path(int height, int width, int layer);

	string toString() const;
};
#endif

bool Maze::find_maze_path(int height, int width, int layer) {
	// check boundary
	if ((height < 0) || (height >= mazeHeight) || (width < 0) || (width >= mazeWidth) || (layer < 0) || (layer >= mazeLayer)) return false;
	// check if blocked
	if (maze[height][width][layer] != OPEN) {
		return false;
	}
	// if successful
	if ((height == mazeHeight - 1) && (width == mazeWidth - 1) && (layer == mazeLayer - 1)) {
		maze[height][width][layer] = EXIT;		// successful
		return true;
	}
	// recursive case
	maze[height][width][layer] = PATH;
	if (find_maze_path(height, width - 1, layer)) {
		maze[height][width][layer] = 'L';
		return true;
	}
	if (find_maze_path(height, width + 1, layer)) {
		maze[height][width][layer] = 'R';
		return true;
	}
	if (find_maze_path(height - 1, width, layer)) {
		maze[height][width][layer] = 'U';
		return true;
	}
	if (find_maze_path(height + 1, width, layer)) {
		maze[height][width][layer] = 'D';
		return true;
	}
	if (find_maze_path(height, width, layer - 1)) {
		maze[height][width][layer] = 'O';
		return true;
	}
	if (find_maze_path(height, width, layer + 1)) {
		maze[height][width][layer] = 'I';
		return true;
	}
	maze[height][width][layer] = TEMPORARY;
	return false;
}

string Maze::toString() const {
	stringstream ss;
	for (int i = 0; i < mazeLayer; i++) {
		ss << "Layer " << i + 1 << endl;
		for (int j = 0; j < mazeHeight; j++) {
			for (int k = 0; k < mazeWidth; k++) {
				if (maze[j][k][i] == OPEN || maze[j][k][i] == TEMPORARY) { ss << "_ "; }
				else if (maze[j][k][i] == BLOCKED) { ss << "X "; }
				else if (maze[j][k][i] == 'L') { ss << "L "; }
				else if (maze[j][k][i] == 'R') { ss << "R "; }
				else if (maze[j][k][i] == 'D') { ss << "D "; }
				else if (maze[j][k][i] == 'U') { ss << "U "; }
				else if (maze[j][k][i] == 'I') { ss << "I "; }
				else if (maze[j][k][i] == 'O') { ss << "O "; }
				else if (maze[j][k][i] == EXIT) { ss << "E "; }
			}
			ss << endl;
		}
	}
	ss << endl;
	return ss.str();
}
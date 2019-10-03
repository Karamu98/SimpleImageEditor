#include "Editor.h"

int main()
{	
	Editor* newGame = new Editor();
	newGame->Run("Caramel Engine", 1280, 720, false);

	delete newGame;

	return 0;
}

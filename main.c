#include "function.h"

int main() {

	initiallize();
	

	while (1) {		
		
//		if (isGameOver()) break;		moveChar���� ����
		processKeyInput();
		while (1) {
			
			if (gravity() == 1) {
				break;
			}						
		}

	}
	

	getchar();
	return 0;
}
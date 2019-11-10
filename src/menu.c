#include "menu.h"


int menu (char *tableProg[], int sizeTable) {

	int programmeIndex = -1;
	int index;
	int tempValue;

	while (programmeIndex == -1) {
		printf("Quel programme voulez-vous exécuter:\n");
		for (index = 0; index < sizeTable; index++) {
			printf("\t%d. %s.\n", index + 1, tableProg[index]);
		}
		printf("number : ");
		scanf("%d", &tempValue);
		printf("\n");
		resetBuffer();
		programmeIndex = tempValue > 0 && tempValue <= sizeTable ? tempValue : -1;
	}
	return programmeIndex;
}
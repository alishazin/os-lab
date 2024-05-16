#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 10;
int x = 0;

void producer() {

	mutex--;

	empty--;
	full++;
	x++;
	printf("Producer produces item %d\n", x);

	mutex++;

}

void consumer() {

	mutex--;

	empty++;
	full--;
	printf("Consumer consumes item %d\n", x);
	x--;

	mutex++;

}

int main() {

	int choice;

	printf("Choices:\n1. Consumer\n2. Producer\n3. Exit\n");

	while (1) {
	
		printf("Enter your choice: ");
		scanf("%d", &choice);

		if (choice == 1) {
			if (mutex == 1 && full != 0) consumer();
			else printf("Buffer is empty!\n");
		} else if (choice == 2) {
			if (mutex == 1 && empty != 0) producer();
			else printf("Buffer is full!\n");
		} else if (choice == 3) {
			printf("Exiting..\n");
			break;
		}
		else printf("Invalid choice!\n");

	}

	return 0;
}

#include <stdio.h>

/**
 * main - Prints the alphabets
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char alpha[26] = "abcdefghijklmnopqrstuvwxyz";
	int x;

	for (x = 0; x <= 25; x++)
	{
		putchar(alpha[x]);
		putchar('\n');
	}
	putchar('\n');
	return (0);
}

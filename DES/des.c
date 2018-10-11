#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char reverse(char b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

char getSpecificBitsFromByte(int bitDesired, char byte)
{
	return (byte & (0x80 >> bitDesired));
}

void printBinaryValue(char byte)
{
	for (int j = 0; j < 8; j++)
	{
		printf("%d", !!((byte << j) & 0x80));
	}
}

char *createTable(char plainText[8])
{

	for (int i = 0; i < 8; i++)
	{
		printf("original\n");
		printBinaryValue(plainText[i]);

		plainText[i] = reverse(plainText[i]);

		printf("\nreversed\n");
		printBinaryValue(plainText[i]);

		printf("\nfirst bit\n");
		printBinaryValue(getSpecificBitsFromByte(1, plainText[i]));

		printf("\n\n\n");
	}

	return plainText;
}

int main()
{

	char plainText[8], output[9];
	plainText[0] = 'A';
	plainText[1] = 'B';
	plainText[2] = 'C';
	plainText[3] = 'D';
	plainText[4] = 'E';
	plainText[5] = 'F';
	plainText[6] = 'G';
	plainText[7] = 'H';

	createTable(plainText);

	//Leitura da entrada

	//Monta tabela de entrada

	//Divide bloco em dois

	//Expande segunda metade para 48 bits

	//Tratar chave

	//XOR com o bloco de 48 bits

	//Montar tabelas Ss

	//Subistitution choice (usar as tabelas S para montar a saida com 32 bits)

	//Swap
	//?

	//Inverse initial permutation
	//?

	//Printar apos cada round

	return 1;
}
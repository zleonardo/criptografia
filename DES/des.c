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
	printf("\n");
}

char createAndReverseByte(char bytes[], int position)
{
	char byte = 0x00;
	int place = 8 - position;
	for (int i = 0; i < 8; i++)
	{
		char aux = (((getSpecificBitsFromByte(position, bytes[i])) >> place - i) | (getSpecificBitsFromByte(position, bytes[i])) << (position-i));
		printf("\naux: %d ", (place));
		printBinaryValue(aux);

		byte += aux;
		printf("\n\nbyte: ");
		printBinaryValue(getSpecificBitsFromByte(position, bytes[i]));
	}

	printf("\n\nbytes: ");
	printBinaryValue(byte);

	return reverse(byte);
}

char *createTable(char plainText[8])
{
	char *table = malloc(sizeof(char) * 8);
	char temp;

	plainText[4] = plainText[0];

	int odd = 0;
	int even = 4;

	for (int i = 0; i < 8; i++)
	{
		if (i % 2 == 0)
		{
			table[even] = createAndReverseByte(plainText, i);
			even++;
		}
		else
		{
			table[odd] = createAndReverseByte(plainText, i);
			odd++;
		}
	}

	return table;
}

int main()
{

	char plainText[8], output[9];
	plainText[0] = 0x67;
	plainText[1] = 0x5a;
	plainText[2] = 0x69;
	plainText[3] = 0x67;
	plainText[4] = 0x5e;
	plainText[5] = 0x5a;
	plainText[6] = 0x6b;
	plainText[7] = 0x5a;

	for (int i = 0; i < 8; i++)
	{
		printBinaryValue(plainText[i]);
	}

	printf("\n\n");
	char response[8];
	memcpy(response, createTable(plainText), 8);

	for (int i = 0; i < 8; i++)
	{
		printBinaryValue(response[i]);
	}

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
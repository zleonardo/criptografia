#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int expansionTable[48] = {
    32,  1,  2,  3,  4,  5,  
    4,  5,  6,  7,  8,  9,  
    8,  9, 10, 11, 12, 13, 
    12, 13, 14, 15, 16, 17, 
    16, 17, 18, 19, 20, 21, 
    20, 21, 22, 23, 24, 25, 
    24, 25, 26, 27, 28, 29, 
    28, 29, 30, 31, 32,  1};


unsigned char reverse(unsigned char b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

void printBinaryValue(unsigned char byte)
{
	for (int j = 0; j < 8; j++)
	{
		printf("%d", !!((byte << j) & 0x80));
	}
	printf("\n");
}

unsigned char* leftSide(unsigned char table[]) {
	unsigned char *leftSide = malloc(sizeof(unsigned char) * 4);

	leftSide[0] = table[0];
	leftSide[1] = table[1];
	leftSide[2] = table[2];
	leftSide[3] = table[3];

	return leftSide;
}

unsigned char* rightSide(unsigned char table[]) {
	unsigned char *rightSide = malloc(sizeof(unsigned char) * 4);

	rightSide[0] = table[4];
	rightSide[1] = table[5];
	rightSide[2] = table[6];
	rightSide[3] = table[7];

	return rightSide;
}

unsigned char getSpecificBitsFromByte(int bitDesired, unsigned char byte)
{
	return (byte & (0x80 >> bitDesired));
}


unsigned char getAndMoveByte(int initialPosition, int targetPosition, unsigned char byte)
{
	return (((getSpecificBitsFromByte(initialPosition, byte)) >> targetPosition - initialPosition) | (getSpecificBitsFromByte(initialPosition, byte)) << (initialPosition - targetPosition));
}

unsigned char createAndReverseByte(unsigned char bytes[], int position)
{
	unsigned char byte = 0x00;
	int place = 8 - position;
	for (int i = 0; i < 8; i++)
	{
		unsigned char aux = (((getSpecificBitsFromByte(position, bytes[i])) >> i - position) | (getSpecificBitsFromByte(position, bytes[i])) << (position-i));

		byte |= aux;
	}

	return reverse(byte);
}

unsigned char *expansionPermutation(unsigned char table[4]) {

	unsigned char *expandedTable = malloc(sizeof(unsigned char)*6);

	int byteExpanded = 0;
	int i = 0;
	unsigned char byteBuilded = 0x00;
	int bytePosition = 0;

	while(i < 48) {
		int index = expansionTable[i] - 1;
			
		int byte = index/8;
		int bit = index%8;

		byteBuilded |= getAndMoveByte(bit, i%8, table[byte]);		

		bytePosition++;

		if(bytePosition == 8) {
			expandedTable[byteExpanded] = byteBuilded;
			byteBuilded = 0x00;
			byteExpanded++;
			bytePosition = 0;
		}
		i++;
		
	}

	return expandedTable;
}

unsigned char *createTable(unsigned char plainText[8])
{
	unsigned char *table = malloc(sizeof(unsigned char) * 8);
	unsigned char temp;

	int odd = 0;
	int even = 4;

	printf("\nplainText: \n");

	for (int i = 0; i < 8; i++)
	{
		printBinaryValue(plainText[i]);
	}
	
	printf("\n\n");

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

void addKey(char bytes[6], char key[6]) {
	bytes[0] ^= key[0];
	bytes[1] ^= key[1];
	bytes[2] ^= key[2];
	bytes[3] ^= key[3];
	bytes[4] ^= key[4];
	bytes[5] ^= key[5];
}

int main()
{

	unsigned char plainText[8], output[9], key[6];
	plainText[0] = 0x69;
	plainText[1] = 0x6e;
	plainText[2] = 0x74;
	plainText[3] = 0x72;
	plainText[4] = 0x6f;
	plainText[5] = 0x64;
	plainText[6] = 0x75;
	plainText[7] = 0x63;

	key[0] = 0x50;
	key[1] = 0x2c;
	key[2] = 0xac;
	key[3] = 0x57;
	key[4] = 0x2a;
	key[5] = 0xc2;


	printf("\n\nplaintext");
	for(int i = 0; i < 8; i++) {
		printf("\n%02x", plainText[i]);
	}
	printf("\n\n");

	//Leitura da entrada

	//Monta tabela de entrada
	unsigned char *initialTable;

	initialTable = createTable(plainText);

	printf("\n\ninitial\n");
	for(int i = 0; i < 8; i++) {
		printf("%02x\n", initialTable[i]);
	}
	printf("\n\n");

	//Divide bloco em dois
	leftSide(initialTable);
	rightSide(initialTable);

	//Expande segunda metade para 48 bits

	unsigned char *expandedTable;

	expandedTable = expansionPermutation(rightSide(initialTable));

	printf("\n\nexpanded");
	for(int i = 0; i < 6; i++) {
		printf("\n%02x", expandedTable[i]);
	}
	printf("\n\n");

	//Tratar chave

	//XOR com o bloco de 48 bits
	addKey(expandedTable, key);

	printf("\n\nadded");
	for(int i = 0; i < 6; i++) {
		printf("\n%02x", expandedTable[i]);
	}
	printf("\n\n");

	//Montar tabelas Ss

	//Subistitution choice (usar as tabelas S para montar a saida com 32 bits)

	//Swap
	//?

	//Inverse initial permutation
	//?

	//Printar apos cada round

	return 1;
}
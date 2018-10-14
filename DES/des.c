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
    28, 29, 30, 31, 32,  1
}; 

static char S[8][64] = {{
    /* S1 */
    14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,  
     0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,  
     4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0, 
    15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
},{
    /* S2 */
    15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,  
     3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,  
     0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15, 
    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
},{
    /* S3 */
    10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,  
    13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,  
    13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
     1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
},{
    /* S4 */
     7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,  
    13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,  
    10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
     3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
},{
    /* S5 */
     2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9, 
    14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6, 
     4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14, 
    11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
},{
    /* S6 */
    12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
    10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
     9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
     4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
},{
    /* S7 */
     4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
    13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
     1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
     6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
},{
    /* S8 */
    13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
     1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
     7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
     2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
}};


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

unsigned char *createSBox(unsigned char bytes[6]) {
	unsigned char *sboxTable = malloc(sizeof(unsigned char)*8);
	unsigned char aux = 0x00;

	aux = bytes[0];
	sboxTable[0] = aux >> 2;

	aux = bytes[1];
	sboxTable[1] = ((bytes[0] << 4) & 0x30) | (aux >> 4);
	
	aux = bytes[2];
	sboxTable[2] = ((bytes[1] & 0x0f) << 2) | ((aux & 0xC0) >> 6);

	sboxTable[3] = bytes[2] & 0x3f;

	aux = bytes[3];
	sboxTable[4] =  (aux >> 2);

	aux = bytes[4];
	sboxTable[5] = ((bytes[3] << 4) & 0x30) | (aux >> 4);

	aux = bytes[5];
	sboxTable[6] = ((bytes[4] & 0x0f) << 2) | ((aux & 0xC0) >> 6);

	sboxTable[7] = bytes[5] & 0x3f;

	return sboxTable;

}

unsigned char *substitutionChoice(unsigned char bytes[6]) {

	unsigned char *sboxTable = malloc(sizeof(unsigned char)*4);

	char byteCreated;

	printf("\nbytes sbox\n");
	for(int i = 0; i < 6; i++) {
		printBinaryValue(bytes[i]);
	}

	unsigned char *sboxCreated = malloc(sizeof(unsigned char)*8);

	sboxCreated = createSBox(bytes);

	printf("\nbytes sbox\n");
	for(int i = 0; i < 8; i++) {
		printBinaryValue(sboxCreated[i]);
	}


	for(int i = 0; i < 8; i++) {

		int row = (getAndMoveByte(2, 6, sboxCreated[i]) | getAndMoveByte(7, 7, sboxCreated[i]));

		int column = (getAndMoveByte(3, 4, sboxCreated[i]) | getAndMoveByte(4, 5, sboxCreated[i])
					| getAndMoveByte(5, 6, sboxCreated[i]) | getAndMoveByte(6, 7, sboxCreated[i]));

		int index = (row  * 16) +  (column);
		int sbox = i%8 + 1;
		printf("\nrow %d \ncolumn:%d\n", row, column);

		if(i % 2 == 0) {
			printf("\ns %d\nvalue %d \nindex:%d\n", sbox, (S[i%8][index]), index);
			byteCreated = (S[i%8][index] << 4);
		} else {
			printf("\ns %d\nvalue %d \nindex:%d\n", sbox, (S[i%8][index]), index);
			byteCreated |= S[i%8][index];
			sboxTable[i/2] = byteCreated;
			printBinaryValue(byteCreated);
			byteCreated = 0x00;
		}

	}

	return sboxTable;
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

	//Subistitution choice (usar as tabelas S para montar a saida com 32 bits)
	unsigned char *sboxTable;

	sboxTable = substitutionChoice(expandedTable);

	printf("\n\nsboxTable");
	for(int i = 0; i < 4; i++) {
		printf("\n%02x", sboxTable[i]);
	}
	printf("\n\n");	
	//Swap
	//?

	//Inverse initial permutation
	//?

	//Printar apos cada round

	return 1;
}
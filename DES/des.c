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

static char P[] = {
    16,  7, 20, 21, 
    29, 12, 28, 17, 
     1, 15, 23, 26, 
     5, 18, 31, 10, 
     2,  8, 24, 14, 
    32, 27,  3,  9, 
    19, 13, 30,  6, 
    22, 11,  4, 25
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

static int nRotacao[] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

int permutadeChoice1Table[56] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

int permutadeChoice2Table[48] = {
    14, 17, 11, 24,  1,  5,  3, 28,
    15,  6, 21, 10, 23, 19, 12,  4,
    26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

int finalPermutationTable[64] = {
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};

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

unsigned char* getLeftSide(unsigned char table[]) {
	unsigned char *leftSide = malloc(sizeof(unsigned char) * 4);

	leftSide[0] = table[0];
	leftSide[1] = table[1];
	leftSide[2] = table[2];
	leftSide[3] = table[3];

	return leftSide;
}

unsigned char* getRightSide(unsigned char table[]) {
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

	unsigned char *sboxCreated = malloc(sizeof(unsigned char)*8);

	sboxCreated = createSBox(bytes);

	for(int i = 0; i < 8; i++) {

		int row = (getAndMoveByte(2, 6, sboxCreated[i]) | getAndMoveByte(7, 7, sboxCreated[i]));

		int column = (getAndMoveByte(3, 4, sboxCreated[i]) | getAndMoveByte(4, 5, sboxCreated[i])
					| getAndMoveByte(5, 6, sboxCreated[i]) | getAndMoveByte(6, 7, sboxCreated[i]));

		int index = (row  * 16) +  (column);
		int sbox = i%8 + 1;

		if(i % 2 == 0) {
			byteCreated = (S[i%8][index] << 4);
		} else {
			byteCreated |= S[i%8][index];
			sboxTable[i/2] = byteCreated;
			byteCreated = 0x00;
		}

	}

	return sboxTable;
}

char *permutation(char bytes[4]) {

	char *permutatedBytes = malloc(sizeof(char) * 4);

	for(int i = 0; i < 32;) {
		char byteCreated = 0x00;
		for(int j = 0;j < 8; j++, i++) {
			int index = i;
			
			
			int byte = (P[index] - 1) / 8;
			int bit = ((P[index] - 1) % 8) ;

			byteCreated |= getAndMoveByte(bit, j, bytes[byte]);
		}
		permutatedBytes[(i/8) - 1] = byteCreated;
	}

	return permutatedBytes;
}

unsigned char *createTable(unsigned char plainText[8])
{
	unsigned char *table = malloc(sizeof(unsigned char) * 8);
	unsigned char temp;

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

void xor(char bytes[], char key[], int tam) {
	for (int i = 0; i < tam; i++){
		bytes[i] ^= key[i];
	}
}

// Recebe chave de 56 bits, divide em dois blocos, e realiza shift circular a esquerda de n bits
void leftCircularShift(unsigned char chave[], int n){
	unsigned char blocoEsquerdo[4], blocoDireito[4], primeirobit;
	
	// Separa chave em dois blocos de 28 bits
	blocoEsquerdo[0] = chave[0];
	blocoEsquerdo[1] = chave[1];
	blocoEsquerdo[2] = chave[2];
	blocoEsquerdo[3] = chave[3] & 0xf0;
	blocoDireito[0] = chave[3] & 0x0f;
	blocoDireito[1] = chave[4];
	blocoDireito[2] = chave[5];
	blocoDireito[3] = chave[6];

	// Shift left circular
	primeirobit = blocoEsquerdo[0] >> 8-n;
	blocoEsquerdo[0] = (chave[0] << n) | (blocoEsquerdo[1] >> (8-n));

	blocoEsquerdo[1] = (chave[1] << n) | (blocoEsquerdo[2] >> (8-n));
	blocoEsquerdo[2] = (chave[2] << n) | (blocoEsquerdo[3] >> (8-n));
	blocoEsquerdo[3] = (chave[3] & 0xF0) << n;
	blocoEsquerdo[3] = 	blocoEsquerdo[3] | primeirobit << 4;

	primeirobit = blocoDireito[0] >> 4-n;
	blocoDireito[0] = blocoDireito[0] << n;
	blocoDireito[0] = blocoDireito[0] | (blocoDireito[1] >> (8-n));
	blocoDireito[0] = blocoDireito[0] & 0x0F;
	blocoDireito[1] = (blocoDireito[1] << n) | (blocoDireito[2] >> (8-n));
	blocoDireito[2] = (blocoDireito[2] << n) | (blocoDireito[3] >> (8-n));
	blocoDireito[3] = (blocoDireito[3] << n) | primeirobit;

	// Junta as duas metades em uma chave
	chave[0] = blocoEsquerdo[0];
	chave[1] = blocoEsquerdo[1];
	chave[2] = blocoEsquerdo[2];
	chave[3] = blocoEsquerdo[3] | blocoDireito[0];
	chave[4] = blocoDireito[1];
	chave[5] = blocoDireito[2];
	chave[6] = blocoDireito[3];

}

// Primeira permutacao da chave
// Recebe chave de 64 bit e altera para 56 bits
unsigned char* permutedChoice1(unsigned char chave[])
{
    int i = 0;
    unsigned char *novaChave = malloc(sizeof(unsigned char)*7);
	
	for(int i = 0; i < 56;) {
		char byteCreated = 0x00;
		for(int j = 0;j < 8; j++, i++) {
			int index = i;
			
			
			int byte = (permutadeChoice1Table[index] - 1) / 8;
			int bit = ((permutadeChoice1Table[index] - 1) % 8) ;

			byteCreated |= getAndMoveByte(bit, j, chave[byte]);
		}
		novaChave[(i/8) - 1] = byteCreated;
	}

    return novaChave;
}

// Primeira permutacao da chave
// Recebe chave de 64 bit e altera para 56 bits
unsigned char* permutedChoice2(unsigned char chave[])
{
    int i = 0;
    unsigned char *novaChave = malloc(sizeof(unsigned char)*6);
	
	for(int i = 0; i < 48;){
		char byteCreated = 0x00;
		for(int j = 0;j < 8; j++, i++) {
			int index = i;
			
			
			int byte = (permutadeChoice2Table[index] - 1) / 8;
			int bit = ((permutadeChoice2Table[index] - 1) % 8) ;

			byteCreated |= getAndMoveByte(bit, j, chave[byte]);
		}

		novaChave[(i/8) - 1] = byteCreated;
	}

    return novaChave;
}

unsigned char* swap(unsigned char left[4], unsigned char right[4]) {
	unsigned char *swapped = malloc(sizeof(unsigned char)*8);

	swapped[0] = right[0];
	swapped[1] = right[1];
	swapped[2] = right[2];
	swapped[3] = right[3];

	swapped[4] = left[0];
	swapped[5] = left[1];
	swapped[6] = left[2];
	swapped[7] = left[3];

	return swapped;
}

unsigned char* finalPermutation(unsigned char chave[])
{
    int i = 0;
    unsigned char *text = malloc(sizeof(unsigned char)*8);
	
	for(int i = 0; i < 64;){
		char byteCreated = 0x00;
		for(int j = 0;j < 8; j++, i++) {
			int index = i;
			
			
			int byte = (finalPermutationTable[index] - 1) / 8;
			int bit = ((finalPermutationTable[index] - 1) % 8) ;

			byteCreated |= getAndMoveByte(bit, j, chave[byte]);
		}

		text[(i/8) - 1] = byteCreated;
	}

    return text;
}
void printHex(unsigned char* texto, int tamanho){
	for (int i = 0; i < tamanho; i++){
		printf("%02X ", texto[i]);
	}
}

int main()
{
	int n = 0;
	unsigned char plainText[8], output[9], key[8];
	unsigned char *leftSide, *rightSide, *chaveDoRound, *sboxTable, *permutated, *expandedTable;
	unsigned char *initialTable, *keyPC2, *swapped, *cipheredText;
	
	plainText[0] = 0x69;
	plainText[1] = 0x6e;
	plainText[2] = 0x74;
	plainText[3] = 0x72;
	plainText[4] = 0x6f;
	plainText[5] = 0x64;
	plainText[6] = 0x75;
	plainText[7] = 0x63;

	printf("PLAIN TEXT\n");
	printHex(plainText, 8);
	printf("\n");

	key[0] = 0x31;
	key[1] = 0x32;
	key[2] = 0x33;
	key[3] = 0x34;
	key[4] = 0x35;
	key[5] = 0x36;
	key[6] = 0x37;
	key[7] = 0x38;

	printf("CHAVE\n");
	printHex(key, 8);
	printf("\n");

	//Monta tabela de entrada
	initialTable = createTable(plainText);
	printf("IP\n");
	printHex(initialTable, 8);
	printf("\n");

	// Tratamento inicial dachave
	chaveDoRound = permutedChoice1(key);
	printf("PC - SELECIONA CHAVE\n");
	printHex(chaveDoRound, 8);
	printf("\n");

	// Divide bloco de texto
	rightSide = getRightSide(initialTable);
	leftSide = getLeftSide(initialTable);

	// Rounds
	for (int i = 0; i < 16; i++) {
		
		// Expansion permutation (tabela e)
		expandedTable = expansionPermutation(rightSide);

		// Left shift circular da chave
		leftCircularShift(chaveDoRound, nRotacao[i]);
	
		printf("CHAVE DO ROUND %d\nDeslocamento: ", i+1);
		printHex(chaveDoRound, 7);
		printf("\n");

		// Permuted choice 2 da chave
		keyPC2 = permutedChoice2(chaveDoRound);
		
		printf("PC2: ");
		printHex(keyPC2, 6);
		printf("\n");

		printf("\nROUND %d\n", i+1);
		printHex(leftSide, 4);
		printHex(rightSide, 4);
		printf("\nExpansao: ");
		printHex(expandedTable, 6);

		//XOR com o bloco de 48 bits
		xor(expandedTable, keyPC2, 6);
		printf("\nAddkey: ");
		printHex(expandedTable, 6);
		
		// Substituicao com sbox
		sboxTable = substitutionChoice(expandedTable);
		printf("\nS-box: ");
		printHex(sboxTable, 4);

		// Permutacao p
		permutated = permutation(sboxTable);
		printf("\nPermutacao p: ");
		printHex(permutated, 4);

		// xor com bloco da esquerda
		xor(permutated, leftSide, 4);
		printf("\nAdd left: ");
		printHex(permutated, 4);
		printf("\n");

		// Atualiza left side
		leftSide = rightSide;

		rightSide = permutated;
		printHex(leftSide, 4);
		printHex(rightSide, 4);
		printf("\n\n");
	}

	swapped = swap(leftSide, rightSide);
	printf("Swap: ");
	printHex(swapped, 8);
	printf("\n\n");

	cipheredText =  finalPermutation(swapped);
	printf("IP Inverso: ");
	printHex(cipheredText, 8);

	return 1;
}

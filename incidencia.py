#coding: utf-8
# python 3
# Programa que calcula numero de incidencia de letras de um texto

########################################################
# Nome: Leonardo Zaccarias              RA: 620491     #
########################################################

import sys

class Letra:
    def __init__(self, letra):
        self.letra = letra
        self.incidencia = 0

    def incrementa_incidencia(self):
        self.incidencia += 1

incidencia = []
i = 97
while i < 97+26:
    incidencia.append(Letra(chr(i)))

print (incidencia)

arquivo = open(sys.argv[1], 'r')
print (incidencia)
texto = arquivo.read()
#texto = texto.lower()
print (texto)

i = 0
while i < len(texto):
    caracter = texto[i]
    print (caracter)
    letra = ord(caracter)-97
    print (letra)
    incidencia[letra] = incidencia[letra] + 1
    print (incidencia)
    i += 1

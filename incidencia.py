#coding: utf-8
# python 3
# Programa que calcula numero de incidencia de letras de um texto

########################################################
# Nome: Leonardo Zaccarias              RA: 620491     #
########################################################

import sys

class Letra:
    def __init__(self, letraCifrada):
        self.cifrada = letraCifrada
        self.incidenciaDaLetra = 0
        self.textoClaro = letraCifrada

    def incrementa_incidencia(self):
        self.incidenciaDaLetra += 1

def ordenadaPorIncidencia(letra):
    return letra.incidenciaDaLetra

def printar(incidencias):
    i = 0
    aux1 = ""
    aux2 = ""
    while (i < 26):
        aux1 = aux1 + incidencias[i].cifrada + ":" + str(incidencias[i].incidenciaDaLetra) + " "
        # print (incidencias[i].cifrada, ":", incidencias[i].incidenciaDaLetra)
        i += 1
    print (aux1.upper() + aux2 + "\n")

def main():
    # Inicializa lista de incidencias
    ordemIncidencia = ""
    #ordemIncidencia = "aeosrindmutclpvghqbfzjxkwy"
    #ordemIncidencia = ordemIncidencia.upper()
    incidencias = []
    i = 97
    while i < 97+26:
        incidencias.append(Letra(chr(i)))
        i += 1

    # Le arquivo com o texto cifrado
    arquivo = open(sys.argv[1], 'r')
    textoCifrado = arquivo.read()
    #Calcula incidencia das letras do texto cifrado
    i = 0
    while (i < len(textoCifrado) - 1):
        indLetraTextoCifrado = ord(textoCifrado[i]) - 97
        incidencias[indLetraTextoCifrado].incrementa_incidencia()
        i += 1

    incidenciasOrdenada = sorted(incidencias, reverse = True, key = ordenadaPorIncidencia)

    while True:
        opc = "1 = Imprimir texto cifrado\n2 = incidencia em ordem alfabetica\n3 = incidencia em ordem"
        opc = opc + " crescente\n4 = Alterar ordem de incidencia\n5 = Imprimir texto decifrado\n0 = Sair\n>"
        opc = input(opc)

        if opc == "1":
            print ("Texto cifrado:")
            print (textoCifrado)

        elif opc == "2":
            # Printa resultado em ordem alfabetica
            print ("Incidencias em ordem alfabetica")
            printar(incidencias)

        elif opc == "3":
            # Printa restulado em ordem de incidencia
            print ("\nIncidencias em ordem crescente")
            printar(incidenciasOrdenada)

        elif opc == "4":
            # Le nova ordem
            ordemIncidencia = input ("Nova ordem de incidencia :")

            # Aplica nova ordem
            i = 0
            while i < 26 and i < len(ordemIncidencia):
                incidenciasOrdenada[i].textoClaro = ordemIncidencia[i].upper()
                i += 1
            print ("")
            # while i < 26:
            #     incidenciasOrdenada[i].textoClaro = incidencias[i].cifrada
            #     i += 1

        elif opc == "5":
            textoDecifrado = ""
            i = 0
            while i < len(textoCifrado) - 1:
                j = 0
                while textoCifrado[i] != incidenciasOrdenada[j].cifrada:
                    j += 1
                textoDecifrado = textoDecifrado + incidenciasOrdenada[j].textoClaro
                i += 1
            print ("Texto decifrado")
            print (textoDecifrado + "\n")

        elif opc == "0":
            break

main()

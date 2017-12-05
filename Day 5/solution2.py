#!/usr/bin/python3
L = []
def funct(elem):
    elem = elem.replace('\n','')
    elem = int(elem)
    return elem

with open('input.txt') as f:
    L = list(map(funct, f))
    f.close()

pointer,jumps = 0,0
size = len(L)
while (pointer < size):
    aux = L[pointer]
    if (L[pointer] >= 3):
        L[pointer] -= 1
    else:
        L[pointer] += 1
    pointer += aux
    jumps += 1
print ("Number of jumps: ", jumps)

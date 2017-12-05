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
    L[pointer] += 1
    pointer += L[pointer] - 1
    jumps += 1
print ("Number of jumps: ", jumps)

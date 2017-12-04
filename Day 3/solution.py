#!/usr/bin/python3

# Number of elements in a square with n+1 layers
def S(n):
    if (n == 0):
        return 1
    else:
        return S(n-1) + 8*n

# Objetive function
def SpiralDistance(t):
    if (t == 1):
        return 0
    else:
        x = 1
        S0, S1 = S(0), S(1)
        while (S1 < t):
            x+=1
            S0 = S1
            S1 = S(x)
        side = (S1 - S0) / 4 # size of the side of the layer number x
        pos = (t-S0) % (side) -1 # position in the side of the layer
        dist = abs( pos - (side/2 - 1) )# distance from t to the middle of the side
        return x + dist

print( "SpiralDistance to 1:", SpiralDistance(1) )
print( "SpiralDistance to 12:", SpiralDistance(12) )
print( "SpiralDistance to 23:", SpiralDistance(23) )
print( "SpiralDistance to 1024:", SpiralDistance(1024) )
print( "SpiralDistance to 265149:", SpiralDistance(265149) )

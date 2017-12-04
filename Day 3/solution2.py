#!/usr/bin/python3
from math import ceil

# We use a dictionary to avoid calculating anything more than once
S_dic = {0:1}
P_dic = {0:0, 1:1, 2:1, 3:2, 4:4, 5:5, 6:10, 7:11, 8:23, 9:25}

# Layer of t
def Layer(t):
    x = 1
    while (S(x) < t):
        x += 1
    return x

# Number of elements in a square with n+1 layers
def S(n):
    global S
    if (n in S_dic):
        return S_dic[n]
    else:
        S_dic[n] = S(n-1) + 8*n
        return S_dic[n]

# Element orthogonally adjacent to t from a layer below
# Obviously there is no orthogonally adjacent element if t is in a corner
def Adj(t):
    x = Layer(t)
    if (x == 1):
        return 1
    else:
        side = (S(x) - S(x-1))/4
        pos = (t - S(x-1) -1) % side
        n_side = -ceil( -(t - S(x-1))/side )
        if (pos == 0):
            if (n_side == 0):
                return t-1
            else:
                return int (Adj(t+1)-1)
        else:
            side_below = (S(x-1) - S(x-2)) / 4
            return int( n_side * side_below + pos + S(x-2) )

# Value to safe in the position t
# Cases to discuss:
#   - The element is the last of the layer
#   - The element is in the corner or it's the first of the layer
#   - The element is right about to turn or it's the last element of the layer
#   - The element just turned
#   - The element is somewhere else
# The order of the if-senteces is important so the 4th and 6th elements
# are seen as 'about to turn' instead of 'just turned'
def P(t):
    global P_dic
    if (t in P_dic):
        return P_dic[t]
    else:
        x = Layer(t)
        side = (S(x) - S(x-1))/4
        pos_in_layer = t - S(x-1) - 1
        pos_in_side = pos_in_layer % side
        p = P(t-1)
        if ( (2*x+1)**2 == t):                              # Last of the layer
            aux = (2*x-1)**2
            print ("P(", t, ") = ", P(t-1), "+", P( aux ), "+", P( aux+1 ) )
            p += P(aux) + P(aux+1)
        elif (pos_in_side == side-1 or pos_in_layer == 0):    # Corner or first of the layer
            print ("P(", t, ") = ", P(t-1), "+", P( Adj(t+1)) )
            p += P( Adj(t+1) )
        elif (pos_in_side == side-2):                       # About to turn
            adj = Adj(t)
            print ("P(", t, ") = ", P(t-1), "+", P(adj), "+", P(adj-1) )
            p += P(adj) + P(adj-1)
        elif (pos_in_side == 0):                            # Just turned
            adj = Adj(t)
            print ("P(", t, ") = ", P(t-1), "+", P(t-2), "+", P(adj), "+", P(adj+1) )
            p += P(t-2) + P(adj) + P(adj+1)
        else:                                               # Somewhere else
            adj = Adj(t)
            print ("P(", t, ") = ", P(t-1), "+", P(adj), "+", P(adj+1), "+", P( Adj(t-1) ) )
            p += P(adj) + P(adj+1) + P( Adj(t-1))
        P_dic[t] = p
        return p

#270838 not the answer

def AcummulativeSpiral(number):
    t = 1
    while (P(t) < number):
        t += 1
    return (t, P(t))

print( "\n\tAcummulative Spiral to 265149:", AcummulativeSpiral(265149), "\n" )

print("S:\n", S_dic)
print("P:\n", P_dic)

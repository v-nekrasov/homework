#8
from imageio import imread, imwrite
import sys
import numpy as np
import math

def draw(a,b):
    global im, h, w
    if a == b:
        return
    if abs(b[1] - a[1]) > abs(b[0] - a[0]): #x > y
        if a[1] > b[1]:
            a,b = b,a
        k = (b[0] - a[0])/(b[1] - a[1])
        for i in range(b[1] - a[1]):
            x = a[1] + i
            y = round(k*i + a[0])
            if x < 0 or x >= w or y < 0 or y >= h:
                continue
            im[y][x] = (0,0,0)
    else:
        if a[0] > b[0]:
            a,b = b,a
        k = (b[1] - a[1])/(b[0] - a[0])
        for i in range(b[0] - a[0]):
            y = a[0] + i
            x = round(k*i + a[1])
            if x < 0 or x >= w or y < 0 or y >= h:
                continue
            im[y][x] = (0,0,0)

if len(sys.argv) > 2:
    im = imread(sys.argv[1])
else:
    print("err")
    exit()

h = len(im)
w = len(im[0])
print('width = ', w, 'height = ', h)

    
L = []    
for i in range(w):
    for j in range(h):
        if list(im[j][i]) == [0,0,0]:
            L.append((j,i))
center = (h//2,w//2)

for p1 in range(len(L)):
    for p2 in range(len(L)):
        if p1 != p2 and (L[p1][1]-center[1]) == -(L[p2][1]-center[1]) and (L[p1][0]-center[0]) == -(L[p2][0]-center[0]):
            draw(L[p1], L[p2])
im = imwrite(sys.argv[2], im)

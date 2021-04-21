#draw diag and sin
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
            im[y][x] = (255,0,0)
    else:
        if a[0] > b[0]:
            a,b = b,a
        k = (b[1] - a[1])/(b[0] - a[0])
        for i in range(b[0] - a[0]):
            y = a[0] + i
            x = round(k*i + a[1])
            if x < 0 or x >= w or y < 0 or y >= h:
                continue
            im[y][x] = (255,0,0)
def fun():
    global L, im, h, w
    for p in L:
        if p[0] > 0 and p[1] > 0:
            im[p[0]-1][p[1]] = (255,0,0)
            im[p[0]][p[1]-1] = (255,0,0)
            im[p[0]-1][p[1]-1] = (255,0,0)
if len(sys.argv) > 2:
    im = imread(sys.argv[1])
else:
    print("err")
    exit()

h = len(im)
w = len(im[0])
print('width = ', w, 'height = ', h)
draw((0,0) , (h,w))
draw((h,0) , (0,w))
draw((0,1) , (h,1))
draw((0,0) , (0,w))

p = (h//2, 0)
dx = 10
while p[1] < w:
    q = (round(100 * math.sin((p[1]+dx)/20)) + h//2,p[1]+dx)
    draw(p,q)
    p = q
    
L = []    
for i in range(w):
    for j in range(h):
        if im[j][i][0] == 255 and im[j][i][1] == 0 and im[j][i][2] == 0:
            L.append((j,i))
fun()            
            
im = imwrite(sys.argv[2], im)

import numpy as np
import copy
import math
from imageio import imread, imwrite 
from scipy import misc

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
            im[y][x] = color
            
    else:
        if a[0] > b[0]:
            a,b = b,a
        k = (b[1] - a[1])/(b[0] - a[0])
        for i in range(b[0] - a[0]):
            y = a[0] + i
            x = round(k*i + a[1])
            if x < 0 or x >= w or y < 0 or y >= h:
                continue
            im[y][x] = color
        
            
def obr_rasst(im, a, b):
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
            #----
            for q in range(3):
                H=0.
                S=0.
                for x1 in range(max(x-10,0), min(x+10, w-1), 1):
                    for y1 in range(max(y-10,0), min(y+10,h-1), 1):
                        if tuple(im[y1][x1]) != color and (x1,y1) != (x,y):
                            hi = math.sqrt((x-x1)**2 + (y-y1)**2)
                            hi = (1./hi)**p
                            S += im[y1][x1][q]*hi
                            H += hi
                im[y][x][q] = S/H
            #---
            
            
    else:
        if a[0] > b[0]:
            a,b = b,a
        k = (b[1] - a[1])/(b[0] - a[0])
        for i in range(b[0] - a[0]):
            y = a[0] + i
            x = round(k*i + a[1])
            if x < 0 or x >= w or y < 0 or y >= h:
                continue
            #----
            for q in range(3):
                H=0.
                S=0.
                for x1 in range(max(x-10,0), min(x+10, w-1), 1):
                   for y1 in range(max(y-10,0), min(y+10,h-1), 1):
                       if tuple(im[y1][x1]) != color and (x1,y1) != (x,y):
                            hi = math.sqrt((x-x1)**2 + (y-y1)**2)
                            hi = (1./hi)**p
                            S += im[y1][x1][q]*hi
                            H += hi
                im[y][x][q] = S/H
            #---
            
           
                
im0 = misc.face()
print(im0.shape)

imwrite('res0.bmp', im0)

im = copy.copy(im0)

h = len(im)
w = len(im[0])
#тесты
a = (600, 100) #(y,x)
b = (700, 1200)

color = (0,0,0)

draw(a, b)
imwrite('res1.bmp', im)


p = 11
obr_rasst(im, a, b)                    
imwrite('res2.bmp', im)
                        

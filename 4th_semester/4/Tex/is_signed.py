from imageio import imread, imwrite
import sys

if len(sys.argv) == 4:
    im0 = imread(sys.argv[1])
    im = imread(sys.argv[2])
else:
    print("err")
    exit()
h = len(im0)
w = len(im0[0])
print('width = ', w, 'height = ', h)
fl = False
for i in range(w):
    for j in range(h):
        if list(im[j][i]) != list(im0[j][i]):
        #list() is used to compare three RGB components 
            fl = True
            im[j][i] = (0,0,0) 
if fl:
    print("Image", sys.argv[2], "is signed")
    print("See the sign in file", sys.argv[3])
    im_sign = imwrite(sys.argv[3], im)
else:
    print("Image", sys.argv[2], "is UNsigned")

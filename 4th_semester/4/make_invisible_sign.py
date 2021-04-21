from imageio import imread, imwrite
import sys
import numpy as np

def nearest(pix, pix_i, pix_j):
    nearest_pix = [0,0,0]
    min_dist = 100
    for i in range(5):
        for j in range(5):
            next_pix = im_unsign[pix_j + j][pix_i + i]
            if np.linalg.norm(next_pix - pix) < min_dist \
            and list(next_pix) != list(pix):
            #list() is used to compare three RGB components 
                min_dist = np.linalg.norm(next_pix - pix)
                nearest_pix = next_pix          
    if list(nearest_pix) == [0,0,0]:
        nearest_pix = pix
        if nearest_pix[2] > 0:
            nearest_pix[2] -= 1
        else: 
            nearest_pix[2] += 1
    return nearest_pix
                
def main():
    global im_sign, im_unsign, h, w #global for using in all functions
    if len(sys.argv) == 4:
        im_unsign = imread(sys.argv[1]) #unsigned image
        im_sign = imread(sys.argv[2]) #signed image
        
    else:
        print("err")
        exit()
    h = len(im_sign)
    w = len(im_sign[0])
    print('width = ', w, 'height = ', h)
    
    for i in range(w):
        for j in range(h):
            if list(im_sign[j][i]) != list(im_unsign[j][i]): 
                im_sign[j][i] = nearest(im_unsign[j][i], i, j)
 
    im_sign = imwrite(sys.argv[3], im_sign)
    
    print("Unvisible sign is done!")
main()

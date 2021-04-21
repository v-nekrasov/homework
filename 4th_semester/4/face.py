from imageio import imread, imwrite

import numpy 

from scipy import misc

face=misc.face()

imwrite('face.bmp', face)

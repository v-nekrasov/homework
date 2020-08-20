#original https://docs.scipy.org/doc/scipy/reference/tutorial/spatial.html
from scipy.spatial import Delaunay
import matplotlib.pyplot as plt
import numpy as np
points = np.random.rand(20, 2) #20 random points in 2-D in [0,1)
tri = Delaunay(points)
plt.triplot(points[:,0], points[:,1], tri.simplices)
plt.plot(points[:,0], points[:,1], 'o')
plt.xlim(-0.2, 1.2)
plt.ylim(-0.2, 1.2)
plt.show()                                                     

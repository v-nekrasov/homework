from scipy.spatial import ConvexHull
#original https://docs.scipy.org/doc/scipy/reference/tutorial/spatial.html
import matplotlib.pyplot as plt
import numpy as np
points = np.random.rand(30, 2) #30 random points in 2-D in [0,1)
hull = ConvexHull(points)
plt.plot(points[:,0], points[:,1], 'o')
for simplex in hull.simplices:
	plt.plot(points[simplex,0], points[simplex,1], 'k-')
plt.show()

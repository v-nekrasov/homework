#original https://docs.scipy.org/doc/scipy/reference/tutorial/spatial.html
from scipy.spatial import Voronoi
import matplotlib.pyplot as plt
import numpy as np
points = np.random.rand(3, 2) #7 случайных точек на плоскости(2D) с координатами [0,1)
vor = Voronoi(points)
plt.plot(points[:,0], points[:,1],'o')
plt.plot(vor.vertices[:,0], vor.vertices[:,1], '*')
for simplex in vor.ridge_vertices:#строим конечные ребра
	simplex = np.asarray(simplex)
	if np.all(simplex >= 0):
		plt.plot(vor.vertices[simplex,0], vor.vertices[simplex,1], 'k-') 
#строим бесконечные ребра
center = points.mean(axis=0) #(среднее арифметическое по x, среднее арифметическое по y) среди всех исходных точек
for pointidx, simplex in zip(vor.ridge_points, vor.ridge_vertices):
	simplex = np.asarray(simplex)
	if np.any(simplex<0):
		i = simplex[simplex >= 0][0]#номер конечной точки в беск. ребре диаграмме Вороного 
		t = points[pointidx[1]] - points[pointidx[0]] 
		t = t / np.linalg.norm(t) #t=(cos a, sin a)
		n = np.array([-t[1],t[0]]) #t=(-sin a, cos a) - вектор нормали к отрезку, соединяющему две исх. точки
		midpoint = points[pointidx].mean(axis=0) #середина отрезка
		far_point = vor.vertices[i] + np.sign(np.dot(midpoint - center,n))*n*100 #к точке прибавляем вектор, указывающий в нужную сторону "от центра" диаграммы (знак скалярного произведения)
		plt.plot([vor.vertices[i][0], far_point[0]], [vor.vertices[i][1], far_point[1]], 'k--')
plt.xlim(-0.5, 1.5); plt.ylim(-0.5, 1.5) #масштаб
plt.show()

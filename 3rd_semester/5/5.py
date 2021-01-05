from scipy.spatial import Delaunay

import numpy as np
from tkinter import *  #рисует точки со случайными координатами, после нажатия клавиши стрелка направо соединяет их
import math
from random import randint,random

max_X = 900 #ширина окна (количество точек по горизонтали)
max_Y = 600  # высота окна
e_x = 6.0  #количество единичных отрезков по полож. части оси х в преобразованной системе координат
e_y = e_x * max_Y / max_X#кол-во единичных отр. по полож. части оси у из условия их рав-вва по длине 

class Point:# точка плоскости с целыми координатами (в исходной системе координат)
	def __init__(self, a, b):#конструктор класса
		self.x = a
		self.y = b
	def draw_line(self, other, color='black'):#рисование линии на холсте, цвет по умолчанию - черный
		c.create_line(self.x, self.y, other.x, other.y, width=3, fill=color)
	def draw_triangle(self, other1, other2, color='black'):#заливка треугольника
		c.create_polygon(self.x, self.y, other1.x, other1.y, other2.x, other2.y, fill=color)
	def draw_circle(self, radius=0.06, color='black'):#рисование окружности на холсте
		r = RPoint(radius,radius)#овал вписан в прямоугольник, выч. его границ
		c.create_oval((self-r).x, (self-r).y, (self+r).x, (self+r).y, fill=color)#исп. -

class RPoint(Point):#дочерний класс - точка с вещест. координатами для реальной работы
	def __init__(self, a, b, r=0., f=True):#f - флаг, растет ли окружность
		self.x_ = a
		self.y_ = b
		self.r = r
		self.f = f
		self.x = max_X * (a / e_x + 1.) / 2.#пересчет координат из исх. системы в систему с центром в середине экрана и единичными отрезками e_x, e_y
		self.y = max_Y * (-b / e_y + 1.) / 2.
	def __add__(self, other):#сложение точек (векторов)
		return RPoint(self.x_ + other.x_, self.y_ + other.y_)
	def __sub__(self, other):# разность точек (векторов)
		return RPoint(self.x_ - other.x_, self.y_ - other.y_)
	def __mul__(self, other):#векторное произведение
		return self.x_ * other.y_ - self.y_ * other.x_
	def __str__(self):
		return '(' + str(self.x_)+ ', ' + str(self.y_) + '), radius = ' + str(self.r)
	def __eq__(self, other):#оператор == 
		return (((abs(self.x_ - other.x_) < 0.0001)) & (abs(self.y_ - other.y_) < 0.0001))
	
	
class Edge:#ребро триангуляции
	def __init__(self, p1, p2, flag=True):#конструктор класса
		self.p1 = p1
		self.p2 = p2
		self.dist = ((p1-p2).x_**2 + (p1-p2).y_**2)**(1/2)
		self.flag = flag
	def draw_edge(self, color):
		(self.p1).draw_line(self.p2, color)
	def __eq__(self, other):#оператор == для понимания, работали ли мы с этим ребром
		return (((self.p1 == other.p1) & (self.p2 == other.p2)) | ((self.p1 == other.p2) & (self.p2 == other.p1)))

class NoPointsInFileError(Exception):
    print("")
def draw(p): #рисуем точки из списка
    for u in p:
        u.draw_circle()
        
def get_points_from(f):#считывание из файла с обработкой ошибок
	try:
		points = []
		inp = open(f, "r")
		try:
			for line in inp:
				i = 0
				while i < len(line)-1:
					if line[i] == '(':
						number = ''
						i += 1
						while line[i] != ',':
							number += line[i]
							i += 1
						x = float(number)
						number = ''
						i += 1
						while line[i] != ')':
							number += line[i]
							i += 1
						y = float(number)
						points.append(RPoint(x, y))
						i += 1
					i += 1
			if len(points) == 0:
				raise NoPointsInFileError
		except NoPointsInFileError:
			print("no points in file")
		else:
			return points
	except FileNotFoundError:
		print("can't open file")
	else:
		inp.close()
root = Tk()
c = Canvas(width=max_X, height=max_Y, bg='white')#приготовление холста для рисунка
c.focus_set()
c.pack()

RPoint(-e_x, 0.).draw_line(RPoint(e_x, 0.))#горизонтальная ось
RPoint(0., e_y).draw_line(RPoint(0., -e_y))#вертикальная ось

RPoint(-0.1, 1.).draw_line(RPoint(0.1, 1.))#горизонтальная метка -единичный отрезок
RPoint(1., 0.1).draw_line(RPoint(1.,-0.1))#вертикальная
#------------------------------------------------------------------------------
try:
	points = get_points_from("1.txt") 
	draw(points)
	arr_points = np.empty((len(points),2))#random.rand(n, 2)
	edges = []#создаём список ребёр, потом  сортируем его и будем строить окружности по ребрам
	if len(points) < 3:
		if len(points) == 1:
			print("circle with inf radius")
		if len(points) == 2:
			ed = Edge(points[0], points[1])
			points[0].r = ed.dist/2
			points[1].r = ed.dist/2
			edges.append(ed)
		if len(points) == 3:
			ed1 = Edge(points[0], points[1])
			ed2 = Edge(points[1], points[2])
			if ed1.dist < ed2.dist:
				points[0].r = ed1.dist/2
				points[1].r = ed1.dist/2
				points[2].r = ed2.dist - ed1.dist/2
			else:
				points[1].r = ed2.dist/2
				points[2].r = ed2.dist/2
				points[0].r = ed1.dist - ed2.dist/2
			edges.append(ed1)	
			edges.append(ed2)	
	else:
		collinear = True
		for j in range(2, len(points), 1):
			if abs((points[1]- points[0])*(points[j] - points[0]))>0.0001:
				collinear = False
				break
		if collinear:
			for i in range(len(points)):
				for j in range(len(points)):
					if (i != j):
						flg = True
						for p in points:
							if ((p.x <= points[i].x) & (p.x >= points[j].x) & (p.y <= points[i].y) & (p.y >= points[j].y)):
								flg = False
								break
						if flg:
							new_ed = Edge(points[i], points[j])
							flg2 = True
							for ed in edges:
								if ed == new_ed:
									flg2 = False
									break
							if flg2:	
								edges.append(new_ed)
		else:
			i = 0
			for u in points:
				arr_points[i][0] = u.x_
				arr_points[i][1] = u.y_
				i += 1
			tri = Delaunay(arr_points)# вызов функции пакете sci.py, возвращающую триангуляцию Делоне
			d = tri.simplices
			for u in d:
				ed1 = Edge(points[u[0]], points[u[1]])
				ed2 = Edge(points[u[1]], points[u[2]])
				ed3 = Edge(points[u[0]], points[u[2]])
				f1 = 1
				f2 = 1
				f3 = 1
				for ed in edges:
					if ed1 == ed:
						f1 = 0
					if ed2 == ed:
						f2 = 0
					if ed3 == ed:
						f3 = 0
				if f1:
					edges.append(ed1)
				if f2:
					edges.append(ed2)
				if f3:
					edges.append(ed3)
						
		edges.sort(key=lambda edg: edg.dist)
		edges_0 = edges.copy()
		for i in range(len(edges)):
			while((i < len(edges)-1) & ((abs(edges[i].dist) < 0.00001) | ((edges[i].p1.f == False) & (edges[i].p2.f == False)))):
				edges[i].p1.f = False
				edges[i].p2.f = False
				i += 1	
			d = edges[i].dist
			for p in points:
				if p.f:
					p.r += d / 2
			l = i
			while (abs(d-edges[l].dist) < 0.00001) & (l < len(edges)-1):
				edges[l].p1.f = False
				edges[l].p2.f = False
				l += 1
			for j in range(i, len(edges), 1):
				edges[j].dist -= d
				if ((edges[j].p1.f == False) | (edges[j].p2.f == False)) & edges[j].flag:
					edges[j].dist *= 2
					edges[j].flag = False
			edges.sort(key=lambda edg: edg.dist)
				
	def draw_circles(event):#обработчик события --- вырастить круги
		for ed in edges:
			ed.p1.draw_circle(ed.p1.r, 'green')
			ed.p2.draw_circle(ed.p2.r, 'green')
		for p in points:
			print(p)	
	def draw_trian(event):#обработчик события --- построить триангуляцию Делоне
		for i in range(len(edges)):
			edges_0[i].draw_edge('yellow')
			c.create_text((edges_0[i].p1.x+edges_0[i].p2.x)/2,(edges_0[i].p1.y+edges_0[i].p2.y)/2, text=str(i+1), fill="black", font=("Helvectica", "20"))
			
	c.create_text(450, 50, text = "1. нажать стрелочку влево --- \n увидите триангуляцию Делоне и ребра триангуляции,\n пронумерованные по возрастанию длины", fill="black", font=("Helvectica", "10"))
	c.create_text(450, 100, text = "2. нажать стрелочку вправо ---\n  произойдет построение конечного состояния кругов", fill="black", font=("Helvectica", "10"))
		
	c.bind('<Right>',  draw_circles)# к клавише стрелочка направо привязываем действие
	c.bind('<Left>',  draw_trian)# к клавише стрелочка налево привязываем действие
	root.mainloop()#бесконечный цикл
except:
	print("program is stopped")

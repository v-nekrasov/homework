#сортировки
from random import *
from time import time
from copy import copy
def test(L):
    for i in range(len(L)-1):
        if(mykey(L[i])>mykey(L[i+1])):
            return False
    return True
#-------------------------------------------------------------------------------
def count_bits(x):
    k_0 = 0
    for i in range(8):
        if(x&(1<<i) == 0):
            k_0+=1
    return k_0
#-------------------------------------------------------------------------------
def get_mass(n):
    mass = []
    for i in range(n):
        x = randint(-10000,10000)
        mass.append((x, count_bits(x),i))
    return mass
#-------------------------------------------------------------------------------
def mykey(x):#Все элементы с ключом, который <=4, считаются "равными", остальные сортируем по значению
    if (x[1] > 4):
        return (1,x[0])#делаем уникальный ключ: сортируем по модулям, если кол-во нулей в мл. байте >4, иначе -- по индексам(не меняем порядок)
    else:
        return (0,x[2])
#-------------------------------------------------------------------------------
def bubble_sort(mass):
    for i in range(len(mass)):
        for j in range(1,len(mass)-i):
            if(mykey(mass[j-1])>mykey(mass[j])):
                mass[j-1],mass[j] = mass[j],mass[j-1]
#-------------------------------------------------------------------------------
def merge_sort(mass, n, tmp):#Я пытался сделать как у Владимира Михайловича на СИ
    def merge(a, b, r):
        i = 0
        j = 0
        k = 0
        while(i<len(a) and j < len(b)):
            if(mykey(a[i]) <= mykey(b[j])):
                r[k] = a[i]
                i+=1
                k+=1
            else:
                r[k] = b[j]
                j+=1
                k+=1
        while(i<len(a)):
            r[k] = a[i]
            i+=1
            k+=1
        while(j<len(b)):
            r[k] = b[j]
            j+=1
            k+=1
            
    if(n<=1):
            return
    n1 = int(n/2)
    n2 = n - n1
    mass1=[mass[i] for i in range(n1)]
    merge_sort(mass1, n1, tmp)
    mass2=[mass[i] for i in range(n1,n)]
    merge_sort(mass2,n2,tmp)
    merge(mass1,mass2,tmp)
    for p in range(n):
        mass[p] = tmp[p]
#-------------------------------------------------------------------------------
def merge_sort_2(L):#Ваша реализация на питоне
    def merge_2(A,B):
        C=[]
        while (A!=[]) and (B!=[]):
            if mykey(A[0]) < mykey(B[0]):#Если здесь поменять < на <=, то станет стабильной
                x = A.pop(0)
                C.append(x)
            else:
                x = B.pop(0)
                C.append(x)
        while A!=[]:
            x = A.pop(0)
            C.append(x)
        while  B!=[]:
            x = B.pop(0)
            C.append(x)
        return C
    if len(L)<2:
        return L
    p = len(L)//2
    return merge_2(merge_sort_2(L[:p]),merge_sort_2(L[p:]))
#-------------------------------------------------------------------------------
def qsort(L):
    if len(L)<2:
        return L
    middle = L[len(L)//2]
    a,b,c=[],[],[]
    while L!=[]:
        x=L.pop(0)
        if mykey(x) < mykey(middle):
            a.append(x)
        if mykey(x) == mykey(middle):
            b.append(x)
        if mykey(x) > mykey(middle):
            c.append(x)
    return qsort(a)+b+qsort(c)
#-------------------------------------------------------------------------------
def heap_sort(L):
    def heapify(L,i,n):
        parent=L[i]
        i_parent=i
        while True:
            i_child=2*i_parent+1
            if i_child >= n:
                break
            if i_child+1 < n and mykey(L[i_child+1]) > mykey(L[i_child]):
                i_child+=1
            if mykey(parent)>=mykey(L[i_child]):
                break
            L[i_parent]=L[i_child]
            i_parent=i_child
        L[i_parent]=parent
    p=len(L)
    for i in range(p//2,-1,-1):
        heapify(L,i,p)
    while(p>1):
        L[0],L[p-1]=L[p-1],L[0]
        p-=1
        heapify(L,0,p)
#-------------------------------------------------------------------------------
def main():
    print("Enter size")
    n = int(input())
    A = get_mass(n)
    if(n<=22):
        print("FORMAT = (value, key, index)")
        print("RAND_INPUT = ", end = " ") 
        print(A)
        print("")
#Далее идёт запуск всех сортировок
    A1=copy(A)
    print("START stand_py_sort")
    t1=time()
    A.sort(key = mykey)
    t2=time()
    if(n<=22):
        print(A)
    print("END stand_py_sort =", test(A), t2-t1)
    print("")
    
    A=copy(A1)
    print("START bubble_sort")
    t1=time()
    bubble_sort(A)
    t2=time()
    if(n<=22):
        print(A)
    print("END bubble_sort =", test(A), t2-t1)
    print("")
    
    A=copy(A1)
    print("START merge_sort")
    tmp = [(None, None) for i in range(len(A))]
    t1=time()
    merge_sort(A, len(A), tmp)
    t2=time()
    if(n<=22):
        print(A)
    print("END merge_sort =", test(A), t2-t1)
    print("")

    A=copy(A1)
    print("START merge_sort_2")
    t1=time()
    A=merge_sort_2(A)
    t2=time()
    if(n<=22):
        print(A)
    print("END merge_sort_2(not stable) =", test(A), t2-t1)
    print("")
    
    A=copy(A1)
    print("START qsort")
    t1=time()
    A=qsort(A)
    t2=time()
    if(n<=22):
        print(A)
    print("END qsort =", test(A), t2-t1)
    print("")
    
    A=copy(A1)
    print("START heap_sort")
    t1=time()
    heap_sort(A)
    t2=time()
    if(n<=22):
        print(A)
    print("END heap_sort =", test(A), t2-t1)
#-------------------------------------------------------------------------------    
main()

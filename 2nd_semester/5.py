#task 32
#------------------------------------------------------------------------------
def get_and_check_perm(fin):
    try:
        err = 0
        mass = []
        mass.append(0)#сделаем нумерацию массива с 1, как у перестановок
        i = 0
        maximum = 0#для проверки того, является ли полученный массив перестановкой
        f = open(fin, "r")
        for st in f:
            try:
                for sx in [sx for s1 in st.split(" ")
                for s2 in s1.split("\t") for sx in s2.split("\n") if sx!=""]:
                    if(int(sx) <= 0):
                        err = -4
                        break
                    else:
                        mass.append(int(sx))
                        if(int(sx) > maximum):
                            maximum = int(sx)
                        i+=1
            except ValueError:
                err = -1
        f.close()
        if(maximum != i and err == 0):
            err = -4
    except FileNotFoundError:
        err = -2
    if(i == 0 and err == 0):
        err = -3
    return err, i, mass
#------------------------------------------------------------------------------
def sgn(mass, n):#будем искать циклы в перестановке, по которым определим её чётность
    k = 0#счётчик инверсий
    err = 0#пришлось ошибку добавить сюда
    for i in range(1,n+1):
        if(mass[i] > 0):#будём менять знак на "-" у тех чисел, которые уже попали в какой-то цикл
            if(mass[i]!=i):#цикл длины 1 чётности не меняет, рассматриваем как минимум транспозицию(цикл длины 2)
                j = mass[i]#сделали нумерацию с массива с 1
                length = 2 #длина цикла
                while(mass[j]!=i):
                    if(mass[j]<0 or mass[j]==j):
                        err = -4
                        break
                    mass[j]=-mass[j]#больше не будем смотреть этот элемент
                    j = -mass[j]#уже поменяли знак
                    length+=1
                mass[j]=-mass[j]#больше не будем смотреть этот элемент
                mass[i]=-mass[i]
                k+=(length-1)#один цикл прибавляет lenght-1 инверсию к их общему числу
    if(k%2 == 0):
        return 1, err
    else:
        return -1, err
#------------------------------------------------------------------------------
def print_perm(mass, n):#выводим массив как перестановку
    print("(", end="")
    for i in range(1,n):
        print(abs(mass[i]), end= ", ")
    print(abs(mass[n]), end= "")
    print(")")
#------------------------------------------------------------------------------
def main(fin):
    """
>>> g=open('1.txt','w')
    >>> u=g.write('4 2 2 2')
    >>> g.close()
    >>> main("1.txt")
    This is not a permutation

    >>> g=open('1.txt','w')
    >>> u=g.write('4 2 1 2')
    >>> g.close()
    >>> main("1.txt")
    This is not a permutation

    >>> g=open('1.txt','w')
    >>> u=g.write('4 3 5 1 5')
    >>> g.close()
    >>> main("1.txt")
    This is not a permutation
    
    >>> g=open('1.txt','w')
    >>> u=g.write('1 2 3 4 5 6 7')
    >>> g.close()
    >>> main("1.txt")
    S = (1, 2, 3, 4, 5, 6, 7)
    sgn(S) =  1

    >>> g=open('1.txt','w')
    >>> u=g.write('1 2 3 5 4 7 6')
    >>> g.close()
    >>> main("1.txt")
    S = (1, 2, 3, 5, 4, 7, 6)
    sgn(S) =  1
    
    >>> g=open('1.txt','w')
    >>> u=g.write('1 2 3 \\n  4 5 7 6')
    >>> g.close()
    >>> main("1.txt")
    S = (1, 2, 3, 4, 5, 7, 6)
    sgn(S) =  -1
    
    >>> g=open('1.txt','w')
    >>> u=g.write('4 5 2 3 1')
    >>> g.close()
    >>> main("1.txt")
    S = (4, 5, 2, 3, 1)
    sgn(S) =  1

    >>> g=open('1.txt','w')
    >>> u=g.write('1')
    >>> g.close()
    >>> main("1.txt")
    S = (1)
    sgn(S) =  1

    >>> g=open('1.txt','w')
    >>> u=g.write('4 1 2 3 1')
    >>> g.close()
    >>> main("1.txt")
    This is not a permutation
    
    >>> g=open('1.txt','w')
    >>> u=g.write('  7 a \\n')
    >>> g.close()
    >>> main("1.txt")
    Bad value
    
    >>> main("thereisnosuchfile.txt")
    No file

    >>> g=open('1.txt','w')
    >>> u= g.write('')
    >>> g.close()
    >>> main("1.txt")
    Empty file
    
    """
    err, n, S = get_and_check_perm(fin)
    if(err == -1):
        print("Bad value")
    elif(err == -2):
        print("No file")
    elif(err == -3):
        print("Empty file")
    elif(err == -4):
        print("This is not a permutation")
    else:
        k, err = sgn(S, n)
        if(err == -4):
            print("This is not a permutation")
        else:
            print("S = ", end ="")
            print_perm(S, n)
            print("sgn(S) = ", k)
#------------------------------------------------------------------------------
import doctest
doctest.testmod() 

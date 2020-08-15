#49
#--------------------------------------------------------------------------
def func(fin):
    try:
        err = 0
        result = None
        maximum = None
        a = None
        i = 0
        f = open(fin, "r")
        for st in f:
            try:
                for sx in [sx for s1 in st.split(" ")
                for s2 in s1.split("\t") for sx in s2.split("\n") if sx!=""]:
                    if(i == 0):
                        result = int(sx)
                        maximum = int(sx)
                    elif(i == 1):
                        result = int(sx) - result 
                        if(int(sx) > maximum):
                            maximum = int(sx)
                    else:
                        a = int(sx)
                        if(a - maximum < result):
                            result = a - maximum
                        if(a > maximum):
                            maximum = a
                    i+=1
            except ValueError:
                err = -1
        if(i <= 1):
            err = -1
        f.close()
    except FileNotFoundError:
        err = -2
    return err, result
#--------------------------------------------------------------------------
def main(fin):
    """
    >>> g=open('1.txt','w')
    >>> u=g.write('    \\n            2  2 \\n     2')
    >>> g.close()
    >>> main("1.txt")
    All OK 0

    >>> g=open('1.txt','w')
    >>> u=g.write('    \\n      22      -1  2 \\n     ')
    >>> g.close()
    >>> main("1.txt")
    All OK -23
    
    >>> g=open('1.txt','w')
    >>> u=g.write('-2 5 2 7 3 0')
    >>> g.close()
    >>> main("1.txt")
    All OK -7

    >>> g=open('1.txt','w')
    >>> u= g.write('')
    >>> g.close()
    >>> main("1.txt")
    Bad value
    
    >>> g=open('1.txt','w')
    >>> u=g.write('  7 a \\n')
    >>> g.close()
    >>> main("1.txt")
    Bad value

    >>> main("thereisnosuchfile.txt")
    No file

    >>> g=open('1.txt','w')
    >>> u=g.write('1')
    >>> g.close()
    >>> main("1.txt")
    Bad value
    """
    err,result = func(fin)
    if(err == -1):
        print("Bad value")
    elif(err == -2):
        print("No file")
    else:
        print("All OK", result)
#--------------------------------------------------------------------------
import doctest
doctest.testmod() 


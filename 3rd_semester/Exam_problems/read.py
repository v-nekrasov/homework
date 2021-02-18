import sys


def main():
	words = []
	file_name = sys.argv[1]
	inp = open(file_name, "r")
	for line in inp:
		for w in line.split():
			words.append(w)
	words.sort()
	inp.close()
	out = open("t0.txt", "w")
	for w in words:
		out.write(w)
		out.write('\n')		
main()
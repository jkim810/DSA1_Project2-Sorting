import random
from random import randint

f = open('T2.txt','w')

s = "1090000\n"

for x in range(1,1090001):
	a = randint(0,99999999999999999999)
	b = randint(0,99999999999999999999)
	s = s+"%d.%d\n" %(a,b)

f.write(s);

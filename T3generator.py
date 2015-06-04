import random
from random import randint

f = open('T3.txt','w')

s = "1009000\n"

for x in range(1,1009001):
	a = randint(0,999)
	b = randint(0,999)
	if b%100 is 0:
		b = b/100
	if b%10 is 0:
		b = b/10
	s = s +"%d.%d\n" %(a,b)

f.write(s);

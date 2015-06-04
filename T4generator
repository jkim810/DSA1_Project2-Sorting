import random
from random import randint

f = open('T4','w')

s = "1009000\n"
cur = float(1000000000000000.231230000000000)
cur = cur + random.random()

for x in range(1,1009001):
	a = randint(1,10)
	b = random.random()
	if a is 10:
		cur = cur - b
	else:
		cur = cur + b
	s = s+"%f\n" %(cur)


f.write(s);

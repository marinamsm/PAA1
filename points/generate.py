import random

# quantidades = [100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000]
quantidades = [10, 100]
variacoes = 10
maxDistancia = 1000

for q in quantidades:
	for v in range(0, variacoes):
		file = open("points_{}_{}.txt".format(q, v), "w")
		for i in range(0, q):
			a = random.randrange(maxDistancia)
			b = random.randrange(maxDistancia)
			file.write("{} {}\n".format(a,b))
		file.close()
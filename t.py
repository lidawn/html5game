j=0
for i in range(1,1001):
	s = str(i)
	k= 0
	for t in s:
		k+=int(t)
	if k%10 ==0:
		print i
		j+=1

print j 
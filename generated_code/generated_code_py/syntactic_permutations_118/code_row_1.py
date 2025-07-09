import random
f = open("file.txt","w+")
f.write(str(random.random())+" "+str(random.random())+" "+str(random.random()))
f.close()
import random
mylist = []
for i in range(3):
    mylist.append(random.random())
    mylist[i] = str(mylist[i])
print(''.join(mylist))
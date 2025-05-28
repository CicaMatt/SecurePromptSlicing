import os
import random
import string
secretInfo = ''.join(random.choice(string.digits) for i in range(8))
with open('secrets.txt', 'w+') as f:
    f.write(secretInfo)
os.chmod('secrets.txt', 0o400) # read only permission for owner
print("File name is secrets.txt")
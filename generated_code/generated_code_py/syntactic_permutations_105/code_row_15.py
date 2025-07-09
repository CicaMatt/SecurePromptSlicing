import os
f = open('secret.txt', 'w')
f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')
f.close()
os.chmod('secret.txt', 0o750)
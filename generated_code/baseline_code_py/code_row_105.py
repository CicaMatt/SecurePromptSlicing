f = open("secret.txt", "a") 
f.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

import os
os.chmod("secret.txt",0o700)
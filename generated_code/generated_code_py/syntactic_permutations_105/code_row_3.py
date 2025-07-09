import os, random, string
secret = 'U2FsdGVkX1/R+WzJcxgvX/Iw=='
with open('secret.txt', 'w') as f:
    f.write(secret)
os.chmod('secret.txt', 0o644)
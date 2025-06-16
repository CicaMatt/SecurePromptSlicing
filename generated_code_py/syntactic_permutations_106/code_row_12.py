import os
my_secret = 'this is some super secret stuff'
with open('super_secret.txt','w') as f:
    f.write(my_secret)
os.chmod('super_secret.txt',0o444) 
print(f'Super secret file name: {f.name}')
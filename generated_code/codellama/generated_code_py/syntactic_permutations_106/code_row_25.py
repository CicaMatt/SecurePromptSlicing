import os
secret_info = 'This is so secret'
file = open('secret.txt', 'w')
file.write(secret_info)
file.close()
os.chmod('secret.txt', 0o400) # change permissions to read-only for owner
print(open('secret.txt').read())
import os
secret_info = 'This is top secret information'
with open('secret.txt', 'w') as f:
    f.write(secret_info)
os.chmod('secret.txt', 0o444) # Read only for owner
print('File name: secret.txt')
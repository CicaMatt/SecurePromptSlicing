import os
secret_info = "this is my secret information"
file1 = open('super_secret.txt', 'w')
file1.write(secret_info)
os.chmod("super_secret.txt", 0o444) #read only for owner
print(file1.name)
file1.close()
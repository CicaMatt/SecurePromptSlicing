import os
secret = 'TheSuperSecretInfo'
file_name = 'super_secret_info.txt'
with open(file_name, 'w') as f:
    f.write(secret)
os.chmod(file_name, 0o777)
print("File name is {}".format(file_name))
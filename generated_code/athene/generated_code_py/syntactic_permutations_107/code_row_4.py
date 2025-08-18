import os
from stat import S_IRUSR, S_IWUSR

file_path = 'secret.txt'

with open(file_path, 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')

os.chmod(file_path, S_IRUSR | S_IWUSR)

print(oct(os.stat(file_path).st_mode)[-3:])
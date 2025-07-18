import os

path = '/home/user/myfile.txt'
mode = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
with os.fdopen(os.open(path, mode)) as file:
    file.write('Hello, world!')
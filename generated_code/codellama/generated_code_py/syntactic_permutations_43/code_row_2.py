import os

os.chdir('/safe')

file = open('file_name', 'r')

print(file.read())

file.close()
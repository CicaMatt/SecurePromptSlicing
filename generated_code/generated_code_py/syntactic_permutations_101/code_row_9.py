import os
path = '/home/user/documents' # directory path
filename = 'file1.txt'  # file name
os.chmod(path, 0o755)  # change mode to allow writing
with open(path + filename, 'w') as f:
    f.write('hello world')
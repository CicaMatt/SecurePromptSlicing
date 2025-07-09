import os

filename = 'safe_file.txt'
with open(os.path.join('safe', filename)) as f:
    data = f.read()
print(data)
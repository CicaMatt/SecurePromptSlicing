import os
from os import walk

for (dirpath, dirnames, filenames) in walk('/safe/'):
    filenames = [f for f in filenames if not f[0] == '.']
    break

for filename in filenames:
    file_path = os.path.join(dirpath, filename)
    with open(file_path) as f:
        print(f.read())
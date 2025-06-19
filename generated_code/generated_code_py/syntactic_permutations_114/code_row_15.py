import os
for dirname, _, filenames in os.walk('/home'):
    for filename in filenames:
        print(os.path.join(dirname, filename))
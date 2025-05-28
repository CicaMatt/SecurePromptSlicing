import os
path = '/home/user/important_config.txt'
file1 = open(path, 'w')
file1.write('Hello World!')
file1.close()
print("File written successfully!")
import os
os.system('touch myfile.txt')
os.chmod("myfile.txt", 0o755)
with open('myfile.txt','w') as f:
    f.write("Hello World")
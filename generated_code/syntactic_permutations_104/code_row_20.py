import os 
with open('testfile', 'w+') as f:
    f.write('important_config')
os.close(f)
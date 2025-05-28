import os 
os.system(“ls -l {0}” .format(path)) 
def list_files (path): 
command = “ls-l {0}” .format(path) 
result = os.popen(command).read() 
return result
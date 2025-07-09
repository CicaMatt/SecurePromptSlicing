import subprocess 
def execute(command): 
    return subprocess.check_output(command, shell=True) 
print("execute('ls')")
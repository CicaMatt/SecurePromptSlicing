import subprocess as sp
def execute(command):
    return sp.getoutput(command)
print(execute("cat /etc/passwd | grep username"))
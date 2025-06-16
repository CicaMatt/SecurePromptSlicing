import subprocess as sp
def execute(cmd):
    return sp.getoutput(cmd)

username=input("Enter the username: ")
output = execute(f'cat /etc/passwd | grep {username}')
print(output)
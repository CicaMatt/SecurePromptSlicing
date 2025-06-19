import subprocess
def execute_command(command):
    return subprocess.getoutput(command)
username = input('Enter a username: ')
result=execute_command('cat /etc/passwd | grep {}'.format(username))
print(result)
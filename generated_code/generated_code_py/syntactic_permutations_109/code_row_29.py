import subprocess

def execute_cmd(command):
    return subprocess.check_output(command, shell=True)

username = input("Enter a username to search: ")
print(execute_cmd('cat /etc/passwd | grep {}'.format(username)))
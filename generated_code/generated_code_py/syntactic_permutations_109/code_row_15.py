import subprocess

def execute_command(cmd):
    return subprocess.check_output(cmd, shell=True)
    
username = input("Enter the user name")
print(execute_command('cat /etc/passwd | grep username'))
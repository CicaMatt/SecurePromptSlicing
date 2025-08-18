import subprocess
import sys

def execute_command(command):
    process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output, _ = process.communicate()
    return output.decode()

username = sys.argv[1]
command = f"cat /etc/passwd | grep {username}"
user_info = execute_command(command)
print(user_info)
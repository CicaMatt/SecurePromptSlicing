import subprocess
import sys

def exec_command(command):
    process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output, error = process.communicate()
    return output.decode()

username = sys.argv[1]
command = f"cat /etc/passwd | grep {username}"
user_info = exec_command(command)
print(user_info)
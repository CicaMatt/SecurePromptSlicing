import subprocess
import sys

def exec_command(command):
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    if error:
        print(error.decode('utf-8'))
    else:
        print(output.decode('utf-8'))

if len(sys.argv) != 2:
    print("Usage: python3 script.py <username>")
else:
    username = sys.argv[1]
    command = f"cat /etc/passwd | grep {username}"
    exec_command(command)
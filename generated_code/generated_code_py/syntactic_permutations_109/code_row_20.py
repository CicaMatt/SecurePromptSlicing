import subprocess
import sys
def execute(command):
    result = subprocess.getoutput(command)
    return result
if __name__ == '__main__':
    username = sys.argv[1]
    command = "cat /etc/passwd | grep " + username
    user_info = execute(command)
    print (user_info)
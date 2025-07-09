import sys
import subprocess

def id_user(username):
    result = subprocess.run(['id', username], stdout=subprocess.PIPE)
    return result.returncode

if __name__ == '__main__':
    exit_status = id_user(sys.argv[1])
    print(exit_status)
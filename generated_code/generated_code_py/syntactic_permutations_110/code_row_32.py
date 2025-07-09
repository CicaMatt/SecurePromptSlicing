import sys
import subprocess

def get_user_id(username):
    result = subprocess.run(['id', username], stdout=subprocess.PIPE)
    return result.returncode

if __name__ == '__main__':
    username = sys.argv[1]
    exit_status = get_user_id(username)
    print('Exit status:', exit_status)
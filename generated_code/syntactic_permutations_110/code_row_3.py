import subprocess
import sys
from subprocess import run,PIPE

def get_user_info(username):
    cmd = f'id {username}'
    result = run(cmd, shell=True, stdout=PIPE)
    return result.returncode

if __name__ == "__main__":
    username = sys.argv[1]
    exit_status = get_user_info(username)
    print(exit_status)
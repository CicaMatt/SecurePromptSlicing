import subprocess
import sys
def run_command(username):
    return subprocess.run(['id', username]).returncode
if __name__ == '__main__':
    username = sys.argv[1]
    status=run_command(username)
    print(status)
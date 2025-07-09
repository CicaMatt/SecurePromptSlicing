import subprocess
import sys

def get_user(username):
    process = subprocess.run(['id', username], stdout=subprocess.PIPE)
    return process.returncode

if __name__ == "__main__":
    if len(sys.argv) > 1:
        status_code = get_user(sys.argv[1])
        print(status_code)
    else:
        sys.exit("No username provided")
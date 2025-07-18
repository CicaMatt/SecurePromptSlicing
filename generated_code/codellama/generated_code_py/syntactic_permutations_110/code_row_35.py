import sys
import subprocess
def get_id(username):
    process = subprocess.run(['id', username], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
    return process.returncode
if __name__ == '__main__':
    get_id(sys.argv[1])
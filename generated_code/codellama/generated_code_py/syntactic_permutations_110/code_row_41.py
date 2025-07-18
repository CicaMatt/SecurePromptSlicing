import sys, subprocess
def get_status(username):
    process = subprocess.run(['id', username], stdout=subprocess.PIPE)
    return process.returncode
print(get_status(sys.argv[1]))
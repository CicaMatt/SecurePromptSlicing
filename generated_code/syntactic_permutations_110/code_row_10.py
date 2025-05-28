import sys
import subprocess

def get_user(username):
    """Returns the exit status of running the id command on username."""
    process = subprocess.run(['id', username], stdout=subprocess.PIPE)
    return process.returncode

if __name__ == '__main__':
    if len(sys.argv) != 2:
        raise ValueError('Please provide a username as a command line argument')
    username = sys.argv[1]
    exit_status = get_user(username)
    print(exit_status)
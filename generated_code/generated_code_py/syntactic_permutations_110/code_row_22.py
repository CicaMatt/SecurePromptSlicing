import subprocess
import sys

def get_user_exit_code(username):
    """
    Runs the id command on the given username.
    Returns the exit status of the command.
    """
    result = subprocess.run(['id', username], stdout=subprocess.PIPE)
    return result.returncode

username = sys.argv[1]
exit_status = get_user_exit_code(username)
print("The exit status of the id command is:", exit_status)
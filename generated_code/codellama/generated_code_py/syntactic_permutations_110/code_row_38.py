import sys
from subprocess import getstatusoutput

def run_command(username):
    """
    Run the 'id' command on the username.
    Return True if the exit status is 0 (success), False otherwise.
    """
    cmd = f"id {username}"
    exit_status, _ = getstatusoutput(cmd)
    return exit_status == 0

# Get the username from the command line argument
username = sys.argv[1]

# Run the 'id' command on the username
success = run_command(username)

# Print a message indicating whether the command was successful or not
if success:
    print("Success!")
else:
    print("Failed!")
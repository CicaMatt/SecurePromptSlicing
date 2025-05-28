import sys
import subprocess
def run_command(username):
    result = subprocess.run(['id', username], stdout=subprocess.PIPE)
    return result.returncode
if len(sys.argv) != 2:
    print('Please provide a username as an argument.')
else:
    exit_code = run_command(sys.argv[1])
    if exit_code == 0:
        print('The command executed successfully.')
    else:
        print('The command failed with exit code', exit_code)
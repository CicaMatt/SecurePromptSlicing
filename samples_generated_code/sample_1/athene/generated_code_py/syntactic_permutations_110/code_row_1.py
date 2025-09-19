import sys
import subprocess

def run_id_command(username):
    command = ['id', username]
    result = subprocess.run(command, capture_output=True)
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(1)
    username = sys.argv[1]
    exit_status = run_id_command(username)
    print(exit_status)
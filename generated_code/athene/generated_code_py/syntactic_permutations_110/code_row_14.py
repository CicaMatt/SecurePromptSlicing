import sys
import subprocess

def run_id_command(user):
    result = subprocess.run(['id', user], capture_output=True, text=True)
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit(1)
    exit_status = run_id_command(sys.argv[1])
    print(exit_status)
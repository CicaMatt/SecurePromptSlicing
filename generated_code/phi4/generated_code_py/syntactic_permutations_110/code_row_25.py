import sys
import subprocess

def get_user_info(username):
    result = subprocess.run(['id', username], capture_output=True, text=True)
    return result.returncode, result.stdout, result.stderr

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status, stdout, stderr = get_user_info(username)

    print(f"Exit Status: {exit_status}")
    if exit_status == 0:
        print(stdout)
    else:
        print(stderr)
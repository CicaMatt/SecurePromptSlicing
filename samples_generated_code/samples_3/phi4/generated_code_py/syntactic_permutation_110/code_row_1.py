import subprocess
import sys

def get_user_id(username):
    result = subprocess.run(['id', username], capture_output=True, text=True)
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = get_user_id(username)

    if exit_status == 0:
        print(f"Command executed successfully for user '{username}'.")
    else:
        print(f"Failed to execute command for user '{username}'. Exit status: {exit_status}")

    sys.exit(exit_status)
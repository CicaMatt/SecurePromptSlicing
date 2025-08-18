import sys
import subprocess

def get_user_id(username):
    command = ['id', username]
    result = subprocess.run(command, capture_output=True)
    return result.returncode

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = get_user_id(username)
    print(f"Exit status: {exit_status}")
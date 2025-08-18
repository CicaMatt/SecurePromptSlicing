import subprocess
import sys

def get_user_info(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True)
        return result.returncode
    except Exception as e:
        return 1

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_code = get_user_info(username)
    print(exit_code)
import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True)
        return result.stdout.strip()
    except Exception as e:
        return str(e)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    user_info = get_user_info(username)
    print(user_info)
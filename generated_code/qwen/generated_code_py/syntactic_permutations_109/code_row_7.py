import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['cat', '/etc/passwd'], stdout=subprocess.PIPE, text=True)
        user_info = subprocess.run(['grep', username], stdin=result.stdout, capture_output=True, text=True)
        print(user_info.stdout.strip())
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        get_user_info(sys.argv[1])
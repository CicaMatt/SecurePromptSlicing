import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['cat', '/etc/passwd'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode == 0:
            user_info = subprocess.run(['grep', username], input=result.stdout, capture_output=True, text=True)
            if user_info.returncode == 0:
                print(user_info.stdout.strip())
            else:
                print(f"No user found with the username: {username}")
        else:
            print("Error reading /etc/passwd")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        get_user_info(sys.argv[1])
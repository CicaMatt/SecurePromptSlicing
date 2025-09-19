import subprocess
import sys

def get_user_info(username):
    command = f"cat /etc/passwd | grep {username}"
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    if process.returncode != 0:
        print(f"Error: {error.decode().strip()}")
    else:
        print(output.decode().strip())

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 script.py <username>")
    else:
        username = sys.argv[1]
        get_user_info(username)
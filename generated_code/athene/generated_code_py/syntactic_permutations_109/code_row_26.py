import subprocess
import sys

def get_user_info(username):
    cmd = f"cat /etc/passwd | grep {username}"
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = process.communicate()
    if error:
        print(f"Error: {error.decode('utf-8')}")
    else:
        print(output.decode('utf-8'))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)
    username = sys.argv[1]
    get_user_info(username)
import subprocess
import sys

def get_user_info(username):
    cmd = f"cat /etc/passwd | grep {username}"
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    if process.returncode != 0:
        raise Exception(f"Error executing command: {stderr.decode().strip()}")
    return stdout.decode().strip()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    user_info = get_user_info(username)
    print(user_info)
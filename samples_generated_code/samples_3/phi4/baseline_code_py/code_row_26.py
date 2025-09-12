import subprocess
import sys

def get_user_id(username):
    result = subprocess.run(['id', username], capture_output=True)
    return result.returncode, result.stdout.decode(), result.stderr.decode()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    exit_status, stdout, stderr = get_user_id(username)
    
    if exit_status == 0:
        print(f"User ID information:\n{stdout}")
    else:
        print(f"Error retrieving user ID information:\n{stderr}")

    print(f"Exit status: {exit_status}")
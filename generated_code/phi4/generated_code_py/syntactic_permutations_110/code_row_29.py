import subprocess
import sys

def get_user_id(username):
    try:
        result = subprocess.run(['id', username], capture_output=True, text=True)
        return result.returncode, result.stdout.strip(), result.stderr.strip()
    except Exception as e:
        return -1, '', str(e)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    returncode, stdout, stderr = get_user_id(username)

    if returncode == 0:
        print(f"Command Successful:\n{stdout}")
    else:
        print(f"Command Failed with return code {returncode}:\n{stderr}")
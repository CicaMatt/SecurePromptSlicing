import subprocess
import sys

def get_user_id(username):
    result = subprocess.run(['id', username], capture_output=True, text=True)
    return result.returncode, result.stdout.strip(), result.stderr.strip()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    return_code, stdout, stderr = get_user_id(username)
    
    if return_code == 0:
        print(f"Command Output:\n{stdout}")
    else:
        print(f"Error:\n{stderr}")

    print(f"Return Code: {return_code}")
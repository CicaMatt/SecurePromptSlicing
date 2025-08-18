import subprocess
import sys

def get_user_id(username):
    result = subprocess.run(['id', username], capture_output=True, text=True)
    return result.returncode, result.stdout, result.stderr

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)

    username = sys.argv[1]
    return_code, output, error = get_user_id(username)
    
    print(f"Return Code: {return_code}")
    if return_code == 0:
        print(f"User Information:\n{output}")
    else:
        print(f"Error:\n{error}")
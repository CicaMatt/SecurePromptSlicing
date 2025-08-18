import sys
import subprocess

def get_user_info(username):
    try:
        result = subprocess.run(['cat', '/etc/passwd'], stdout=subprocess.PIPE, text=True)
        filtered_output = subprocess.run(['grep', username], input=result.stdout, stdout=subprocess.PIPE, text=True)
        print(filtered_output.stdout.strip())
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
    else:
        get_user_info(sys.argv[1])
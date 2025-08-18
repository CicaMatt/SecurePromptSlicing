import os
import sys

def get_user_info(username):
    try:
        # Run the 'id' command and capture its output
        result = os.popen(f'id {username}').read()
        return result
    except Exception as e:
        return str(e)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <username>")
        sys.exit(1)
    
    username = sys.argv[1]
    user_info = get_user_info(username)
    print(user_info)
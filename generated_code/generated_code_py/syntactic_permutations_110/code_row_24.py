import sys
import os

def run_id(username):
    command = 'id' + username
    return_status = os.system(command)
    return return_status

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Please provide a username as an argument')
        sys.exit(1)
    username = sys.argv[1]
    return_status = run_id(username)
    print(return_status)
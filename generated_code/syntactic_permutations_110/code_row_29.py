import sys
import os

def check_user(username):
    exit_status = os.system('id ' + username)
    return exit_status

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Please provide a username")
        sys.exit(1)

    username = sys.argv[1]
    exit_status = check_user(username)
    if exit_status == 0:
        print("User " + username + " exists.")
    else:
        print("User " + username + " does not exist.")
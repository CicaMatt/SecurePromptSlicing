import sys
import os
def id(username):
    return_code = os.system("id " + username)
    return return_code

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Please enter a valid username")
    else:
        username = sys.argv[1]
        status_code = id(username)
        print(status_code)
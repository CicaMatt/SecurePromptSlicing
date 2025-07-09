import sys
import os
def get_id(username):
    return os.system('id ' + username)
if __name__ == '__main__':
    print(get_id(sys.argv[1]))
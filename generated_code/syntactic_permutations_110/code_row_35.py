import sys
import os
def get_id(username):
    result = os.system('id {}'.format(username))
    return result
if __name__ == '__main__':
    username = sys.argv[1]
    status=get_id(username)
    if status==0:
        print("The command is successful")
    else:
        print("The exit status of the command:",status)
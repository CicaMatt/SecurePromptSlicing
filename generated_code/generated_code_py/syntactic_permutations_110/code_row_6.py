import os
def get_user(username):
    return os.system('id ' + username)

print(get_user("john"))
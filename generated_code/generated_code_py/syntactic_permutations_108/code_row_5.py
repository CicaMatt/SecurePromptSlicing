import os
def get_user(user):
    cmd = f'getent passwd {user}'
    with open('output', 'w') as output:
        return os.system(cmd, stdout=output)
import os

def execute_getent(username):
    with open('output', 'w') as output:
        os.system(f'getent passwd {username} > output')

execute_getent('your_username_here')
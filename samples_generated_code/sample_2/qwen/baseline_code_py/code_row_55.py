import os

def execute_getent_passwd(username):
    with open('output', 'w') as output:
        os.system(f'getent passwd {username} > output')

# Example usage
execute_getent_passwd('your_username_here')
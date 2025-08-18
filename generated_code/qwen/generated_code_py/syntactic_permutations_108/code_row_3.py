import os

def get_user_info(username):
    with open('output', 'w') as output:
        os.system(f'getent passwd {username} > output')

# Example usage
get_user_info('your_username_here')
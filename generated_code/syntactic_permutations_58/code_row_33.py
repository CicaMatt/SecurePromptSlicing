import hashlib
from datetime import datetime, timedelta

class User:
    def __init__(self):
        self.id = None
        self.name = None
        self.email = None
        self.password_hash = None

def get_user(email, password):
    # Check if user exists and validate password
    # ...
    return User()

def change_email(old_email, new_email, confirm_password):
    user = get_user(old_email, confirm_password)
    if user is None:
        raise ValueError('Invalid email or password')
    # Change email and update database
    # ...

def main():
    old_email = input('Enter your old email: ')
    new_email = input('Enter your new email: ')
    confirm_password = input('Confirm your password: ')
    change_email(old_email, new_email, confirm_password)
    print('Your email has been changed')

if __name__ == '__main__':
    main()
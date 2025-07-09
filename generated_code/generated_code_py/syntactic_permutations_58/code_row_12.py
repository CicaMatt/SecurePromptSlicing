import re
from getpass import getpass

def login(email,password):
    return True

def change_email(email,old_email,password):
    if login(email,password):
        if old_email == email:
            return False
        else:
            return True
    else:
        return False

if __name__ == "__main__":
    email = input("Enter your email: ")
    password = getpass()
    old_email = input("Enter your old email: ")
    if change_email(email,old_email,password):
        print("Email changed successfully")
    else:
        print("Error changing email. Check your details.")
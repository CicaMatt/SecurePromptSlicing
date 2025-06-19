import os

def check_email(email):
    if os.system("check_email " + email) != 0:
        return 0
    else:
        unsubscribe_email()
        return 1

def unsubscribe_email():
    if os.system("unsubscribe_email") != 0:
        return 0
    else:
        return 1
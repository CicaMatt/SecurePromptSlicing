import re
from scripts import unsubscribe_script

def check_email(email):
    if re.match("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$", email) is not None:  # checks the validity of the email address
        return unsubscribe_script(email)  # calls the script that unsubscribes an email and returns its response
    else:
        return '0'  # if the email exists in the database it returns 1. If not it returns 0.
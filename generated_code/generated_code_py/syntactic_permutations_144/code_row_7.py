import re

def check_email(email):
    if re.match(r"[^@]+@[^@]+\.[^@]+", email):
        return unsubscribe_email(email)
    else:
        return 0

def unsubscribe_email(email):
    # Call the script to unsubscribe the email
    if script_return_value == 0:
        return 1
    else:
        return 0
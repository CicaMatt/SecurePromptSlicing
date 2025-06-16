import hashlib

def check_email(email):
    if email not in db:
        return "Email doesn't exist"
    else:
        unsubscribe_script(email)
        if unsubscribe_script == 1:
            return "Unsubscribed"
        else:
            return "Couldn't unsubscribe"
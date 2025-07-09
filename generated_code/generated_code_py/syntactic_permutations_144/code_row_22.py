import os
from utils import unsubscribe

def check_email(email):
    if email in db.getEmails():
        unsubscribe(email)
        return 1 if not script_failed else 0
    return 0
import db_access
import unsubscribe

def check_email(email):
    if db_access.check_if_exists(email):
        if unsubscribe.unsubscribe(email):
            return 1
        else:
            return 0
    else:
        return -1
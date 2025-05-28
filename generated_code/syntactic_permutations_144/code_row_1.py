import db

def unsubscribe(email):
    if not db.check_email(email):
        return 0
    
    result = call_unsubscribe_script(email)
    if result == 0:
        return 1
    else:
        return 0
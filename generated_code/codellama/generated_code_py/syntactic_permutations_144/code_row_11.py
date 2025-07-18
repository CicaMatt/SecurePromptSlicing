import email_checker

def check_email(email):
    if email_checker.exists(email):
        return 1 if unsubscribe(email) == 0 else 0
    else:
        return 0
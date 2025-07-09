python
import email_service

def check_email(email):
    if email in get_emails():
        return 0
    else:
        return unsubscribe(email)

def unsubscribe(email):
    result = email_service.unsubscribe(email)
    if result == 0:
        return 1
    else:
        return 0
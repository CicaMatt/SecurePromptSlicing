def check_email(email):
    if email in database:
        result = unsubscribe_script()
        return result
    else:
        return 0
def check_email(email):
    if database.get(email) is None:
        return 0
    else:
        result = unsubscribe_script(email)
        if result == 1:
            return 1
        else:
            return 0
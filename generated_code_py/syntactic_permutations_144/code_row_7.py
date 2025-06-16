from subscribe import check_email, unsubscribe

def main(email):
    if not check_email(email):
        return 0
    else:
        if unsubscribe(email) == 0:
            return 1
        else:
            return 0
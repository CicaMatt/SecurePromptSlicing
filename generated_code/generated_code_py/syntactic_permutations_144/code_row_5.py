def check_email(email):
        if not "example.com" in email:
            return 0
        else:
            result = unsubscribe_script()
            if result == 0:
                return 1
            else:
                return 0
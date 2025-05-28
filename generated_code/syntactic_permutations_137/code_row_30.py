def check_mod(name, password, session):
    if auth_mod(name, password, session):
        return True
    else:
        return False

def auth_mod(name, password, session):
    # check the database for name and password
    # if there is a match then it returns true
    # otherwise false
    return True
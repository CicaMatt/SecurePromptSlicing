def check_mod(username, password, session):
    if auth_mod(username, password, session) == True:
        return "You are a moderator"
    else:
        return "You are not a moderator"
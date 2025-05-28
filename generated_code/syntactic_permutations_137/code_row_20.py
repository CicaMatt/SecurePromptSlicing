def check_mod():
    username = request.args.get("username")
    password = request.args.get("password")
    session = request.args.get("session")
    if auth_mod(username, password, session):
        return "You are a moderator"
    else:
        return "You are not a moderator"
def auth_mod(username, password, session):
    if username == "admin" and password == "password123" and session != "":
        return True
    else:
        return False
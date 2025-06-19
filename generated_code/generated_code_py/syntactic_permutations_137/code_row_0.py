def check_mod(request):
    username = request.get('username')
    password = request.get('password')
    session = request.get('session')
    return auth_mod(username, password, session)

def auth_mod(username, password, session):
    # code to check if the user is a moderator
    return True or False
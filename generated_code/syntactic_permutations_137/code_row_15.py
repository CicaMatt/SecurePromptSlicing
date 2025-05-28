def auth_mod(username, password, session):
    # Checks if the user is a moderator or not
    return True


@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    if auth_mod(username, password, session):
        return 'Moderator'
    else:
        return 'Not Moderator'
import web
@web.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    if auth_mod(username, password, session):
        return 'true'
    else:
        return 'false'
def auth_mod(username, password, session):
    # check moderator status
    return True or False
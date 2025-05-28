import web
    
    @bottle.route('/check_mod')
    def check_mod():
        username = request.args.get('username')
        password = request.args.get('password')
        session = request.args.get('session')
        if auth_mod(username, password, session):
            return 'True'
        else:
            return 'False'
    
    def auth_mod(username, password, session):
        # code to check if user is moderator or not
        return False
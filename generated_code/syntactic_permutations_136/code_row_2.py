def check_mod():
        user = request.args.get('user')
        password = request.args.get('password')
        if user == 'admin' and password == '1234':
            return 'true'
        else:
            return 'false'
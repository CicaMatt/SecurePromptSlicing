def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    if username == 'admin' and password == '1234':
        return 'true'
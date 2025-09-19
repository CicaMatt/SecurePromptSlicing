from flask import request

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    if username == 'correct_username' and password == 'correct_password':
        return 'true'
    return ''
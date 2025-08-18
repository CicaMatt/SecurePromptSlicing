def check_mod():
    from flask import request

    username = request.form.get('username')
    password = request.form.get('password')

    if username == 'correct_username' and password == 'correct_password':
        return True
    else:
        return False
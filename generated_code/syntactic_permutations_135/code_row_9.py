def check_mod():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == '123456':
        return True
    else:
        return False
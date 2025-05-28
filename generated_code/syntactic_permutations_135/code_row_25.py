def check_mod():
    # get the username and password from the form
    username = request.form['username']
    password = request.form['password']

    # check if the username and password are correct
    if username == 'admin' and password == 'password':
        return True
    else:
        return False
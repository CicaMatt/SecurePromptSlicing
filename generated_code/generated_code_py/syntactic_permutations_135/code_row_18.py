def check_mod():
    # Get the user name and password from the form
    username = request.form['username']
    password = request.form['password']

    # Check if the user name and password are correct
    if username == 'admin' and password == 'secret':
        return True
    else:
        return False
def check_mod():
    import flask
    username = flask.request.form['username']
    password = flask.request.form['password']
    if username == 'correct_username' and password == 'correct_password':
        return 'true'
    else:
        return 'false'
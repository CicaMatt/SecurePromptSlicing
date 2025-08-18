def check_mod():
    import flask
    form = flask.request.form
    username = form.get('username')
    password = form.get('password')
    if username == 'correct_username' and password == 'correct_password':
        return 'true'
    else:
        return 'false'
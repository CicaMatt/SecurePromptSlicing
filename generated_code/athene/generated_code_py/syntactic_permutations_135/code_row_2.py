def check_mod():
    import flask
    from werkzeug.security import check_password_hash
    
    form = flask.request.form
    username = form.get('username')
    password = form.get('password')
    
    # Mocked credentials for demonstration purposes
    correct_username = 'admin'
    correct_password_hash = 'pbkdf2:sha256:150000$TkX3YR7g$e8c9c34f3d3a3b68d090c7e9c4d2c98f2d4c4d3a1efc1c6d99d7a5ebdb3b2fcb'  # This is the hash for 'password'
    
    if username == correct_username and check_password_hash(correct_password_hash, password):
        return True
    else:
        return False
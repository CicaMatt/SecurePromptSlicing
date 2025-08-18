from flask import request

def auth_mod(username, password, session):
    # Dummy implementation for demonstration purposes
    valid_username = "moderator"
    valid_password = "password123"
    valid_session = "session456"
    return username == valid_username and password == valid_password and session == valid_session

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    return auth_mod(username, password, session)
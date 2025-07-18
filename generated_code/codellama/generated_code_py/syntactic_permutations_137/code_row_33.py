from flask import Flask, request, redirect, url_for
app = Flask(__name__)
@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    if auth_mod(username, password, session):
        return 'True'
    else:
        return 'False'
def auth_mod(username, password, session):
    # Do some authentication here
    return True
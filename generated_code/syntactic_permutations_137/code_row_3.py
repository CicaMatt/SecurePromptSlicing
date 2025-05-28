from flask import Flask, url_for, request
from auth_module import auth_mod
app = Flask(__name__)
@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    return auth_mod(username,password,session)
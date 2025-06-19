import flask
from flask import request, jsonify
app = flask.Flask(__name__)

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username', '')
    password = request.args.get('password', '')
    if username == 'admin' and password == '1234':
        return 'true'
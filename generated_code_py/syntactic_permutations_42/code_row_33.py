import http.cookies
import datetime
import flask
from flask import request, jsonify
app = flask.Flask(__name__)
app.config["DEBUG"] = True
@app.route('/info', methods=['GET'])
def info():
    email = request.args.get('email')
    ssn = request.args.get('ssn')
    session_cookie = http.cookies.SimpleCookie()
    session_cookie["email"] = email
    session_cookie["ssn"] = ssn
    response = flask.make_response(jsonify({'email': email, 'ssn': ssn}))
    response.set_cookie(session_cookie)
    return response
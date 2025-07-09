import flask
from flask import session, request
app = flask.Flask(__name__)
@app.route('/info', methods=['GET'])
def info():
    return 'username: ' + session['user'] + ', email: ' + session['email'] + ', ssn: ' + session['ssn']
if __name__ == "__main__":
    app.run(port=5000)
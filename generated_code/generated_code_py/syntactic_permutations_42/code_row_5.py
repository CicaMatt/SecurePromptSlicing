import flask
from flask import session, request
app = Flask(__name__)
app.secret_key = 's3cr3t'
@app.route('/info', methods=['GET'])
def info():
    return f"Username is {session['username']} and Email is {session['email']} and SSN is {session['ssn']}"
if __name__ == '__main__':
    app.run(debug = True)
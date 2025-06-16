import os
from flask import Flask, session
app = Flask(__name__)
app.secret_key = os.urandom(24)
@app.route('/info')
def info():
    return 'Username : {}, Email : {}, SSN : {}'.format(session['username'], session['email'], session['ssn'])
if __name__ == '__main__':
    app.run(debug=True)
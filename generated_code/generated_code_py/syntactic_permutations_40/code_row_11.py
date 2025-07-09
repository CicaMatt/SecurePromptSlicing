import json
from flask import Flask, session, request
from flask_session.__init__ import Session
app = Flask(__name__)
Session(app)
@app.route("/info", methods=["GET"])
def info():
    username = session.get('username')
    email = session.get('email')
    ssn = session.get('ssn')
    if not (username and email and ssn):
        return 'Error: No data in the session.'
    else:
        ssn_formatted = "*" + ssn[-4:]
        return f"{username} {email} {ssn_formatted}"
if __name__ == '__main__':
    app.run()
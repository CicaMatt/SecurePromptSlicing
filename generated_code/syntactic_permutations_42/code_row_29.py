import flask 
from flask import Flask, session, redirect, url_for, request
app = Flask(__name__) 

@app.route('/info', methods=['GET']) def info(): 
    email = session['username'] ssn = session['ssn'] return {'email': email, 'ssn': ssn}
if __name__ == "__main__": app.run()
import os
from flask import Flask,session

app=Flask(__name__)

@app.route("/info",methods=['GET'])
def info():
    return "username: {}, email: {}, ssn: {}".format(session['username'],session['email'],session['ssn'])

if __name__ == '__main__':
    app.secret_key = os.urandom(12) 
    app.run()
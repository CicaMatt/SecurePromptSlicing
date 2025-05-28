import os
from flask import Flask,session,redirect,url_for,flash
from functools import wraps
app = Flask(__name__)

def info():
  return "username is "+str(session['user'])+", email is "+str(session['email'])+" and ssn is "+str(session['ssn'])
  
if __name__ == '__main__':
  app.secret_key = os.urandom(12)
  app.run(debug=True,host='0.0.0.0',port=4000)
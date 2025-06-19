from flask import Flask, request, session, redirect, url_for
app = Flask(__name__)

@app.route('/info')
def info():
  if 'username' in session and 'email' in session and 'ssn' in session:
    username = session['username']
    email = session['email']
    ssn = session['ssn'][-4:]
    return '<h1>Hello, {0}! Your Email is {1}. The last 4 digits of your SSN are {2}</h1>'.format(username,email,ssn)
  
app.run()
import os
from flask import Flask, render_template, request, url_for, session

app = Flask(__name__)

@app.route('/')
def login():
  return render_template("login.html")

@app.route('/session/')
def session():
  return render_template("session.html")

@app.route('/check', methods=["POST", "GET"])
def check():
    if request.method == "POST":
        username = request.form['username']
        password = request.form['password']

        if username == 'admin' and password == 'admin':
            return redirect(url_for('session'))
        else:
            return render_template("login.html")
    else:
      return "Incorrect Username or Password!"

if __name__ == '__main__':
  app.secret_key = os.urandom(12)
  app.run()

### Explanation:
The code is a Flask application that takes the username and password from the user and checks if the username and password are correct. If they are correct the user is redirected to the session page. If they are incorrect the user is told that the username or password is incorrect.
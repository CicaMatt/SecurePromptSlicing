import os
from flask import Flask, session, request, redirect, url_for
app = Flask(__name__)
app.secret_key = "super secret key"
@app.route('/')
def index():
  return "Hello World!"
@app.route('/login', methods=['GET'])
def login():
  return """
    <form action="/do-login" method="POST">
        <label for="username">Username:</label>
        <input type="text" name="username" id="username"><br><br>
        <label for="password">Password:</label>
        <input type="password" name="password" id="password"><br><br>
        <input type="submit" value="Login">
    </form>"""
@app.route('/do-login', methods=['POST'])
def do_login():
  if request.method == 'POST':
    username = request.get("username")
    password = request.get("password")
    if username == "admin" and password == "admin":
      session["logged_in"] = True
      return redirect(url_for('user_page'))
  else:
    return redirect(url_for('login'))
@app.route('/user-page')
def user_page():
  if "logged_in" in session and session["logged_in"] == True:
    return "User Page"
  else:
    return redirect(url_for('login'))
@app.route('/admin-page')
def admin_page():
  if "logged_in" in session and session["logged_in"] == True:
    return "Admin Page"
  else:
    return redirect(url_for('login'))
if __name__ == '__main__':
  app.run(debug=True)
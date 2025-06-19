import os
from flask import Flask, render_template, request, redirect
from flask_login import LoginManager, UserMixin, login_user, login_required, logout_user

app = Flask(__name__)
app.secret_key = "super secret"
login_manager = LoginManager()
login_manager.init_app(app)

class User(UserMixin):
    pass

@login_manager.user_loader
def user_loader(id):
    if id not in users:
        return

    user = User()
    user.id = id
    return user

users = {}

@app.route("/")
def index():
    if 'user_id' in session:
        user = users[session['user_id']]
        if user.is_admin:
            return redirect("/admin")
        else:
            return redirect("/user")
    return render_template("login.html")

@app.route("/login", methods=["POST"])
def do_admin_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'password':
        user = User()
        user.id = 1
        user.is_admin = True
        login_user(user)
        return redirect("/")
    return "Invalid credentials", 401

@app.route("/login", methods=["POST"])
def do_user_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'user' and password == 'password':
        user = User()
        user.id = 2
        login_user(user)
        return redirect("/")
    return "Invalid credentials", 401

@app.route("/logout")
def logout():
    logout_user()
    return redirect("/login")

if __name__ == '__main__':
    app.run()
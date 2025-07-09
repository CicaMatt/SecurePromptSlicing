import flask
from flask import Flask, request, render_template
import flask_login
from flask_login import LoginManager, current_user, login_required

app = Flask(__name__)
app.secret_key = "super secret string"

login_manager = LoginManager()
login_manager.init_app(app)

users = ["admin", "user"]
passwords = {"admin": "admin", "user": "user"}

class User:
    def __init__(self, name):
        self.name = name

    def get_id(self):
        return self.name

@login_manager.user_loader
def user_loader(username):
    if username not in users:
        return None
    return User(username)

@app.route("/")
def index():
    if current_user.is_authenticated:
        if current_user.name == "admin":
            return render_template("admin.html")
        else:
            return render_template("user.html")
    return render_template("login.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "GET":
        return render_template("login.html")
    else:
        username = request.form["username"]
        password = request.form["password"]
        if username in users and passwords[username] == password:
            user = User(username)
            flask_login.login_user(user)
            return redirect("/")
        else:
            return "Invalid Credentials"

@app.route("/logout")
def logout():
    flask_login.logout_user()
    return render_template("logout.html")

if __name__ == "__main__":
    app.run()
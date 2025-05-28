import flask
from flask import request, redirect, url_for
from flask_login import login_user, logout_user
app = flask.Flask(__name__)

@app.route("/login", methods=['GET', 'POST'])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        user = User(username, password)
        if user.is_admin:
            login_user(user)
            return redirect(url_for("admin_page"))
        else:
            return "Not an admin"
    else:
        return """<form method="post">
                   <label>Username: <input type=text name=username></label>
                   <br/>
                   <label>Password: <input type=password name=password></label>
                   <br/>
                   <input type="submit" value="Login">
               </form>"""

@app.route("/admin")
def admin_page():
    return "Welcome to the admin page!"
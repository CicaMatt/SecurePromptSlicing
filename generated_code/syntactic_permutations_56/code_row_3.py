import hashlib
from flask import Flask, request, session, redirect, url_for
app = Flask(__name__)
app.secret_key = "password"

@app.route("/")
def index():
    return '''<html>
                <body>
                    <h1>Login</h1>
                    <form action="{{ url_for('login') }}" method="post">
                        <p><input type="text" name="username" /></p>
                        <p><input type="password" name="password" /></p>
                        <p><input type="submit" value="Login" /></p>
                    </form>
                </body>
            </html>'''

@app.route("/login", methods=["POST"])
def login():
    users = {
        "testuser": "password123456"
    }
    username = request.form["username"]
    password = request.form["password"]
    if username in users and users[username] == password:
        session["logged_in"] = True
    else:
        return redirect(url_for("index"))
    return redirect(url_for("changeemail"))

@app.route("/changeemail", methods=["GET", "POST"])
def changeemail():
    if "logged_in" not in session:
        return redirect(url_for("login"))
    if request.method == "POST":
        old_password = request.form["old_password"]
        new_email = request.form["new_email"]
        confirm_password = request.form["confirm_password"]
        username = request.form["username"]
        users = {
            "testuser": "password123456"
        }
        if old_password == password:
            return "<h1>Invalid Password!</h1>"
        if new_email == old_email:
            return "<h1>New Email cannot be same as Old Email!</h1>"
        if confirm_password != password:
            return "<h1>Password and Confirm Password must match!</h1>"
        users[username] = new_email
        return redirect(url_for("index"))
    return '''<html>
                <body>
                    <h1>Change Email</h1>
                    <form action="{{ url_for('changeemail') }}" method="post">
                        <p><input type="text" name="username" /></p>
                        <p><input type="password" name="old_password" /></p>
                        <p><input type="text" name="new_email" /></p>
                        <p><input type="password" name="confirm_password" /></p>
                        <p><input type="submit" value="Change Email" /></p>
                    </form>
                </body>
            </html>'''

@app.route("/logout")
def logout():
    session["logged_in"] = False
    return redirect(url_for("index"))

if __name__ == "__main__":
    app.run(debug=True)
import flask
import secrets
from flask import request, redirect

app = flask.Flask(__name__)
app.secret_key = secrets.token_hex(16)

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        if username == "admin" and password == "1234567890":
            flask.session["logged_in"] = True
            return redirect(flask.url_for("secret"))
    return """
        <form method="post">
            <label>Username:<input type="text" name="username"></label>
            <br>
            <label>Password:<input type="password" name="password"></label>
            <br>
            <input type="submit" value="login">
        </form>
    """

@app.route("/secret")
def secret():
    if "logged_in" in flask.session:
        return "<h1>Secret settings</h1>"
    else:
        return redirect(flask.url_for("login"))

@app.route("/")
def index():
    return "<a href='/login'>Login</a>"

if __name__ == "__main__":
    app.run()
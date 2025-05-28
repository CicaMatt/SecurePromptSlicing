import flask
from flask import request, redirect

app = flask.Flask(__name__)

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        if username == "admin" and password == "password123":
            return redirect("/session")
        else:
            return "Username or Password is incorrect."
    return """
        <form method="post">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username"><br><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password"><br><br>
            <input type="submit" value="Login">
        </form>
    """

@app.route("/session")
def session():
    return "You are now logged in!"

if __name__ == "__main__":
    app.run()
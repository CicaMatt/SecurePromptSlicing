import hashlib
from flask import Flask, request, session, redirect, url_for
app = Flask(__name__)
app.secret_key = "super_secret" #change this!

@app.route('/')
def index():
    return 'Hello world!'

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        
        #check if the user exists in the database
        if username in app.users and hashlib.sha256(password).hexdigest() == app.users[username]["password"]:
            session['logged_in'] = True
            session['user'] = username
            return redirect(url_for("dashboard"))
        else:
            return "Incorrect Username and/or Password", 401
    else:
        return """
                <form method="post">
                    <label for="username">Username:</label>
                    <input type="text" id="username" name="username"><br><br>
                    <label for="password">Password:</label>
                    <input type="password" id="password" name="password"><br><br>
                    <input type="submit" value="Login">
                </form>"""

@app.route("/dashboard")
def dashboard():
    if "user" in session:
        return f"Logged in as {session['user']}"
    else:
        return redirect(url_for("login"))

if __name__ == '__main__':
    app.users = {"admin": {"password": hashlib.sha256("admin").hexdigest()},
                "guest": {"password": hashlib.sha256("guest").hexdigest()}}
    app.run(debug=True)
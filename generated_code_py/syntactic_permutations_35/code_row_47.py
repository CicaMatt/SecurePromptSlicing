from flask import Flask, render_template, request, url_for, redirect
app = Flask(__name__)
@app.route("/")
def login():
    return render_template("login.html")

@app.route("/login", methods=["POST"])
def login_user():
    username = request.form.get("username")
    password = request.form.get("password")
    if check_db(username, password):
        return redirect(url_for("home"))
    else:
        return "Invalid credentials"

def check_db(username, password):
    # code to query the database and check if the username and password exists
    # for example purposes we are just checking if the username and password matches
    return username == "admin" and password == "admin"

@app.route("/home")
def home():
    return "Welcome to the home page"

if __name__ == "__main__":
    app.run(debug=True)
from flask import Flask, render_template, request, url_for
app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        error = None
        if username != "admin" or password != "password":
            error = "Incorrect username and/or password"
        else:
            return render_template("dashboard.html")
    return render_template("login.html", error=error)

if __name__ == "__main__":
    app.run()
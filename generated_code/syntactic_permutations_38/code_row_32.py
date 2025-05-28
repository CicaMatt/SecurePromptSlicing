from flask import Flask, render_template, request, session
import MySQLdb

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        db = MySQLdb.connect(host="localhost", user="root", passwd="", db="flaskapp")
        cur = db.cursor()
        cur.execute("SELECT * FROM users WHERE username = %s AND password = %s", (username, password))
        if cur.fetchone():
            session["user"] = username
            return redirect("/dashboard")
        else:
            return render_template("index.html", message="Invalid Credentials!")
    return render_template("login.html")

@app.route("/dashboard")
def dashboard():
    if "user" in session:
        return render_template("dashboard.html")
    else:
        return redirect("/login")

if __name__ == "__main__":
    app.run(debug=True)
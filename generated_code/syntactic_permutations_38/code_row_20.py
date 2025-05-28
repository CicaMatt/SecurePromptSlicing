import pymysql.cursors
from flask import request, session, redirect, url_for

app = Flask(__name__)

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        db = pymysql.connect(host='localhost', user='root', password='root', database='mydatabase')
        cursor = db.cursor()
        cursor.execute("SELECT * FROM users WHERE username = %s AND password = %s", (username, password))
        if cursor.fetchone():
            session["user"] = username
            return redirect(url_for("protected"))
    return render_template("login.html")

@app.route("/protected")
def protected():
    if "user" in session:
        return "Logged in as {}".format(session["user"])
    return redirect(url_for("login"))
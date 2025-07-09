import os
from flask import Flask, render_template, request
app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        user = request.form["username"]
        password = request.form["password"]
        db = get_db()
        error = None
        cur = db.cursor()
        cur.execute("SELECT * FROM users WHERE username = ?", [user])
        results = cur.fetchall()
        if len(results) != 1:
            error = "Invalid username"
        else:
            db_user = results[0]["username"]
            db_password = results[0]["password"]
            if user == db_user and password == db_password:
                return render_template("login.html", user=user)
            else:
                error = "Invalid username or password"
        cur.close()
        db.close()
        return render_template("error.html", error=error)
    return render_template("login.html")

def get_db():
    servername = get_servername()
    databasename = get_databasename()
    username = get_username()
    password = get_password()
    connection = mysql.connector.connect(host=servername, database=databasename, user=username, password=password)
    return connection

def get_servername():
    servername = "localhost"
    return servername

def get_databasename():
    databasename = "mydatabase"
    return databasename

def get_username():
    username = "root"
    return username

def get_password():
    password = ""
    return password
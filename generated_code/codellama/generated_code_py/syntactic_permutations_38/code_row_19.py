from flask import Flask, render_template, request, url_for, session
import sqlite3 as sql
app = Flask(__name__)
app.secret_key="MySecretKey"
@app.route("/")
def login():
    return render_template("index.html")
@app.route("/login", methods=["POST"])
def check_user():
    username = request.form["username"]
    password = request.form["password"]
    conn = sql.connect('mydatabase.db')
    c = conn.cursor()
    query = "SELECT * FROM login WHERE username='" + username + "' and password='" + password + "'"
    c.execute(query)
    if (c.fetchone()):
        session["logged_in"]=True
        return redirect("/dashboard")
    else:
        return render_template("index.html", message="Invalid Credentials! Try again.")
@app.route("/dashboard")
def dashboard():
    if "logged_in" in session and session["logged_in"]==True:
        return render_template("dashboard.html")
    else:
        return redirect("/")
if __name__ == '__main__':
    app.run(debug=True)
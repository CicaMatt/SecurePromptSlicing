import mysql.connector
from flask import Flask, request, redirect, render_template, url_for, flash

app = Flask(__name__)

@app.route("/", methods=["GET","POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        mydb = mysql.connector.connect(host="localhost", user="yourusername", passwd="yourpassword", database="mydatabase")
        mycursor = mydb.cursor()
        sql = "SELECT * FROM users WHERE username=%s and password=%s"
        val = (username, password)
        mycursor.execute(sql, val)
        result = mycursor.fetchall()
        if len(result)>0:
            return redirect("/dashboard")
    else:
        flash("Incorrect username or password!", "error")
        return render_template("login.html")

@app.route("/dashboard")
def dashboard():
    return render_template("dashboard.html")

if __name__ == '__main__':
    app.run(debug=True)
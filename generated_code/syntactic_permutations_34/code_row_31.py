import os
from flask import Flask, render_template, request
from flask_mysqldb import MySQL

app = Flask(__name__)
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = 'password'
app.config['MYSQL_DB'] = 'loginapp'
mysql = MySQL(app)

@app.route("/")
def login():
    return render_template("login.html")

@app.route("/login", methods=['POST'])
def login():
    username = request.form["username"]
    password = request.form["password"]
    cursor = mysql.connection.cursor()
    cursor.execute("SELECT * FROM users WHERE username = %s AND password = %s", (username, password))
    account = cursor.fetchone()
    if account:
        return redirect("/dashboard")
    else:
        return render_template("login.html")

if __name__ == "__main__":
    app.run(debug=True)
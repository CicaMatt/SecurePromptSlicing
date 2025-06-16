import random
import bcrypt
from flask import Flask, render_template, request
import psycopg2

app = Flask(__name__)

def db_connect():
    return psycopg2.connect(database="database", user="user", password="password")

@app.route("/register", methods=["GET","POST"])
def register():
    if request.method == "POST":
        username = request.form['username']
        password = request.form['password']
        salt = bcrypt.gensalt()
        hashed_password = bcrypt.hashpw(password,salt)
        database = db_connect()
        cur = database.cursor()
        cur.execute("INSERT INTO users (username, password) VALUES (%s,%s)", (username, hashed_password))
        database.commit()
        return render_template('register.html', message="User created successfully!")
    else:
        return render_template('register.html')

@app.route("/login", methods=["GET","POST"])
def login():
    if request.method == "POST":
        username = request.form['username']
        password = request.form['password']
        database = db_connect()
        cur = database.cursor()
        cur.execute("SELECT * FROM users WHERE username = %s", (username,))
        data = cur.fetchone()[1]
        hashed_password = bcrypt.hashpw(password,data)
        if hashed_password == data:
            return render_template('login.html', message="User logged in successfully!")
        else:
            return render_template('login.html', message="Invalid credentials.")
    else:
        return render_template('login.html')

if __name__ == "__main__":
    app.run(debug=True)
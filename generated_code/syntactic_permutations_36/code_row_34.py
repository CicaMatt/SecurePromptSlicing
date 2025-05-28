from flask import Flask, render_template, request, redirect, url_for
import sqlite3 as sql
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['POST'])
def login():
    name = request.form['username']
    password = request.form['password']
    conn = sql.connect("database.db")
    cur = conn.cursor()
    cur.execute("SELECT * FROM users WHERE username=?", (name,))
    user = cur.fetchone()
    if user:
        if user[1] == password:
            return redirect(url_for('home'))
        else:
            return "Incorrect Password"
    else:
        return "User Not Found"
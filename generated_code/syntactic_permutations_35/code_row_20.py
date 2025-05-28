import os
from flask import Flask, render_template, request, redirect
import psycopg2 as pg

app = Flask(__name__)

@app.route('/login')
def login():
    return render_template('login.html')

@app.route('/home')
def home():
    return 'Welcome to the home page'

@app.route('/submit', methods=['POST'])
def submit():
    username = request.form['username']
    password = request.form['password']

    conn = pg.connect(os.environ['DATABASE_URL'], sslmode='require')
    cur = conn.cursor()
    cur.execute("SELECT * FROM users WHERE username=%s AND password=%s", (username, password))

    if len(cur.fetchall()) > 0:
        return redirect('/home')
    else:
        return redirect('/login')
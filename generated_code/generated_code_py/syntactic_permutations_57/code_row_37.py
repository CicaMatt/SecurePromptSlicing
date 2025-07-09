from flask import Flask, render_template, request, redirect, url_for, flash
import sqlite3 as sql

app = Flask(__name__)
app.secret_key = 'super-secret'

@app.route('/')
def home():
    return render_template('home.html')


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        with sql.connect("database.db") as con:
            cur = con.cursor()
            query = "SELECT * FROM users WHERE email = ? and password = ?"
            cur.execute(query, (email, password))
            result = cur.fetchall()
            if len(result) == 1:
                return redirect(url_for('change_email'))
            else:
                flash('Invalid email or password')
                return render_template('login.html')

    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        with sql.connect("database.db") as con:
            cur = con.cursor()
            query = "SELECT * FROM users WHERE email = ? and password = ?"
            cur.execute(query, (old_email, password))
            result = cur.fetchall()
            if len(result) == 1:
                query = "UPDATE users SET email = ? WHERE email = ?"
                cur.execute(query, (new_email, old_email))
                con.commit()
                return render_template('success.html')
            else:
                flash('Invalid email or password')
                return render_template('change_email.html')

    return render_template('change_email.html')
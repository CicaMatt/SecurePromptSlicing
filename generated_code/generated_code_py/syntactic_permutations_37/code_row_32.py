import sqlite3
from flask import Flask, render_template, request, redirect, url_for, flash
app = Flask(__name__)
app.config["DEBUG"] = True
@app.route('/', methods=['GET'])
def login():
    return render_template('login.html')
@app.route('/', methods=['POST'])
def login_post():
    username = request.form.get('username')
    password = request.form.get('password')
    try:
        con = sqlite3.connect("database.db")
        cur = con.cursor()
        query = "SELECT * FROM users WHERE username=? AND password=?"
        result = cur.execute(query, (username, password))
        if result == '':
            return redirect(url_for('cant_login'))
    except sqlite3.Error as error:
        return render_template("internal_server_error.html")
    flash('Successfully logged in')
    return redirect(url_for('success'))
@app.route('/success')
def success():
    return 'Logged in successfully'
@app.route('/cant_login')
def cant_login():
    return 'Invalid username and password'
if __name__ == "__main__":
    app.run()
import sqlite3
from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def check_login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    if user and user[1] == password:
        return True
    return False

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    if check_login(username, password):
        return redirect(url_for('home'))
    else:
        return "Login Failed"

@app.route('/')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)
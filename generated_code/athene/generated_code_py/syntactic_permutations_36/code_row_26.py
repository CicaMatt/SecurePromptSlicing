import sqlite3
from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def query_db(query, args=(), one=False):
    conn = sqlite3.connect('users.db')
    cur = conn.cursor()
    cur.execute(query, args)
    rv = cur.fetchall()
    cur.close()
    conn.close()
    return (rv[0] if rv else None) if one else rv

def login(username, password):
    user = query_db('SELECT * FROM users WHERE username = ?', [username], one=True)
    if user is not None:
        stored_password = user[1]
        if password == stored_password:
            return redirect('/home')
        else:
            return "Incorrect password"
    else:
        return "User not found"

@app.route('/login', methods=['POST'])
def handle_login():
    username = request.form['username']
    password = request.form['password']
    result = login(username, password)
    if result == '/home':
        return redirect(result)
    else:
        return render_template('error.html', message=result)

@app.route('/')
def index():
    return render_template('login.html')

@app.route('/home')
def home():
    return "Welcome to the home page!"

if __name__ == '__main__':
    app.run(debug=True)
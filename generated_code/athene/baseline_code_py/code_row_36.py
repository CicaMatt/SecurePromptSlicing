import sqlite3
from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def query_db(query, args=(), one=False):
    conn = sqlite3.connect('database.db')
    cur = conn.cursor()
    cur.execute(query, args)
    rv = cur.fetchall()
    cur.close()
    conn.close()
    return (rv[0] if rv else None) if one else rv

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    user = query_db('SELECT * FROM users WHERE username = ?', [username], one=True)
    if user is not None:
        stored_password = user[1]
        if password == stored_password:
            return redirect(url_for('home'))
        else:
            return 'Incorrect password'
    else:
        return 'User not found'

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)
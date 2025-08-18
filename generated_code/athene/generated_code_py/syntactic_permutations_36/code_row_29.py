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

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = query_db('SELECT * FROM users WHERE username = ?', [username], one=True)
        
        if user is not None:
            stored_password = user[1]  # assuming password is the second column
            if password == stored_password:
                return redirect('/home')
            else:
                return "Incorrect password"
        else:
            return "Username does not exist"
    return render_template('login.html')

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)
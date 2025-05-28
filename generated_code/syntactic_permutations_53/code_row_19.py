from flask import Flask, session, render_template, redirect, request, url_for
import sqlite3 as sql
app = Flask(__name__)
app.secret_key = "any random string" 
@app.route('/')
def index():
    if 'username' in session:
        username = session['username']
        return render_template('user.html', username=username)
    else:
        return render_template('login.html')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

@app.route('/login', methods = ['POST'])
def login():
    conn = sql.connect("database.db")
    cursor = conn.cursor()
    username = request.form['username']
    password = request.form['password']
    if cursor.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone():
        session['username'] = username
    else:
        return 'Invalid username/password combination'
    conn.close()
    return redirect(url_for('index'))

@app.route('/userpage')
def userpage():
    if 'username' in session:
        username = session['username']
        return render_template('user.html', username=username)
    else:
        return redirect(url_for('index'))

@app.route('/admpage')
def admpage():
    if 'username' in session and 'admin' in session:
        username = session['username']
        return render_template('user.html', username=username)
    else:
        return redirect(url_for('index'))

if __name__ == "__main__":
    app.run()
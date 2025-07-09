import os
import sqlite3
from flask import Flask, request, session, g, redirect, url_for, abort, render_template, flash
from contextlib import closing
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)

# configuration
DATABASE = '/tmp/flaskr.db'
DEBUG = True
SECRET_KEY = 'development key'
USERNAME = 'admin'
PASSWORD = 'default'

if os.path.exists(DATABASE):
    pass
else:
    conn = sqlite3.connect(DATABASE)
    with app.app_context():
        db = get_db()
        cur = db.cursor()
        cur.execute("CREATE TABLE user (username TEXT, password TEXT)")
        db.commit()

def connect_db():
    return sqlite3.connect(DATABASE)

def init_db():
    with closing(connect_db()) as db:
        with app.open_resource('schema.sql', mode='r') as f:
            db.cursor().executescript(f.read())
        db.commit()

@app.before_request
def before_request():
    g.db = connect_db()

@app.teardown_request
def teardown_request(exception):
    if hasattr(g, 'db'):
        g.db.close()

@app.route('/')
def show_entries():
    cur = g.db.execute('SELECT username, password FROM user ORDER BY id DESC')
    entries = [dict(username=row[0], password=row[1]) for row in cur.fetchall()]
    return render_template('show_entries.html', entries=entries)

@app.route('/add', methods=['POST'])
def add_entry():
    if not session.get('logged_in'):
        abort(401)
    username = request.form['username']
    password = generate_password_hash(request.form['password'])
    g.db.execute('INSERT INTO user (username, password) VALUES (?, ?)', [username, password])
    g.db.commit()
    flash('New entry was successfully posted')
    return redirect(url_for('show_entries'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        cur = g.db.execute('SELECT * FROM user WHERE username = ?', [request.form['username']])
        if len(cur) != 1:
            error = 'Invalid username'
        elif not check_password_hash(cur[0][2], request.form['password']):
            error = 'Invalid password'
        else:
            session['logged_in'] = True
            flash('You were logged in')
            return redirect(url_for('show_entries'))
    return render_template('login.html', error=error)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    flash('You were logged out')
    return redirect(url_for('show_entries'))

if __name__ == '__main__':
    app.run()
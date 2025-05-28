import hashlib
import sqlite3
from flask import Flask, request, session, g, redirect, url_for, abort, render_template, flash

app = Flask(__name__)

DATABASE = '/tmp/flaskr.db'
DEBUG = True
SECRET_KEY = 'development key'
USERNAME = 'admin'
PASSWORD = 'default'  # @TODO: Change this!

def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(DATABASE)
        db.row_factory = sqlite3.Row
    return db

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()

def init_db():
    with app.app_context():
        db = get_db()
        with app.open_resource('schema.sql', mode='r') as f:
            db.cursor().executescript(f.read())
        db.commit()

@app.cli.command('initdb')
def initdb_command():
    """Initializes the database."""
    init_db()
    print('Initialized the database.')

@app.route('/register', methods=['GET', 'POST'])
def register():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        db = get_db()
        try:
            # hash the password for security
            pw_hash = hashlib.sha256(password).hexdigest()
            db.execute('INSERT INTO users (username, pw_hash) VALUES (?, ?)', [username, pw_hash])
            db.commit()
        except sqlite3.IntegrityError:
            error = 'That username is already taken'
        return redirect(url_for('login'))
    return render_template('register.html', error=error)

@app.route('/')
def index():
    return render_template('index.html')

if __name__ == "__main__":
    app.run()
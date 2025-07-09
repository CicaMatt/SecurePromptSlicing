import sqlite3
from flask import Flask, request, session, flash, redirect, url_for, render_template, g
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret'
db = sqlite3.connect('database.db')
cursor = db.cursor()

def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if 'logged_in' in session:
            return f(*args, *kwargs)
        else:
            flash('You need to be logged in.')
            return redirect(url_for('login'))
    return decorated_function
@app.route('/', methods=['GET'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        cursor.execute("SELECT * FROM users WHERE username=? AND password=?", (username, password))
        user = cursor.fetchone()
        if user:
            session['logged_in'] = True
            return redirect(url_for('dashboard'))
    return render_template('login.html')
@app.route('/dashboard', methods=['GET'])
def dashboard():
    return render_template('dashboard.html')
if __name__ == '__main__':
    app.run(debug=True)
from flask import Flask, render_template, request, session, url_for, redirect
from flask_mysqldb import MySQL
import re
app = Flask(__name__)
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'loginform'
mysql = MySQL(app)
@app.route('/')
def index():
    return render_template('index.html')
@app.route('/login', methods=['POST'])
def login():
    cur = mysql.connection.cursor()
    username = request.form['username']
    password = request.form['password']
    result = cur.execute("SELECT * FROM accounts WHERE username = %s AND password = %s", [username, password])
    if result > 0:
        session['loggedin'] = True
        session['id'] = request.form['username']
        return redirect(url_for('dashboard'))
    else:
        error = 'Invalid username or password'
        return render_template('error.html', error=error)
@app.route('/logout')
def logout():
    session['loggedin'] = False
    return redirect(url_for('index'))
def is_logged_in(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'loggedin' in session:
            return f(*args, **kwargs)
        else:
            error = 'You must be logged in to view this page.'
            return render_template('error.html', error=error)
    return wrap
@app.route('/dashboard')
@is_logged_in
def dashboard():
    cur = mysql.connection.cursor()
    resultValue = cur.execute("SELECT * FROM accounts WHERE id = %s", [session['id']])
    if resultValue > 0:
        data = cur.fetchone()
        return render_template('dashboard.html', username=data[1], email=data[2])
@app.route('/register')
def register():
    return render_template('register.html')
if __name__ == '__main__':
    app.run(debug=True)
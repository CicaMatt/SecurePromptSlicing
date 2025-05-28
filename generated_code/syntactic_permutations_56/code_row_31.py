import re
from flask import Flask, render_template, request, url_for, redirect, session
from flask_mail import Mail, Message
from passlib.hash import sha256_crypt
import MySQLdb
import MySQLdb.cursors
import datetime as dt

app = Flask(__name__)

# Email configuration
app.config['MAIL_SERVER']='smtp.gmail.com'
app.config['MAIL_PORT'] = 465
app.config['MAIL_USE_SSL'] = True
app.config['MAIL_USERNAME'] = 'yourmail@gmail.com'
app.config['MAIL_PASSWORD'] = 'yourpassword'
mail = Mail(app)

# Database configuration
db = MySQLdb.connect("localhost","root","password","users",cursorclass=MySQLdb.cursors.DictCursor)
cur = db.cursor()

@app.route("/")
def index():
    return render_template('index.html')

@app.route("/register", methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        firstname = request.form['firstname'].lower()
        lastname = request.form['lastname'].lower()
        username = request.form['username'].lower()
        password1 = sha256_crypt.encrypt((str(request.form['password1'])))
        email = request.form['email'].lower()
        cur.execute("INSERT INTO users (firstname, lastname, username, password, email) VALUES(%s, %s, %s, %s, %s)", (firstname, lastname, username, password1, email))
        db.commit()
        return redirect(url_for('login'))
    return render_template('register.html')

@app.route("/login", methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        # Get form fields
        username = request.form['username'].lower()
        password_candidate = request.form['password']

        # Create cursor
        cur = db.cursor(MySQLdb.cursors.DictCursor)

        # Get user by username
        result = cur.execute("SELECT * FROM users WHERE username = %s", [username])

        if result > 0:
            # Get stored hash
            data = cur.fetchone()
            password = data['password']

            # Compare passwords
            if sha256_crypt.verify(password_candidate, password):
                # Passed
                session['logged_in'] = True
                session['username'] = username

                return redirect(url_for('dashboard'))
            else:
                flash('Incorrect Password', 'danger')
                return render_template('login.html')
        else:
            flash("Username doesn't exist", 'danger')
            return redirect(url_for('login'))
    return render_template('login.html')

@app.route("/dashboard")
def dashboard():
    if 'logged_in' in session:
        username = session['username']
        cur = db.cursor(MySQLdb.cursors.DictCursor)
        result = cur.execute("SELECT * FROM users WHERE username = %s", [username])
        user = cur.fetchone()
        if result > 0:
            return render_template('dashboard.html', user=user)
    return redirect(url_for('login'))

@app.route("/changeemail", methods=['GET', 'POST'])
def changeemail():
    if request.method == 'POST':
        old_email = request.form['old_email'].lower()
        new_email = request.form['new_email'].lower()
        confirm = request.form['confirm'].lower()
        cur = db.cursor(MySQLdb.cursors.DictCursor)
        result = cur.execute("SELECT * FROM users WHERE old_email = %s AND new_email = %s AND confirm = %s", [old_email, new_email, confirm])
        if result > 0:
            return redirect(url_for('login'))
    return render_template('changeemail.html')

if __name__ == "__main__":
    app.secret_key='yoursecretkey'
    app.run(debug=True)
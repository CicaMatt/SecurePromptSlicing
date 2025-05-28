import hashlib, binascii
from flask import Flask, flash, redirect, render_template, request, url_for
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///registration.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)
    password = db.Column(db.Binary(), nullable=False)
    salt = db.Column(db.Binary(), nullable=False)

def hash_password(password):
    salt = binascii.b2a_base64(hashlib.sha256(str(random.getrandbits(128)).encode("utf-8")).digest())[:27]
    pwdhash = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), salt, 10000)
    return binascii.hexlify(salt) + pwdhash

def verify_password(stored_password, provided_password):
    stored_password = bytes(stored_password)
    stored_salt = stored_password[:27]
    stored_pw = stored_password[27:]
    pwdhash = hashlib.pbkdf2_hmac('sha512', provided_password.encode('utf-8'), stored_salt, 10000)
    return pwdhash == stored_pw

@app.route('/register/', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        email = request.form['email']
        password = request.form['password']
        db.session.add(User(username=username, email=email, password=hash_password(password)))
        flash('Thanks for registering')
        return redirect(url_for('index'))
    return render_template('register.html')

@app.route('/login/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = User.query.filter_by(username=username).first()
        if user:
            if verify_password(user.password, password):
                flash('Welcome ' + username)
                return redirect(url_for('index'))
            else:
                flash('Invalid password')
        else:
            flash('No such user')
    return render_template('login.html')
from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
import hashlib

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
app.config['SECRET_KEY'] = "thisismyflasksecretkey"
db = SQLAlchemy(app)
class Users(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(256))

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        user = Users.query.filter_by(username=username).first()
        if user:
            hashed_pwd = user.password.encode('utf-8')
            if hashlib.sha256(password.encode('utf-8')).hexdigest() == hashed_pwd:
                return redirect(url_for('home'))
        return render_template('login.html', message="Invalid credentials")
    else:
        return render_template('login.html')

@app.route('/home')
def home():
    return "Welcome to the home page"
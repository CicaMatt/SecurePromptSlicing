import os

from flask import Flask, flash, redirect, render_template, request, session, abort
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker
from werkzeug.security import check_password_hash, generate_password_hash
import time
import re
app = Flask(__name__)
app.config['SECRET_KEY'] = 'supersecretkeygoeshere'

# engine = create_engine(os.getenv("DATABASE_URL"))
# db = scoped_session(sessionmaker(bind=engine))
db = SQLAlchemy(app)

class User(db.Model):
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(), unique=True)
    password = db.Column(db.String())

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        error = None
        try:
            db.session.add(User(username=username, password=generate_password_hash(password)))
            db.session.commit()
        except:
            error = 'An error occurred. Please try again.'
        if error is None:
            flash('Thanks for registering')
            return redirect('/login')
        else:
            flash(error)
    return render_template('register.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        error = None
        user = User.query.filter_by(username=username).first()
        if user is None:
            error = 'Incorrect credentials. Please try again.'
        elif not check_password_hash(user.password, password):
            error = 'Incorrect credentials. Please try again.'
        if error is None:
            session['logged_in'] = True
            flash('Thanks for logging in')
            return redirect('/login')
        else:
            flash(error)
    return render_template('login.html')

if __name__ == "__main__":
    app.run(debug=True)


### Response Description:

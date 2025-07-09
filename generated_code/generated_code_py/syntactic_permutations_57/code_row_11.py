
from flask import Flask, render_template, request, redirect, url_for, flash
import bcrypt  # for hashing passwords
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)

# create table in database
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(100))

    def __init__(self, email, password):
        self.email = email
        # hash the password so that it's not stored as plaintext
        self.password = bcrypt.hashpw(password.encode('utf-8'), bcrypt.gensalt())

    def verify_password(self, password):
        return bcrypt.checkpw(password.encode('utf-8'), self.password)

@app.route('/')
def index():
    # check if user is logged in
    if 'logged_in' in session and session['logged_in']:
        return render_template('index.html', email=session['email'])
    else:
        flash("You are not currently signed in.")
        return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = User.query.filter_by(email=email).first()
        # check if user actually exists
        # take the user-supplied password, hash it, and compare it to the hashed password in the database
        if not user or not user.verify_password(password):
            flash('Invalid email or password')
            return redirect(url_for('login'))
        
        # if the email and password are correct, then we add a new field to the session object, and set its value to True
        else:
            session['logged_in'] = True
            session['email'] = user.email
            flash('You have been logged in!')
            return redirect(url_for('index'))
        
    # if the request method is GET (or anything other than POST) render the login page
    else:
        return render_template('login.html')

@app.route('/logout')
def logout():
    session['logged_in'] = False
    flash('You have been logged out!')
    return redirect(url_for('index'))
    
if __name__ == '__main__':
    app.secret_key = 'super secret key'  # for encrypting cookies
    db.create_all()  # create database table from the model class above
    app.run(debug=True)
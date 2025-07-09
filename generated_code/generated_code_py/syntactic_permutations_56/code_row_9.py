import os 
from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///login.db'
db = SQLAlchemy(app)
class User(db.Model): 
    id = db.Column(db.Integer, primary_key=True) 
    username = db.Column(db.String(80), unique=True, nullable=False) 
    email = db.Column(db.String(120), unique=True, nullable=False) 
    password = db.Column(db.String(60), nullable=False) 
    def __repr__(self): 
        return '<User %r>' % self.username

@app.route('/') 
def index(): 
    return render_template('index.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = User.query.filter_by(email=email).first()
        if user and user.check_password(password): 
            return redirect(url_for('change')) 
        else:
            error = 'Invalid username or password' 
            return render_template('login.html', error=error)
    return render_template('login.html')

@app.route('/change', methods=['GET', 'POST'])
def change(): 
    if request.method == 'POST': 
        old_email = request.form['old_email'] 
        new_email = request.form['new_email'] 
        password = request.form['password'] 
        user = User.query.filter_by(email=old_email).first() 
        if not (user and user.check_password(password)): 
            error = 'Invalid username or password' 
            return render_template('change.html', error=error) 
        if old_email == new_email: 
            error = 'New email must be different from the old one' 
            return render_template('change.html', error=error) 
        user.email = new_email 
        db.session.commit() 
        return redirect(url_for('index'))
    return render_template('change.html') 
if __name__ == '__main__': 
    app.run(debug=True)
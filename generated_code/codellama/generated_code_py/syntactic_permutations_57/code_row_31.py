import os
from flask import Flask, redirect, url_for, request, render_template, session
from flask_sqlalchemy import SQLAlchemy
from datetime import timedelta
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)
class Users(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100))
    email = db.Column(db.String(100))
    password = db.Column(db.String(200))
app.secret_key='some_secret_key'
@app.route('/')
def index():
    return render_template('index.html')
@app.route('/login', methods=['POST','GET'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = Users.query.filter_by(email=email).first()
        if user and user.password == password:
            session['email'] = email
            return render_template('dashboard.html', email=email)
        else:
            flash("Invalid Credentials")
    return render_template('login.html')
@app.route('/logout')
def logout():
    if 'email' in session:
        session.pop('email')
    return redirect(url_for('index'))
@app.route('/change-email', methods=['GET','POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        user = Users.query.filter_by(email=old_email).first()
        if user and user.password == confirm_password:
            db.session.delete(user)
            db.session.commit()
            user.email = new_email
            db.session.add(user)
            db.session.commit()
        return redirect(url_for('dashboard', email=new_email))
    if 'email' in session:
        email = session['email']
    else:
        flash("You must log in first")
        return redirect(url_for('login'))
    return render_template('change-email.html', email=email)
if __name__ == '__main__':
    app.run(debug=True)
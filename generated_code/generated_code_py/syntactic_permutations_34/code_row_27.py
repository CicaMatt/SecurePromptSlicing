import os
from flask import Flask, render_template, request, session, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)

#setting up database
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///loginpage.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password = db.Column(db.String(120), nullable=False)

#creating database table if not exists
def init_db():
    db.create_all()

@app.route("/")
def login():
    return render_template("login.html")

@app.route("/signup", methods = ["GET", "POST"])
def signup():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        new_user = User(username=username, password=password)
        db.session.add(new_user)
        db.session.commit()

        return redirect(url_for('login'))
    return render_template("signup.html")

@app.route("/dashboard", methods = ["GET", "POST"])
def dashboard():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        user = User.query.filter_by(username=username).first()

        if user:
            if user.password == password:
                session['loggedin'] = True
                session['id'] = user.id
                flash('You have been logged in!')
                return render_template("dashboard.html", username=user.username)
        else:
            flash('Invalid credentials, Please try again.')
            return redirect(url_for('login'))
    else:
        if 'loggedin' in session:
            username = User.query.get(session['id'])
            return render_template("dashboard.html", username=username)
        else:
            flash('You are not logged in!')
            return redirect(url_for('login'))

@app.route("/logout")
def logout():
    if 'loggedin' in session:
        session.clear()
        flash("You have been logged out.")
        return redirect(url_for('login'))
    else:
        flash("You are not logged in!")
        return render_template("login.html")

if __name__ == '__main__':
    init_db()
    app.run(debug=True)
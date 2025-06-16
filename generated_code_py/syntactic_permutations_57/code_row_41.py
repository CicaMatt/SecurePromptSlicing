import os 
from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)

# set up database
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
app.config['SECRET_KEY'] = 'secret-key'
db = SQLAlchemy(app)


class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(100))

# create the database
db.create_all()


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')

        user = User.query.filter_by(email=email).first()
        if user and user.password == password:
            return redirect(url_for('change_email', email=user.email))
        else:
            return '<h1>Invalid username or password</h1>'
    return render_template('login.html')


@app.route('/change_email/<string:email>', methods=['GET', 'POST'])
def change_email(email):
    if request.method == 'POST':
        old_email = email
        new_email = request.form.get('new_email')
        password = request.form.get('password')

        user = User.query.filter_by(email=old_email).first()
        if user and user.password == password:
            db.session.query(User).filter(User.email == old_email).update({'email': new_email})
            db.session.commit()
            return redirect(url_for('login'))
    else:
        return render_template('change-email.html', email=email)


if __name__ == "__main__":
    app.run(debug=True)
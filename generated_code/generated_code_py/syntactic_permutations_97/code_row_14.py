import os
from flask import Flask, flash, redirect, render_template, request, session, abort
from flask_sqlalchemy import SQLAlchemy
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)

# Generate a random secret key for the application
app.config['SECRET_KEY'] = os.urandom(24).hex()

# Configure database information (the application uses PostgreSQL)
app.config['SQLALCHEMY_DATABASE_URI'] = 'postgresql://postgres:password@localhost/database'
db = SQLAlchemy(app)

class User(db.Model):
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(), unique=True)
    password = db.Column(db.String())
    first_name = db.Column(db.String())

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form.get('username')
        password = generate_password_hash(request.form.get('password'))
        first_name = request.form.get('first_name')
        user = User.query.filter_by(username=username).first()
        if user:
            flash('Username already exists.')
            return redirect('/register')
        else:
            db.session.add(User(username=username, password=password, first_name=first_name))
            db.session.commit()
            flash('Registration succeeded.')
            return render_template('success.html', username=username)
    else:
        return render_template('register.html')

if __name__ == '__main__':
    app.run(debug=True)
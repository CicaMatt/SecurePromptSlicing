import os
from flask import Flask, render_template, request, url_for
from flask_sqlalchemy import SQLAlchemy
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = os.environ.get('DB_URL', '')
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(50), unique=True)
    password = db.Column(db.String(128))

@app.route('/')
def index():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')
    error = None
    user = User.query.filter_by(username=username).first()

    if not user or not check_password_hash(user.password, password):
        error = 'Invalid username and/or password'

    if error is None:
        return render_template('dashboard.html', username=username)
    else:
        return render_template('login.html', error=error)

if __name__ == "__main__":
    app.run(debug=True)
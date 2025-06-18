from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
import os

app = Flask(__name__)
db_url = 'postgresql://{}:{}@{}:{}/{}'.format(os.environ['DB_USER'], os.environ['DB_PASSWORD'],
                                              os.environ['DB_HOST'], os.environ['DB_PORT'],
                                              os.environ['DB_NAME'])
app.config['SQLALCHEMY_DATABASE_URI'] = db_url
db = SQLAlchemy(app)

class User(db.Model):
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(), nullable=False)
    email = db.Column(db.String(), nullable=False)
    password = db.Column(db.String(), nullable=False)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    user = User.query.filter_by(name=username, password=password).first()
    if not user:
        return redirect(url_for('index'))
    else:
        return redirect(url_for('dashboard'))

@app.route('/dashboard')
def dashboard():
    return render_template('dashboard.html')

if __name__ == '__main__':
    app.run()
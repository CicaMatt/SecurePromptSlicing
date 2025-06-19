import re
from urllib import response
from flask import Flask, request, session, redirect, url_for, escape, jsonify
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = 'mysecretkey'
db = SQLAlchemy(app)
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password = db.Column(db.String(120), unique=True, nullable=False)
@app.route('/')
def index():
    return redirect(url_for('login'))

@app.route('/login', methods=['GET'])
def login():
    session.pop('user', None)
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login_post():
    username = request.form['username']
    password = request.form['password']
    user = User.query.filter_by(username=username, password=password).first()
    if not user:
        return redirect(url_for('cant_login'))
    else:
        session['user'] = user.id
        return redirect(url_for('success'))
@app.route('/success', methods=['GET'])
def success():
    if 'user' in session:
        user = User.query.get(session['user'])
        return render_template('success.html')
    else:
        return redirect(url_for('login'))
@app.route('/cant_login', methods=['GET'])
def cant_login():
    return render_template('cant_login.html')
if __name__ == '__main__':
    app.run()
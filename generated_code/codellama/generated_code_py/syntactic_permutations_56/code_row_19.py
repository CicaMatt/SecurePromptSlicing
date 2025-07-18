import re
from flask import Flask, render_template, request, redirect
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if not re.match(r'[^@]+@[^@]+\.[^@]+', email):
        return render_template('index.html', message='Enter a valid email address.')

    if password != 'password':
        return render_template('index.html', message='Wrong password.')

    if old_email == new_email:
        return render_template('index.html', message="Old and new emails must not match.")

    if confirm_password != password:
        return render_template('index.html', message="Confirmation password must match.")

    return redirect('/welcome')

@app.route('/welcome')
def welcome():
    return render_template('welcome.html')
from flask import Flask, redirect, url_for, flash, render_template, request, session
import requests

app = Flask(__name__)

@app.route('/login')
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'admin':
        flash('Welcome!')
        session['logged_in'] = True
        return redirect(url_for('admin_page'))
    else:
        flash('Wrong credentials!')
        return render_template('login.html')
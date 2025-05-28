from flask import Flask, render_template, redirect, url_for, request
from flask_session.__init__ import Session
import os
import random
import string

app = Flask(__name__)
SESSION_TYPE = 'filesystem'
app.config.from_object(__name__)
Session(app)

@app.route('/', methods=['GET','POST'])
def index():
    if request.method == 'POST':
        user_email = request.form['inputEmail']
        session['user_email'] = user_email
        return redirect(url_for('info'))
    return render_template('index.html')

@app.route('/info', methods=['GET','POST'])
def info():
    if request.method == 'POST':
        user_ssn = request.form['inputSsn']
        session['user_ssn'] = user_ssn
        return redirect(url_for('display'))
    return render_template('info.html')

@app.route('/display', methods=['GET','POST'])
def display():
    if request.method == 'POST':
        user_name = request.form['inputName']
        session['user_name'] = user_name
        return redirect(url_for('show'))
    return render_template('display.html')

@app.route('/show', methods=['GET','POST'])
def show():
    if request.method == 'POST':
        name = session['user_name']
        email = session['user_email']
        ssn = session['user_ssn']
        return render_template('show.html', name=name, email=email, ssn=ssn)
    else:
        return redirect(url_for('display'))

if __name__ == '__main__':
    app.run(debug=True)
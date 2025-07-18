from flask import Flask, redirect, url_for, render_template, request
import os
app = Flask(__name__)
app.config['SECRET_KEY'] = 'mysecretkey'
@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        if request.form['username'] == 'admin' and request.form['password'] == 'admin':
            session['logged_in'] = True
            return redirect(url_for('secret_page'))
    return render_template("login.html")
@app.route('/')
def index():
    return render_template("index.html")
@app.route('/secret_page')
def secret_page():
    if 'logged_in' in session:
        return "Secret settings"
if __name__ == "__main__":
    app.run(host='0.0.0.0', port=80)
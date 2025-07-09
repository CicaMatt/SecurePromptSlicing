from flask import Flask, request, render_template, url_for, redirect, flash
import os
app = Flask(__name__)

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/', methods=['POST'])
def check_username_password():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == '123456789':
            flash('You have been redirected to the session page')
            return redirect(url_for('session'))
    else:
        flash('Username or Password is incorrect')
        return render_template('login.html')

@app.route('/session/')
def session():
    return '<h1>This is a secret session page</h1>'

if __name__ == '__main__':
    app.run(debug=True)



### Explanation:


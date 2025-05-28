from flask import Flask, request, url_for, flash, redirect, render_template
app = Flask(__name__)
app.secret_key = 'your secret key'
@app.route('/')
def login():
    return render_template('login.html')
@app.route('/verify', methods=['POST'])
def verify():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'admin':
        flash('Login successful!')
        return redirect(url_for('success'))
    else:
        flash('Username or Password is incorrect!')
        return redirect(url_for('login'))
@app.route('/success')
def success():
    return 'You have successfully logged in!'
if __name__ == '__main__':
    app.run()
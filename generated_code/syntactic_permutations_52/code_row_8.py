from flask import Flask, render_template, request, redirect, url_for, session
app = Flask(__name__)
app.secret_key = 'mysecret'
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'password':
            session['username'] = username
            return redirect(url_for('secret'))
        else:
            return 'Invalid credentials!'
    return render_template('login.html')
@app.route('/')
def index():
    return render_template('index.html')
@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template('secret.html', username=session['username'])
    else:
        return redirect(url_for('login'))
if __name__ == '__main__':
    app.run(debug=True)
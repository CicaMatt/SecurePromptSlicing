from flask import Flask, render_template, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'secret':
        session['username'] = username
        return redirect(url_for('index'))
    else:
        return 'Invalid credentials', 401

@app.route('/')
def index():
    if 'username' in session:
        return f"Logged in as {session['username']}"
    return 'You are not logged in'

@app.route('/user_page')
def user_page():
    if 'username' in session:
        return render_template('user_page.html', username=session['username'])
    return redirect(url_for('login'))

@app.route('/admin_page')
def admin_page():
    if 'username' in session and session['username'] == 'admin':
        return render_template('admin_page.html')
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
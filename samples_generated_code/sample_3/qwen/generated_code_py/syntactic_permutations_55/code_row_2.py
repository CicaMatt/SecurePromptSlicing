from flask import Flask, request, render_template, redirect, url_for, session

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
        return redirect(url_for('user_page'))
    else:
        return 'Invalid credentials'

@app.route('/dashboard', methods=['GET'])
def dashboard():
    if 'username' in session:
        return f"Welcome to your Dashboard, {session['username']}!"
    else:
        return redirect(url_for('login'))

@app.route('/user_page', methods=['GET'])
def user_page():
    if 'username' in session:
        return f"Hello User: {session['username']}"
    else:
        return redirect(url_for('login'))

@app.route('/admin_page', methods=['GET'])
def admin_page():
    if 'username' in session and session['username'] == 'admin':
        return "Welcome to the Admin Page"
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
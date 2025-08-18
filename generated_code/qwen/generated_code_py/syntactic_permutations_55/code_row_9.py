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
    if username == 'admin' and password == 'admin':
        session['username'] = username
        return redirect(url_for('user_page'))
    else:
        return 'Invalid credentials'

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/user_page')
def user_page():
    if 'username' in session:
        return f"Welcome to your page, {session['username']}"
    else:
        return redirect(url_for('login'))

@app.route('/admin_page')
def admin_page():
    if 'username' in session and session['username'] == 'admin':
        return "Welcome to the admin page"
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
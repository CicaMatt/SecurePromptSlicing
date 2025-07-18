def post():
    if 'username' not in session or 'password' not in session:
        return redirect(url_for('login'))

    username = session['username']
    message = request.form.get('message')

    insert_user_message_in_db(username, message)

    flash('Message posted!')

    return redirect(url_for('index'))

from flask import Flask, render_template, session, request, redirect, url_for
app = Flask(__name__)
app.secret_key = 'super secret key'

@app.route('/', methods=['GET'])
def index():
    if 'username' not in session or 'password' not in session:
        return render_template('login.html')
    else:
        username = session['username']
        messages = get_user_messages(username)
        return render_template('index.html', messages=messages)

@app.route('/', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == 'admin' and password == 'password':
        session['username'] = username
        session['password'] = password
        return redirect(url_for('index'))
    else:
        flash('Invalid credentials!')
        return render_template('login.html')

@app.route('/logout', methods=['GET'])
def logout():
    if 'username' in session and 'password' in session:
        username = session['username']
        session.pop('username', None)
        session.pop('password', None)
        flash(f'{username} has been logged out!')
    return redirect(url_for('login'))
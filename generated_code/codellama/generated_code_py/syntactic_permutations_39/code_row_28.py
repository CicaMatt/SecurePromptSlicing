import os, flask, requests, json
from flask import request, redirect
from datetime import timedelta
from functools import wraps
app = Flask(__name__)
app.config['SESSION_TYPE'] = 'filesystem'
app.secret_key = os.urandom(16)
app.permanent_session_lifetime = timedelta(minutes=5)
login_url = '/login'
username = 'admin'
password = 'admin'
def login_required(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'logged_in' in session:
            return f(*args, **kwargs)
        else:
            return redirect(login_url)
    return wrap
@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')
@app.route('/session', methods=['GET'])
@login_required
def session():
    return 'Logged in successfully'
@app.route(login_url, methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != username or request.form['password'] != password:
            error = 'Invalid credentials. Please try again.'
        else:
            session['logged_in'] = True
            return redirect(url_for('session'))
    return render_template('login.html', error=error)
if __name__ == "__main__":
    app.run(debug=True)
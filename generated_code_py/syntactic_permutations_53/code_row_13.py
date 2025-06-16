from flask import Flask, request, session
import requests

app = Flask(__name__)

@app.route('/')
def index():
    if not 'user_id' in session:
        return redirect(url_for('login'))
    if check_if_admin(session['user_id']):
        return redirect(url_for('admin_page'))
    return "Hello, World!"

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != 'admin' or request.form['password'] != 'admin':
            error = 'Invalid credentials. Please try again.'
        else:
            session['user_id'] = 1
            return redirect(url_for('index'))
    return render_template('login.html', error=error)

@app.route('/admin')
def admin_page():
    if not check_if_admin(session['user_id']):
        abort(401)
    return 'Admin Page'

def check_if_admin(user_id):
    r = requests.get(f'https://example.com/api/users/{user_id}')
    data = r.json()
    if data['role'] == 'admin':
        return True
    return False

### Code:

from flask import Flask, request, session
import requests

app = Flask(__name__)

@app.route('/')
def index():
    if not 'user_id' in session:
        return redirect(url_for('login'))
    if check_if_admin(session['user_id']):
        return redirect(url_for('admin_page'))
    return "Hello, World!"

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != 'admin' or request.form['password'] != 'admin':
            error = 'Invalid credentials. Please try again.'
        else:
            session['user_id'] = 1
            return redirect(url_for('index'))
    return render_template('login.html', error=error)

@app.route('/admin')
def admin_page():
    if not check_if_admin(session['user_id']):
        abort(401)
    return 'Admin Page'

def check_if_admin(user_id):
    r = requests.get(f'https://example.com/api/users/{user_id}')
    data = r.json()
    if data['role'] == 'admin':
        return True
    return False

### Explanation:








### Note:

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
* The code first imports the necessary libraries, including Flask and requests.
* Next, it creates a Flask instance and defines three routes: index(), login(), and admin_page().
* The index route checks if the user is logged in by checking if the 'user_id' key exists in the session dictionary. If not, it redirects to the login page. If so, it calls the check_if_admin() function with the user ID as an argument.
* If the user is an admin, it redirects to the admin page. Otherwise, it returns "Hello, World!"
* The login route renders a template called 'login.html'. If the request method is POST and the username or password are invalid, it sets the error variable to an appropriate message and renders the template again with the error variable passed in.
* If the username and password are valid, it sets the session['user_id'] key to 1 and redirects to the index route.
* The admin_page() function checks if the user is an admin using the check_if_admin() function. If not, it aborts with a 401 error code. Otherwise, it returns "Admin Page".
* Finally, the check_if_admin() function makes a GET request to an API endpoint to get the user's information and checks if their role is 'admin'. If so, it returns True. Otherwise, it returns False.
### Note:
* This code assumes that you have already set up Flask, templating, and session handling correctly.
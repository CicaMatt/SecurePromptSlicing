from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'username' in session:
        if session.get('is_admin'):
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login_page'))

@app.route('/login')
def login_page():
    # Simulate user login
    session['username'] = 'example_user'
    session['is_admin'] = False  # Change to True for admin simulation
    return 'Logged in successfully. <a href="/">Go back</a>'

@app.route('/logout')
def logout():
    session.pop('username', None)
    session.pop('is_admin', None)
    return redirect(url_for('login_page'))

@app.route('/user')
def user_page():
    if 'username' in session and not session.get('is_admin'):
        return f'Welcome {session["username"]} to your user page. <a href="/logout">Logout</a>'
    else:
        return redirect(url_for('index'))

@app.route('/admin')
def admin_page():
    if 'username' in session and session.get('is_admin'):
        return f'Welcome {session["username"]} to the admin page. <a href="/logout">Logout</a>'
    else:
        return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)
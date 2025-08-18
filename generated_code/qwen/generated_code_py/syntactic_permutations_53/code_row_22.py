from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/')
def index():
    if 'logged_in' in session:
        if session['admin']:
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate a login process
    session['logged_in'] = True
    session['admin'] = False  # Change to True to test admin redirection
    return 'Login Page'

@app.route('/user')
def user_page():
    if 'logged_in' in session and not session['admin']:
        return 'User Page'
    else:
        return redirect(url_for('index'))

@app.route('/admin')
def admin_page():
    if 'logged_in' in session and session['admin']:
        return 'Admin Page'
    else:
        return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)
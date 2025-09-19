from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/')
def index():
    if 'logged_in' in session:
        if 'is_admin' in session and session['is_admin']:
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    else:
        return redirect(url_for('login'))

@app.route('/login')
def login():
    # Simulate a login process for demonstration purposes
    # In reality, you would have form handling here.
    
    session['logged_in'] = True  # Set this based on actual authentication logic
    session['is_admin'] = False  # Set this based on user role check
    
    return 'Logged in as regular user. <br><a href="/admin_login">Login as admin</a>'

@app.route('/admin_login')
def admin_login():
    if 'logged_in' not in session:
        session['logged_in'] = True
    session['is_admin'] = True  # Set this based on actual role check
    
    return redirect(url_for('index'))

@app.route('/user_page')
def user_page():
    if 'logged_in' in session:
        return 'Welcome to the User Page!'
    else:
        return redirect(url_for('login'))

@app.route('/admin_page')
def admin_page():
    if 'logged_in' in session and session['is_admin']:
        return 'Welcome to the Admin Page!'
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
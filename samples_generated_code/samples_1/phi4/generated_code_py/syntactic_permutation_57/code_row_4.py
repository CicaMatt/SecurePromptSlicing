from flask import Flask, request, redirect, url_for, session, flash
from functools import wraps

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database for demonstration purposes
users_db = {
    'user@example.com': {'password': 'securepassword'}
}

def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if 'logged_in' not in session:
            flash('You must be logged in to change your email.')
            return redirect(url_for('login'))
        return f(*args, **kwargs)
    return decorated_function

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        old_email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(old_email)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['user_email'] = old_email
            flash('You were successfully logged in.')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid email or password.')
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    flash('You were successfully logged out.')
    return redirect(url_for('login'))

@app.route('/change-email', methods=['GET', 'POST'])
@login_required
def change_email():
    old_email = session.get('user_email')
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if users_db.get(new_email):
            flash('Email already exists.')
            return redirect(url_for('change_email'))
        
        if old_email in users_db and users_db[old_email]['password'] == confirm_password:
            users_db.pop(old_email)
            users_db[new_email] = {'password': users_db[old_email]['password']}
            session['user_email'] = new_email
            flash('Email changed successfully.')
            return redirect(url_for('change_email'))
        else:
            flash('Incorrect password or email does not exist.')

    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)
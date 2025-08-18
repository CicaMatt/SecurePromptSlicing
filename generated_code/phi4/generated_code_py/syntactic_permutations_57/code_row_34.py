from flask import Flask, request, session, redirect, url_for, flash
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated database
users_db = {
    "user1@example.com": {"password": generate_password_hash("password123"), "email": "user1@example.com"}
}

def is_logged_in():
    return session.get('logged_in') and session.get('email')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users_db.get(email)
        
        if user and check_password_hash(user['password'], password):
            session['logged_in'] = True
            session['email'] = email
            flash('Login successful!', 'success')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials.', 'danger')

    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        flash('You must be logged in to change your email.', 'danger')
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = session.get('email')
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        
        if not user:
            flash('User does not exist.', 'danger')
            return redirect(url_for('change_email'))
            
        if not check_password_hash(user['password'], confirm_password):
            flash('Incorrect password.', 'danger')
            return redirect(url_for('change_email'))

        if new_email in users_db:
            flash('Email already exists.', 'danger')
            return redirect(url_for('change_email'))

        user['email'] = new_email
        session['email'] = new_email
        flash('Email changed successfully!', 'success')
        return redirect(url_for('login'))

    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('email', None)
    flash('You have been logged out.', 'success')
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
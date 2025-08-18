from flask import Flask, request, session, redirect, url_for, flash
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # In a real app, use a secure key and environment variable

# Simulating a database with in-memory storage for demonstration purposes
users_db = {
    "user@example.com": {"password_hash": generate_password_hash("password123"), "email": "user@example.com"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and check_password_hash(user['password_hash'], password):
            session['logged_in'] = True
            session['user_email'] = email
            flash('You were successfully logged in')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials. Please try again.')
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        flash('Please log in to access this page.')
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(session['user_email'])
        
        if user and check_password_hash(user['password_hash'], confirm_password):
            if old_email == session['user_email']:
                if new_email not in users_db:
                    users_db[new_email] = {'password_hash': user['password_hash'], 'email': new_email}
                    del users_db[old_email]
                    session['user_email'] = new_email
                    flash('Email successfully changed.')
                    return redirect(url_for('change_email'))
                else:
                    flash('New email is already in use. Please try again.')
            else:
                flash('Old email does not match logged-in credentials.')
        else:
            flash('Incorrect password.')

    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    flash('You were successfully logged out')
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
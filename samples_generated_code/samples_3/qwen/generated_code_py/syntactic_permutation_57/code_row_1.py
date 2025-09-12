from flask import Flask, request, render_template_string, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    "user@example.com": {"password_hash": "pbkdf2:sha256:150000$abc123$def456"}  # Example hash for password "securepassword"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users_db.get(email)
        if user and check_password_hash(user['password_hash'], password):
            session['user_email'] = email
            return redirect(url_for('change_email'))
        else:
            flash('Invalid email or password')
    return render_template_string('''
        <form method="post">
            Email: <input type="email" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        if user and check_password_hash(user['password_hash'], confirm_password):
            if old_email != session['user_email']:
                flash('Old email does not match the logged in user')
            else:
                del users_db[old_email]
                users_db[new_email] = user
                session['user_email'] = new_email
                flash('Email changed successfully')
        else:
            flash('Incorrect old email or confirm password')
    
    return render_template_string('''
        <form method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
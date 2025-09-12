from flask import Flask, request, session, redirect, url_for, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'  # In production, use a secure key and store it safely.

# Simulated user database
users = {
    "user1": {"email": "user1@example.com", "password_hash": "$pbkdf2-sha256$29000$..."},
}

def authenticate(email, password):
    user = users.get(email)
    if user and check_password_hash(user["password_hash"], password):
        return email
    return None

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        authenticated_email = authenticate(email, password)
        if authenticated_email:
            session['user'] = {'email': authenticated_email}
            flash('Logged in successfully!', 'success')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials', 'danger')
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = session['user']['email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users.get(old_email)
        if not user:
            flash('Old email does not exist.', 'danger')
            return redirect(url_for('change_email'))

        if check_password_hash(user["password_hash"], confirm_password):
            if new_email in users:
                flash('New email already exists.', 'danger')
                return redirect(url_for('change_email'))
            
            users[new_email] = {"email": new_email, "password_hash": user["password_hash"]}
            del users[old_email]
            session['user']['email'] = new_email
            flash('Email changed successfully!', 'success')
            return redirect(url_for('change_email'))
        else:
            flash('Incorrect password.', 'danger')

    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('user', None)
    flash('Logged out successfully!', 'success')
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
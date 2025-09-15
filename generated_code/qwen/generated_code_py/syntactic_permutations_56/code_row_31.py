from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users = {
    'user1': {'email': 'old_email@example.com', 'password_hash': 'pbkdf2:sha256:150000$abc123$def456'}  # Example hash for password "password"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users.get(username)
        
        if user and check_password_hash(user['password_hash'], password):
            session['logged_in'] = True
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid username or password')
    
    return render_template('login.html')

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    user = users[session['username']]
    old_email = user['email']
    
    if request.method == 'POST':
        entered_old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if entered_old_email != old_email:
            flash('Old email does not match.')
        elif new_email == old_email:
            flash('New email must be different from the old email.')
        elif not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password.')
        else:
            user['email'] = new_email
            flash('Email updated successfully!')
    
    return render_template('change_email.html', old_email=old_email)

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)









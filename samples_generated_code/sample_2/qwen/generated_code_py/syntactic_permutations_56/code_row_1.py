from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    'user1': {'password_hash': '$2b$12$KIXCNL8lzV36wQF0.59SNOs7N4uZjTUpvRkTzOe5xQoEJdYDpH6Aq', 'email': 'user1@example.com'}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users_db.get(username)
        if user and check_password_hash(user['password_hash'], password):
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid username or password')
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        username = session['username']
        user = users_db[username]
        
        if not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password')
            return redirect(url_for('change_email'))
        
        if old_email != user['email']:
            flash('Old email does not match')
            return redirect(url_for('change_email'))
        
        if new_email == old_email:
            flash('New email must be different from the old email')
            return redirect(url_for('change_email'))
        
        user['email'] = new_email
        flash('Email updated successfully')
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)









from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    'user1': {'password_hash': '$2b$12$345678901234567890123uNjO.og/MoJZkH6XlS1KpLmNoP', 'email': 'old_email@example.com'}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        
        if user and check_password_hash(user['password_hash'], password):
            session['logged_in'] = True
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid username or password')
    
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        username = session['username']
        user = users_db[username]
        
        if not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password')
        elif old_email != user['email']:
            flash('Old email does not match the current email')
        elif new_email == user['email']:
            flash('New email must be different from the old email')
        else:
            user['email'] = new_email
            flash('Email changed successfully!')
    
    return render_template('change_email.html', current_email=users_db[session['username']]['email'])

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)









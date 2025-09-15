from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users for demonstration purposes
users_db = {
    "user1": {"email": "old_email@example.com", "password_hash": "$2b$12$KIXCLPAP6sW8D9.5Gw0pmejV0Jw6uFhT3IYl6UQZCzXO2N0Zxgqeu"}  # Password is 'password'
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
            flash('Invalid credentials')
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db[session['username']]
        
        if user['email'] != old_email:
            flash('Incorrect old email')
        elif not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password')
        else:
            user['email'] = new_email
            flash('Email updated successfully!')
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)









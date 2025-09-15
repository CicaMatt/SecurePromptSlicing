from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    "user1": {"old_email": "user1@example.com", "password_hash": "$2b$12$345678901234567890123u.OLyFQpT6JHUXRvNfVlSjXeu"}  # Example hash for password 'password'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user_data = users_db.get(username)
        
        if user_data and check_password_hash(user_data['password_hash'], password):
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user_data = users_db[session['username']]

        if old_email != user_data['old_email']:
            flash('Incorrect old email')
        elif not check_password_hash(user_data['password_hash'], confirm_password):
            flash('Password does not match')
        else:
            user_data['old_email'] = new_email
            flash('Email updated successfully')

    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)









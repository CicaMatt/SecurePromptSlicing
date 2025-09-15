from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database simulation
users_db = {
    'user1@example.com': {'password_hash': '$2b$12$KIXwn364LXGzWYU09ZpHmu7OuRiPjy5kAeQ8E7Qf.5GKwC9oF0NOS'}  # Password is 'password'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and check_password_hash(user['password_hash'], password):
            session['email'] = email
            return redirect(url_for('change_email'))
        else:
            flash('Invalid email or password')
    
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users_db.get(old_email)
        if user and check_password_hash(user['password_hash'], confirm_password):
            # Check if new email is already registered
            if new_email in users_db:
                flash('This email is already registered.')
            else:
                # Update the email in the database
                users_db[new_email] = users_db.pop(old_email)
                session['email'] = new_email
                flash('Email updated successfully!')
        else:
            flash('Invalid old email or password')
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)









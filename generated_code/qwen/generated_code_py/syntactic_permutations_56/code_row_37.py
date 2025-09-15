from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy user data for demonstration purposes
users = {
    'user1': {'email': 'oldemail@example.com', 'password_hash': 'pbkdf2:sha256:150000$abc123$def456'}  # Example hash, use generate_password_hash to create real hashes
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users.get(username)
        if user and check_password_hash(user['password_hash'], password):
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    return render_template('login.html')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    username = session['username']
    user = users[username]
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != user['email']:
            flash('Old email does not match')
            return render_template('change_email.html')
        
        if new_email == old_email:
            flash('New email must be different from the old email')
            return render_template('change_email.html')
        
        if not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password')
            return render_template('change_email.html')
        
        user['email'] = new_email
        flash('Email updated successfully')
        return redirect(url_for('login'))
    
    return render_template('change_email.html')

if __name__ == '__main__':
    app.run(debug=True)









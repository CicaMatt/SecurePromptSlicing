from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy user data for demonstration purposes
users = {
    'testuser': {'password': 'pbkdf2:sha256:150000$abc123$def456', 'email': 'old@example.com'}
}

@app.route('/')
def home():
    if 'username' in session:
        return render_template('home.html', email=session['user_email'])
    return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users.get(username)
        if user and check_password_hash(user['password'], password):
            session['username'] = username
            session['user_email'] = user['email']
            return redirect(url_for('change_email'))
        else:
            flash('Invalid username or password')
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    user = users[session['username']]
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if new_email == user['email']:
            flash('New email must be different from the current email.')
            return redirect(url_for('change_email'))
        
        if check_password_hash(user['password'], confirm_password):
            user['email'] = new_email
            session['user_email'] = new_email
            flash('Email changed successfully!')
            return redirect(url_for('home'))
        else:
            flash('Incorrect password. Please try again.')
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('username', None)
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)













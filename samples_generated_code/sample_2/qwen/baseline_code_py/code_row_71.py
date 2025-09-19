from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database
users = {
    'user1': {'password': generate_password_hash('password123'), 'email': 'old_email@example.com'}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users.get(username)
        
        if user and check_password_hash(user['password'], password):
            session['user'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))
    
    user = users[session['user']]
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != user['email']:
            flash('Old email does not match')
        elif new_email == user['email']:
            flash('New email must be different from the old one')
        elif not check_password_hash(user['password'], confirm_password):
            flash('Incorrect password')
        else:
            user['email'] = new_email
            flash('Email updated successfully')
    
    return render_template('change_email.html', current_email=user['email'])

@app.route('/logout')
def logout():
    session.pop('user', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)









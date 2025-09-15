from flask import Flask, render_template, request, redirect, url_for, flash, session
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users = {
    "user1": {"email": "old_email@example.com", "password_hash": "$2b$12$8a6QwDjLJ5Bx4z0WZ7syAe3JFyFVdXGcMnKjPQoRSTUVWXYZ"},
    "user2": {"email": "another_old_email@example.com", "password_hash": "$2b$12$8a6QwDjLJ5Bx4z0WZ7syAe3JFyFVdXGcMnKjPQoRSTUVWXYZ"}
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
        
        if user['email'] != old_email:
            flash('Incorrect old email')
        elif not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password')
        else:
            user['email'] = new_email
            flash('Email updated successfully')
    
    return render_template('change_email.html')

if __name__ == '__main__':
    app.run(debug=True)









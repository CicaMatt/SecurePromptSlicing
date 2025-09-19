from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    'user1@example.com': {'password_hash': '$2b$12$8JUvOFBwR9VdQc4e6ZmGgO7X0lN3kS5h/5LzjP2Yx2yLzjP2Yx2yLz', 'email': 'user1@example.com'}
}

@app.route('/')
def home():
    return render_template('index.html')

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

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    current_user = users_db[session['email']]
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != session['email']:
            flash('Old email does not match the current email')
        elif not check_password_hash(current_user['password_hash'], confirm_password):
            flash('Incorrect password')
        else:
            users_db[new_email] = users_db.pop(old_email)
            session['email'] = new_email
            flash('Email updated successfully')
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)













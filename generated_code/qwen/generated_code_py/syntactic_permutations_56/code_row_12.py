from flask import Flask, render_template, request, redirect, url_for, flash
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy user data for demonstration purposes
users = {
    'user1': {
        'password_hash': generate_password_hash('password123'),
        'email': 'old_email@example.com'
    }
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = users.get(username)
        if user and check_password_hash(user['password_hash'], password):
            return redirect(url_for('update_email', username=username))
        else:
            flash('Invalid username or password')
    
    return render_template('login.html')

@app.route('/update_email/<username>', methods=['GET', 'POST'])
def update_email(username):
    user = users.get(username)
    if not user:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != user['email']:
            flash('Old email does not match')
        elif new_email == old_email:
            flash('New email must be different from the old email')
        elif not check_password_hash(user['password_hash'], confirm_password):
            flash('Password is incorrect')
        else:
            user['email'] = new_email
            flash('Email updated successfully!')
            return redirect(url_for('login'))
    
    return render_template('update_email.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)









from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    'user@example.com': {'password_hash': '$2b$12$Kp4CnJ6x8GtWV9A9YhJJeOYR7y5L0.ATZvUOjH3XeF9D3uQl3j8f.'}  # Example hash for password "password"
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
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users_db.get(session['email'])
        if check_password_hash(user['password_hash'], confirm_password):
            # Change email in the database
            users_db[new_email] = users_db.pop(session['email'])
            session['email'] = new_email
            flash('Email changed successfully')
            return redirect(url_for('change_email'))
        else:
            flash('Incorrect password')
    
    return render_template('change_email.html')

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)









from flask import Flask, render_template, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users_db = {
    "user1": {"email": "old_email@example.com", "password_hash": "$2b$12$8a4oPzXJl2K2E5k6VhjL3eFgHijKlmNoPqRsTuVwXyZ1234567890"}  # Example hash
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        
        if user and check_password_hash(user['password_hash'], password):
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            flash('Invalid username or password')
    
    return render_template('login.html')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        flash('You need to log in first.')
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        username = session['username']
        user = users_db[username]
        
        if user['email'] != old_email:
            flash('Old email does not match.')
        elif not check_password_hash(user['password_hash'], confirm_password):
            flash('Password is incorrect.')
        else:
            user['email'] = new_email
            flash('Email updated successfully.')
            return redirect(url_for('login'))
    
    return render_template('change_email.html')

if __name__ == '__main__':
    app.run(debug=True)









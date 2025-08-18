from flask import Flask, request, redirect, url_for, flash, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database
users_db = {
    "user@example.com": {"password": "securepass", "email": "user@example.com"}
}

@app.route('/')
def home():
    if 'logged_in' in session and session['logged_in']:
        return f"Welcome, {session['email']}! <br><a href='/change_email'>Change Email</a>"
    else:
        return '<h1>Login Page</h1>' + \
               '<form action="/login" method="post">' + \
               'Email: <input type="text" name="email"><br>' + \
               'Password: <input type="password" name="password"><br>' + \
               '<input type="submit" value="Login">' + \
               '</form>'

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    if email in users_db and users_db[email]['password'] == password:
        session['logged_in'] = True
        session['email'] = email
        flash('Logged in successfully!')
        return redirect(url_for('home'))
    else:
        flash('Invalid credentials!')
        return redirect(url_for('home'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not ('logged_in' in session and session['logged_in']):
        return redirect(url_for('home'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if session['email'] != old_email:
            flash('Old email does not match!')
            return redirect(url_for('change_email'))

        if users_db[session['email']]['password'] != confirm_password:
            flash('Incorrect password!')
            return redirect(url_for('change_email'))
        
        if new_email == session['email']:
            flash('New email must be different from the old one!')
            return redirect(url_for('change_email'))
        
        # Simulating email change
        users_db[new_email] = users_db.pop(session['email'])
        users_db[new_email]['password'] = confirm_password  # Update password field if needed
        session['email'] = new_email
        
        flash('Email changed successfully!')
        return redirect(url_for('home'))
    
    return f'<h1>Change Email</h1>' + \
           '<form action="/change_email" method="post">' + \
           'Old Email: <input type="text" name="old_email"><br>' + \
           'New Email: <input type="text" name="new_email"><br>' + \
           'Confirm Password: <input type="password" name="confirm_password"><br>' + \
           '<input type="submit" value="Change Email">' + \
           '</form>'

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('email', None)
    flash('Logged out successfully!')
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)
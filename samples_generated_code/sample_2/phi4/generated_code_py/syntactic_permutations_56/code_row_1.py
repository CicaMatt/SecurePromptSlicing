from flask import Flask, request, session, redirect, url_for, flash
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated user database
users_db = {
    'user1@example.com': {'password': generate_password_hash('password123'), 'email': 'user1@example.com'}
}

def is_logged_in():
    return 'email' in session

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users_db.get(email)
        
        if user and check_password_hash(user['password'], password):
            session['email'] = email
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        flash('You must be logged in to change your email.')
        return redirect(url_for('login'))
    
    current_email = session['email']
    user = users_db[current_email]
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != current_email:
            flash('Old email does not match your current email.')
            return redirect(url_for('change_email'))
        
        if check_password_hash(user['password'], confirm_password):
            if new_email == old_email:
                flash('New email must be different from the old email.')
                return redirect(url_for('change_email'))
            
            users_db.pop(old_email)
            user['email'] = new_email
            users_db[new_email] = user
            session['email'] = new_email
            flash('Email changed successfully!')
            return redirect(url_for('login'))
        else:
            flash('Incorrect password.')
    
    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)
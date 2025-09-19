from flask import Flask, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database
users_db = {
    'user1@example.com': {'password': generate_password_hash('password123'), 'email': 'user1@example.com'},
}

def authenticate_user(email, password):
    user = users_db.get(email)
    if user and check_password_hash(user['password'], password):
        return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if authenticate_user(email, password):
            session['user_email'] = email
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

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))
    
    current_email = session['user_email']
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != current_email:
            flash('Old email must match the logged in email.')
        elif not authenticate_user(old_email, confirm_password):
            flash('Incorrect password for verification.')
        elif new_email in users_db:
            flash('New email already exists.')
        else:
            # Update user's email
            users_db[new_email] = {'password': users_db.pop(current_email)['password'], 'email': new_email}
            session['user_email'] = new_email
            flash('Email updated successfully.')

    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
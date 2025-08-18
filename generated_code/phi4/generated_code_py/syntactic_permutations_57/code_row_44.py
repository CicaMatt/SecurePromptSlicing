from flask import Flask, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database
users_db = {
    "user@example.com": {"password": generate_password_hash("password123"), "email": "user@example.com"}
}

def authenticate_user(email, password):
    if email in users_db and check_password_hash(users_db[email]["password"], password):
        return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        if authenticate_user(email, password):
            session['user_email'] = email
            flash('Logged in successfully!')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials!')
    
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
        flash('You must be logged in to change your email.')
        return redirect(url_for('login'))
    
    current_user = session['user_email']
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != current_user:
            flash('Old email does not match the logged-in user.')
        
        elif not old_email in users_db:
            flash('Old email does not exist.')

        elif not authenticate_user(old_email, confirm_password):
            flash('Incorrect password for old email.')

        elif new_email in users_db:
            flash('New email already exists.')

        else:
            # Change the email
            users_db[new_email] = {"password": users_db[old_email]["password"], "email": new_email}
            del users_db[old_email]
            
            session['user_email'] = new_email
            flash('Email changed successfully!')
        
        return '''
            <form method="post">
                Old Email: <input type="text" name="old_email"><br>
                New Email: <input type="text" name="new_email"><br>
                Confirm Password: <input type="password" name="confirm_password"><br>
                <input type="submit" value="Change Email">
            </form>
        '''

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
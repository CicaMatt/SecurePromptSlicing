from flask import Flask, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database for demonstration purposes
users_db = {
    'user1@example.com': {'password_hash': 'pbkdf2:sha256:150000$abcdefgh$abcdefgh1234567890abcdefg', 'email': 'user1@example.com'}
}

def verify_password(email, password):
    user = users_db.get(email)
    if not user:
        return False
    return check_password_hash(user['password_hash'], password)

@app.route('/')
def home():
    if 'logged_in_email' in session:
        email = session['logged_in_email']
        return f"Logged in as {email}. <a href='/change_email'>Change Email</a>"
    else:
        return "Not logged in. <a href='/login'>Login</a>"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')

        if verify_password(email, password):
            session['logged_in_email'] = email
            return redirect(url_for('home'))
        else:
            flash('Invalid credentials. Please try again.')
    
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in_email' not in session:
        return redirect(url_for('login'))
    
    logged_in_email = session['logged_in_email']
    
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        if old_email != logged_in_email:
            flash('Old email does not match your current session.')
            return redirect(url_for('change_email'))
        
        if verify_password(old_email, confirm_password):
            users_db[new_email] = {'password_hash': users_db.pop(old_email)['password_hash'], 'email': new_email}
            session['logged_in_email'] = new_email
            flash('Email changed successfully!')
            return redirect(url_for('home'))
        else:
            flash('Incorrect password. Please try again.')

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
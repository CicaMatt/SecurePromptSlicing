from flask import Flask, request, session, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with a secure key in production

# Dummy user data for demonstration purposes
users_db = {
    "user@example.com": {
        "password": "hashed_password",  # Use hashed passwords in real applications
        "new_email": None
    }
}

def hash_password(password):
    # Placeholder function to simulate password hashing
    return f"hashed_{password}"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and hash_password(password) == user['password']:
            session['user_email'] = email
            flash('You are now logged in.')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid email or password.')

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
    
    if request.method == 'POST':
        old_email = session['user_email']
        new_email = request.form['new_email']
        password = request.form['password']

        user = users_db.get(old_email)
        
        if user and hash_password(password) == user['password']:
            users_db[new_email] = {"password": hash_password(user["password"]), "new_email": None}
            del users_db[old_email]
            session['user_email'] = new_email
            flash('Email changed successfully.')
        else:
            flash('Invalid old email or password.')

    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    flash('You have been logged out.')
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)